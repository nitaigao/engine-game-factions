/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

//
// [None, one or two] diffuse maps, no normal map, with and without shadows. Vertex lit with one or two lights

//:STYLE VertOneLightT0 PixT0 LD1 T0  
//:STYLE VertOneLightShadowProjT0 PixShadowSceneT0 LD1 T0 SHADOWMAP
//:STYLE VertOneLightT1 PixT1 LD1 T1 DIFFUSE0
//:STYLE VertOneLightShadowProjT1 PixShadowSceneT1 LD1 T1 SHADOWMAP DIFFUSE0
//:STYLE VertOneLightT1 PixT1 LD1 T1 DIFFUSE0 SPECULAR0 DEFINE:USE_SPEC 
//:STYLE VertOneLightShadowProjT1 PixShadowSceneT1 LD1 T1 SHADOWMAP DIFFUSE0 SPECULAR0 DEFINE:USE_SPEC 
//:STYLE VertOneLightT2 PixT2 LD1 T2 DIFFUSE0 DIFFUSE1
//:STYLE VertOneLightShadowProjT2 PixShadowSceneT2 LD1 T2 SHADOWMAP DIFFUSE0 DIFFUSE1

//:STYLE VertOneLightT0 PixT0 LD2 T0
//:STYLE VertOneLightShadowProjT0 PixShadowSceneT0 LD2 T0 SHADOWMAP
//:STYLE VertOneLightT1 PixT1 LD2 T1 DIFFUSE0
//:STYLE VertOneLightShadowProjT1 PixShadowSceneT1 LD2 T1 SHADOWMAP DIFFUSE0
//:STYLE VertOneLightT1 PixT1 LD2 T1 DIFFUSE0 SPECULAR0 DEFINE:USE_SPEC 
//:STYLE VertOneLightShadowProjT1 PixShadowSceneT1 LD2 T1 SHADOWMAP DIFFUSE0 SPECULAR0 DEFINE:USE_SPEC 
//:STYLE VertOneLightT2 PixT2 LD2 T2 DIFFUSE0 DIFFUSE1
//:STYLE VertOneLightShadowProjT2 PixShadowSceneT2 LD2 T2 SHADOWMAP DIFFUSE0 DIFFUSE1

//:STYLE VertOneLightT0 PixT0 LD1 T0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightShadowProjT0 PixShadowSceneT0 LD1 T0 SHADOWMAP INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightT1 PixT1 LD1 T1 DIFFUSE0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightShadowProjT1 PixShadowSceneT1 LD1 T1 SHADOWMAP DIFFUSE0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightT2 PixT2 LD1 T2 DIFFUSE0 DIFFUSE1 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightShadowProjT2 PixShadowSceneT2 LD1 T2 SHADOWMAP DIFFUSE0 DIFFUSE1 INSTANCED DEFINE:HKG_INSTANCING

//:STYLE VertOneLightT0 PixT0 LD2 T0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightShadowProjT0 PixShadowSceneT0 LD2 T0 SHADOWMAP INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightT1 PixT1 LD2 T1 DIFFUSE0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightShadowProjT1 PixShadowSceneT1 LD2 T1 SHADOWMAP DIFFUSE0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightT2 PixT2 LD2 T2 DIFFUSE0 DIFFUSE1 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertOneLightShadowProjT2 PixShadowSceneT2 LD2 T2 SHADOWMAP DIFFUSE0 DIFFUSE1 INSTANCED DEFINE:HKG_INSTANCING

#include "CommonHeader.hlslh"

// extra matrices
float4x4 g_mWorldInv;
float4x4 g_mWorldView		: WorldView;
float4x4 g_mProj			: Proj;
float4x4 g_mViewInv			: ViewInverse;
 

// Vertex based lighting (with specular)
vertexOutputT0 VertOneLightT0(vertexInputT0 In) 
{
    vertexOutputT0 Output;
       
#ifdef HKG_INSTANCING
	float3x4 world;
   	world[0] = In.transformRow0;
   	world[1] = In.transformRow1;
   	world[2] = In.transformRow2;
   	//world[3] = In.transformRow3;
   	float3 worldVertPos = mul(world , float4(In.position.xyz, 1) ).xyz;
	float4 viewPos = mul( float4(worldVertPos, 1.0), g_mView);
	float3 N = mul( world, In.normal ); //assumes no scale etc
#else
	float3 worldVertPos = mul(float4(In.position.xyz , 1.0), g_mWorld).xyz;
	float4 viewPos = mul( float4(In.position.xyz, 1.0), g_mWorldView);
	float3 N = mul( In.normal, (float3x3)g_mWorldInvTranspose ); //normal vector
#endif

	Output.position = mul( viewPos, g_mProj);
    Output.posView = viewPos;
  
	//calculate our vectors N, E, L, and H
	float3 worldEyePos = g_mViewInv[3].xyz;
	float4 light0;
	float4 light1;
	LightVertex(worldVertPos, N, worldEyePos, light0, light1);
	float4 vertColor = 1;
	MaterialContribution(vertColor, light0, light1, Output.diffColor0, Output.diffColor1, Output.specCol0);

	return Output; 
}

// Vertex based lighting (with specular), also projects the position into the shadow map space
vertexOutputShadowT0 VertOneLightShadowProjT0(vertexInputT0 In) 
{
    vertexOutputShadowT0 Output;
    
  #ifdef HKG_INSTANCING
	float3x4 world;
   	world[0] = In.transformRow0;
   	world[1] = In.transformRow1;
   	world[2] = In.transformRow2;
   	//world[3] = IN.transformRow3;
   	float3 worldVertPos = mul(world , float4(In.position.xyz, 1) ).xyz;
	float4 viewPos = mul( float4(worldVertPos, 1.0), g_mView);
	float3 N = mul( world, In.normal ); //assumes no scale etc
#else
	float3 worldVertPos = mul(float4(In.position.xyz , 1.0), g_mWorld).xyz;
	float4 viewPos = mul( float4(In.position.xyz, 1.0), g_mWorldView);
	float3 N = mul( In.normal, (float3x3)g_mWorldInvTranspose ); //normal vector
#endif

    Output.position = mul( viewPos, g_mProj);
    
	// project pos into light space
    Output.posLight = mul( viewPos, g_mViewToLightProj );
    
    Output.posView = viewPos;
    #ifdef HKG_SHADOWS_VSM
        Output.posLight1 = mul( viewPos, g_mViewToLightProj1 );
		Output.posLight2 = mul( viewPos, g_mViewToLightProj2 );
		Output.posLight3 = mul( viewPos, g_mViewToLightProj3 );
	#endif
  
    // Lighting:
    
	//calculate our vectors N, E, L, and H
	float3 worldEyePos = g_mViewInv[3].xyz;
    float4 light0;
	float4 light1;
	LightVertex(worldVertPos, N, worldEyePos, light0, light1);
	float4 vertColor = float4(1,1,1,1);
	MaterialContribution(vertColor, light0, light1, Output.diffColor0, Output.diffColor1, Output.specCol0);
		
	return Output;
}

// Vertex based lighting (with specular)
vertexOutputT1 VertOneLightT1(vertexInputT1 In) 
{
    vertexOutputT1 Output;

 #ifdef HKG_INSTANCING
	float3x4 world;
   	world[0] = In.transformRow0;
   	world[1] = In.transformRow1;
   	world[2] = In.transformRow2;
   	//world[3] = In.transformRow3;
   	float3 worldVertPos = mul(world , float4(In.position.xyz, 1) ).xyz;
	float4 viewPos = mul( float4(worldVertPos, 1.0), g_mView);
	float3 N = mul( world, In.normal ); //assumes no scale etc
#else
	float3 worldVertPos = mul(float4(In.position.xyz , 1.0), g_mWorld).xyz;
	float4 viewPos = mul( float4(In.position.xyz, 1.0), g_mWorldView);
	float3 N = mul( In.normal, (float3x3)g_mWorldInvTranspose ); //normal vector
#endif
	
	Output.position = mul( viewPos, g_mProj);
	Output.posView = viewPos;
    Output.texCoord0 = In.texCoord0;
	
	//calculate our vectors N, E, L, and H
	float3 worldEyePos = g_mViewInv[3].xyz;
    float4 light0;
	float4 light1;
	LightVertex(worldVertPos, N, worldEyePos, light0, light1);
	float4 vertColor = 1;
	MaterialContribution(vertColor, light0, light1, Output.diffColor0, Output.diffColor1, Output.specCol0);
	return Output;
}

// Vertex based lighting (with specular), also projects the position into the shadow map space
vertexOutputShadowT1 VertOneLightShadowProjT1(vertexInputT1 In) 
{
    vertexOutputShadowT1 Output;
    
 #ifdef HKG_INSTANCING
	float3x4 world;
   	world[0] = In.transformRow0;
   	world[1] = In.transformRow1;
   	world[2] = In.transformRow2;
   	//world[3] = IN.transformRow3;
   	float3 worldVertPos = mul(world , float4(In.position.xyz, 1) ).xyz;
	float4 viewPos = mul( float4(worldVertPos, 1.0), g_mView);
	float3 N = mul( world, In.normal ); //assumes no scale etc
#else
	float3 worldVertPos = mul(float4(In.position.xyz , 1.0), g_mWorld).xyz;
	float4 viewPos = mul( float4(In.position.xyz, 1.0), g_mWorldView);
	float3 N = mul( In.normal, (float3x3)g_mWorldInvTranspose ); //normal vector
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
  
    // Lighting:
    
	//calculate our vectors N, E, L, and H
	float3 worldEyePos = g_mViewInv[3].xyz;
    
	float4 light0;
	float4 light1;
	LightVertex(worldVertPos, N, worldEyePos, light0, light1);
	float4 vertColor = 1;
	MaterialContribution(vertColor, light0, light1, Output.diffColor0, Output.diffColor1, Output.specCol0);
	
	return Output;
}


// Vertex based lighting (with specular)
vertexOutputT2 VertOneLightT2(vertexInputT2 In) 
{
    vertexOutputT2 Output;

#ifdef HKG_INSTANCING
	float3x4 world;
   	world[0] = In.transformRow0;
   	world[1] = In.transformRow1;
   	world[2] = In.transformRow2;
   	//world[3] = IN.transformRow3;
   	float3 worldVertPos = mul(world , float4(In.position.xyz, 1) ).xyz;
	float4 viewPos = mul( float4(worldVertPos, 1.0), g_mView);
	float3 N = mul( world, In.normal ); //assumes no scale etc
#else
	float3 worldVertPos = mul(float4(In.position.xyz , 1.0), g_mWorld).xyz;
	float4 viewPos = mul( float4(In.position.xyz, 1.0), g_mWorldView);
	float3 N = mul( In.normal, (float3x3)g_mWorldInvTranspose ); //normal vector
#endif
	
	Output.position = mul( viewPos, g_mProj);
	Output.posView = viewPos;
    Output.texCoord0 = In.texCoord0;
	Output.texCoord1 = In.texCoord1;
	
	//calculate our vectors N, E, L, and H
	float3 worldEyePos = g_mViewInv[3].xyz;
	float4 light0;
	float4 light1;
	LightVertex(worldVertPos, N, worldEyePos, light0, light1);
	float4 vertColor = float4(1,1,1,1);
	MaterialContribution(vertColor, light0, light1, Output.diffColor0, Output.diffColor1, Output.specCol0);
	return Output;
}

// Vertex based lighting (with specular), also projects the position into the shadow map space
vertexOutputShadowT2 VertOneLightShadowProjT2(vertexInputT2 In) 
{
    vertexOutputShadowT2 Output;
    
#ifdef HKG_INSTANCING
	float3x4 world;
   	world[0] = In.transformRow0;
   	world[1] = In.transformRow1;
   	world[2] = In.transformRow2;
   	//world[3] = IN.transformRow3;
   	float3 worldVertPos = mul(world , float4(In.position.xyz, 1) ).xyz;
	float4 viewPos = mul( float4(worldVertPos, 1.0), g_mView);
	float3 N = mul( world, In.normal ); //assumes no scale etc
#else
	float3 worldVertPos = mul(float4(In.position.xyz , 1.0), g_mWorld).xyz;
	float4 viewPos = mul( float4(In.position.xyz, 1.0), g_mWorldView);
	float3 N = mul( In.normal, (float3x3)g_mWorldInvTranspose ); //normal vector
#endif

    Output.position = mul( viewPos, g_mProj);
    Output.texCoord01.xy = In.texCoord0;
    Output.texCoord01.zw = In.texCoord1;
    
	// project pos into light space
    Output.posLight = mul( viewPos, g_mViewToLightProj );
    
    Output.posView = viewPos;
    #ifdef HKG_SHADOWS_VSM
        Output.posLight1 = mul( viewPos, g_mViewToLightProj1 );
		Output.posLight2 = mul( viewPos, g_mViewToLightProj2 );
		Output.posLight3 = mul( viewPos, g_mViewToLightProj3 );
	#endif
  
    // Lighting:
    
	//calculate our vectors N, E, L, and H
	float3 worldEyePos = g_mViewInv[3].xyz;
   	float4 light0;
	float4 light1;
	LightVertex(worldVertPos, N, worldEyePos, light0, light1);
	float4 vertColor = float4(1,1,1,1);
	MaterialContribution(vertColor, light0, light1, Output.diffColor0, Output.diffColor1, Output.specCol0);
	
	return Output;
}

pixelOutput PixShadowSceneT0( vertexOutputShadowT0 In )
{
    pixelOutput Output;

	clip( In.diffColor0.a - ALPHA_DISCARD_TOLERANCE );

    #ifdef HKG_SHADOWS_VSM 
		float lightAmount = getLightAmountVSM( In.posLight, In.posLight1, In.posLight2, In.posLight3, In.posView );
 	#else
		float lightAmount = getLightAmountSM( In.posLight ); 
	#endif
	
	float3 amb = g_cDiffuseColor.rgb * g_cAmbientColor.rgb;
	Output.color.rgb = (1-lightAmount)*( amb + In.diffColor1.rgb ) + lightAmount*( In.diffColor0.rgb + In.diffColor1.rgb ) + lightAmount*In.specCol0.rgb;
	Output.color.a = In.diffColor0.a; // modulate alpha as is, shadow doesn't affect it.
    if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }

	Output.pzDepth.rgba = In.posView.z * g_iDepthParams.x ;
    
    return Output;
}

pixelOutput PixShadowSceneT1( vertexOutputShadowT1 In )
{
    pixelOutput Output;

    #ifdef HKG_SHADOWS_VSM 
		float lightAmount = getLightAmountVSM( In.posLight, In.posLight1, In.posLight2, In.posLight3, In.posView  );
 	#else
		float lightAmount = getLightAmountSM( In.posLight ); 
	#endif
	
	float4 texel = _sample4(In.texCoord0 );

    float4 SpecMap = 1;
#ifdef USE_SPEC 
    SpecMap = _sample5(In.texCoord0);
#endif

	float3 amb = g_cDiffuseColor.rgb * g_cAmbientColor.rgb;
	float3 matLight = (1-lightAmount)*( amb + In.diffColor1.rgb) + lightAmount*( In.diffColor0.rgb + In.diffColor1.rgb ) + lightAmount*In.specCol0.rgb*SpecMap;
	
	Output.color.rgb = texel.rgb*matLight;
	Output.color.a = texel.a * In.diffColor0.a; // modulate alpha as is, shadow doesn't affect it.
	clip( Output.color.a - ALPHA_DISCARD_TOLERANCE );

    if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x ;
    Output.pzDepth.a = Output.color.a;

    return Output;
}

pixelOutput PixShadowSceneT2( vertexOutputShadowT2 In )
{
    pixelOutput Output;

    #ifdef HKG_SHADOWS_VSM 
		float lightAmount = getLightAmountVSM( In.posLight, In.posLight1, In.posLight2, In.posLight3, In.posView  );
 	#else
		float lightAmount = getLightAmountSM( In.posLight ); 
	#endif
	
	float4 texel0 = _sample4(In.texCoord01.xy );
    float4 texel1 = _sample5(In.texCoord01.zw );
    float3 texelTotal = (texel0.rgb + (texel1.rgb * 0.6));
     
	float3 amb = g_cDiffuseColor.rgb * g_cAmbientColor.rgb;
	float3 matLight = (1-lightAmount)*( amb + In.diffColor1.rgb) + lightAmount*( In.diffColor0.rgb + In.diffColor1.rgb ) + lightAmount*In.specCol0.rgb;
	Output.color.rgb = texelTotal.rgb*matLight;
	Output.color.a = texel0.a * texel1.a * In.diffColor0.a; // modulate alpha as is, shadow doesn't affect it.
   	clip( Output.color.a - ALPHA_DISCARD_TOLERANCE );
	 if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x;
    Output.pzDepth.a = Output.color.a;

    return Output;
}


pixelOutput PixT0( vertexOutputT0 In ) 
{ 
    pixelOutput Output;
    Output.color.rgb = In.diffColor0.rgb + In.diffColor1.rgb + In.specCol0.rgb;
    Output.color.a = In.diffColor0.a;
   	clip( Output.color.a - ALPHA_DISCARD_TOLERANCE );
	 if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }

    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x;
    Output.pzDepth.a = Output.color.a;

    return Output;
}

pixelOutput PixT1( vertexOutputT1 In ) 
{ 
    pixelOutput Output;
    float4 texel = _sample0(In.texCoord0); 

    float4 SpecMap = 1;
#ifdef USE_SPEC 
    SpecMap = _sample1(In.texCoord0);
#endif

    Output.color.rgb = texel.rgb * (In.diffColor0.rgb + In.diffColor1.rgb) + (In.specCol0.rgb*SpecMap);
    Output.color.a = texel.a * In.diffColor0.a;

    clip( Output.color.a - ALPHA_DISCARD_TOLERANCE );
    if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }

    Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x;
    Output.pzDepth.a = Output.color.a; 
	return Output;
}

pixelOutput PixT2( vertexOutputT2 In ) 
{ 
    pixelOutput Output;
    float4 texel0 = _sample0(In.texCoord0 );
    float4 texel1 = _sample1(In.texCoord1 );
    float3 texelTotal = texel0.rgb + (texel1.rgb * 0.6);
    
	Output.color.rgb = texelTotal.rgb * (In.diffColor0.rgb + In.diffColor1.rgb) + In.specCol0.rgb;
    Output.color.a = texel0.a * texel1.a * In.diffColor0.a;
	clip( Output.color.a - ALPHA_DISCARD_TOLERANCE );

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
