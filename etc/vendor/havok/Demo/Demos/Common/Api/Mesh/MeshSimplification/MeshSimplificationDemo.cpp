/* 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Demos/Common/Api/Mesh/MeshSimplification/MeshSimplificationDemo.h>
#include <Common/Internal/MeshSimplifier/hkMeshSimplifier.h>

#include <Common/Serialize/Packfile/hkPackfileData.h>
#include <Common/Serialize/Util/hkSerializeUtil.h>
#include <Common/SceneData/Scene/hkxScene.h>
#include <Common/SceneData/Mesh/hkxMesh.h>

#include <Common/Serialize/Util/hkLoader.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Algorithm/Sort/hkSort.h>
#include <Common/Base/Container/LocalArray/hkLocalArray.h>
#include <Common/SceneData/Scene/hkxSceneUtils.h>
#include <Common/SceneData/Mesh/hkxMeshSection.h>
#include <Common/SceneData/Mesh/hkxVertexDescription.h>
#include <Common/SceneData/Mesh/hkxVertexBuffer.h>
#include <Common/SceneData/Mesh/hkxIndexBuffer.h>
#include <Common/SceneData/Mesh/hkxMeshSection.h>
#include <Common/Visualize/hkDebugDisplay.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>

#include <Demos/DemoCommon/Utilities/Asset/hkAssetManagementUtil.h>

enum DemoMesh
{
	MESH_SPHERE,
	MESH_GDC05, 
	MESH_SQUARE,
};

struct MeshSimplificationVariant
{
	const char*         m_name;
	DemoMesh			m_meshType;
	const char*         m_filename;
	const char*         m_details;
	int					m_upIndex;
	hkBool				m_backfaceCulling;
	hkReal				m_fractionToRemove;
};


static const char* helpString = "Mesh simplification example. A mesh is loaded and a fixed fraction of the faces are removed.";
static const char* helpString2 = "Mesh simplificatin example. A mesh is procedurally created, and the boundary vertices are constrained";

static MeshSimplificationVariant g_meshSimplificationVariants[] = 
{
	{ "Sphere, 50% simplification", MESH_SPHERE, "Resources/Common/Api/MeshSimplification/sphere.xml", helpString, 1, false, .5f},

#if defined(USING_HAVOK_PHYSICS) && defined (USING_HAVOK_ANIMATION)
	{ "GDC05 Level, 25% simplification" , MESH_GDC05, "Resources/Animation/ShowCase/Gdc2005/Level/hkGdcLevel_Lightmap.hkx", helpString,  1, false, .25f},
	{ "GDC05 Level, 50% simplification" , MESH_GDC05, "Resources/Animation/ShowCase/Gdc2005/Level/hkGdcLevel_Lightmap.hkx", helpString,  1, false, .50f},
#endif

	{ "Tesselated square, 75% simplification", MESH_SQUARE, HK_NULL, helpString2, 1, false, .90f	}

};


static void collectSimplifiedMesh(const hkQemMeshSimplifier& simplifier, hkGeometry& geomOut)
{
	geomOut.m_vertices.clear();
	geomOut.m_triangles.clear();

	const hkArray<hkQemMutableMesh::Vertex>& verts = simplifier.m_mesh->getVertices();
	const hkArray<hkQemMutableMesh::Face>& faces = simplifier.m_mesh->getFaces();

	geomOut.m_vertices.setSize(verts.getSize());
	for (int i=0; i<verts.getSize(); i++)
	{
		geomOut.m_vertices[i] = verts[i].m_position;
	}

	for (int i=0; i<faces.getSize(); i++)
	{
		const hkQemMutableMesh::Face& face = faces[i];
		if (face.m_isValid)
		{
			hkGeometry::Triangle& tri = geomOut.m_triangles.expandOne();

			tri.m_a = face.m_vertexIndices[0];
			tri.m_b = face.m_vertexIndices[1];
			tri.m_c = face.m_vertexIndices[2];
		}
	}
}

MeshSimplificationDemo::~MeshSimplificationDemo()
{
	if (m_loader)
	{
		m_loader->removeReference();
	}

	setGraphicsState(HKG_ENABLED_CULLFACE, true);
}

MeshSimplificationDemo::MeshSimplificationDemo( hkDemoEnvironment* env )
:	hkDefaultDemo( env ), 
	m_loader(HK_NULL),
	m_displayMeshIndex(1),
	m_numDisplayMeshes(2),
	m_runQem(true),
	m_alwaysRunQem(false)
{

	MeshSimplificationVariant& variant = g_meshSimplificationVariants[m_variantId];

	{
		m_up.setZero4();
		m_up(variant.m_upIndex) = 1.0f;
	}

	setGraphicsState(HKG_ENABLED_CULLFACE, variant.m_backfaceCulling);

	m_worldTransform.setIdentity();

	
	//
	// Load the specified mesh and collection the mesh sections
	//
	hkAabb meshAabb;
	meshAabb.setEmpty();

	if (variant.m_meshType != MESH_SQUARE)
	{
		hkxScene* scenePtr;
		m_loader = new hkLoader();

		hkString assetFile = hkAssetManagementUtil::getFilePath(variant.m_filename);
		hkRootLevelContainer* container = m_loader->load( assetFile.cString() );
		HK_ASSERT2(0x27343437, container != HK_NULL , "Could not load asset");

		scenePtr = reinterpret_cast<hkxScene*>( container->findObjectByType( hkxSceneClass.getName() ));
	

		if (scenePtr == HK_NULL || (scenePtr->m_rootNode == HK_NULL) )
		{
			HK_ASSERT(0xa54323c0, "No scene data (or scene data root hkxNode) found. Can't continue.");
			return;
		}

		{
			hkArray<hkxNode*> nodes;
			hkxSceneUtils::findAllMeshNodes(scenePtr, scenePtr->m_rootNode, nodes);

			scenePtr->getWorldFromNodeTransform(nodes[0], m_worldTransform);
		}

		// Grab all the sections from the file
 		{
			for( int nMesh = 0; nMesh < scenePtr->m_numMeshes; nMesh++ )
			{
				hkxMesh* originalMesh = scenePtr->m_meshes[nMesh];

				for( int nSection = 0; nSection < originalMesh->m_numSections; nSection++ )
				{
					hkxMeshSection* section = originalMesh->m_sections[nSection];
					m_sections.pushBack(section);

					hkArray<hkVector4> verticesTemp;
					section->collectVertexPositions(verticesTemp);
					for (int v=0; v<verticesTemp.getSize(); v++)
					{
						hkVector4 tempV;
						m_worldTransform.multiplyVector(verticesTemp[v], tempV);
						meshAabb.includePoint(tempV);
					}
				}
			}
 		}
	}
	else
	{
		hkVector4 p(64, 20, 64);
		meshAabb.includePoint(p);
		p.setNeg3( p );
		meshAabb.includePoint(p);

		m_worldTransform.setIdentity();
	}

	
	{
		setupDefaultCameras( env, meshAabb.m_max, meshAabb.m_min, m_up, .1f, 10000.0f );
		setupGraphics();
	}
}


void MeshSimplificationDemo::drawGeometry( const hkGeometry& geom, int triColor) const
{
	const hkVector4 up = m_up;

	for (int tri=0; tri<geom.m_triangles.getSize(); tri++)
	{
		const hkGeometry::Triangle& triangle = geom.m_triangles[tri];
		const hkVector4 vertA = geom.m_vertices[triangle.m_a];
		const hkVector4 vertB = geom.m_vertices[triangle.m_b];
		const hkVector4 vertC = geom.m_vertices[triangle.m_c];

		hkVector4 ba; ba.setSub4(vertB, vertA);
		hkVector4 ca; ca.setSub4(vertC, vertA);
		hkVector4 cross; cross.setCross(ba, ca);
		cross.normalize3();
		hkReal dot = hkMath::fabs( cross.dot3(up) );
		dot *= dot;
		hkReal mult = .75f*dot + .25f;

		HK_DISPLAY_LINE(vertA, vertB, hkColor::BLACK);
		HK_DISPLAY_LINE(vertB, vertC, hkColor::BLACK);
		HK_DISPLAY_LINE(vertC, vertA, hkColor::BLACK);

		int color = hkColor::rgbFromFloats( mult*.5f, mult*.5f, mult*.85f, 1.0f );
		color;
		HK_DISPLAY_TRIANGLE(vertA, vertB, vertC, color);
		
		// Draw normal
		if(0)
		{
			hkVector4 centroid; 
			centroid.setAdd4(vertA, vertB);
			centroid.add4(vertC);
			centroid.mul4(.333333f);

			cross.mul4(.25f);
			HK_DISPLAY_ARROW(centroid, cross, hkColor::BLACK);
		}
	}
}

void MeshSimplificationDemo::doMeshSimplify()
{
	MeshSimplificationVariant& variant = g_meshSimplificationVariants[m_variantId];
	hkQemMutableMesh mutMesh;
	{
		HK_TIME_CODE_BLOCK("QEM", HK_NULL);

		if (variant.m_meshType == MESH_SQUARE)
		{
			setupSquareMutatableMesh(mutMesh);
		}
		else
		{
			setupMutatableMesh(mutMesh);
		}
		
		mutMesh.validate();

		//
		// Now set up and run the simplifier
		//
		hkQemMeshSimplifier simplifier;
		if (variant.m_meshType == MESH_SQUARE)
		{
			// Decrease the boundary penalty in this variant, so that we can make sure that the hard constraints work correctly.
			simplifier.m_params.m_boundaryPenalty = 1.0f;
		}
		simplifier.m_params.m_allowTriangleFlips = false;
		
		simplifier.m_mesh = &mutMesh;
		// Grab the unsimplified mesh for comparison purposes
		collectSimplifiedMesh(simplifier, m_geom[0]);

		simplifier.initialize(&mutMesh);

 		m_originalNumVerts = simplifier.m_numVertices;
 		m_originalNumFaces = simplifier.m_numFaces;

		//
		// All the real work is done here
		// We remove a fraction of the faces
		// Even removing a small number of faces could remove a large number of redundant vertices
		//
		hkReal fraction = g_meshSimplificationVariants[m_variantId].m_fractionToRemove;
		simplifier.removeFractionOfFaces( fraction );
		simplifier.finalize();

		m_numVerts = simplifier.m_numVertices;
		m_numFaces = simplifier.m_numFaces;
		
		// Grab the simplified mesh so that we can display it.
		collectSimplifiedMesh(simplifier, m_geom[1]);
	}
}

void MeshSimplificationDemo::handleInput()
{
	if ( m_env->m_gamePad->wasButtonPressed(HKG_PAD_BUTTON_1) )
	{
		m_displayMeshIndex++;
		m_displayMeshIndex = m_displayMeshIndex % m_numDisplayMeshes;
	}

	if ( m_env->m_gamePad->wasButtonPressed(HKG_PAD_BUTTON_2) )
	{
		m_alwaysRunQem = !m_alwaysRunQem;
	}
}

void MeshSimplificationDemo::displayInfoText()
{
	hkString s;
	int color, numVerts, numFaces;
	if (m_displayMeshIndex == 0)
	{
		s.printf("Displaying original mesh");
		color = hkColor::WHITE;
		numVerts = m_originalNumVerts;
		numFaces = m_originalNumFaces;
	}
	else // if (m_displayMeshIndex == 1)
	{
		s.printf("Displaying hkQem mesh");
		color = hkColor::GREEN;
		numVerts = m_numVerts;
		numFaces = m_numFaces;
	}
	hkString s2; s2.printf("%d vertices\n%d faces", numVerts, numFaces);
	const char* keys = "1) Toggle original/simplified\n2) Toggle resimplify each frame";

	const int h = m_env->m_window->getHeight();
	m_env->m_textDisplay->outputText( s.cString(), 20, h-120, color);
	m_env->m_textDisplay->outputText( s2.cString(), 20, h-90);
	m_env->m_textDisplay->outputText( keys, 20, h-45);


}

hkDemo::Result MeshSimplificationDemo::stepDemo()
{
	handleInput();

	if (m_runQem || m_alwaysRunQem)
	{
		hkStopwatch timer;
		{
			timer.start();
			doMeshSimplify();
			timer.stop();
		}
		if (!m_alwaysRunQem)
		{
			hkprintf("Mesh simplification finished in %f seconds.\n", timer.getElapsedSeconds());
		}
		m_runQem = false;
	}

	int color = hkColor::rgbFromChars( 120, 120, 220, 255 );
	drawGeometry( m_geom[m_displayMeshIndex], color );

	displayInfoText();

	return hkDefaultDemo::stepDemo();
}

void MeshSimplificationDemo::setupMutatableMesh( hkQemMutableMesh& mutMesh )
{
	hkArray<hkVector4> vertices;
	int indexOffset = 0;

	//
	// Initialize the simplifier from the loaded mesh
	//
	for (int s=0; s<m_sections.getSize(); s++)
	{
		vertices.clear();
		HK_TIME_CODE_BLOCK("Add verts", HK_NULL);
		//
		// First, get the vertices from the mesh, transform, and add them to the mutable mesh
		//
		m_sections[s]->collectVertexPositions( vertices );
		{
			for (int v=0; v<vertices.getSize(); v++)
			{
				hkVector4 tempV;
				m_worldTransform.multiplyVector(vertices[v], tempV);
				vertices[v] = tempV;
			}
		}

		mutMesh.addVertices( vertices );

		//
		// Then add the triangle information
		// We don't have materials in this mesh, but we can treat each section as a different material
		// Different materials can be merged, but the resulting triangle with have the material of one of the original faces
		//
		for(hkUint32 nTri = 0; nTri < m_sections[s]->getNumTriangles(); nTri++ )
		{
			hkUint32 i1, i2, i3;
			m_sections[s]->getTriangleIndices( nTri, i1, i2, i3 );
			mutMesh.addTriangleWithMaterial( i1+indexOffset, i2+indexOffset, i3+indexOffset, s);
		}
		indexOffset += vertices.getSize();
	}
}

void MeshSimplificationDemo::setupSquareMutatableMesh( hkQemMutableMesh& mutMesh )
{
	//
	// Create a square mesh that is parabolic in shape
	// 
	const int res = 32; // number of points in each direction
	const hkReal size = hkReal ( 2 * res );

	hkArray<hkVector4> vertices;
	vertices.setSize(res*res);

	const hkReal dx = 2.0f * size / hkReal(res-1);
	const hkReal dz = 2.0f * size / hkReal(res-1);

	for (int i=0; i<res; i++)
	{
		for (int j=0; j<res; j++)
		{
			
			hkReal x = i*dx - size;
			hkReal z = j*dz - size;
			hkReal y = 1.25f * ( (x*x)/hkReal(res*res) + (z*z)/hkReal(res*res) );
			vertices[i*res + j].set( x, y, z);
		}
	}

	// Add the veritices to the mesh
	mutMesh.addVertices( vertices );

	// Constrain the border vertices. This will prevent them from being moved during an edge contraction.
	for (int i=0; i<res; i++)
	{
		for (int j=0; j<res; j++)
		{
			if ((i==0) || (i == (res-1)) || (j == 0) || (j == (res-1)))
			{
				int k = i*res + j;
				mutMesh.setVertexConstrained( k, true );
				HK_DISPLAY_STAR( vertices[k], .25f, hkColor::CYAN );
			}
		}
	}

	// Add the triangles
	for (int i=0; i<res-1; i++)
	{
		for (int j=0; j<res-1; j++)
		{
			int i00 = i*res + j;
			int i01 = i*res + (j+1);
			int i10 = (i+1)*res + j;
			int i11 = (i+1)*res + (j+1);
		
			mutMesh.addTriangle(i00, i11, i01);
			mutMesh.addTriangle(i00, i11, i10);
		}
	}
}


#if	defined	(	HK_COMPILER_MWERKS	)
#	pragma	force_active	on
#	pragma	fullpath_file	on
#	endif

HK_DECLARE_DEMO_VARIANT_USING_STRUCT( MeshSimplificationDemo, HK_DEMO_TYPE_OTHER, MeshSimplificationVariant, g_meshSimplificationVariants, "Mesh simplification example");

/*
* Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20090704)
* 
* Confidential Information of Havok.  (C) Copyright 1999-2009
* Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
* Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
* rights, and intellectual property rights in the Havok software remain in
* Havok and/or its suppliers.
* 
* Use of this software for evaluation purposes is subject to and indicates
* acceptance of the End User licence Agreement for this product. A copy of
* the license is included with this software and is also available at www.havok.com/tryhavok.
* 
*/
