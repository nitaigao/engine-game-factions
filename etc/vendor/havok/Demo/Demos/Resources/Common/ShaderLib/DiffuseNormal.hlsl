/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

//
// One diffuse map along with a normal map, with and without shadows. A common demo shader
// with 'proper' assets 
//
//:STYLE VertOneLightBump PixT1Bump LD1 T1 DIFFUSE0 NORMAL0
//:STYLE VertOneLightBumpShadowProj PixShadowSceneT1Bump LD1 T1 SHADOWMAP DIFFUSE0 NORMAL0

//:STYLE VertOneLightBump PixT1Bump LD2 T1 DIFFUSE0 NORMAL0
//:STYLE VertOneLightBumpShadowProj PixShadowSceneT1Bump LD2 T1 SHADOWMAP DIFFUSE0 NORMAL0

//:STYLE VertOneLightBump PixT1BumpND LD1 T1 NORMAL0
//:STYLE VertOneLightBumpShadowProj PixShadowSceneT1BumpND LD1 T1 SHADOWMAP NORMAL0

//:STYLE VertOneLightBump PixT1BumpND LD2 T1 NORMAL0
//:STYLE VertOneLightBumpShadowProj PixShadowSceneT1BumpND LD2 T1 SHADOWMAP NORMAL0

//:STYLE VertOneLightBump PixT1Bump LD1 T1 DIFFUSE0 NORMAL0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpShadowProj PixShadowSceneT1Bump LD1 T1 SHADOWMAP DIFFUSE0 NORMAL0 INSTANCED DEFINE:HKG_INSTANCING

//:STYLE VertOneLightBump PixT1Bump LD2 T1 DIFFUSE0 NORMAL0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpShadowProj PixShadowSceneT1Bump LD2 T1 SHADOWMAP DIFFUSE0 NORMAL0 INSTANCED DEFINE:HKG_INSTANCING

//:STYLE VertOneLightBump PixT1BumpND LD1 T1 NORMAL0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpShadowProj PixShadowSceneT1BumpND LD1 T1 SHADOWMAP NORMAL0 INSTANCED DEFINE:HKG_INSTANCING

//:STYLE VertOneLightBump PixT1BumpND LD2 T1 NORMAL0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightBumpShadowProj PixShadowSceneT1BumpND LD2 T1 SHADOWMAP NORMAL0 INSTANCED DEFINE:HKG_INSTANCING

// Destruction's Atlas style (so 2 tex coords)
//:STYLE VertOneLightBump PixT1Bump LD1 T2 DIFFUSE0 NORMAL1 DEFINE:TWO_TCOORDS
//:STYLE VertOneLightBumpShadowProj PixShadowSceneT1Bump LD1 T2 SHADOWMAP DIFFUSE0 NORMAL1 DEFINE:TWO_TCOORDS

//:STYLE VertOneLightBump PixT1Bump LD2 T2 DIFFUSE0 NORMAL1 DEFINE:TWO_TCOORDS
//:STYLE VertOneLightBumpShadowProj PixShadowSceneT1Bump LD2 T2 SHADOWMAP DIFFUSE0 NORMAL1 DEFINE:TWO_TCOORDS

//:STYLE VertOneLightBump PixT1Bump LD1 T2 DIFFUSE0 NORMAL1 INSTANCED DEFINE:HKG_INSTANCING DEFINE:TWO_TCOORDS
//:STYLE VertOneLightBumpShadowProj PixShadowSceneT1Bump LD1 T2 SHADOWMAP DIFFUSE0 NORMAL1 INSTANCED DEFINE:HKG_INSTANCING DEFINE:TWO_TCOORDS

//:STYLE VertOneLightBump PixT1Bump LD2 T2 DIFFUSE0 NORMAL1 INSTANCED DEFINE:HKG_INSTANCING DEFINE:TWO_TCOORDS
//:STYLE VertOneLightBumpShadowProj PixShadowSceneT1Bump LD2 T2 SHADOWMAP DIFFUSE0 NORMAL1 INSTANCED DEFINE:HKG_INSTANCING DEFINE:TWO_TCOORDS


#include "CommonHeader.hlslh"


// extra matrices
float4x4 g_mWorldInv;
float4x4 g_mWorldView		: WorldView;
float4x4 g_mProj			: Proj;
float4x4 g_mViewInv			: ViewInverse;
 
// Vertex Shaders
#ifdef TWO_TCOORDS
vertexOutputT2B VertOneLightBump( vertexInputT2B In )
{
	vertexOutputT2B Out;
#else
vertexOutputT1B VertOneLightBump( vertexInputT1B In )
{
	vertexOutputT1B Out;
#endif

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
#ifdef TWO_TCOORDS
    Out.texCoord0 = In.texCoord0;
	Out.texCoord1 = In.texCoord1;
#else
	Out.texCoord0 = In.texCoord0;
#endif

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
#ifdef TWO_TCOORDS
vertexOutputShadowT2B VertOneLightBumpShadowProj( vertexInputT2B In) 
{
    vertexOutputShadowT2B Output;
#else
vertexOutputShadowT1B VertOneLightBumpShadowProj( vertexInputT1B In) 
{
    vertexOutputShadowT1B Output;

#endif

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
    
#ifdef TWO_TCOORDS
    Output.texCoord01.xy = In.texCoord0;
	Output.texCoord01.zw = In.texCoord1;
#else
	Output.texCoord0 = In.texCoord0;
#endif
	
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
	
//////////////////////////////////////////////////////////////////
//
// Pixel Shaders
//


// Pixel shaders
#ifdef TWO_TCOORDS
pixelOutput PixT1Bump( vertexOutputT2B In )
{
#else
pixelOutput PixT1Bump( vertexOutputT1B In )
{
#endif

	float4 ColorMap = float4(1,1,1,1);
	float3 N = float3(0,0,1); 
	
#if ENABLE_DIFFUSE_MAP
    ColorMap = _sample0( In.texCoord0);
#endif

#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		#ifdef TWO_TCOORDS
			N = _sample1(In.texCoord1).xyz*2.0 - 1.0;
		#else
			N = _sample1(In.texCoord0).xyz*2.0 - 1.0;
		#endif
		N = normalize(N);
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
	
	Output.color.rgb = negLight*g_cAmbientColor.rgb*ColorMap.rgb + totalLight*ColorMap.rgb + light0.www*g_cSpecularColor.rgb;
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
pixelOutput PixT1BumpND( vertexOutputT1B In )
{

	float4 ColorMap = g_cDiffuseColor;
	clip( ColorMap.a - ALPHA_DISCARD_TOLERANCE );

	float3 N = float3(0,0,1); 
	
#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		N = _sample0(In.texCoord0).xyz*2.0 - 1.0;
		N = normalize(N);
	#endif
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
	
	Output.color.rgb = negLight*g_cAmbientColor.rgb*ColorMap.rgb + totalLight*ColorMap.rgb + light0.www*g_cSpecularColor.rgb;
	Output.color.a = ColorMap.a; // modulate alpha as is, light doesn't affect it.
	if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
	
	Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x ;
    Output.pzDepth.a = Output.color.a;

    return Output; 
}
 
#ifdef TWO_TCOORDS
pixelOutput PixShadowSceneT1Bump( vertexOutputShadowT2B In )
{
#else
pixelOutput PixShadowSceneT1Bump( vertexOutputShadowT1B In )
{
#endif
	pixelOutput Output;
    
    #ifdef HKG_SHADOWS_VSM
		float lightAmount = getLightAmountVSM( In.posLight, In.posLight1, In.posLight2, In.posLight3, In.posView );
    #else
		float lightAmount = getLightAmountSM( In.posLight ); 
	#endif
		
	float4 ColorMap = float4(1,1,1,1);
	float3 N = float3(0,0,1); 
	
#if ENABLE_DIFFUSE_MAP
	#ifdef TWO_TCOORDS
		ColorMap = _sample4(In.texCoord01.xy);
	#else
		ColorMap = _sample4(In.texCoord0);
	#endif
#endif

#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		#ifdef TWO_TCOORDS
			N = _sample5(In.texCoord01.zw).xyz*2.0 - 1.0;
		#else
			N = _sample5(In.texCoord0).xyz*2.0 - 1.0;
		#endif	
		N = normalize(N);
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
		light1 = max( NdotL1, 0 ) * g_cLight1Color.rgb;
	}
#else
	float4 light0 = 1;
	float4 light1 = 0;
#endif
	
	float3 totalLight = light0.rgb + light1.rgb  + g_cAmbientColor.rgb;
	saturate(totalLight);
	Output.color.rgb = (1-lightAmount)*(light1.rgb+g_cAmbientColor.rgb)*ColorMap.rgb + lightAmount*( totalLight*ColorMap.rgb + light0.www*g_cSpecularColor.rgb );
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

	float3 N = float3(0,0,1); 
	
#if ENABLE_NORMAL_MAP
	#if ENABLE_LIGHTING
		N = _sample4(In.texCoord0).xyz*2.0 - 1.0;
		N = normalize(N);
	#endif
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
		light1 = max( NdotL1, 0 ) * g_cLight1Color.rgb;
	}
#else
	float4 light0 = 1;
	float4 light1 = 0;
#endif
	
	float3 totalLight = light0.rgb + light1.rgb  + g_cAmbientColor.rgb;
	saturate(totalLight);
	Output.color.rgb = (1-lightAmount)*(light1.rgb+g_cAmbientColor.rgb)*ColorMap.rgb + lightAmount*( totalLight*ColorMap.rgb + light0.www*g_cSpecularColor.rgb );
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
