/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

//
// One or Two diffuse maps, along with a normal and specular map, with and without shadows. The most common demo shaders 
// with 'proper' assets. These will currently also allow loading of a gloss map, but will ignore it
// 

//:STYLE VertOneLightReflectT1 PixT1ReflectNoDiff LD1 T1 REFLECTION NORMAL0 SPECULAR0 DEFINE:HKG_CUBEMAP_SLOT0 DEFINE:_PT1ReflectNoDiff
//:STYLE VertOneLightReflectShadowProjT1 PixShadowSceneT1ReflectNoDiff LD1 T1 SHADOWMAP REFLECTION NORMAL0 SPECULAR0 DEFINE:HKG_CUBEMAP_SLOT4 DEFINE:_PShadowSceneT1ReflectNoDiff

//:STYLE VertOneLightReflectT1 PixT1ReflectNoDiffNoSpec LD1 T1 REFLECTION NORMAL0 DEFINE:HKG_CUBEMAP_SLOT0 DEFINE:_PT1ReflectNoDiffNoSpec
//:STYLE VertOneLightReflectShadowProjT1 PixShadowSceneT1ReflectNoDiffNoSpec LD1 T1 SHADOWMAP REFLECTION NORMAL0 DEFINE:HKG_CUBEMAP_SLOT4 DEFINE:_PShadowSceneT1ReflectNoDiffNoSpec

//:STYLE VertOneLightReflectT1 PixT1ReflectNoSpec LD1 T1 DIFFUSE0 REFLECTION NORMAL0 DEFINE:HKG_CUBEMAP_SLOT1 DEFINE:_PT1ReflectNoSpec
//:STYLE VertOneLightReflectShadowProjT1 PixShadowSceneT1ReflectNoSpec LD1 T1 SHADOWMAP DIFFUSE0 REFLECTION NORMAL0 DEFINE:HKG_CUBEMAP_SLOT5 DEFINE:_PShadowSceneT1ReflectNoSpec

//:STYLE VertOneLightReflectT1 PixT1Reflect LD1 T1 DIFFUSE0 REFLECTION NORMAL0 SPECULAR0 DEFINE:HKG_CUBEMAP_SLOT1 DEFINE:_PT1Reflect
//:STYLE VertOneLightReflectShadowProjT1 PixShadowSceneT1Reflect LD1 T1 SHADOWMAP DIFFUSE0 REFLECTION NORMAL0 SPECULAR0 DEFINE:HKG_CUBEMAP_SLOT5 DEFINE:_PShadowSceneT1Reflect
//:STYLE VertOneLightReflectT1 PixT1ReflectMask LD1 T1 DIFFUSE0 REFLECTION REFLECTION NORMAL0 SPECULAR0 DEFINE:HKG_CUBEMAP_SLOT2 DEFINE:_PT1ReflectMask
//:STYLE VertOneLightReflectShadowProjT1 PixShadowSceneT1ReflectMask LD1 T1 SHADOWMAP DIFFUSE0 REFLECTION REFLECTION NORMAL0 SPECULAR0 DEFINE:HKG_CUBEMAP_SLOT6 DEFINE:_PShadowSceneT1ReflectMask
//:STYLE VertOneLightReflectT2 PixT2ReflectMask LD1 T2 DIFFUSE0 REFLECTION REFLECTION NORMAL0 SPECULAR0 DEFINE:HKG_CUBEMAP_SLOT2 DEFINE:_PT2ReflectMask
//:STYLE VertOneLightReflectShadowProjT2 PixShadowSceneT2ReflectMask LD1 T2 SHADOWMAP DIFFUSE0 REFLECTION REFLECTION NORMAL0 SPECULAR0 DEFINE:HKG_CUBEMAP_SLOT6 DEFINE:_PShadowSceneT2ReflectMask

//:STYLE VertOneLightReflectT1 PixT1ReflectNoDiff LD2 T1 REFLECTION NORMAL0 SPECULAR0 DEFINE:HKG_CUBEMAP_SLOT0 DEFINE:_PT1ReflectNoDiff
//:STYLE VertOneLightReflectShadowProjT1 PixShadowSceneT1ReflectNoDiff LD2 T1 SHADOWMAP REFLECTION NORMAL0 SPECULAR0 DEFINE:HKG_CUBEMAP_SLOT4 DEFINE:_PShadowSceneT1ReflectNoDiff

//:STYLE VertOneLightReflectT1 PixT1ReflectNoDiffNoSpec LD2 T1 REFLECTION NORMAL0 DEFINE:HKG_CUBEMAP_SLOT0 DEFINE:_PT1ReflectNoDiffNoSpec
//:STYLE VertOneLightReflectShadowProjT1 PixShadowSceneT1ReflectNoDiffNoSpec LD2 T1 SHADOWMAP REFLECTION NORMAL0 DEFINE:HKG_CUBEMAP_SLOT4 DEFINE:_PShadowSceneT1ReflectNoDiffNoSpec

//:STYLE VertOneLightReflectT1 PixT1ReflectNoSpec LD2 T1 DIFFUSE0 REFLECTION NORMAL0 DEFINE:HKG_CUBEMAP_SLOT1  DEFINE:_PT1ReflectNoSpec
//:STYLE VertOneLightReflectShadowProjT1 PixShadowSceneT1ReflectNoSpec LD2 T1 SHADOWMAP DIFFUSE0 REFLECTION NORMAL0 DEFINE:HKG_CUBEMAP_SLOT5 DEFINE:_PShadowSceneT1ReflectNoSpec

//:STYLE VertOneLightReflectT1 PixT1Reflect LD2 T1 DIFFUSE0 REFLECTION NORMAL0 SPECULAR0 DEFINE:HKG_CUBEMAP_SLOT1 DEFINE:_PT1Reflect
//:STYLE VertOneLightReflectShadowProjT1 PixShadowSceneT1Reflect LD2 T1 SHADOWMAP DIFFUSE0 REFLECTION NORMAL0 SPECULAR0 DEFINE:HKG_CUBEMAP_SLOT5 DEFINE:_PShadowSceneT1Reflect
//:STYLE VertOneLightReflectT1 PixT1ReflectMask LD2 T1 DIFFUSE0 REFLECTION REFLECTION NORMAL0 SPECULAR0 DEFINE:HKG_CUBEMAP_SLOT2 DEFINE:_PT1ReflectMask
//:STYLE VertOneLightReflectShadowProjT1 PixShadowSceneT1ReflectMask LD2 T1 SHADOWMAP DIFFUSE0 REFLECTION REFLECTION NORMAL0 SPECULAR0 DEFINE:HKG_CUBEMAP_SLOT6 DEFINE:_PShadowSceneT1ReflectMask
//:STYLE VertOneLightReflectT2 PixT2ReflectMask LD2 T2 DIFFUSE0 REFLECTION REFLECTION NORMAL0 SPECULAR0 DEFINE:HKG_CUBEMAP_SLOT2 DEFINE:_PT2ReflectMask
//:STYLE VertOneLightReflectShadowProjT2 PixShadowSceneT2ReflectMask LD2 T2 SHADOWMAP DIFFUSE0 REFLECTION REFLECTION NORMAL0 SPECULAR0 DEFINE:HKG_CUBEMAP_SLOT6 DEFINE:_PShadowSceneT2ReflectMask


//:STYLE VertOneLightReflectT1 PixT1ReflectNoDiff LD1 T1 REFLECTION NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_CUBEMAP_SLOT0 DEFINE:_PT1ReflectNoDiff DEFINE:HKG_INSTANCING
//:STYLE VertOneLightReflectShadowProjT1 PixShadowSceneT1ReflectNoDiff LD1 T1 SHADOWMAP REFLECTION NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_CUBEMAP_SLOT4 DEFINE:_PShadowSceneT1ReflectNoDiff DEFINE:HKG_INSTANCING

//:STYLE VertOneLightReflectT1 PixT1ReflectNoDiffNoSpec LD1 T1 REFLECTION NORMAL0 INSTANCED DEFINE:HKG_CUBEMAP_SLOT0 DEFINE:_PT1ReflectNoDiffNoSpec DEFINE:HKG_INSTANCING
//:STYLE VertOneLightReflectShadowProjT1 PixShadowSceneT1ReflectNoDiffNoSpec LD1 T1 SHADOWMAP REFLECTION NORMAL0 INSTANCED DEFINE:HKG_CUBEMAP_SLOT4 DEFINE:_PShadowSceneT1ReflectNoDiffNoSpec DEFINE:HKG_INSTANCING

//:STYLE VertOneLightReflectT1 PixT1ReflectNoSpec LD1 T1 DIFFUSE0 REFLECTION NORMAL0 INSTANCED DEFINE:HKG_CUBEMAP_SLOT1 DEFINE:_PT1ReflectNoSpec DEFINE:HKG_INSTANCING
//:STYLE VertOneLightReflectShadowProjT1 PixShadowSceneT1ReflectNoSpec LD1 T1 SHADOWMAP DIFFUSE0 REFLECTION NORMAL0 INSTANCED DEFINE:HKG_CUBEMAP_SLOT5 DEFINE:_PShadowSceneT1ReflectNoSpec DEFINE:HKG_INSTANCING

//:STYLE VertOneLightReflectT1 PixT1Reflect LD1 T1 DIFFUSE0 REFLECTION NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_CUBEMAP_SLOT1 DEFINE:_PT1Reflect DEFINE:HKG_INSTANCING
//:STYLE VertOneLightReflectShadowProjT1 PixShadowSceneT1Reflect LD1 T1 SHADOWMAP DIFFUSE0 REFLECTION NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_CUBEMAP_SLOT5 DEFINE:_PShadowSceneT1Reflect DEFINE:HKG_INSTANCING
//:STYLE VertOneLightReflectT1 PixT1ReflectMask LD1 T1 DIFFUSE0 REFLECTION REFLECTION NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_CUBEMAP_SLOT2 DEFINE:_PT1ReflectMask DEFINE:HKG_INSTANCING
//:STYLE VertOneLightReflectShadowProjT1 PixShadowSceneT1ReflectMask LD1 T1 SHADOWMAP DIFFUSE0 REFLECTION REFLECTION NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_CUBEMAP_SLOT6 DEFINE:_PShadowSceneT1ReflectMask DEFINE:HKG_INSTANCING
//:STYLE VertOneLightReflectT2 PixT2ReflectMask LD1 T2 DIFFUSE0 REFLECTION REFLECTION NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_CUBEMAP_SLOT2 DEFINE:_PT2ReflectMask DEFINE:HKG_INSTANCING
//:STYLE VertOneLightReflectShadowProjT2 PixShadowSceneT2ReflectMask LD1 T2 SHADOWMAP DIFFUSE0 REFLECTION REFLECTION NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_CUBEMAP_SLOT6 DEFINE:_PShadowSceneT2ReflectMask DEFINE:HKG_INSTANCING

//:STYLE VertOneLightReflectT1 PixT1ReflectNoDiff LD2 T1 REFLECTION NORMAL0 SPECULAR0 DEFINE:HKG_CUBEMAP_SLOT0 INSTANCED DEFINE:_PT1ReflectNoDiff DEFINE:HKG_INSTANCING
//:STYLE VertOneLightReflectShadowProjT1 PixShadowSceneT1ReflectNoDiff LD2 T1 SHADOWMAP REFLECTION NORMAL0 SPECULAR0 DEFINE:HKG_CUBEMAP_SLOT4 INSTANCED DEFINE:_PShadowSceneT1ReflectNoDiff DEFINE:HKG_INSTANCING

//:STYLE VertOneLightReflectT1 PixT1ReflectNoDiffNoSpec LD2 T1 REFLECTION NORMAL0 INSTANCED DEFINE:HKG_CUBEMAP_SLOT0 DEFINE:_PT1ReflectNoDiffNoSpec DEFINE:HKG_INSTANCING
//:STYLE VertOneLightReflectShadowProjT1 PixShadowSceneT1ReflectNoDiffNoSpec LD2 T1 SHADOWMAP REFLECTION NORMAL0 INSTANCED DEFINE:HKG_CUBEMAP_SLOT4 DEFINE:_PShadowSceneT1ReflectNoDiffNoSpec DEFINE:HKG_INSTANCING

//:STYLE VertOneLightReflectT1 PixT1ReflectNoSpec LD2 T1 DIFFUSE0 REFLECTION NORMAL0 DEFINE:HKG_CUBEMAP_SLOT1 INSTANCED DEFINE:_PT1ReflectNoSpec DEFINE:HKG_INSTANCING
//:STYLE VertOneLightReflectShadowProjT1 PixShadowSceneT1ReflectNoSpec LD2 T1 SHADOWMAP DIFFUSE0 REFLECTION NORMAL0 INSTANCED DEFINE:HKG_CUBEMAP_SLOT5 DEFINE:_PShadowSceneT1ReflectNoSpec DEFINE:HKG_INSTANCING

//:STYLE VertOneLightReflectT1 PixT1Reflect LD2 T1 DIFFUSE0 REFLECTION NORMAL0 SPECULAR0 DEFINE:HKG_CUBEMAP_SLOT1 INSTANCED DEFINE:_PT1Reflect DEFINE:HKG_INSTANCING
//:STYLE VertOneLightReflectShadowProjT1 PixShadowSceneT1Reflect LD2 T1 SHADOWMAP DIFFUSE0 REFLECTION NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_CUBEMAP_SLOT5 DEFINE:_PShadowSceneT1Reflect DEFINE:HKG_INSTANCING
//:STYLE VertOneLightReflectT1 PixT1ReflectMask LD2 T1 DIFFUSE0 REFLECTION REFLECTION NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_CUBEMAP_SLOT2 DEFINE:_PT1ReflectMask DEFINE:HKG_INSTANCING
//:STYLE VertOneLightReflectShadowProjT1 PixShadowSceneT1ReflectMask LD2 T1 SHADOWMAP DIFFUSE0 REFLECTION REFLECTION NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_CUBEMAP_SLOT6 DEFINE:_PShadowSceneT1ReflectMask DEFINE:HKG_INSTANCING
//:STYLE VertOneLightReflectT2 PixT2ReflectMask LD2 T2 DIFFUSE0 REFLECTION REFLECTION NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_CUBEMAP_SLOT2 DEFINE:_PT2ReflectMask DEFINE:HKG_INSTANCING
//:STYLE VertOneLightReflectShadowProjT2 PixShadowSceneT2ReflectMask LD2 T2 SHADOWMAP DIFFUSE0 REFLECTION REFLECTION NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_CUBEMAP_SLOT6 DEFINE:_PShadowSceneT2ReflectMask DEFINE:HKG_INSTANCING



#include "CommonHeader.hlslh"


// Matrices
float4x4 g_mWorldInv;
float4x4 g_mWorldView		: WorldView;
float4x4 g_mProj			: Proj;
float4x4 g_mViewInv			: ViewInverse;

 


void computeTangentSpace( float3x3 worldInv, float3 tangent, float3 binormal, float3 normal, out float3x3 objToTangentSpaceInv, inout float4 tangentToWorldSpaceRow0, inout float4 tangentToWorldSpaceRow1, inout float4 tangentToWorldSpaceRow2 )
{
	float bumpHeight = 1.0f;
	
	objToTangentSpaceInv[0] = tangent * bumpHeight;
	objToTangentSpaceInv[1] = binormal * bumpHeight;
	objToTangentSpaceInv[2] = normal;
 
	tangentToWorldSpaceRow0.x = dot(objToTangentSpaceInv[0].xyz, worldInv[0]);
	tangentToWorldSpaceRow0.y = dot(objToTangentSpaceInv[1].xyz, worldInv[0]);
	tangentToWorldSpaceRow0.z = dot(objToTangentSpaceInv[2].xyz, worldInv[0]);
	tangentToWorldSpaceRow1.x = dot(objToTangentSpaceInv[0].xyz, worldInv[1]);
	tangentToWorldSpaceRow1.y = dot(objToTangentSpaceInv[1].xyz, worldInv[1]);
	tangentToWorldSpaceRow1.z = dot(objToTangentSpaceInv[2].xyz, worldInv[1]);
	tangentToWorldSpaceRow2.x = dot(objToTangentSpaceInv[0].xyz, worldInv[2]);
	tangentToWorldSpaceRow2.y = dot(objToTangentSpaceInv[1].xyz, worldInv[2]);
	tangentToWorldSpaceRow2.z = dot(objToTangentSpaceInv[2].xyz, worldInv[2]);  
}


vertexOutputT1BR VertOneLightReflectT1( vertexInputT1B In )
{
	vertexOutputT1BR Out;

#ifdef HKG_INSTANCING
	float3x4 world;
   	world[0] = In.transformRow0;
   	world[1] = In.transformRow1;
   	world[2] = In.transformRow2;
   	//world[3] = In.transformRow3;
   	float3 worldVertPos = mul( world, float4(In.position.xyz, 1) ).xyz;
	float4 viewPos = mul( float4(worldVertPos, 1.0), g_mView);
	float3 lightVec = mul( g_vLightDir, (float3x3)world );  // rev mult order 
	float3 lightVec1 = mul( g_vLight1Dir, (float3x3)world );  // rev mult order 
	float3 eyeVec = g_mViewInv[3].xyz - worldVertPos.xyz; // world space eye vector

	eyeVec = normalize(eyeVec);
	Out.TangToWorld0.w = eyeVec.x;
	Out.TangToWorld1.w = eyeVec.y;
	Out.TangToWorld2.w = eyeVec.z;
	
	eyeVec = mul(eyeVec, (float3x3) world );  // transform back to object space
	
	float3x3 objToTangentSpaceInv;
	computeTangentSpace( (float3x3)world, In.tangent, In.binormal, In.normal, objToTangentSpaceInv, Out.TangToWorld0, Out.TangToWorld1, Out.TangToWorld2);

#else
	float3 worldVertPos = mul(float4(In.position.xyz , 1.0), g_mWorld).xyz;
	float4 viewPos = mul( float4(In.position.xyz, 1.0), g_mWorldView);
	float3 lightVec = mul( g_vLightDir, (float3x3)g_mWorldInv ); 
	float3 lightVec1 = mul( g_vLight1Dir, (float3x3)g_mWorldInv );  
	float3 eyeVec = g_mViewInv[3].xyz - worldVertPos.xyz; // world space eye vector
	
	eyeVec = normalize(eyeVec);
	Out.TangToWorld0.w = eyeVec.x;
	Out.TangToWorld1.w = eyeVec.y;
	Out.TangToWorld2.w = eyeVec.z;
	
	eyeVec = mul(eyeVec, (float3x3) g_mWorldInv );  // transform back to object space

	float3x3 objToTangentSpaceInv;
	computeTangentSpace( (float3x3) g_mWorldInv, In.tangent, In.binormal, In.normal, objToTangentSpaceInv, Out.TangToWorld0, Out.TangToWorld1, Out.TangToWorld2);

#endif

	Out.position = mul( viewPos, g_mProj);
	Out.texCoord0 = In.texCoord0;
	
	float3 L0 = mul( objToTangentSpaceInv, lightVec ).xyz; // transform from object to tangent space
	float3 L1 = 0;
	if (g_iNumLights > 1)
	{
		L1 = mul( objToTangentSpaceInv, lightVec1 ).xyz; // transform from object to tangent space
	}

	// eye vector
	float3 e = mul( objToTangentSpaceInv, eyeVec );
	packBumpLights( L0, L1, e, viewPos, Out.posView, Out.L0, Out.E );

	return Out;
}


vertexOutputShadowT1BR VertOneLightReflectShadowProjT1( vertexInputT1B In) 
{
    vertexOutputShadowT1BR Output;
    
 #ifdef HKG_INSTANCING
	float3x4 world;
   	world[0] = In.transformRow0;
   	world[1] = In.transformRow1;
   	world[2] = In.transformRow2;
   	//world[3] = In.transformRow3;
   	float3 worldVertPos = mul(world , float4(In.position.xyz, 1) ).xyz;
	float4 viewPos = mul( float4(worldVertPos, 1.0), g_mView);
	float3 lightVec = mul( g_vLightDir, (float3x3)world );  // rev mult order 
	float3 lightVec1 = mul( g_vLight1Dir, (float3x3)world );  // rev mult order 
	float3 eyeVec = g_mViewInv[3].xyz - worldVertPos.xyz; // world space eye vector

	eyeVec = normalize(eyeVec);
	Output.TangToWorld0.w = eyeVec.x;
	Output.TangToWorld1.w = eyeVec.y;
	Output.TangToWorld2.w = eyeVec.z;
	
	eyeVec = mul(eyeVec, (float3x3) world );  // transform back to object space
	
	float3x3 objToTangentSpaceInv;
	computeTangentSpace( (float3x3)world, In.tangent, In.binormal, In.normal, objToTangentSpaceInv, Output.TangToWorld0, Output.TangToWorld1, Output.TangToWorld2);

#else
	float3 worldVertPos = mul(float4(In.position.xyz , 1.0), g_mWorld).xyz;
	float4 viewPos = mul( float4(In.position.xyz, 1.0), g_mWorldView);
	float3 lightVec = mul( g_vLightDir, (float3x3)g_mWorldInv ); 
	float3 lightVec1 = mul( g_vLight1Dir, (float3x3)g_mWorldInv );  
	float3 eyeVec = g_mViewInv[3].xyz - worldVertPos.xyz; // world space eye vector
	
	eyeVec = normalize(eyeVec);
	Output.TangToWorld0.w = eyeVec.x;
	Output.TangToWorld1.w = eyeVec.y;
	Output.TangToWorld2.w = eyeVec.z;
	
	eyeVec = mul(eyeVec, (float3x3) g_mWorldInv );  // transform back to object space

	float3x3 objToTangentSpaceInv;
	computeTangentSpace( (float3x3) g_mWorldInv, In.tangent, In.binormal, In.normal, objToTangentSpaceInv, Output.TangToWorld0, Output.TangToWorld1, Output.TangToWorld2);

#endif
	
    Output.position = mul( viewPos, g_mProj);
    Output.texCoord0 = In.texCoord0;
		 
		// project pos into light space
    Output.posLight = mul( viewPos, g_mViewToLightProj );
    Output.posView = viewPos;

    #ifdef HKG_SHADOWS_VSM
        //XX Output.posLight1 = mul( viewPos, g_mViewToLightProj1 );
		//XX Output.posLight2 = mul( viewPos, g_mViewToLightProj2 );
		//XX Output.posLight3 = mul( viewPos, g_mViewToLightProj3 );
	#endif
   
	float3 L0 = mul( objToTangentSpaceInv, lightVec ).xyz; // transform from object to tangent space
	float3 L1 = 0;
	if (g_iNumLights > 1)
	{
		L1 = mul( objToTangentSpaceInv, lightVec1 ).xyz; // transform from object to tangent space
	}

	// eye vector
	float3 e = mul( objToTangentSpaceInv, eyeVec );
	packBumpLights( L0, L1, e, viewPos, Output.posView, Output.L0, Output.E );

	return Output;
}


vertexOutputT2BR VertOneLightReflectT2( vertexInputT2B In )
{
	vertexOutputT2BR Out;

 #ifdef HKG_INSTANCING
	float3x4 world;
   	world[0] = In.transformRow0;
   	world[1] = In.transformRow1;
   	world[2] = In.transformRow2;
   	//world[3] = In.transformRow3;
   	float3 worldVertPos = mul(world , float4(In.position.xyz, 1) ).xyz;
	float4 viewPos = mul( float4(worldVertPos, 1.0), g_mView);
	float3 lightVec = mul( g_vLightDir, (float3x3)world );  // rev mult order 
	float3 lightVec1 = mul( g_vLight1Dir, (float3x3)world );  // rev mult order 
	float3 eyeVec = g_mViewInv[3].xyz - worldVertPos.xyz; // world space eye vector

	eyeVec = normalize(eyeVec);
	Out.TangToWorld0.w = eyeVec.x;
	Out.TangToWorld1.w = eyeVec.y;
	Out.TangToWorld2.w = eyeVec.z;
	
	eyeVec = mul(eyeVec, (float3x3) world );  // transform back to object space
	
	float3x3 objToTangentSpaceInv;
	computeTangentSpace( (float3x3)world, In.tangent, In.binormal, In.normal, objToTangentSpaceInv, Out.TangToWorld0, Out.TangToWorld1, Out.TangToWorld2);

#else
	float3 worldVertPos = mul(float4(In.position.xyz , 1.0), g_mWorld).xyz;
	float4 viewPos = mul( float4(In.position.xyz, 1.0), g_mWorldView);
	float3 lightVec = mul( g_vLightDir, (float3x3)g_mWorldInv ); 
	float3 lightVec1 = mul( g_vLight1Dir, (float3x3)g_mWorldInv );  
	float3 eyeVec = g_mViewInv[3].xyz - worldVertPos.xyz; // world space eye vector
	
	eyeVec = normalize(eyeVec);
	Out.TangToWorld0.w = eyeVec.x;
	Out.TangToWorld1.w = eyeVec.y;
	Out.TangToWorld2.w = eyeVec.z;
	
	eyeVec = mul(eyeVec, (float3x3) g_mWorldInv );  // transform back to object space

	float3x3 objToTangentSpaceInv;
	computeTangentSpace( (float3x3) g_mWorldInv, In.tangent, In.binormal, In.normal, objToTangentSpaceInv, Out.TangToWorld0, Out.TangToWorld1, Out.TangToWorld2);

#endif

	Out.texCoord0 = In.texCoord0;
	Out.texCoord1 = In.texCoord1;
	
	Out.position = mul( viewPos, g_mProj);
	Out.posView = viewPos;
  	
	float3 L0 = mul( objToTangentSpaceInv, lightVec ).xyz; // transform from object to tangent space
	float3 L1 = 0;
	if (g_iNumLights > 1)
	{
		L1 = mul( objToTangentSpaceInv, lightVec1 ).xyz; // transform from object to tangent space
	}

	// eye vector
	float3 e = mul( objToTangentSpaceInv, eyeVec );
	packBumpLights( L0, L1, e, viewPos,  Out.posView, Out.L0, Out.E );

	return Out;
}


vertexOutputShadowT2BR VertOneLightReflectShadowProjT2( vertexInputT2B In) 
{
    vertexOutputShadowT2BR Output;
    
#ifdef HKG_INSTANCING
	float3x4 world;
   	world[0] = In.transformRow0;
   	world[1] = In.transformRow1;
   	world[2] = In.transformRow2;
   	//world[3] = In.transformRow3;
   	float3 worldVertPos = mul(world , float4(In.position.xyz, 1) ).xyz;
	float4 viewPos = mul( float4(worldVertPos, 1.0), g_mView);
	float3 lightVec = mul( g_vLightDir, (float3x3)world );  // rev mult order 
	float3 lightVec1 = mul( g_vLight1Dir, (float3x3)world );  // rev mult order 
	float3 eyeVec = g_mViewInv[3].xyz - worldVertPos.xyz; // world space eye vector

	eyeVec = normalize(eyeVec);
	Output.TangToWorld0.w = eyeVec.x;
	Output.TangToWorld1.w = eyeVec.y;
	Output.TangToWorld2.w = eyeVec.z;
	
	eyeVec = mul(eyeVec, (float3x3) world );  // transform back to object space
	
	float3x3 objToTangentSpaceInv;
	computeTangentSpace( (float3x3)world, In.tangent, In.binormal, In.normal, objToTangentSpaceInv, Output.TangToWorld0, Output.TangToWorld1, Output.TangToWorld2);

#else
	float3 worldVertPos = mul(float4(In.position.xyz , 1.0), g_mWorld).xyz;
	float4 viewPos = mul( float4(In.position.xyz, 1.0), g_mWorldView);
	float3 lightVec = mul( g_vLightDir, (float3x3)g_mWorldInv ); 
	float3 lightVec1 = mul( g_vLight1Dir, (float3x3)g_mWorldInv );  
	float3 eyeVec = g_mViewInv[3].xyz - worldVertPos.xyz; // world space eye vector
	
	eyeVec = normalize(eyeVec);
	Output.TangToWorld0.w = eyeVec.x;
	Output.TangToWorld1.w = eyeVec.y;
	Output.TangToWorld2.w = eyeVec.z;
	
	eyeVec = mul(eyeVec, (float3x3) g_mWorldInv );  // transform back to object space

	float3x3 objToTangentSpaceInv;
	computeTangentSpace( (float3x3) g_mWorldInv, In.tangent, In.binormal, In.normal, objToTangentSpaceInv, Output.TangToWorld0, Output.TangToWorld1, Output.TangToWorld2);

#endif

    Output.position = mul( viewPos, g_mProj);
    
    Output.texCoord01 = float4( In.texCoord0.xy, In.texCoord1.xy);
	 
		// project pos into light space
    Output.posLight.xyz = mul( viewPos, g_mViewToLightProj );
    
    #ifdef HKG_SHADOWS_VSM
        //XX Output.posLight1 = mul( viewPos, g_mViewToLightProj1 );
		//XX Output.posLight2 = mul( viewPos, g_mViewToLightProj2 );
		//XX Output.posLight3 = mul( viewPos, g_mViewToLightProj3 );
	#endif
    
	float3 L0 = mul( objToTangentSpaceInv, lightVec ).xyz; // transform from object to tangent space
	float3 L1 = 0;
	if (g_iNumLights > 1)
	{
		L1 = mul( objToTangentSpaceInv, lightVec1 ).xyz; // transform from object to tangent space
	}

	// eye vector
	float3 e = mul( objToTangentSpaceInv, eyeVec );
	packBumpLights( L0, L1, e, viewPos, Output.posView, Output.L0, Output.E );

	return Output;
}


// Pixel Shaders

#ifdef _PT1Reflect
pixelOutput PixT1Reflect( vertexOutputT1BR In )
{
	float4 ColorMap = float4(1,1,1,1);
	float3 SpecMap = g_cSpecularColor.rgb;
	float3 N = float3(0,0,1); 
	
#if ENABLE_DIFFUSE_MAP0
	ColorMap = _sample0( In.texCoord0);
#endif
	
#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		N = _sample2(In.texCoord0).xyz*2.0 - 1.0;
		N = normalize(N);
	#else
		ColorMap = _sample2(In.texCoord0);
	#endif
#endif

	float3 worldEyeVec = float3( -In.TangToWorld0.w, -In.TangToWorld1.w, -In.TangToWorld2.w ); 
	float3 worldNormal = float3( dot(In.TangToWorld0.xyz, N), dot(In.TangToWorld1.xyz, N), dot(In.TangToWorld2.xyz, N) );
	float3 reflVect = reflect( worldEyeVec, worldNormal ); 
	
	float4 ReflectionMap = _cubeSample1(reflVect); 

	ColorMap.rgb = ColorMap.rgb * ReflectionMap.rgb;  


#if ENABLE_SPEC_MAP
	SpecMap *= _sample3(In.texCoord0).rgb;
#endif

	ColorMap *= g_cDiffuseColor;
	clip( ColorMap.a - ALPHA_DISCARD_TOLERANCE );

	float NdotL0;
	float NdotL1;
	float NdotH0; 
	unpackBumpLights( N, In.posView, In.L0, In.E, NdotL0, NdotL1, NdotH0);

#if ENABLE_LIGHTING
	float4 light0 = Phong(NdotL0, NdotH0, g_cSpecularPower) * float4(g_cLightColor.rgb,1);
	float3 light1 = 0;
	if ( g_iNumLights > 1)
	{
		light1.rgb = max( NdotL1, 0 ) * g_cLight1Color.rgb;
	}
#else
	float4 light0 = 1;
	float3 light1 = 0;
#endif
		
	pixelOutput Output;
	float3 totalLight = light0.rgb + light1.rgb + g_cAmbientColor.rgb;
	saturate(totalLight);
	
	Output.color.rgb = totalLight*ColorMap.rgb + light0.www*SpecMap.rgb;
	Output.color.a = ColorMap.a; // modulate alpha as is, light doesn't affect it.

	//Output.color.rgb = ColorMap.rgb;

	if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x ;
    Output.pzDepth.a = Output.color.a;

    return Output; 
}
#endif

#ifdef _PT1ReflectNoSpec
pixelOutput PixT1ReflectNoSpec( vertexOutputT1BR In )
{
	float4 ColorMap = float4(1,1,1,1);
	float3 SpecMap = g_cSpecularColor.rgb;
	float3 N = float3(0,0,1); 
	
#if ENABLE_DIFFUSE_MAP0
    ColorMap = _sample0(In.texCoord0);
#endif
	
#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		N = _sample2(In.texCoord0).xyz*2.0 - 1.0;
		N = normalize(N);
	#else
		ColorMap = _sample2(In.texCoord0);
	#endif
#endif

	float3 worldEyeVec = float3( -In.TangToWorld0.w, -In.TangToWorld1.w, -In.TangToWorld2.w ); 
	float3 worldNormal = float3( dot(In.TangToWorld0.xyz, N), dot(In.TangToWorld1.xyz, N), dot(In.TangToWorld2.xyz, N) );
	float3 reflVect = reflect( worldEyeVec, worldNormal ); 
	
	float4 ReflectionMap = _cubeSample1( reflVect ); 

	ColorMap.rgb = ColorMap.rgb * ReflectionMap.rgb;  

	ColorMap *= g_cDiffuseColor;
	clip( ColorMap.a - ALPHA_DISCARD_TOLERANCE );
	
	float NdotL0;
	float NdotL1;
	float NdotH0; 
	unpackBumpLights( N, In.posView, In.L0, In.E, NdotL0, NdotL1, NdotH0);

#if ENABLE_LIGHTING
	float4 light0 = Phong(NdotL0, NdotH0, g_cSpecularPower) * float4(g_cLightColor.rgb,1);
	float3 light1 = 0;
	if ( g_iNumLights > 1)
	{
		light1.rgb = max( NdotL1, 0 ) * g_cLight1Color.rgb;
	}
#else
	float4 light0 = 1;
	float3 light1 = 0;
#endif
		
	pixelOutput Output;
	float3 totalLight = light0.rgb + light1.rgb + g_cAmbientColor.rgb;
	saturate(totalLight);
	
	Output.color.rgb = totalLight*ColorMap.rgb + light0.www*SpecMap.rgb;
	Output.color.a = ColorMap.a; // modulate alpha as is, light doesn't affect it.

	//Output.color.rgb = ReflectionMap.rgb;

	if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x ;
    Output.pzDepth.a = Output.color.a;

    return Output; 
}
#endif

#ifdef _PT1ReflectNoDiff
pixelOutput PixT1ReflectNoDiff( vertexOutputT1BR In )
{
	float4 ColorMap = float4(1,1,1,1);
	float3 SpecMap = g_cSpecularColor.rgb;
	float3 N = float3(0,0,1); 
	
#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		N = _sample1(In.texCoord0).xyz*2.0 - 1.0;
		N = normalize(N);
	#else
		ColorMap = _cubeSample1(In.texCoord0);
	#endif
#endif

	float3 worldEyeVec = float3( -In.TangToWorld0.w, -In.TangToWorld1.w, -In.TangToWorld2.w ); 
	float3 worldNormal = float3( dot(In.TangToWorld0.xyz, N), dot(In.TangToWorld1.xyz, N), dot(In.TangToWorld2.xyz, N) );
	float3 reflVect = reflect( worldEyeVec, worldNormal ); 
	
	float4 ReflectionMap = _cubeSample0(reflVect); 

	ColorMap.rgb = ColorMap.rgb * ReflectionMap.rgb;  

#if ENABLE_SPEC_MAP
	SpecMap *= _sample2(In.texCoord0).rgb;
#endif

	ColorMap *= g_cDiffuseColor;
		clip( ColorMap.a - ALPHA_DISCARD_TOLERANCE );

	float NdotL0;
	float NdotL1;
	float NdotH0; 
	unpackBumpLights( N, In.posView, In.L0, In.E, NdotL0, NdotL1, NdotH0);

#if ENABLE_LIGHTING
	float4 light0 = Phong(NdotL0, NdotH0, g_cSpecularPower) * float4(g_cLightColor.rgb,1);
	float3 light1 = 0;
	if ( g_iNumLights > 1)
	{
		light1.rgb = max( NdotL1, 0 ) * g_cLight1Color.rgb;
	}
#else
	float4 light0 = 1;
	float3 light1 = 0;
#endif
		
	pixelOutput Output;
	float3 totalLight = light0.rgb + light1.rgb + g_cAmbientColor.rgb;
	saturate(totalLight);
	
	Output.color.rgb = totalLight*ColorMap.rgb + light0.www*SpecMap.rgb;
	Output.color.a = ColorMap.a; // modulate alpha as is, light doesn't affect it.

	if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x ;
    Output.pzDepth.a = Output.color.a;

    return Output; 
}
#endif

#ifdef _PT1ReflectNoDiffNoSpec
pixelOutput PixT1ReflectNoDiffNoSpec( vertexOutputT1BR In )
{
	float4 ColorMap = float4(1,1,1,1);
	float3 SpecMap = g_cSpecularColor.rgb;
	float3 N = float3(0,0,1); 
	
#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		N = _sample1(In.texCoord0).xyz*2.0 - 1.0;
		N = normalize(N);
	#else
		ColorMap = _sample1(In.texCoord0);
	#endif
#endif

	float3 worldEyeVec = float3( -In.TangToWorld0.w, -In.TangToWorld1.w, -In.TangToWorld2.w ); 
	float3 worldNormal = float3( dot(In.TangToWorld0.xyz, N), dot(In.TangToWorld1.xyz, N), dot(In.TangToWorld2.xyz, N) );
	float3 reflVect = reflect( worldEyeVec, worldNormal ); 
	
	float4 ReflectionMap = _cubeSample0(reflVect); 

	ColorMap.rgb = ColorMap.rgb * ReflectionMap.rgb;  
	ColorMap *= g_cDiffuseColor;
		clip( ColorMap.a - ALPHA_DISCARD_TOLERANCE );

	float NdotL0;
	float NdotL1;
	float NdotH0; 
	unpackBumpLights( N, In.posView, In.L0, In.E, NdotL0, NdotL1, NdotH0);

#if ENABLE_LIGHTING
	float4 light0 = Phong(NdotL0, NdotH0, g_cSpecularPower) * float4(g_cLightColor.rgb,1);
	float3 light1 = 0;
	if ( g_iNumLights > 1)
	{
		light1.rgb = max( NdotL1, 0 ) * g_cLight1Color.rgb;
	}
#else
	float4 light0 = 1;
	float3 light1 = 0;
#endif
		
	pixelOutput Output;
	float3 totalLight = light0.rgb + light1.rgb + g_cAmbientColor.rgb;
	saturate(totalLight);
	
	Output.color.rgb = totalLight*ColorMap.rgb + light0.www*SpecMap.rgb;
	Output.color.a = ColorMap.a; // modulate alpha as is, light doesn't affect it.

	if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x ;
    Output.pzDepth.a = Output.color.a;

    return Output; 
}
#endif

#ifdef _PT1ReflectMask
pixelOutput PixT1ReflectMask( vertexOutputT1BR In )
{
	float4 ColorMap = float4(1,1,1,1);
	float3 SpecMap = g_cSpecularColor.rgb;
	float3 N = float3(0,0,1); 
	
#if ENABLE_DIFFUSE_MAP0
    ColorMap = _sample0(In.texCoord0);
#endif

#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		N = _sample3(In.texCoord0).xyz*2.0 - 1.0;
		N = normalize(N);
	#else
		ColorMap = _sample3(In.texCoord0);
	#endif
#endif

	float3 worldEyeVec = float3( -In.TangToWorld0.w, -In.TangToWorld1.w, -In.TangToWorld2.w ); 
	float3 worldNormal = float3( dot(In.TangToWorld0.xyz, N), dot(In.TangToWorld1.xyz, N), dot(In.TangToWorld2.xyz, N) );
	float3 reflVect = reflect( worldEyeVec, worldNormal ); 
	
	float4 ReflectionMap = _cubeSample2(reflVect); 

	float4 ReflectionMask = _sample1(In.texCoord0); 

	ColorMap.rgb = (1-ReflectionMask.rgb)*ColorMap.rgb + ReflectionMask.rgb*ReflectionMap.rgb*ColorMap.rgb;  
		


#if ENABLE_SPEC_MAP
	SpecMap *= _sample4(In.texCoord0).rgb;
#endif

	ColorMap *= g_cDiffuseColor;
	clip( ColorMap.a - ALPHA_DISCARD_TOLERANCE );


	float NdotL0;
	float NdotL1;
	float NdotH0; 
	unpackBumpLights( N, In.posView, In.L0, In.E, NdotL0, NdotL1, NdotH0);

	
#if ENABLE_LIGHTING
    float specPower = g_cSpecularPower;
	float4 light0 = Phong(NdotL0, NdotH0, specPower) * float4(g_cLightColor.rgb, 1);
	float3 light1 = 0; 
	if ( g_iNumLights > 1)
	{
		light1 = max( NdotL1, 0 ) * g_cLight1Color.rgb;
	}
#else
	float4 light0 = 1;
	float4 light1 = 0;
#endif
	
	pixelOutput Output;
	float3 totalLight = light0.rgb + light1.rgb  + g_cAmbientColor.rgb;
	saturate(totalLight);

	Output.color.rgb = totalLight*ColorMap.rgb + light0.www*SpecMap.rgb;
	
	Output.color.a = ColorMap.a; // modulate alpha as is, light doesn't affect it.
	 if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x;
	Output.pzDepth.a = Output.color.a;

    return Output; 
}
#endif

#ifdef _PT2ReflectMask
pixelOutput PixT2ReflectMask( vertexOutputT2BR In )
{
	float4 ColorMap = float4(1,1,1,1);
	float3 SpecMap = g_cSpecularColor.rgb;
	float3 N = float3(0,0,1); 
	
#if ENABLE_DIFFUSE_MAP0
    ColorMap = _sample0(In.texCoord0);
#endif
	
#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		N = _sample3(In.texCoord0).xyz*2.0 - 1.0;
		N = normalize(N);
	#else
		ColorMap = _sample3(In.texCoord0);
	#endif
#endif

	
	float3 worldEyeVec = float3( -In.TangToWorld0.w, -In.TangToWorld1.w, -In.TangToWorld2.w ); 
	float3 worldNormal = float3( dot(In.TangToWorld0.xyz, N), dot(In.TangToWorld1.xyz, N), dot(In.TangToWorld2.xyz, N) );
	float3 reflVect = reflect( worldEyeVec, worldNormal ); 

	float4 ReflectionMap = _cubeSample2(reflVect); 

	float4 ReflectionMask = _sample1(In.texCoord1); 
	ColorMap.rgb = (1-ReflectionMask.rgb)*ColorMap.rgb + ReflectionMask.rgb*ReflectionMap.rgb*ColorMap.rgb;  

#if ENABLE_SPEC_MAP
	SpecMap *= _sample4(In.texCoord0).rgb;
#endif

	ColorMap *= g_cDiffuseColor;
	clip( ColorMap.a - ALPHA_DISCARD_TOLERANCE );


	float NdotL0;
	float NdotL1;
	float NdotH0; 
	unpackBumpLights( N, In.posView, In.L0, In.E, NdotL0, NdotL1, NdotH0);


#if ENABLE_LIGHTING
	float specPower = g_cSpecularPower;
	float4 light0 = Phong(NdotL0, NdotH0, specPower) * float4(g_cLightColor.rgb, 1);
	float3 light1 = 0; 
	if ( g_iNumLights > 1)
	{
		light1 = max( NdotL1, 0 ) * g_cLight1Color.rgb;
	}
#else
	float4 light0 = 1;
	float4 light1 = 0;
#endif
	
	pixelOutput Output;
	float3 totalLight = light0.rgb + light1.rgb  + g_cAmbientColor.rgb;
	saturate(totalLight);
	Output.color.rgb = totalLight*ColorMap.rgb + light0.www*SpecMap.rgb;
	Output.color.a = ColorMap.a; // modulate alpha as is, light doesn't affect it.

	if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x;
    Output.pzDepth.a = Output.color.a;

    return Output; 
}
#endif

#ifdef _PShadowSceneT1Reflect
pixelOutput PixShadowSceneT1Reflect( vertexOutputShadowT1BR In )
{
    pixelOutput Output;
    
    #ifdef HKG_SHADOWS_VSM
		float lightAmount = getLightAmountVSM( In.posLight, float4(0,0,0,1), float4(0,0,0,1), float4(0,0,0,1), In.posView );
  	#else
		float lightAmount = getLightAmountSM( In.posLight ); 
	#endif
		
	float4 ColorMap = float4(1,1,1,1);
	float3 SpecMap = g_cSpecularColor.rgb;
	float3 N = float3(0,0,1); 
	
#if ENABLE_DIFFUSE_MAP0
    ColorMap = _sample4( In.texCoord0);
#endif
		
#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		N = _sample6( In.texCoord0).xyz*2.0 - 1.0;
		N = normalize(N);
	#else
		ColorMap = _sample6(In.texCoord0);
	#endif
#endif

	float3 worldEyeVec = float3( -In.TangToWorld0.w, -In.TangToWorld1.w, -In.TangToWorld2.w ); 
	float3 worldNormal = float3( dot(In.TangToWorld0.xyz, N), dot(In.TangToWorld1.xyz, N), dot(In.TangToWorld2.xyz, N) );
	float3 reflVect = reflect( worldEyeVec, worldNormal ); 

	float4 ReflectionMap = _cubeSample5(reflVect); 

	ColorMap.rgb = ColorMap.rgb * ReflectionMap.rgb;  


#if ENABLE_SPEC_MAP
	SpecMap *= _sample7(In.texCoord0).rgb;
#endif

	ColorMap *= g_cDiffuseColor;
	clip( ColorMap.a - ALPHA_DISCARD_TOLERANCE );


	float NdotL0;
	float NdotL1;
	float NdotH0; 
	unpackBumpLights( N, In.posView, In.L0, In.E, NdotL0, NdotL1, NdotH0);

	
#if ENABLE_LIGHTING
	float specPower = g_cSpecularPower;
	float4 light0 = Phong(NdotL0, NdotH0, specPower) * float4(g_cLightColor.rgb, 1);
	float3 light1 = 0; 
	if ( g_iNumLights > 1)
	{
		light1 = max( NdotL1, 0 ) * g_cLight1Color.rgb;
	}
#else
	float4 light0 = 1;
	float4 light1 = 0;
#endif
	
	float3 totalLight = light0.rgb + light1.rgb  + g_cAmbientColor.rgb;
	saturate(totalLight);
	Output.color.rgb = (1-lightAmount)*(light1.rgb+g_cAmbientColor.rgb)*ColorMap.rgb + lightAmount*( totalLight*ColorMap.rgb + light0.www*SpecMap.rgb );
	Output.color.a = ColorMap.a; // modulate alpha as is, shadow doesn't affect it.
	
     if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x;
    Output.pzDepth.a = Output.color.a;

    return Output;
}
#endif

#ifdef _PShadowSceneT1ReflectNoSpec
pixelOutput PixShadowSceneT1ReflectNoSpec( vertexOutputShadowT1BR In )
{
    pixelOutput Output;
    
    #ifdef HKG_SHADOWS_VSM
		float lightAmount = getLightAmountVSM( In.posLight, float4(0,0,0,1), float4(0,0,0,1), float4(0,0,0,1), In.posView );
  	#else
		float lightAmount = getLightAmountSM( In.posLight ); 
	#endif
		
	float4 ColorMap = float4(1,1,1,1);
	float3 SpecMap = g_cSpecularColor.rgb;
	float3 N = float3(0,0,1); 
	
#if ENABLE_DIFFUSE_MAP0
    ColorMap = _sample4(In.texCoord0);
#endif
		
#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		N = _sample6(In.texCoord0).xyz*2.0 - 1.0;
		N = normalize(N);
	#else
		ColorMap = _sample6(In.texCoord0);
	#endif
#endif

	float3 worldEyeVec = float3( -In.TangToWorld0.w, -In.TangToWorld1.w, -In.TangToWorld2.w ); 
	float3 worldNormal = float3( dot(In.TangToWorld0.xyz, N), dot(In.TangToWorld1.xyz, N), dot(In.TangToWorld2.xyz, N) );
	float3 reflVect = reflect( worldEyeVec, worldNormal ); 

	float4 ReflectionMap = _cubeSample5( reflVect); 

	ColorMap.rgb = ColorMap.rgb * ReflectionMap.rgb;  
	ColorMap *= g_cDiffuseColor;
	clip( ColorMap.a - ALPHA_DISCARD_TOLERANCE );


	float NdotL0;
	float NdotL1;
	float NdotH0; 
	unpackBumpLights( N, In.posView, In.L0, In.E, NdotL0, NdotL1, NdotH0);

	
#if ENABLE_LIGHTING
	float specPower = g_cSpecularPower;
	float4 light0 = Phong(NdotL0, NdotH0, specPower) * float4(g_cLightColor.rgb, 1);
	float3 light1 = 0; 
	if ( g_iNumLights > 1)
	{
		light1 = max( NdotL1, 0 ) * g_cLight1Color.rgb;
	}
#else
	float4 light0 = 1;
	float4 light1 = 0;
#endif
	
	float3 totalLight = light0.rgb + light1.rgb  + g_cAmbientColor.rgb;
	saturate(totalLight);
	Output.color.rgb = (1-lightAmount)*(light1.rgb+g_cAmbientColor.rgb)*ColorMap.rgb + lightAmount*( totalLight*ColorMap.rgb + light0.www*SpecMap.rgb );
	Output.color.a = ColorMap.a; // modulate alpha as is, shadow doesn't affect it.
	
     if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x;
    Output.pzDepth.a = Output.color.a;

    return Output;
}
#endif

#ifdef _PShadowSceneT1ReflectNoDiff
pixelOutput PixShadowSceneT1ReflectNoDiff( vertexOutputShadowT1BR In )
{
    pixelOutput Output;
    
    #ifdef HKG_SHADOWS_VSM
		float lightAmount = getLightAmountVSM( In.posLight, float4(0,0,0,1), float4(0,0,0,1), float4(0,0,0,1), In.posView );
  	#else
		float lightAmount = getLightAmountSM( In.posLight ); 
	#endif
		
	float4 ColorMap = float4(1,1,1,1);
	float3 SpecMap = g_cSpecularColor.rgb;
	float3 N = float3(0,0,1); 
			
#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		N = _sample5(In.texCoord0).xyz*2.0 - 1.0;
		N = normalize(N);
	#else
		ColorMap = _sample5(In.texCoord0);
	#endif
#endif

	float3 worldEyeVec = float3( -In.TangToWorld0.w, -In.TangToWorld1.w, -In.TangToWorld2.w ); 
	float3 worldNormal = float3( dot(In.TangToWorld0.xyz, N), dot(In.TangToWorld1.xyz, N), dot(In.TangToWorld2.xyz, N) );
	float3 reflVect = reflect( worldEyeVec, worldNormal ); 

	float4 ReflectionMap = _cubeSample4( reflVect); 

	ColorMap.rgb = ColorMap.rgb * ReflectionMap.rgb;  

#if ENABLE_SPEC_MAP
	SpecMap *= _sample5(In.texCoord0).rgb;
#endif

	ColorMap *= g_cDiffuseColor;
	clip( ColorMap.a - ALPHA_DISCARD_TOLERANCE );


	float NdotL0;
	float NdotL1;
	float NdotH0; 
	unpackBumpLights( N, In.posView, In.L0, In.E, NdotL0, NdotL1, NdotH0);

	
#if ENABLE_LIGHTING
	float specPower = g_cSpecularPower;
	float4 light0 = Phong(NdotL0, NdotH0, specPower) * float4(g_cLightColor.rgb, 1);
	float3 light1 = 0; 
	if ( g_iNumLights > 1)
	{
		light1 = max( NdotL1, 0 ) * g_cLight1Color.rgb;
	}
#else
	float4 light0 = 1;
	float4 light1 = 0;
#endif
	
	float3 totalLight = light0.rgb + light1.rgb  + g_cAmbientColor.rgb;
	saturate(totalLight);
	Output.color.rgb = (1-lightAmount)*(light1.rgb+g_cAmbientColor.rgb)*ColorMap.rgb + lightAmount*( totalLight*ColorMap.rgb + light0.www*SpecMap.rgb );
	Output.color.a = ColorMap.a; // modulate alpha as is, shadow doesn't affect it.
	
     if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x;
    Output.pzDepth.a = Output.color.a;

    return Output;
}
#endif

#ifdef _PShadowSceneT1ReflectNoDiffNoSpec
pixelOutput PixShadowSceneT1ReflectNoDiffNoSpec( vertexOutputShadowT1BR In )
{
    pixelOutput Output;
    
    #ifdef HKG_SHADOWS_VSM
		float lightAmount = getLightAmountVSM( In.posLight, float4(0,0,0,1), float4(0,0,0,1), float4(0,0,0,1), In.posView );
  	#else
		float lightAmount = getLightAmountSM( In.posLight ); 
	#endif
		
	float4 ColorMap = float4(1,1,1,1);
	float3 SpecMap = g_cSpecularColor.rgb;
	float3 N = float3(0,0,1); 
			
#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		N = _sample5(In.texCoord0).xyz*2.0 - 1.0;
		N = normalize(N);
	#else
		ColorMap = _sample5(In.texCoord0);
	#endif
#endif

	float3 worldEyeVec = float3( -In.TangToWorld0.w, -In.TangToWorld1.w, -In.TangToWorld2.w ); 
	float3 worldNormal = float3( dot(In.TangToWorld0.xyz, N), dot(In.TangToWorld1.xyz, N), dot(In.TangToWorld2.xyz, N) );
	float3 reflVect = reflect( worldEyeVec, worldNormal ); 

	float4 ReflectionMap = _cubeSample4( reflVect); 

	ColorMap.rgb = ColorMap.rgb * ReflectionMap.rgb;  
	ColorMap *= g_cDiffuseColor;
	clip( ColorMap.a - ALPHA_DISCARD_TOLERANCE );


	float NdotL0;
	float NdotL1;
	float NdotH0; 
	unpackBumpLights( N, In.posView, In.L0, In.E, NdotL0, NdotL1, NdotH0);

	
#if ENABLE_LIGHTING
	float specPower = g_cSpecularPower;
	float4 light0 = Phong(NdotL0, NdotH0, specPower) * float4(g_cLightColor.rgb, 1);
	float3 light1 = 0; 
	if ( g_iNumLights > 1)
	{
		light1 = max( NdotL1, 0 ) * g_cLight1Color.rgb;
	}
#else
	float4 light0 = 1;
	float4 light1 = 0;
#endif
	
	float3 totalLight = light0.rgb + light1.rgb  + g_cAmbientColor.rgb;
	saturate(totalLight);
	Output.color.rgb = (1-lightAmount)*(light1.rgb+g_cAmbientColor.rgb)*ColorMap.rgb + lightAmount*( totalLight*ColorMap.rgb + light0.www*SpecMap.rgb );
	Output.color.a = ColorMap.a; // modulate alpha as is, shadow doesn't affect it.
	
     if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x;
    Output.pzDepth.a = Output.color.a;

    return Output;
}
#endif

#ifdef _PShadowSceneT1ReflectMask
pixelOutput PixShadowSceneT1ReflectMask( vertexOutputShadowT1BR In )
{
    pixelOutput Output;
    
    #ifdef HKG_SHADOWS_VSM
		float lightAmount = getLightAmountVSM( In.posLight, float4(0,0,0,1), float4(0,0,0,1), float4(0,0,0,1), In.posView );
  	#else
		float lightAmount = getLightAmountSM( In.posLight ); 
	#endif
		
	float4 ColorMap = float4(1,1,1,1);
	float3 SpecMap = g_cSpecularColor.rgb;
	float3 N = float3(0,0,1); 
	
#if ENABLE_DIFFUSE_MAP0
    ColorMap = _sample4(In.texCoord0);
#endif
	
#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		N = _sample7(In.texCoord0).xyz*2.0 - 1.0;
		N = normalize(N);
	#else
		ColorMap = _sample7(In.texCoord0);
	#endif
#endif	
		
	float3 worldEyeVec = float3( -In.TangToWorld0.w, -In.TangToWorld1.w, -In.TangToWorld2.w ); 
	float3 worldNormal = float3( dot(In.TangToWorld0.xyz, N), dot(In.TangToWorld1.xyz, N), dot(In.TangToWorld2.xyz, N) );
	float3 reflVect = reflect( worldEyeVec, worldNormal ); 

	float4 ReflectionMap = _cubeSample6( reflVect); 

	float4 ReflectionMask = tex2D(g_sSamplerFive, In.texCoord0);
	ColorMap.rgb = ( (float3(1,1,1)-ReflectionMask.rgb) + ReflectionMask.rgb*ReflectionMap.rgb )*ColorMap.rgb;  

#if ENABLE_SPEC_MAP
	//XXX g_sSamplerEight..
	SpecMap *= _sample5(In.texCoord0).rgb;
#endif

	ColorMap *= g_cDiffuseColor;
	clip( ColorMap.a - ALPHA_DISCARD_TOLERANCE );

	// interp will not preserve length

	float NdotL0;
	float NdotL1;
	float NdotH0; 
	unpackBumpLights( N, In.posView, In.L0, In.E, NdotL0, NdotL1, NdotH0);

	
#if ENABLE_LIGHTING
	float specPower = g_cSpecularPower;
	float4 light0 = Phong(NdotL0, NdotH0, specPower) * float4(g_cLightColor.rgb, 1);
	float3 light1 = 0; 
	if ( g_iNumLights > 1)
	{
		light1 = max( NdotL1, 0 ) * g_cLight1Color.rgb;
	}
#else
	float4 light0 = 1;
	float4 light1 = 0;
#endif
	
	float3 totalLight = light0.rgb + light1.rgb  + g_cAmbientColor.rgb;
	saturate(totalLight);
	Output.color.rgb = (1-lightAmount)*(light1.rgb+g_cAmbientColor.rgb)*ColorMap.rgb + lightAmount*( totalLight*ColorMap.rgb + light0.www*SpecMap.rgb );
	Output.color.a = ColorMap.a; // modulate alpha as is, shadow doesn't affect it.
	
	   if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x;
    Output.pzDepth.a = Output.color.a;

    return Output;
}
#endif


#ifdef _PShadowSceneT2ReflectMask
pixelOutput PixShadowSceneT2ReflectMask( vertexOutputShadowT2BR In )
{
    pixelOutput Output;
    
    #ifdef HKG_SHADOWS_VSM
		float lightAmount = getLightAmountVSM( In.posLight, float4(0,0,0,1), float4(0,0,0,1), float4(0,0,0,1), In.posView );
  	#else
		float lightAmount = getLightAmountSM( In.posLight ); 
	#endif
		
	float4 ColorMap = float4(1,1,1,1);
	float3 SpecMap = g_cSpecularColor.rgb;
	float3 N = float3(0,0,1); 
	
	float2 tc0 = In.texCoord01.xy;
	float2 tc1 = In.texCoord01.zw;
	
#if ENABLE_DIFFUSE_MAP0
    ColorMap = _sample4(tc0);
#endif
		
#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		N = _sample7(tc0).xyz*2.0 - 1.0;
		N = normalize(N);
	#else
		ColorMap = _sample7(tc0);
	#endif
#endif

	float3 worldEyeVec = float3( -In.TangToWorld0.w, -In.TangToWorld1.w, -In.TangToWorld2.w ); 
	float3 worldNormal = float3( dot(In.TangToWorld0.xyz, N), dot(In.TangToWorld1.xyz, N), dot(In.TangToWorld2.xyz, N) );
	float3 reflVect = reflect( worldEyeVec, worldNormal ); 

	float4 ReflectionMap = _cubeSample6( reflVect); 

	float4 ReflectionMask = _sample5(tc1);
	ColorMap.rgb = (1-ReflectionMask.rgb)*ColorMap.rgb + ReflectionMask.rgb*ReflectionMap.rgb*ColorMap.rgb;  
	

#if ENABLE_SPEC_MAP
	//XX
	SpecMap *= _sample5(tc0).rgb;
#endif

	ColorMap *= g_cDiffuseColor;
	clip( ColorMap.a - ALPHA_DISCARD_TOLERANCE );


	float NdotL0;
	float NdotL1;
	float NdotH0; 
	unpackBumpLights( N, In.posView, In.L0, In.E, NdotL0, NdotL1, NdotH0);

	
#if ENABLE_LIGHTING
	float specPower = g_cSpecularPower;
	float4 light0 = Phong(NdotL0, NdotH0, specPower) * float4(g_cLightColor.rgb, 1);
	float3 light1 = 0; 
	if ( g_iNumLights > 1)
	{
		light1 = max( NdotL1, 0 ) * g_cLight1Color.rgb;
	}
#else
	float4 light0 = 1;
	float4 light1 = 0;
#endif
	
	float3 totalLight = light0.rgb + light1.rgb  + g_cAmbientColor.rgb;
	saturate(totalLight);
	Output.color.rgb = (1-lightAmount)*(light1.rgb+g_cAmbientColor.rgb)*ColorMap.rgb + lightAmount*( totalLight*ColorMap.rgb + light0.www*SpecMap.rgb );

	Output.color.a = ColorMap.a; // modulate alpha as is, shadow doesn't affect it.


    if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x;
    Output.pzDepth.a = Output.color.a;

    return Output;
}

#endif
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
