
/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

//:STYLE VertShadowDepth PixShadowDepth LD1 T* SHADOWDEPTH 

#include "CommonHeader.hlslh"

#ifdef HKG_SHADOWS_VSM

	vertexOutputShadowDepthVSM VertShadowDepth( vertexInputShadowDepth In)
	{
		vertexOutputShadowDepthVSM Output;
		
		#ifdef HKG_INSTANCING
			float3x4 world;
   			world[0] = In.transformRow0;
   			world[1] = In.transformRow1;
   			world[2] = In.transformRow2;
   			float3 worldVertPos = mul(world , float4(In.position, 1) );
		#else
			float3 worldVertPos = mul(float4(In.position,1), g_mWorld).xyz;
		#endif
		
		Output.position = mul(float4(worldVertPos,1), g_mViewProj); // Light VP in this case
		
		#ifdef ENABLE_ALPHA_SHADOWS
			Output.texCoord0 = In.texCoord0;
		#endif
		
		Output.posWorld = worldVertPos;
		return Output;
	}

	float4 PixShadowDepth( vertexOutputShadowDepthVSM In ) : COLOR
	{
	    #ifdef ENABLE_ALPHA_SHADOWS
	    if (g_iDepthParams.g > 0)
	    {
			float4 tex = tex2D( g_sSamplerZero, In.texCoord0 );
			clip(tex.a - 0.75f); // will be neg for <75 and will discard pixel
	    }
	    #endif
	    
		float4 depth;
		float3 lightDir = g_vLightShadowStartPosWorld - In.posWorld;
		depth.r = dot(lightDir,g_vLightDir) / g_fShadowMapDistance; 
		depth.g = depth.x * depth.x;
		#ifdef HKG_SHADOWS_DISTRIBUTE_16F_OUTPUTS 
			depth.ba = frac(depth.rg * SHADOW_16F_DISTRIBUTE_FACTOR);
			depth.rg = depth.rg - (depth.ba / SHADOW_16F_DISTRIBUTE_FACTOR);
		#else
			depth.ba = depth.rg;
		#endif
		
		return depth;
	}
	
#else

	// Vertex transform only, with tcoord0 the enough to work out the transformed depth (no bias)
	vertexOutputShadowDepth VertShadowDepth( vertexInputShadowDepth In)
	{
		vertexOutputShadowDepth Output;
		#ifdef HKG_INSTANCING
			float3x4 world;
   			world[0] = In.transformRow0;
   			world[1] = In.transformRow1;
   			world[2] = In.transformRow2;
   			float3 worldVertPos = mul(world , float4(In.position, 1) );
		#else
			float3 worldVertPos = mul(float4(In.position,1), g_mWorld).xyz;
		#endif
			
		Output.position = mul(float4(worldVertPos,1), g_mViewProj); // Light VP in this case
		Output.depthZZZW = float4(Output.position.zzz, Output.position.w);
		#ifdef ENABLE_ALPHA_SHADOWS
			Output.texCoord0 = In.texCoord0;
		#endif
		return Output;
	}
	
	float4 PixShadowDepth( vertexOutputShadowDepth In ) : COLOR
	{
		#ifdef ENABLE_ALPHA_SHADOWS
	    if (g_iDepthParams.g)
	    {
			float4 tex = tex2D( g_sSamplerZero, In.texCoord0 );
			clip( tex.a - 0.2 );
	    }
	    #endif
	    
		float depth = (In.depthZZZW.b / In.depthZZZW.a);
		return float4( depth.xxx, 1.0f );
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
