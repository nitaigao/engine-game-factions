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
//:STYLE VertOneLightBumpT1 PixT1BumpND LD1 T1 NORMAL0 SPECULAR0 
//:STYLE VertOneLightBumpT1 PixT1Bump LD1 T1 DIFFUSE0 NORMAL0 SPECULAR0
//:STYLE VertOneLightBumpT1 PixT1Bump LD1 T1 DIFFUSE0 NORMAL0 SPECULAR0 GLOSS0
//:STYLE VertOneLightBumpT2 PixT2Bump LD1 T2 DIFFUSE0 DIFFUSE1 NORMAL0 SPECULAR0
//:STYLE VertOneLightBumpT1 PixT2Bump LD1 T1 DIFFUSE0 DIFFUSE0 NORMAL0 DEFINE:DECAL DEFINE:NO_SPEC
//:STYLE VertOneLightBumpT2 PixT2Bump LD1 T2 DIFFUSE0 DIFFUSE1 NORMAL0 
//:STYLE VertOneLightBumpT1 PixT2Bump LD1 T1 DIFFUSE0 DIFFUSE0 NORMAL0 SPECULAR0 DEFINE:DECAL
//:STYLE VertOneLightBumpT2 PixT2Bump LD1 T2 DIFFUSE0 DIFFUSE1 NORMAL0 SPECULAR0 GLOSS0
//:STYLE VertOneLightBumpT2 PixT2BumpLM LD1 T2 DIFFUSE0 LIGHTMAP1 NORMAL0 SPECULAR0
//:STYLE VertOneLightBumpT2 PixT2BumpLM LD1 T2 DIFFUSE0 LIGHTMAP1 NORMAL0 SPECULAR0 GLOSS0
//:STYLE VertOneLightBumpShadowProjT1 PixShadowSceneT1BumpND LD1 T1 SHADOWMAP NORMAL0 SPECULAR0
//:STYLE VertOneLightBumpShadowProjT1 PixShadowSceneT1Bump LD1 T1 SHADOWMAP DIFFUSE0 NORMAL0 SPECULAR0
//:STYLE VertOneLightBumpShadowProjT1 PixShadowSceneT1Bump LD1 T1 SHADOWMAP DIFFUSE0 NORMAL0 SPECULAR0 GLOSS0
//:STYLE VertOneLightBumpShadowProjT1 PixShadowSceneT1Bump LD1 T1 SHADOWMAP DIFFUSE0 DIFFUSE0 NORMAL0 DEFINE:DECAL DEFINE:NO_SPEC
//:STYLE VertOneLightBumpShadowProjT2 PixShadowSceneT2Bump LD1 T2 SHADOWMAP DIFFUSE0 DIFFUSE1 NORMAL0
//:STYLE VertOneLightBumpShadowProjT1 PixShadowSceneT1Bump LD1 T1 SHADOWMAP DIFFUSE0 DIFFUSE0 NORMAL0 SPECULAR0 DEFINE:DECAL
//:STYLE VertOneLightBumpShadowProjT2 PixShadowSceneT2Bump LD1 T2 SHADOWMAP DIFFUSE0 DIFFUSE1 NORMAL0 SPECULAR0
//:STYLE VertOneLightBumpShadowProjT2 PixShadowSceneT2Bump LD1 T2 SHADOWMAP DIFFUSE0 DIFFUSE1 NORMAL0 SPECULAR0 GLOSS0
//:STYLE VertOneLightBumpShadowProjT2 PixShadowSceneT2BumpLM LD1 T2 SHADOWMAP DIFFUSE0 LIGHTMAP1 NORMAL0 SPECULAR0
//:STYLE VertOneLightBumpShadowProjT2 PixShadowSceneT2BumpLM LD1 T2 SHADOWMAP DIFFUSE0 LIGHTMAP1 NORMAL0 SPECULAR0 GLOSS0

//:STYLE VertOneLightBumpT1 PixT1BumpND LD1 T1 NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpT1 PixT1Bump LD1 T1 DIFFUSE0 NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpT1 PixT1Bump LD1 T1 DIFFUSE0 NORMAL0 SPECULAR0 GLOSS0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpT2 PixT2Bump LD1 T2 DIFFUSE0 DIFFUSE1 NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpT1 PixT2Bump LD1 T1 DIFFUSE0 DIFFUSE0 NORMAL0 INSTANCED DEFINE:HKG_INSTANCING DEFINE:DECAL DEFINE:NO_SPEC
//:STYLE VertOneLightBumpT2 PixT2Bump LD1 T2 DIFFUSE0 DIFFUSE1 NORMAL0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpT1 PixT2Bump LD1 T1 DIFFUSE0 DIFFUSE0 NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_INSTANCING DEFINE:DECAL 
//:STYLE VertOneLightBumpT2 PixT2Bump LD1 T2 DIFFUSE0 DIFFUSE1 NORMAL0 SPECULAR0 GLOSS0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpT2 PixT2BumpLM LD1 T2 DIFFUSE0 LIGHTMAP1 NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpT2 PixT2BumpLM LD1 T2 DIFFUSE0 LIGHTMAP1 NORMAL0 SPECULAR0 GLOSS0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpShadowProjT1 PixShadowSceneT1BumpND LD1 T1 SHADOWMAP NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpShadowProjT1 PixShadowSceneT1Bump LD1 T1 SHADOWMAP DIFFUSE0 NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpShadowProjT1 PixShadowSceneT1Bump LD1 T1 SHADOWMAP DIFFUSE0 NORMAL0 SPECULAR0 GLOSS0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpShadowProjT1 PixShadowSceneT1Bump LD1 T1 SHADOWMAP DIFFUSE0 DIFFUSE0 NORMAL0 INSTANCED DEFINE:HKG_INSTANCING DEFINE:DECAL DEFINE:NO_SPEC 
//:STYLE VertOneLightBumpShadowProjT2 PixShadowSceneT2Bump LD1 T2 SHADOWMAP DIFFUSE0 DIFFUSE1 NORMAL0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpShadowProjT1 PixShadowSceneT1Bump LD1 T1 SHADOWMAP DIFFUSE0 DIFFUSE0 NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_INSTANCING DEFINE:DECAL 
//:STYLE VertOneLightBumpShadowProjT2 PixShadowSceneT2Bump LD1 T2 SHADOWMAP DIFFUSE0 DIFFUSE1 NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpShadowProjT2 PixShadowSceneT2Bump LD1 T2 SHADOWMAP DIFFUSE0 DIFFUSE1 NORMAL0 SPECULAR0 GLOSS0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpShadowProjT2 PixShadowSceneT2BumpLM LD1 T2 SHADOWMAP DIFFUSE0 LIGHTMAP1 NORMAL0 SPECULAR0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpShadowProjT2 PixShadowSceneT2BumpLM LD1 T2 SHADOWMAP DIFFUSE0 LIGHTMAP1 NORMAL0 SPECULAR0 GLOSS0 INSTANCED DEFINE:HKG_INSTANCING


#include "CommonHeader.hlslh"
#include "CommonSampleHeader.hlslh"

// Matrices
float4x4 g_mWorldInv;
float4x4 g_mWorldView		: WorldView;
float4x4 g_mProj			: Proj;
float4x4 g_mViewInv			: ViewInverse;

// Vertex Shaders
vertexOutputT2B VertOneLightBumpT2( vertexInputT2B In )
{
	vertexOutputT2B Out;

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
	Out.texCoord1 = In.texCoord1;
	
	// transform position to clip space
	Out.position = mul( viewPos, g_mProj);
   
	// compute the 3x3 tranform from object space to tangent space
	float3x3 objToTangentSpace;
	
	float bumpHeight = 1.0f;
		
	objToTangentSpace[0] = In.tangent * bumpHeight;
	objToTangentSpace[1] = In.binormal * bumpHeight;
	objToTangentSpace[2] = In.normal;
	
	// light vector
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
    Out.position = mul( viewPos, g_mProj);
   
	// compute the 3x3 tranform from object space to tangent space
	float3x3 objToTangentSpace;
	
	float bumpHeight = 1.0f;
		
	objToTangentSpace[0] = In.tangent * bumpHeight;
	objToTangentSpace[1] = In.binormal * bumpHeight;
	objToTangentSpace[2] = In.normal;
	

	// light vector
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
vertexOutputShadowT2B VertOneLightBumpShadowProjT2( vertexInputT2B In) 
{
    vertexOutputShadowT2B Output;
    
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
    
    Output.texCoord01.xy = In.texCoord0.xy;
	Output.texCoord01.zw = In.texCoord1.xy;
		 
		// project pos into light space
    Output.posLight = mul( viewPos, g_mViewToLightProj );
     
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
	
    // light vector
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
	
	// light vector
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
pixelOutput PixT2Bump( vertexOutputT2B In )
{
	float4 ColorMap = float4(1,1,1,1);
	float3 SpecMap = g_cSpecularColor.rgb;
	float3 N = float3(0,0,1); 
	
#if ENABLE_DIFFUSE_MAP0
    ColorMap = _sample0(In.texCoord0);
#endif

#if ENABLE_DIFFUSE_MAP1
	#if ENABLE_DIFFUSE_MAP0
		ColorMap = ColorMap + (_sample1(In.texCoord1) * 0.6);
	#else
		ColorMap = _sample1(In.texCoord1);
	#endif
#endif
	
#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		N = _sample2( In.texCoord0).xyz*2.0 - 1.0;
		N = normalize(N);
	#else
		ColorMap = _sample2(In.texCoord0);
	#endif
#endif

#ifndef NO_SPEC
	SpecMap *= _sample3( In.texCoord0).rgb;
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
	float3 totalLight = light0.rgb + light1.rgb;
	saturate(totalLight);
	float3 negLight = float3(1,1,1) - totalLight;
	
	Output.color.rgb = negLight*g_cAmbientColor.rgb*ColorMap.rgb + totalLight*ColorMap.rgb + light0.www*SpecMap;
	Output.color.a = ColorMap.a; // modulate alpha as is, light doesn't affect it.
	if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
	}

	Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x ;
    Output.pzDepth.a = Output.color.a;

    return Output; 
}


// Pixel shaders
pixelOutput PixT2BumpLM( vertexOutputT2B In )
{
	float4 ColorMap = float4(1,1,1,1);
	float3 SpecMap = g_cSpecularColor.rgb;
	float3 LightMap = float3(1,1,1);
	float3 N = float3(0,0,1); 
	
#if ENABLE_DIFFUSE_MAP0
    ColorMap = _sample0( In.texCoord0);
#endif

#if ENABLE_LIGHT_MAP
	LightMap = _sample1( In.texCoord1).rgb;
#endif

#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		N = _sample2(In.texCoord0).xyz*2.0 - 1.0;
		N = normalize(N);
	#else
		ColorMap = _sample2(In.texCoord0);
	#endif
#endif

#ifndef NO_SPEC
	SpecMap *= _sample3(In.texCoord0).rgb;
#endif
	
	ColorMap *= g_cDiffuseColor;
	clip( ColorMap.a - ALPHA_DISCARD_TOLERANCE );


	// Green == 59% of the perceived luminosity, while the red and blue channels account for just 30% and 11%
	float luminosity = (LightMap.r*0.33 + LightMap.g*0.59 + LightMap.b*0.11);
	luminosity = saturate( luminosity );
	
	float lightMapShadow = 1 - (luminosity * 0.5); // 1 when in dark areas
	

	float NdotL0;
	float NdotL1;
	float NdotH0; 
	unpackBumpLights( N, In.posView, In.L0, In.E, NdotL0, NdotL1, NdotH0);

#if ENABLE_LIGHTING
	float4 light0 = Phong(NdotL0, NdotH0, g_cSpecularPower) * float4(g_cLightColor.rgb,1);
//	float3 light1 = 0;
//	if ( g_iNumLights > 1)
//	{
//		light1.rgb = max( NdotL1, 0 ) * g_cLight1Color.rgb;
//	}
#else
	float4 light0 = 1;
//	float3 light1 = 0;
#endif
	
	light0 *= luminosity;
	
	pixelOutput Output;
	Output.color.rgb = (1-lightMapShadow)*ColorMap.rgb*LightMap.rgb*0.3 + lightMapShadow*ColorMap.rgb*LightMap.rgb + (light0.www*lightMapShadow*SpecMap.rgb);
	Output.color.a = ColorMap.a; // modulate alpha as is, light doesn't affect it.
	if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }

	Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x ;
    Output.pzDepth.a = Output.color.a;

    return Output; 
}
 
 // Pixel shaders
pixelOutput PixT1Bump( vertexOutputT1B In )
{
	float4 ColorMap = float4(1,1,1,1);
	float3 SpecMap = 0;
	float3 N = float3(0,0,1); 
	
    ColorMap = _sample0(In.texCoord0);
	float4 DecalMap = 1;

#ifdef DECAL

	DecalMap = _sample1(In.texCoord0);

	N = _sample2(In.texCoord0).xyz*2.0 - 1.0;
	N = normalize(N);

#ifndef NO_SPEC
	SpecMap = _sample3(In.texCoord0).rgb * g_cSpecularColor.rgb;
#endif

#else

	N = _sample1(In.texCoord0).xyz*2.0 - 1.0;
	N = normalize(N);

#ifndef NO_SPEC
	SpecMap = _sample2(In.texCoord0).rgb * g_cSpecularColor.rgb;
#endif
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

	float3 totalLight = light0.rgb + light1.rgb;
	saturate(totalLight);
	float3 negLight = float3(1,1,1) - totalLight;
	Output.color.rgb = (negLight*g_cAmbientColor.rgb*ColorMap.rgb + totalLight*ColorMap.rgb + light0.www*SpecMap) * ( DecalMap.rgb );
	Output.color.a = ColorMap.a; // modulate alpha as is, light doesn't affect it.
	if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }

    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x;
    Output.pzDepth.a = Output.color.a;

    return Output; 
}

 // Pixel shaders
pixelOutput PixT1BumpND( vertexOutputT1B In )
{
	float4 ColorMap = g_cDiffuseColor;
	clip( ColorMap.a - ALPHA_DISCARD_TOLERANCE );

	float3 SpecMap = g_cSpecularColor.rgb;
	float3 N = float3(0,0,1); 
		
#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		N = _sample0( In.texCoord0).xyz*2.0 - 1.0;
		N = normalize(N);
	#else
		ColorMap *= _sample0( In.texCoord0);
	#endif
#endif



#ifndef NO_SPEC
	SpecMap *= _sample1(In.texCoord0).rgb;
#endif

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

	float3 totalLight = light0.rgb + light1.rgb;
	saturate(totalLight);
	float3 negLight = float3(1,1,1) - totalLight;
	Output.color.rgb = negLight*g_cAmbientColor.rgb*ColorMap.rgb + totalLight*ColorMap.rgb + light0.www*SpecMap;
	Output.color.a = ColorMap.a; // modulate alpha as is, light doesn't affect it.
	if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }

    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x;
    Output.pzDepth.a = Output.color.a;

    return Output; 
}


pixelOutput PixShadowSceneT2Bump( vertexOutputShadowT2B In )
{
    pixelOutput Output;
    
    #ifdef HKG_SHADOWS_VSM
		float lightAmount = getLightAmountVSM( In.posLight, In.posLight1, In.posLight2, In.posLight3, In.posView.xyz );
   #else
		float lightAmount = getLightAmountSM( In.posLight ); 
	#endif
		
	float4 ColorMap = float4(1,1,1,1);
	float3 SpecMap = g_cSpecularColor.rgb;
	float3 N = float3(0,0,1); 
	
#if ENABLE_DIFFUSE_MAP0
    ColorMap = _sample4(In.texCoord01.xy);
#endif

#if ENABLE_DIFFUSE_MAP1
	#if ENABLE_DIFFUSE_MAP0
		ColorMap = ColorMap + (_sample5(In.texCoord01.zw) * 0.6);
	#else
		ColorMap = _sample5(In.texCoord01.zw);
	#endif
#endif
		
#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		N = _sample6(In.texCoord01.xy).xyz*2.0 - 1.0;
		N = normalize(N);
	#else
		ColorMap = _sample6( In.texCoord01.xy);
	#endif
#endif

#ifndef NO_SPEC
	SpecMap *= _sample7(In.texCoord01.xy).rgb;
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
	
	float3 totalLight = light0.rgb + light1.rgb + g_cAmbientColor.rgb;
	saturate(totalLight);
	Output.color.rgb = (1-lightAmount)*(light1.rgb+g_cAmbientColor.rgb)*ColorMap.rgb + lightAmount*( totalLight*ColorMap.rgb + light0.www*SpecMap );
	Output.color.a = ColorMap.a; // modulate alpha as is, shadow doesn't affect it.
	
    if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x ;
    Output.pzDepth.a = Output.color.a;

    return Output;
}


pixelOutput PixShadowSceneT1Bump( vertexOutputShadowT1B In )
{
    pixelOutput Output;
    
    #ifdef HKG_SHADOWS_VSM
		float lightAmount = getLightAmountVSM( In.posLight, In.posLight1, In.posLight2, In.posLight3, In.posView );
  	#else
		float lightAmount = getLightAmountSM( In.posLight ); 
	#endif
		
	float3 N = float3(0,0,1); 
	
    float3 SpecMap = 0;

#ifdef DECAL
	
	float4 DecalMap = _sample5(In.texCoord0);
	float4 ColorMap = _sample4(In.texCoord0);
	
	N = _sample6(In.texCoord0).xyz*2.0 - 1.0;
	N = normalize(N);

#ifndef NO_SPEC
	SpecMap = _sample7(In.texCoord0).rgb * g_cSpecularColor.rgb;
#endif

#else
	float4 DecalMap = 1;
	float4 ColorMap = _sample4(In.texCoord0);

	N = _sample5(In.texCoord0).xyz*2.0 - 1.0;
	N = normalize(N);

#ifndef NO_SPEC
	SpecMap = _sample6(In.texCoord0).rgb * g_cSpecularColor.rgb;
#endif

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
	
	float3 totalLight = light0.rgb + light1.rgb + g_cAmbientColor.rgb;
	saturate(totalLight);
	Output.color.rgb = ((1-lightAmount)*(light1.rgb+g_cAmbientColor.rgb)*ColorMap.rgb + lightAmount*( totalLight*ColorMap.rgb + light0.www*SpecMap )) * DecalMap.rgb;
	Output.color.a = ColorMap.a; // modulate alpha as is, shadow doesn't affect it.
	
    if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x;
    Output.pzDepth.a = Output.color.a;

    return Output;
}


pixelOutput PixShadowSceneT1BumpND( vertexOutputShadowT1B In )
{
    pixelOutput Output;
    
    #ifdef HKG_SHADOWS_VSM
		float lightAmount = getLightAmountVSM( In.posLight, In.posLight1, In.posLight2, In.posLight3, In.posView );
  	#else
		float lightAmount = getLightAmountSM( In.posLight ); 
	#endif
		
	float4 ColorMap = g_cDiffuseColor;
	clip( ColorMap.a - ALPHA_DISCARD_TOLERANCE );

	float3 SpecMap = g_cSpecularColor.rgb;
	float3 N = float3(0,0,1); 
			
#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		N = _sample4(In.texCoord0).xyz*2.0 - 1.0;
		N = normalize(N);
	#else
		ColorMap *= _sample4(In.texCoord0);
	#endif
#endif

#ifndef NO_SPEC
	SpecMap *= _sample5(In.texCoord0).rgb;
#endif

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
	
	float3 totalLight = light0.rgb + light1.rgb + g_cAmbientColor.rgb;
	saturate(totalLight);
	Output.color.rgb = (1-lightAmount)*(light1.rgb+g_cAmbientColor.rgb)*ColorMap.rgb + lightAmount*( totalLight*ColorMap.rgb + light0.www*SpecMap );
	Output.color.a = ColorMap.a; // modulate alpha as is, shadow doesn't affect it.
	
    if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x;
    Output.pzDepth.a = Output.color.a;

    return Output;
}



pixelOutput PixShadowSceneT2BumpLM( vertexOutputShadowT2B In )
{
    pixelOutput Output;
    
    #ifdef HKG_SHADOWS_VSM
		float shadowAmount = getLightAmountVSM( In.posLight, In.posLight1, In.posLight2, In.posLight3, In.posView);
    #else
		float shadowAmount = getLightAmountSM( In.posLight ); 
	#endif
		
	float4 ColorMap = float4(1,1,1,1);
	float3 SpecMap = g_cSpecularColor.rgb;
	float3 LightMap = float3(1,1,1);
	float3 N = float3(0,0,1); 
	
#if ENABLE_DIFFUSE_MAP0
    ColorMap = _sample4(In.texCoord01.xy);
#endif

#if ENABLE_LIGHT_MAP
    LightMap = _sample5(In.texCoord01.zw);
#endif
		
#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		N = _sample6(In.texCoord01.xy).xyz*2.0 - 1.0;
		N = normalize(N);
	#else
		ColorMap = _sample6( In.texCoord01.xy);
	#endif
#endif

#ifndef NO_SPEC
	SpecMap *= _sample7( In.texCoord01.xy).rgb;
#endif

	ColorMap *= g_cDiffuseColor;
	clip( ColorMap.a - ALPHA_DISCARD_TOLERANCE );

	// Green == 59% of the perceived luminosity, while the red and blue channels account for just 30% and 11%
	float luminosity = (LightMap.r*0.33 + LightMap.g*0.59 + LightMap.b*0.11);
	luminosity = saturate( luminosity );
	
	float lightMapShadow = 1 - (luminosity * 0.5); // 1 when in dark areas
	shadowAmount = max( shadowAmount, lightMapShadow ); // don't have dark shadows in dark lightmap areas
	
	float NdotL0;
	float NdotL1;
	float NdotH0; 
	unpackBumpLights( N, In.posView, In.L0, In.E, NdotL0, NdotL1, NdotH0);

#if ENABLE_LIGHTING
	float4 light0 = Phong(NdotL0, NdotH0, g_cSpecularPower) * float4(g_cLightColor.rgb,1);
//	float3 light1 = 0;
//	if ( g_iNumLights > 1)
//	{
//		light1.rgb = max( NdotL1, 0 ) * g_cLight1Color.rgb;
//	}
#else
	float4 light0 = 1;
//	float3 light1 = 0;
#endif
	
	// Discard normal map and spec map in darker areas
	light0 *= luminosity; // don't want spec etc in dark areas
		
	Output.color.rgb = (1-shadowAmount)*ColorMap.rgb*LightMap.rgb*0.3 + shadowAmount*ColorMap.rgb*LightMap.rgb + (light0.www*SpecMap*shadowAmount);
	Output.color.a = ColorMap.a; // modulate alpha as is, shadow doesn't affect it.
	
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
