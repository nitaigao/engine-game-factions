/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Demos/Physics/UseCase/CharacterControl/CharacterProxyVsRigidBody/UnevenTerrainVs/UnevenTerrainVsDemo.h'
#include <Demos/demos.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Demos/Physics/UseCase/CharacterControl/CharacterProxyVsRigidBody/UnevenTerrainVs/UnevenTerrainVsDemo.h>
#define True true
#define False false



// External pointer and enum types
extern const hkClass UnevenTerrainVsDemoLandscapeContainerClass;
extern const hkClass hkpCharacterContextClass;
extern const hkClass hkpCharacterProxyClass;
extern const hkClass hkpCharacterRigidBodyClass;
extern const hkClass hkpShapePhantomClass;

//
// Class UnevenTerrainVsDemo::Options
//
static const hkInternalClassMember UnevenTerrainVsDemo_OptionsClass_Members[] =
{
	{ "worldCollisionTolerance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(UnevenTerrainVsDemo::Options,m_worldCollisionTolerance), HK_NULL },
	{ "characterCylinderHeight", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(UnevenTerrainVsDemo::Options,m_characterCylinderHeight), HK_NULL },
	{ "characterRadius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(UnevenTerrainVsDemo::Options,m_characterRadius), HK_NULL },
	{ "characterGravity", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(UnevenTerrainVsDemo::Options,m_characterGravity), HK_NULL },
	{ "characterWalkSpeed", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(UnevenTerrainVsDemo::Options,m_characterWalkSpeed), HK_NULL },
	{ "clientStateFiltering", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(UnevenTerrainVsDemo::Options,m_clientStateFiltering), HK_NULL },
	{ "rbSupportDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(UnevenTerrainVsDemo::Options,m_rbSupportDistance), HK_NULL },
	{ "rbHardSupportDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(UnevenTerrainVsDemo::Options,m_rbHardSupportDistance), HK_NULL },
	{ "rbAllowedPenetrationDepth", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(UnevenTerrainVsDemo::Options,m_rbAllowedPenetrationDepth), HK_NULL }
};
namespace
{
	struct UnevenTerrainVsDemoOptions_DefaultStruct
	{
		int s_defaultOffsets[9];
		typedef hkInt8 _hkBool;
		typedef hkReal _hkVector4[4];
		typedef hkReal _hkQuaternion[4];
		typedef hkReal _hkMatrix3[12];
		typedef hkReal _hkRotation[12];
		typedef hkReal _hkQsTransform[12];
		typedef hkReal _hkMatrix4[16];
		typedef hkReal _hkTransform[16];
		hkReal m_worldCollisionTolerance;
		hkReal m_characterCylinderHeight;
		hkReal m_characterRadius;
		hkReal m_characterGravity;
		hkReal m_characterWalkSpeed;
		int m_clientStateFiltering;
		hkReal m_rbSupportDistance;
		hkReal m_rbAllowedPenetrationDepth;
	};
	const UnevenTerrainVsDemoOptions_DefaultStruct UnevenTerrainVsDemoOptions_Default =
	{
		{HK_OFFSET_OF(UnevenTerrainVsDemoOptions_DefaultStruct,m_worldCollisionTolerance),HK_OFFSET_OF(UnevenTerrainVsDemoOptions_DefaultStruct,m_characterCylinderHeight),HK_OFFSET_OF(UnevenTerrainVsDemoOptions_DefaultStruct,m_characterRadius),HK_OFFSET_OF(UnevenTerrainVsDemoOptions_DefaultStruct,m_characterGravity),HK_OFFSET_OF(UnevenTerrainVsDemoOptions_DefaultStruct,m_characterWalkSpeed),HK_OFFSET_OF(UnevenTerrainVsDemoOptions_DefaultStruct,m_clientStateFiltering),HK_OFFSET_OF(UnevenTerrainVsDemoOptions_DefaultStruct,m_rbSupportDistance),-1,HK_OFFSET_OF(UnevenTerrainVsDemoOptions_DefaultStruct,m_rbAllowedPenetrationDepth)},
		0.1f,0.8f,0.6f,-16.0f,10.0f,3,0.1f,-0.1f
	};
}
extern const hkClass UnevenTerrainVsDemoOptionsClass;
const hkClass UnevenTerrainVsDemoOptionsClass(
	"UnevenTerrainVsDemoOptions",
	HK_NULL, // parent
	sizeof(UnevenTerrainVsDemo::Options),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(UnevenTerrainVsDemo_OptionsClass_Members),
	HK_COUNT_OF(UnevenTerrainVsDemo_OptionsClass_Members),
	&UnevenTerrainVsDemoOptions_Default,
	HK_NULL, // attributes
	0, // flags
	0 // version
	);
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(UnevenTerrainVsDemo,Options);

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
