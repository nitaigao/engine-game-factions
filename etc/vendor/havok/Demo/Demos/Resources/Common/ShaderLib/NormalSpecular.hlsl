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
//:STYLE VertOneLightBumpT1 PixT1Bump LD1 T1 NORMAL0 SPECULAR0
//:STYLE VertOneLightBumpShadowProjT1 PixShadowSceneT1Bump LD1 T1 SHADOWMAP NORMAL0 SPECULAR0
//:STYLE VertOneLightBumpT1 PixT1Bump LD2 T1 NORMAL0 SPECULAR0
//:STYLE VertOneLightBumpShadowProjT1 PixShadowSceneT1Bump LD2 T1 SHADOWMAP NORMAL0 SPECULAR0

//:STYLE VertOneLightBumpT1 PixT1Bump LD1 T1 NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpShadowProjT1 PixShadowSceneT1Bump LD1 T1 SHADOWMAP NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpT1 PixT1Bump LD2 T1 NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpShadowProjT1 PixShadowSceneT1Bump LD2 T1 SHADOWMAP NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_INSTANCING

#include "CommonHeader.hlslh"

// Matrices
float4x4 g_mWorldInv;
float4x4 g_mWorldView		: WorldView;
float4x4 g_mProj			: Proj;
float4x4 g_mViewInv			: ViewInverse;
 
vertexOutputT1B VertOneLightBumpT1( vertexInputT1B In )
{
	vertexOutputT1B Out;
	
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
	eyeVec = mul(eyeVec, (float3x3) world );  // transform back to object space
	
#else
	float3 worldVertPos = mul(float4(In.position.xyz , 1.0), g_mWorld).xyz;
	float4 viewPos = mul( float4(In.position.xyz, 1.0), g_mWorldView);
	float3 lightVec = mul( g_vLightDir, (float3x3)g_mWorldInv ); 
	float3 lightVec1 = mul( g_vLight1Dir, (float3x3)g_mWorldInv );  
	float3 eyeVec = g_mViewInv[3].xyz - worldVertPos.xyz; // world space eye vector
	eyeVec = mul(eyeVec, (float3x3) g_mWorldInv );  // transform back to object space
	
#endif

	// copy texture coordinates
	    
    Out.texCoord0 = In.texCoord0;
	
	// transform position to clip space
	Output.position = mul( viewPos, g_mProj);
	Output.posView = viewPos;
    
	// compute the 3x3 tranform from object space to tangent space
	float3x3 objToTangentSpace;
	
	float bumpHeight = 1.0f;
		
	objToTangentSpace[0] = In.tangent * bumpHeight;
	objToTangentSpace[1] = In.binormal * bumpHeight;
	objToTangentSpace[2] = In.normal;
	
	float3 L0 = mul( objToTangentSpace, lightVec ).xyz; // transform from object to tangent space
	float3 L1 = 0;
	if (g_iNumLights > 1)
	{
		L1 = mul( objToTangentSpace, lightVec1 ).xyz; // transform from object to tangent space
	}

	// eye vector
	float3 e = mul( objToTangentSpace, eyeVec );

	packBumpLights( L0, L1, e, viewPos, Out.posView, Out.L0, Out.E );

	return Out;
}

// Vertex based lighting (with specular), also projects the position into the shadow map space
vertexOutputShadowT1B VertOneLightBumpShadowProjT1( vertexInputT1B In) 
{
    vertexOutputShadowT1B Output;
    
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
	eyeVec = mul(eyeVec, (float3x3) world );  // transform back to object space
	
#else
	float3 worldVertPos = mul(float4(In.position.xyz , 1.0), g_mWorld).xyz;
	float4 viewPos = mul( float4(In.position.xyz, 1.0), g_mWorldView);
	float3 lightVec = mul( g_vLightDir, (float3x3)g_mWorldInv ); 
	float3 lightVec1 = mul( g_vLight1Dir, (float3x3)g_mWorldInv );  
	float3 eyeVec = g_mViewInv[3].xyz - worldVertPos.xyz; // world space eye vector
	eyeVec = mul(eyeVec, (float3x3) g_mWorldInv );  // transform back to object space
	
#endif

    Output.position = mul( viewPos, g_mProj);
    
    Output.texCoord0 = In.texCoord0;
		 
		// project pos into light space
    Output.posLight = mul( viewPos, g_mViewToLightProj );
    
    Output.posView = viewPos;
    #ifdef HKG_SHADOWS_VSM
   	    Output.posLight1 = mul( viewPos, g_mViewToLightProj1 );
		Output.posLight2 = mul( viewPos, g_mViewToLightProj2 );
		Output.posLight3 = mul( viewPos, g_mViewToLightProj3 );
    #endif
    
	// compute the 3x3 tranform from object space to tangent space
	float3x3 objToTangentSpace;
	
	float bumpHeight = 1.0f;
		
	objToTangentSpace[0] = In.tangent * bumpHeight;
	objToTangentSpace[1] = In.binormal * bumpHeight;
	objToTangentSpace[2] = In.normal;
	
    float4 vertexPos = mul(In.position, g_mWorld); // world space position

	float3 L0 = mul( objToTangentSpace, lightVec ).xyz; // transform from object to tangent space
	float3 L1 = 0;
	if (g_iNumLights > 1)
	{
		L1 = mul( objToTangentSpace, lightVec1 ).xyz; // transform from object to tangent space
	}

	// eye vector
	float3 e = mul( objToTangentSpace, eyeVec );

	packBumpLights( L0, L1, e, viewPos, Output.posView, Output.L0, Output.E );
	
	return Output;
}


// Pixel Shaders
 
 // Pixel shaders
pixelOutput PixT1Bump( vertexOutputT1B In )
{
	clip( g_cDiffuseColor.a - ALPHA_DISCARD_TOLERANCE );

	float3 SpecMap = g_cSpecularColor.rgb;
	float3 N = float3(0,0,1); 
	
#if ENABLE_NORMAL_MAP
	N = _sample0( In.texCoord0).xyz*2.0 - 1.0;
	N = normalize(N);
#endif

#if ENABLE_SPEC_MAP
	SpecMap *= _sample1( In.texCoord0).rgb;
#endif

	In.L = normalize(In.L);
	In.H = normalize(In.H);

	float NdotL = dot(N, In.L);
	float NdotH = dot(N, In.H);
#if ENABLE_LIGHTING
    float specPower = g_cSpecularPower;
    float4 light = Phong( NdotL, NdotH, specPower ) * float4(g_cLightColor.rgb, 1);
#else
	float4 light = float4(1,1,1,1);
#endif
	
	pixelOutput Output;
	Output.color.rgb = (1-light)*g_cAmbientColor.rgb*g_cDiffuseColor.rgb + light*g_cDiffuseColor.rgb + light.www*SpecMap;
	Output.color.a = g_cDiffuseColor.a; // modulate alpha as is, light doesn't affect it.
	 if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x;
    Output.pzDepth.a = Output.color.a;

    return Output; 
}

pixelOutput PixShadowSceneT1Bump( vertexOutputShadowT1B In )
{
    pixelOutput Output;

	clip( g_cDiffuseColor.a - ALPHA_DISCARD_TOLERANCE );

    #ifdef HKG_SHADOWS_VSM
		float lightAmount = getLightAmountVSM( In.posLight, In.posLight1, In.posLight2, In.posLight3, In.posView );
  	#else
		float lightAmount = getLightAmountSM( In.posLight ); 
	#endif
		
	float3 SpecMap = g_cSpecularColor.rgb;
	float3 N = float3(0,0,1); 
		
#if ENABLE_NORMAL_MAP
	N = _sample4(In.texCoord0).xyz*2.0 - 1.0;
	N = normalize(N);
#endif

#if ENABLE_SPEC_MAP
	SpecMap *= _sample5( In.texCoord0).rgb;
#endif

	// interp will not preserve length
	In.L = normalize(In.L);
	In.H = normalize(In.H);

	float NdotL = dot(N, In.L);
	float NdotH = dot(N, In.H);
	
#if ENABLE_LIGHTING
	float specPower = g_cSpecularPower;
	float4 light = lightAmount * Phong(NdotL, NdotH, specPower) * float4(g_cLightColor.rgb, 1);
#else
	float4 light = float4(1,1,1,1);
#endif
	
	Output.color.rgb = (1-light)*g_cAmbientColor*g_cDiffuseColor.rgb + light.rgb*g_cDiffuseColor.rgb + light.www*SpecMap;
	Output.color.a = g_cDiffuseColor.a; // modulate alpha as is, shadow doesn't affect it.
	
     if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x;
    Output.pzDepth.a = Output.color.a;

    return Output;
}


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
