/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#define SHADOW_EPSILON 0.0001

cbuffer perObject {
	float4x4 g_mWorld			: World;
	float4x4 g_mWorldInv;
	float4x4 g_mWorldView		: WorldView;
	float4x4 g_mWorldViewProj	: WorldViewProjection;
	float4x4 g_mWorldInvTranspose			: WorldInverseTranspose;
};

cbuffer perCamera {
	float4x4 g_mProj			: Proj;
	float4x4 g_mViewProj;
	float4x4 g_mViewInv			: ViewInverse;

	float4x4 g_mViewToLightProj; // for shadow maps
	float4x4 g_mViewToLightProj1;
	float4x4 g_mViewToLightProj2;
	float4x4 g_mViewToLightProj3;
};

//
// Textures, set assignment so that the behaviour is the same no mater what shader is using it 
//
// first 4 samplers will be shadowe maps if VSM used
sampler g_sSamplerZero : register(s0);    // Shadow Map0, or T0
sampler g_sSamplerOne : register(s1);    // PSVSM Map1, or T1
sampler g_sSamplerTwo : register(s2);    // PSVSM Map2, or T2
sampler g_sSamplerThree : register(s3);    // PSVSM Map3, or T4

sampler g_sSamplerFour  : register(s4);     // T0 if shadows
sampler g_sSamplerFive  : register(s5); // T1 if shadows

//
// Lights 
//
cbuffer perLight {
	float3 g_vLightShadowStartPosWorld; 
	float3 g_vLightShadowStartPosView;
	float4 g_vLightDir : Direction  = {0.0f, 1.0f, 0.0f, 1.0f}; // world space
	float4 g_vLightDirView : Direction;  // view space, for PSVSM
	float4 g_cLightColor : Diffuse = {1.0f, 1.0f, 1.0f, 1.0f};
};
 
// 
// Material
//
cbuffer perMaterial {
	float4 g_cAmbientColor	: MaterialAmbient = {0.0f, 0.0f, 0.0f, 1.0f};
	float4 g_cDiffuseColor	: MaterialDiffuse = {1.0f, 1.0f, 1.0f, 1.0f};
	float4 g_cSpecularColor	: MaterialSpecular = {1.0f, 1.0f, 1.0f, 1.0f};
	float  g_cSpecularPower	: Power = 30.0; // 1..128
};

cbuffer generalSettings {
	float  g_iShadowMapSize		= 1024;
	float  g_fShadowMapDistance = 100; // Distance from light / light proj to end of shadow map volume
	float  g_fShadowVsmEpsilon  = 0.0001; 
	float  g_fShadowVsmBias     = 0.0001; 

	float4 m_fShadowSplitDistances; // view space z distances to the far end of each map

	float4 g_cFogColor;
	float4 g_iFogParams;
};

//
// Structures
//
struct vertexInputT2 {
    float3 position			: POSITION;
    float3 normal			: NORMAL;
 #ifdef TEXTURE_ONE
    float2 texCoord0		: TEXCOORD0;
 #endif
 #ifdef TEXTURE_TWO
    float2 texCoord1		: TEXCOORD1;
 #endif
    float4 diffAmbColor		: COLOR0;
};

struct vertexInputPosOnly {
    float3 position			: POSITION;
};

struct vertexInputNoColorT2 {
    float3 position			: POSITION;
    float3 normal			: NORMAL;
 #ifdef TEXTURE_ONE
    float2 texCoord0		: TEXCOORD0;
 #endif
 #ifdef TEXTURE_TWO
     float2 texCoord1		: TEXCOORD1;
 #endif
};

struct vertexInputT1B {
	float4 position  : POSITION; 	
	float3 normal    : NORMAL; 	
#ifdef TEXTURE_ONE
 	float2 texCoord0 : TEXCOORD0; 	
#endif
	float3 tangent   : TANGENT; // well known slot
	float3 binormal  : BINORMAL;	
};



struct vertexOutputT1B {
	float4 position    : POSITION;  // clip space
 	float2 texCoord0   : TEXCOORD0;
	float3 posView 	   : TEXCOORD1; 
    float3 L           : TEXCOORD2; // tangent space
	float3 H           : TEXCOORD3;
};

struct vertexOutputT2 {
    float4 position			: POSITION;
    float3 texCoord0		: TEXCOORD0;
    float2 texCoord1		: TEXCOORD1;
    float3 posView 		    : TEXCOORD2; 
    float4 diffAmbColor		: COLOR0;
    float4 specCol			: COLOR1;
};

struct vertexOutputShadowDepth {
    float4 position			: POSITION;
    float4 depthZZZW		: TEXCOORD0;
};

struct vertexOutputShadowDepthVSM {
    float4 position			: POSITION;
    float3 posWorld		    : TEXCOORD0;
};

struct vertexOutputShadowT2 {
    float4 position			: POSITION;
    float2 texCoord0		: TEXCOORD0;
    float2 texCoord1		: TEXCOORD1;
    float4 posLight			: TEXCOORD2; // ShadowMap 0 lookup coords
    float3 posView 		    : TEXCOORD3; 
    #ifdef HKG_SHADOWS_VSM
  		float4 posLight1		: TEXCOORD4; // ShadowMap 1 lookup coords
		float4 posLight2		: TEXCOORD5; // ShadowMap 2 lookup coords
        float4 posLight3		: TEXCOORD6; // ShadowMap 3 lookup coords
    #endif
    float4 diffAmbColor		: COLOR0;
    float4 specCol			: COLOR1; 
};

struct vertexOutputShadowT1B {
    float4 position			: POSITION;
    float2 texCoord0		: TEXCOORD0;
    float4 posLight			: TEXCOORD1; // ShadowMap 0 lookup coords
    float3 posView 		    : TEXCOORD2; 
    #ifdef HKG_SHADOWS_VSM
  		float4 posLight1		: TEXCOORD3; // ShadowMap 1 lookup coords
		float4 posLight2		: TEXCOORD4; // ShadowMap 2 lookup coords
        float4 posLight3		: TEXCOORD5; // ShadowMap 3 lookup coords
        float3 L				: TEXCOORD6;
		float3 H				: TEXCOORD7;
	#else
	    float3 L				: TEXCOORD3;
		float3 H				: TEXCOORD4;
	#endif
};

struct pixelOutput
{
    float4 color			: COLOR0;  
	float4 pzDepth			: COLOR1; 
};

float4 computeFog( in float viewZ, in float4 c )
{
	float scale = 0;
	float depth = viewZ;
	if (g_iFogParams.x > 2 ) // EXP2
	{	
		float ddensity = depth*g_iFogParams.w;
		scale = 1.0 / exp( ddensity*ddensity ); // 1/(e^((d*density)^2))
	}
	else if (g_iFogParams.x > 1 ) // EXP
	{
		float ddensity = depth*g_iFogParams.w;
		scale = 1.0 / exp( ddensity ); // 1/(e^(d*density))
	}
	else if (g_iFogParams.x > 0 ) // LINEAR
	{
		scale = (g_iFogParams.z - depth) / (g_iFogParams.z - g_iFogParams.y);
	}
	
	scale = clamp(scale, 0, 1);
	return ( (1 - scale) * float4(g_cFogColor.xyz,1) ) + ( scale * c); 
}


//////////////////////////////////////////////////////////////
// 
// Vertex Shaders
//

// No lighting, just transform and pass on texture (and material as diffuse)
vertexOutputT2 VertNoLight(vertexInputNoColorT2 In) 
{
    vertexOutputT2 Output;
    float4 viewPos =  mul( float4(In.position.xyz, 1.0), g_mWorldView);
    Output.position = mul( viewPos, g_mProj);
    Output.posView = viewPos;
	Output.diffAmbColor = g_cDiffuseColor;
    #ifdef TEXTURE_ONE
    #ifdef HKG_SKYMAP
        Output.texCoord0 = mul( float4(In.normal,0), g_mWorldView).xyz;
    #else
	Output.texCoord0 = In.texCoord0.xyy;
    #endif
	#else
		Output.texCoord0 = 0;
	#endif	
	#ifdef TEXTURE_TWO
		Output.texCoord1 = In.texCoord1;
	#else
		Output.texCoord1 = 0;
	#endif	
		
	Output.specCol = float4(0,0,0,0);
    return Output;
}

// No lighting, just transform and pass on texture (and material as diffuse)
vertexOutputShadowT2 VertNoLightShadowProj(vertexInputNoColorT2 In) 
{
    vertexOutputShadowT2 Output;
    float4 viewPos =  mul( float4(In.position.xyz, 1.0), g_mWorldView);
    Output.position = mul( viewPos, g_mProj);
    Output.diffAmbColor = g_cDiffuseColor;
    #ifdef TEXTURE_ONE
		Output.texCoord0 = In.texCoord0;
    #else
    	Output.texCoord0 = 0;
    #endif
    #ifdef TEXTURE_TWO
	    Output.texCoord1 = In.texCoord1;
    #else
		Output.texCoord1 = 0;
    #endif
		
	Output.specCol = float4(0,0,0,0);
    
    	// project pos into light space
    Output.posLight = mul( viewPos, g_mViewToLightProj );

    #ifdef HKG_SHADOWS_VSM
		Output.posLight1 = mul( viewPos, g_mViewToLightProj1 );
		Output.posLight2 = mul( viewPos, g_mViewToLightProj2 );
		Output.posLight3 = mul( viewPos, g_mViewToLightProj3 );
   	#endif

    Output.posView = viewPos;

    return Output;
}

// No lighting, just transform and pass on texture (and vertex color as diffuse)
vertexOutputT2 VertNoLightVC(vertexInputT2 In) 
{
    vertexOutputT2 Output;
    float4 viewPos =  mul( float4(In.position.xyz, 1.0), g_mWorldView);
    Output.position = mul( viewPos, g_mProj);
    Output.posView = viewPos;
    Output.diffAmbColor = In.diffAmbColor;
    #ifdef TEXTURE_ONE
		Output.texCoord0 = In.texCoord0.xyy;
	#else
		Output.texCoord0 = 0;
	#endif
	#ifdef TEXTURE_TWO
		Output.texCoord1 = In.texCoord1;
	#else
		Output.texCoord1 = 0;
	#endif
		
	Output.specCol = float4(0,0,0,0);
    return Output;
}

// No lighting, just transform and pass on texture (and vertex color as diffuse)
// but with transformed view pos wrt shadow map too (for prelit shadow recvs in the scene)
vertexOutputShadowT2 VertNoLightVCShadowProj(vertexInputT2 In) 
{
    vertexOutputShadowT2 Output;
    float4 viewPos =  mul( float4(In.position.xyz, 1.0), g_mWorldView);
    
    Output.position = mul( viewPos, g_mProj);
    #ifdef TEXTURE_ONE
		Output.texCoord0 = In.texCoord0.xyy;
	#else
		Output.texCoord0 = 0;
	#endif
	#ifdef TEXTURE_TWO
		Output.texCoord1 = In.texCoord1;
	#else
		Output.texCoord1 = 0;
	#endif
	
	// project pos into light space
    Output.posLight = mul( viewPos, g_mViewToLightProj );
    
    #ifdef HKG_SHADOWS_VSM
        Output.posLight1 = mul( viewPos, g_mViewToLightProj1 );
		Output.posLight2 = mul( viewPos, g_mViewToLightProj2 );
		Output.posLight3 = mul( viewPos, g_mViewToLightProj3 );
	#endif
    Output.posView = viewPos;
    Output.diffAmbColor = In.diffAmbColor;
    Output.specCol = float4(0,0,0,0);
    return Output;
}

float4 LightVertex( float3 vert, float3 objectNormal, float3 eye )
{
	float4 N = mul( objectNormal, g_mWorldInvTranspose ); //normal vector
    float3 E = normalize( eye - vert ); //eye vector
    float3 L = g_vLightDir.xyz; //light vector
    float3 H = normalize( E + L ); //half angle vector

	//calculate the diffuse and specular contributions
    float  diff = max(0, dot(N,L));
    float  spec = pow( max(0 , dot(N,H) ), g_cSpecularPower);
    if (diff <= 0)
    	spec = 0;
    
	return float4( diff, diff, diff, spec );
}

void MaterialContribution( float4 vertexColor, float4 lightDiffuseAndSpec, out float4 diff, out float4 spec )
{
	float3 ambColor = vertexColor.rgb * g_cDiffuseColor.rgb * g_cAmbientColor.rgb;
    float3 diffColor = vertexColor.rgb * g_cDiffuseColor.rgb * lightDiffuseAndSpec.rgb * g_cLightColor.rgb;
    
    diff.rgb = diffColor.rgb + ambColor.rgb;
    diff.a = vertexColor.a * g_cDiffuseColor.a; 
    
	spec.rgb = g_cSpecularColor.rgb * g_cLightColor.rgb * lightDiffuseAndSpec.w;
    spec.a = 0;
}

// Vertex based lighting (with specular)
vertexOutputT2 VertOneLight(vertexInputNoColorT2 In) 
{
    vertexOutputT2 Output;
    float4 viewPos =  mul( float4(In.position.xyz, 1.0), g_mWorldView);
    Output.position = mul( viewPos, g_mProj);
    Output.posView = viewPos;
    #ifdef TEXTURE_ONE
		Output.texCoord0 = In.texCoord0.xyy;
	#else
		Output.texCoord0 = 0;
	#endif
	#ifdef TEXTURE_TWO
		Output.texCoord1 = In.texCoord1;
	#else
		Output.texCoord1 = 0;
	#endif
	
	//calculate our vectors N, E, L, and H
	float3 worldEyePos = g_mViewInv[3].xyz;
    float3 worldVertPos = mul( In.position, g_mWorld ).xyz;
	float4 light = LightVertex(worldVertPos, In.normal, worldEyePos);
	MaterialContribution(float4(1,1,1,1), light, Output.diffAmbColor, Output.specCol);
	
    return Output;
}

// Vertex based lighting (with specular), also projects the position into the shadow map space
vertexOutputShadowT2 VertOneLightShadowProj(vertexInputNoColorT2 In) 
{
    vertexOutputShadowT2 Output;
    
    float4 viewPos =  mul( float4(In.position.xyz, 1.0), g_mWorldView);
    
    Output.position = mul( viewPos, g_mProj);
   #ifdef TEXTURE_ONE
		Output.texCoord0 = In.texCoord0;
	#else
		Output.texCoord0 = 0;
	#endif
	#ifdef TEXTURE_TWO
		Output.texCoord1 = In.texCoord1;
	#else
		Output.texCoord1 = 0;
	#endif
	
	// project pos into light space
    Output.posLight = mul( viewPos, g_mViewToLightProj );
    
     #ifdef HKG_SHADOWS_VSM
        Output.posLight1 = mul( viewPos, g_mViewToLightProj1 );
		Output.posLight2 = mul( viewPos, g_mViewToLightProj2 );
		Output.posLight3 = mul( viewPos, g_mViewToLightProj3 );
	#endif
  
  	Output.posView =  viewPos;
	
    // Lighting:
    
	//calculate our vectors N, E, L, and H
	float3 worldEyePos = g_mViewInv[3].xyz;
    float3 worldVertPos = mul(In.position, g_mWorld).xyz;
	float4 light = LightVertex(worldVertPos, In.normal, worldEyePos);
	MaterialContribution(float4(1,1,1,1), light, Output.diffAmbColor, Output.specCol);
	
	return Output;
}


// Vertex based lighting (with specular)
vertexOutputT2 VertOneLightVC(vertexInputT2 In) 
{
    vertexOutputT2 Output;
    float4 viewPos =  mul( float4(In.position.xyz, 1.0), g_mWorldView);
    Output.position = mul( viewPos, g_mProj);
    Output.posView = viewPos;
   #ifdef TEXTURE_ONE
		Output.texCoord0 = In.texCoord0.xyy;
	#else
		Output.texCoord0 = 0;
	#endif
	#ifdef TEXTURE_TWO
		Output.texCoord1 = In.texCoord1;
	#else
		Output.texCoord1 = 0;
	#endif
	
	//calculate our vectors N, E, L, and H
	float3 worldEyePos = g_mViewInv[3].xyz;
    float3 worldVertPos = mul( In.position, g_mWorld ).xyz;
	float4 light = LightVertex(worldVertPos, In.normal, worldEyePos);
	MaterialContribution(In.diffAmbColor, light, Output.diffAmbColor, Output.specCol);
	
    return Output;
}

// Vertex based lighting (with specular), also projects the position into the shadow map space
vertexOutputShadowT2 VertOneLightVCShadowProj(vertexInputT2 In) 
{
    vertexOutputShadowT2 Output;
    
    float4 viewPos =  mul( float4(In.position.xyz, 1.0), g_mWorldView);
    
    Output.position = mul( viewPos, g_mProj);
  #ifdef TEXTURE_ONE
		Output.texCoord0 = In.texCoord0;
	#else
		Output.texCoord0 = 0;
	#endif
	#ifdef TEXTURE_TWO
		Output.texCoord1 = In.texCoord1;
	#else
		Output.texCoord1 = 0;
	#endif
	  
	// project pos into light space
    Output.posLight = mul( viewPos, g_mViewToLightProj );
    
    #ifdef HKG_SHADOWS_VSM
        Output.posLight1 = mul( viewPos, g_mViewToLightProj1 );
		Output.posLight2 = mul( viewPos, g_mViewToLightProj2 );
		Output.posLight3 = mul( viewPos, g_mViewToLightProj3 );
	#endif
  	Output.posView = viewPos;
	
    // Lighting:
    
	//calculate our vectors N, E, L, and H
	float3 worldEyePos = g_mViewInv[3].xyz;
    float3 worldVertPos = mul(In.position, g_mWorld).xyz;
	float4 light = LightVertex(worldVertPos, In.normal, worldEyePos);
	MaterialContribution(In.diffAmbColor, light, Output.diffAmbColor, Output.specCol);
	
	return Output;
}


vertexOutputT1B VertOneLightBump( vertexInputT1B In )
{
	vertexOutputT1B Out;

	// copy texture coordinates
	#ifdef TEXTURE_ONE
		Out.texCoord0 = In.texCoord0;
	#else
		Out.texCoord0 = float2(0,0);		
	#endif
	
	// transform position to clip space
	float4 viewPos =  mul( float4(In.position.xyz, 1.0), g_mWorldView);
    Out.position = mul( viewPos, g_mProj);
    Out.posView = viewPos;
   

	// compute the 3x3 tranform from object space to tangent space
	float3x3 objToTangentSpace;
	
	float bumpHeight = 1.0f;
		
	objToTangentSpace[0] = In.tangent * bumpHeight;
	objToTangentSpace[1] = In.binormal * bumpHeight;
	objToTangentSpace[2] = In.normal;
	
    float4 vertexPos = mul(In.position, g_mWorld); // world space position

	// light vector
	float3 lightVec = mul( g_vLightDir, (float3x3)g_mWorldInv );  // transform back to object space
	Out.L = mul( objToTangentSpace, lightVec ); // transform from object to tangent space
	
	// eye vector
	float3 eyeVec = g_mViewInv[3].xyz - vertexPos.xyz; // world space eye vector
	eyeVec = mul(eyeVec, (float3x3) g_mWorldInv );  // transform back to object space
	eyeVec = normalize(eyeVec);
	
	// half-angle vector
	float3 H = normalize(lightVec + eyeVec);
	Out.H = mul(objToTangentSpace, H);	// transform to tangent space

	return Out;
}


// Vertex based lighting (with specular), also projects the position into the shadow map space
vertexOutputShadowT1B VertOneLightBumpShadowProj( vertexInputT1B In) 
{
    vertexOutputShadowT1B Output;
    
    float4 viewPos =  mul( float4(In.position.xyz, 1.0), g_mWorldView);
    Output.position = mul( viewPos, g_mProj);
   
    #ifdef TEXTURE_ONE
		Output.texCoord0 = In.texCoord0;
	#else
		Output.texCoord0 = 0;		
	#endif
	 
		// project pos into light space
    Output.posLight = mul( viewPos, g_mViewToLightProj );
    
    #ifdef HKG_SHADOWS_VSM
        Output.posLight1 = mul( viewPos, g_mViewToLightProj1 );
		Output.posLight2 = mul( viewPos, g_mViewToLightProj2 );
		Output.posLight3 = mul( viewPos, g_mViewToLightProj3 );
    #endif

    Output.posView = viewPos;
  
	// compute the 3x3 tranform from object space to tangent space
	float3x3 objToTangentSpace;
	
	float bumpHeight = 1.0f;
		
	objToTangentSpace[0] = In.tangent * bumpHeight;
	objToTangentSpace[1] = In.binormal * bumpHeight;
	objToTangentSpace[2] = In.normal;
	
    float4 vertexPos = mul(In.position, g_mWorld); // world space position

	// light vector
	float3 lightVec = mul( g_vLightDir, (float3x3)g_mWorldInv );  // transform back to object space
	Output.L = mul( objToTangentSpace, lightVec ); // transform from object to tangent space
	
	// eye vector
	float3 eyeVec = g_mViewInv[3].xyz - vertexPos.xyz; // world space eye vector
	eyeVec = mul(eyeVec, (float3x3) g_mWorldInv );  // transform back to object space
	eyeVec = normalize(eyeVec);
	
	// half-angle vector
	float3 H = normalize(lightVec + eyeVec);
	Output.H = mul(objToTangentSpace, H);	// transform to tangent space

	
	return Output;
}

#ifdef HKG_SHADOWS_VSM

	vertexOutputShadowDepthVSM VertShadowDepth(vertexInputPosOnly In)
	{
		vertexOutputShadowDepthVSM Output;
		
		float3 worldVertPos = mul( float4(In.position,1), g_mWorld);
		Output.position = mul(float4(worldVertPos,1), g_mViewProj); // Light VP in this case
		Output.posWorld = worldVertPos;
		return Output;
	}

#else

	// Vertex transform only, with tcoord0 the enough to work out the transformed depth (no bias)
	vertexOutputShadowDepth VertShadowDepth(vertexOutputShadowDepth In)
	{
		vertexOutputShadowDepth Output;
		Output.position = mul(In.position, g_mWorldViewProj); // Light WVP in this case
		Output.depthZZZW = float4(Output.position.zzz, Output.position.w);
		return Output;
	}

#endif

	
//////////////////////////////////////////////////////////////////
//
// Pixel Shaders
//

// No per pixel lighting, just add the input color with the specular, no texture loookup
pixelOutput PixT0( vertexOutputT2 In ) 
{ 
    pixelOutput Output;
   
    Output.color = In.diffAmbColor + In.specCol;
   
	//texkill completely transparent regions so that ssao not affected by invisible stuff
	clip( Output.color.a - 0.005 );
	
#ifdef HKG_ENABLE_VIEWDEPTH
	if ( g_iFogParams.x > 0)
	{
		Output.color = computeFog( In.posView.z, Output.color );
	}
   	Output.pzDepth.rgba = In.posView.z;
#else
	Output.pzDepth.rgba = 0;
#endif

	return Output;
}

// No per pixel lighting, just modulate the input color with the texture and add specular (afterwards)
pixelOutput PixT1( vertexOutputT2 In ) 
{ 
    pixelOutput Output;
#ifdef HKG_SKYMAP
    Output.color = texCUBE(g_sSamplerZero, In.texCoord0) * In.diffAmbColor;// + In.specCol;
#else
    Output.color = tex2D(g_sSamplerZero, In.texCoord0.xy) * In.diffAmbColor;// + In.specCol;
#endif

	//texkill completely transparent regions so that ssao not affected by invisible stuff
	clip( Output.color.a - 0.005 );
	
#ifdef HKG_ENABLE_VIEWDEPTH
	if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
    Output.pzDepth.rgba = In.posView.z;
#else
	Output.pzDepth.rgba = 0;
#endif

    return Output;
}

pixelOutput PixT2( vertexOutputT2 In ) 
{ 
    pixelOutput Output;
    Output.color = tex2D(g_sSamplerZero, In.texCoord0.xy) * tex2D(g_sSamplerOne, In.texCoord1) * In.diffAmbColor + In.specCol;

	//texkill completely transparent regions so that ssao not affected by invisible stuff
	clip( Output.color.a - 0.005 );

#ifdef HKG_ENABLE_VIEWDEPTH
	if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    
    Output.pzDepth.rgba = In.posView.z;
#else
	Output.pzDepth.rgba = 0;
#endif

    return Output;
}

#ifdef HKG_SHADOWS_VSM

	float4 PixShadowMap( vertexOutputShadowDepthVSM In ): COLOR
	{
		float4 depth;
		float3 lightDir = g_vLightShadowStartPosWorld - In.posWorld;
		depth.x = dot(lightDir,g_vLightDir) / g_fShadowMapDistance; 
		depth.y = depth.x * depth.x;
		
		#ifdef HKG_SHADOWS_DISTRIBUTE_16F_OUTPUTS 
			depth.zw = frac(depth.xy * SHADOW_16F_DISTRIBUTE_FACTOR);
			depth.xy = depth.xy - (depth.zw / SHADOW_16F_DISTRIBUTE_FACTOR);
		#else
			depth.zw = depth.xy;
		#endif
		
		return depth;
	}

#else // standard shadow maps
   
	float4 PixShadowMap( vertexOutputShadowDepth In ) : COLOR
	{
		float depth = (In.depthZZZW.b / In.depthZZZW.a);
		return float4( depth.xxx, 1.0f );
	}

#endif


// Blinn/Phong lighting model
float4 Phong(float2 dots) 
{
	float NdotL = dots.x;
	float NdotH = dots.y;
	float diffuse = max(NdotL, 0.0);
	float specular = pow(NdotH, g_cSpecularPower);
	if (NdotL <= 0) specular = 0;
	return float4(diffuse, diffuse, diffuse, specular);
}

// Pixel shaders
pixelOutput PixT1Bump( vertexOutputT1B In ) : COLOR
{
	pixelOutput Output;

	float4 colorMap = tex2D(g_sSamplerZero, In.texCoord0);
	float3 N = tex2D(g_sSamplerOne, In.texCoord0)*2.0 - 1.0;

	N = normalize(N);

	float NdotL = dot(N, In.L);
	float NdotH = dot(N, In.H);
	float4 light = Phong(float2(NdotL, NdotH));
	
	float4 c = float4(g_cAmbientColor.rgb*colorMap.rgb +light.rgb*g_cDiffuseColor.rgb*colorMap.rgb + light.w*g_cSpecularColor.rgb, g_cDiffuseColor.a);
	
	//texkill completely transparent regions so that ssao not affected by invisible stuff
	clip( c.a - 0.005 );

	if ( g_iFogParams.x > 0)
    {
		c = computeFog( In.posView.z, c );
    }
    
    Output.color = c;
    Output.pzDepth.rgba = In.posView.z;
    
	return Output;
}

 
float getLightAmountVSM( float4 posLight, float3 posView, sampler shadowMap )
{
	float2 shadowTexCoord = posLight.xy / posLight.w;
	
	// Lookup assumes Bil. filtering supported on the float textures
	#ifdef HKG_NO_FLOATBLENDING 
	
		float2 texelpos = g_iShadowMapSize * shadowTexCoord;
		float2 lerps = frac( texelpos );
		float4 sourcevals[4];
		float oneTexel = 1.0/g_iShadowMapSize;
	    
		sourcevals[0] = tex2D( shadowMap, shadowTexCoord );  
		sourcevals[1] = tex2D( shadowMap, shadowTexCoord + float2(oneTexel, 0) );  
		sourcevals[2] = tex2D( shadowMap, shadowTexCoord + float2(0, oneTexel) );  
		sourcevals[3] = tex2D( shadowMap, shadowTexCoord + float2(oneTexel, oneTexel) );  
	        
		// lerp between the shadow values to calculate our light amount
		float4 moments = lerp( lerp( sourcevals[0], sourcevals[1], lerps.x ),
									lerp( sourcevals[2], sourcevals[3], lerps.x ),
									lerps.y );

	#else
	
		float4 moments = tex2D(shadowMap, shadowTexCoord);
	
	#endif
	
	// Rescale light distance and check if we're in shadow
	
	float3 lightDir = g_vLightShadowStartPosView - posView ;
	float distFromLight = dot(lightDir,g_vLightDirView); 
	float rescaledDistToLight = distFromLight / g_fShadowMapDistance; 
	rescaledDistToLight -= g_fShadowVsmBias; 
	rescaledDistToLight = min( rescaledDistToLight, 0.999f);
	float litFactor = (moments.x > 0.99999f) || (moments.x >= rescaledDistToLight); // || (moments.x > 0.95); // if moment.x (depth) > rescaled, then not in shadow. May add check here for detecting 'off the edge of map'(always lit in our demos)
	
	// Variance shadow mapping
	float E_x2 = moments.y;
	float Ex_2 = moments.x * moments.x;
	float variance = min(max(E_x2 - Ex_2, 0.0) + g_fShadowVsmEpsilon, 1.0);
	float m_d = (moments.x - rescaledDistToLight);
	float p = variance / (variance + (m_d * m_d));

	return max(litFactor, p);
}
	
// Pixel shader to use a float based shadow map, will modulate with vertex lit color 
// (does not do per pixel lighting, uses vertex color)	
pixelOutput PixShadowSceneT0( vertexOutputShadowT2 In )
{
    pixelOutput Output;

	float lightAmount = 1;
	if ( In.posView.z < m_fShadowSplitDistances.x)
		lightAmount = getLightAmountVSM( In.posLight, In.posView, g_sSamplerZero );
	else if ( In.posView.z < m_fShadowSplitDistances.y)
		lightAmount = getLightAmountVSM( In.posLight1, In.posView, g_sSamplerOne );
	else if ( In.posView.z < m_fShadowSplitDistances.z)
		lightAmount = getLightAmountVSM( In.posLight2, In.posView, g_sSamplerTwo );
	else 
		lightAmount = getLightAmountVSM( In.posLight3, In.posView, g_sSamplerThree );
	
	Output.color.rgb = (1-lightAmount)*In.diffAmbColor.rgb*0.3 + lightAmount*In.diffAmbColor.rgb + (lightAmount * In.specCol.rgb); // modulate rgb wrt shadow.
    Output.color.a = In.diffAmbColor.a; // modulate alpha as is, shadow doesn't affect it.
	
	//texkill completely transparent regions so that ssao not affected by invisible stuff
	clip( Output.color.a - 0.005 );

	// Fix for some demos just fir now: no fog or ssao on pre lit objects
	if ( g_iFogParams.x > 0)
	{
		Output.color = computeFog( In.posView.z, Output.color );
	}
	Output.pzDepth.rgba = In.posView.z;
    return Output;
}

// Pixel shader to use a float based shadow map, will modulate with vertex lit color 
// (does not do per pixel lighting, uses vertex color)
pixelOutput PixShadowSceneT1( vertexOutputShadowT2 In )
{
    pixelOutput Output;

	float lightAmount = 1;
	if ( In.posView.z < m_fShadowSplitDistances.x)
		lightAmount = getLightAmountVSM( In.posLight, In.posView, g_sSamplerZero );
	else if ( In.posView.z < m_fShadowSplitDistances.y)
		lightAmount = getLightAmountVSM( In.posLight1, In.posView, g_sSamplerOne );
	else if ( In.posView.z < m_fShadowSplitDistances.z)
		lightAmount = getLightAmountVSM( In.posLight2, In.posView, g_sSamplerTwo );
	else 
		lightAmount = getLightAmountVSM( In.posLight3, In.posView, g_sSamplerThree );
	
	float4 texel = tex2D( g_sSamplerFour, In.texCoord0 );
	texel.rgb *= In.diffAmbColor;
    Output.color.rgb = (1-lightAmount)*texel.rgb*0.3 + lightAmount*texel.rgb + (lightAmount * In.specCol.rgb); // modulate rgb wrt shadow.
    Output.color.a = texel.a * In.diffAmbColor.a; // modulate alpha as is, shadow doesn't affect it.

	//texkill completely transparent regions so that ssao not affected by invisible stuff
	clip( Output.color.a - 0.005 );

	if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    Output.pzDepth.rgba = In.posView.z;
    return Output;
}

// Pixel shader to use a float based shadow map, will modulate with vertex lit color 
// (does not do per pixel lighting, uses vertex color)
pixelOutput PixShadowSceneT2( vertexOutputShadowT2 In )
{
    pixelOutput Output;

	float lightAmount = 1;
	if ( In.posView.z < m_fShadowSplitDistances.x)
		lightAmount = getLightAmountVSM( In.posLight, In.posView, g_sSamplerZero );
	else if ( In.posView.z < m_fShadowSplitDistances.y)
		lightAmount = getLightAmountVSM( In.posLight1, In.posView, g_sSamplerOne );
	else if ( In.posView.z < m_fShadowSplitDistances.z)
		lightAmount = getLightAmountVSM( In.posLight2, In.posView, g_sSamplerTwo );
	else 
		lightAmount = getLightAmountVSM( In.posLight3, In.posView, g_sSamplerThree );  
	
	float4 diffuse = float4(((1 - lightAmount)*g_cAmbientColor.rgb),1) + (lightAmount * In.diffAmbColor);
	float4 texel0 = tex2D( g_sSamplerFour, In.texCoord0 );
    float4 texel1 = tex2D( g_sSamplerFive, In.texCoord1 );
    float3 texelTotal = (texel0.rgb * texel1.rgb) * In.diffAmbColor.rgb;    
    Output.color.rgb = (1-lightAmount)*texelTotal*0.3 + lightAmount*texelTotal.rgb + (lightAmount * In.specCol.rgb); // modulate rgb wrt shadow.
    Output.color.a = texel0.a * In.diffAmbColor.a; // modulate alpha as is, shadow doesn't affect it.

	//texkill completely transparent regions so that ssao not affected by invisible stuff
	clip( Output.color.a - 0.005 );

	if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    Output.pzDepth.rgba = In.posView.z;
    return Output;
}

pixelOutput PixShadowSceneT1Bump( vertexOutputShadowT1B In )
{
    pixelOutput Output;
    
	float lightAmount = 1;
	if ( In.posView.z < m_fShadowSplitDistances.x)
		lightAmount = getLightAmountVSM( In.posLight, In.posView, g_sSamplerZero );
	else if ( In.posView.z < m_fShadowSplitDistances.y)
		lightAmount = getLightAmountVSM( In.posLight1, In.posView, g_sSamplerOne );
	else if ( In.posView.z < m_fShadowSplitDistances.z)
		lightAmount = getLightAmountVSM( In.posLight2, In.posView, g_sSamplerTwo );
	else 
		lightAmount = getLightAmountVSM( In.posLight3, In.posView, g_sSamplerThree );
		
    float4 colorMap = tex2D(g_sSamplerFour, In.texCoord0);
	float3 N = tex2D(g_sSamplerFive, In.texCoord0)*2.0 - 1.0;

	N = normalize(N);

	In.L = normalize(In.L);
	In.H = normalize(In.H);

	float NdotL = dot(N, In.L);
	float NdotH = dot(N, In.H);
	float4 light = lightAmount * Phong(float2(NdotL, NdotH));
	
	Output.color.rgb = g_cAmbientColor*colorMap*g_cDiffuseColor + light*g_cDiffuseColor*colorMap + light.w*g_cSpecularColor ;
	Output.color.a = colorMap.a * g_cDiffuseColor.a; // modulate alpha as is, shadow doesn't affect it.

	//texkill completely transparent regions so that ssao not affected by invisible stuff
	clip( Output.color.a - 0.005 );

	if ( g_iFogParams.x > 0)
    {
		Output.color = computeFog( In.posView.z, Output.color );
    }
    Output.pzDepth.rgba = In.posView.z;
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
