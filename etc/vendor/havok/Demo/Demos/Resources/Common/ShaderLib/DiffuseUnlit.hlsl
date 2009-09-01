/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

//
// One diffuse map, with and without shadows. Unlit.
//:STYLE VertT1 PixT1 LD0 T1 DIFFUSE0
//:STYLE VertShadowProjT1 PixShadowSceneT1 LD0 T1 SHADOWMAP DIFFUSE0

//:STYLE VertT1 PixT1 LD0 T1 DIFFUSE0 INSTANCED DEFINE:HKG_INSTANCING
//:STYLE VertShadowProjT1 PixShadowSceneT1 LD0 T1 SHADOWMAP DIFFUSE0 INSTANCED DEFINE:HKG_INSTANCING

#include "CommonHeader.hlslh"

// extra matrices
float4x4 g_mWorldView		: WorldView;
float4x4 g_mProj			: Proj;
 

vertexOutputUnlitT1 VertT1(vertexInputUnlitT1 In) 
{
	vertexOutputUnlitT1 Output;
    
#ifdef HKG_INSTANCING
	float3x4 world;
   	world[0] = In.transformRow0;
   	world[1] = In.transformRow1;
   	world[2] = In.transformRow2;
   	//world[3] = In.transformRow3;
   	float3 worldVertPos = mul(world , float4(In.position.xyz, 1) ).xyz;
	float4 viewPos = mul( float4(worldVertPos, 1.0), g_mView);
#else
	float4 viewPos = mul( float4(In.position.xyz, 1.0), g_mWorldView);	
#endif

    Output.position = mul( viewPos, g_mProj);
	Output.posView = viewPos;
    Output.texCoord0 = In.texCoord0;
	return Output;
}

vertexOutputShadowUnlitT1 VertShadowProjT1(vertexInputUnlitT1 In) 
{
    vertexOutputShadowUnlitT1 Output;
    
#ifdef HKG_INSTANCING
	float3x4 world;
   	world[0] = In.transformRow0;
   	world[1] = In.transformRow1;
   	world[2] = In.transformRow2;
   	//world[3] = In.transformRow3;
   	float3 worldVertPos = mul(world , float4(In.position.xyz, 1) ).xyz;
	float4 viewPos = mul( float4(worldVertPos, 1.0), g_mView);
#else
	float4 viewPos = mul( float4(In.position.xyz, 1.0), g_mWorldView);	
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
  
	return Output;
}


pixelOutput PixShadowSceneT1( vertexOutputShadowUnlitT1 In )
{
    pixelOutput Output;

    #ifdef HKG_SHADOWS_VSM 
		float lightAmount = getLightAmountVSM( In.posLight,  In.posLight1, In.posLight2, In.posLight3, In.posView );
 	#else
		float lightAmount = getLightAmountSM( In.posLight ); 
	#endif
	
    float4 texel = _sample4(In.texCoord0 );
    Output.color.rgb = texel.rgb * lightAmount.rrr; // modulate rgb wrt shadow.
    Output.color.a = texel.a; // set alpha as is, shadow doesn't affect it.
	clip( texel.a - ALPHA_DISCARD_TOLERANCE );

	if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
	Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x;
	Output.pzDepth.a = Output.color.a;
	
	return Output;
}


pixelOutput PixT1( vertexOutputUnlitT1 In ) 
{ 
    pixelOutput Output;
    Output.color = _sample0(In.texCoord0); 
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
