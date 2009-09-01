

#ifdef _XBOX
// as we use a proper depth resolve (with bias) we don't need epsilon in here
#define SHADOW_EPSILON 0.0
#else
#define SHADOW_EPSILON 0.0001
#endif
#define SHADOW_16F_DISTRIBUTE_FACTOR 32

static const int MAX_MATRICES = 48;
float4x3    g_mLocalMatrixArray[MAX_MATRICES] : WorldMatrixArray : register(c0);

float4x4    g_mWorld;
float4x4    g_mWorldViewProj;
float4x4    g_mWorldInvTranspose;
float4x4    g_mWorldView;
float4x4    g_mViewProj;
float4x4    g_mProj;

float4x4 g_mViewToLightProj; // for shadow maps
float4x4 g_mViewToLightProj1;
float4x4 g_mViewToLightProj2;
float4x4 g_mViewToLightProj3;

// support for one dir light
float3 g_vLightShadowStartPosWorld; 
float3 g_vLightShadowStartPosView;
float4 g_vLightDir : Direction  = {0.0f, 1.0f, 0.0f, 1.0f}; // world space
float4 g_vLightDirView : Direction;  // view space, for PSVSM
float4 g_cLightColor : Diffuse = {1.0f, 1.0f, 1.0f, 1.0f};

float4 g_vLight1Dir : Direction  = {0.0f, 1.0f, 0.0f, 1.0f}; // world space
float4 g_cLight1Color : Diffuse = {1.0f, 1.0f, 1.0f, 1.0f};

float g_iNumLights; // normally 1, can be 2 with these shaders


// support for diffuse mat
float4 g_cAmbientColor	: MaterialAmbient = {0.0f, 0.0f, 0.0f, 1.0f};
float4 g_cDiffuseColor	: MaterialDiffuse = {1.0f, 1.0f, 1.0f, 1.0f};

float  g_iShadowMapSize		= 1024;
float  g_fShadowMapDistance = 100; // Distance from light / light proj to end of shadow map volume
float  g_fShadowVsmEpsilon  = 0.0001; 
float  g_fShadowVsmBias     = 0.0001; 

float4 m_fShadowSplitDistances; // view space z distances to the far end of each map

float4 g_cFogColor;
float4 g_iFogParams;
float4 g_iDepthParams; // x == LinearDepth output enabled. y == AlphaBlend enabled.

// Support for one diffuse tex at time, no shadows
sampler g_sSamplerZero : register(s0);    // Shadow Map0, or T0
sampler g_sSamplerOne : register(s1);    // PSVSM Map1, or T1
sampler g_sSamplerTwo : register(s2);    // PSVSM Map2, or T2
sampler g_sSamplerThree : register(s3);    // PSVSM Map3, or T4

sampler g_sSamplerFour  : register(s4);     // T0 if shadows
sampler g_sSamplerFive  : register(s5); // T1 if shadows

//
// Utils
//
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

void skinPN( float3 skinPos, float3 skinNorm, float BlendWeightsArray[4], int IndexArray[4], out float3 Pos, out float3 Normal )
{
    // calculate the pos/normal using the "normal" weights 
    // and accumulate the weights to calculate the last weight
    Pos = 0.0f;
    Normal = 0.0f;  
    float LastWeight = 0.0f;
    for (int iBone = 0; iBone < 3; iBone++)
    {
        LastWeight = LastWeight + BlendWeightsArray[iBone];
        
        Pos += mul(float4(skinPos,1), g_mLocalMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
        Normal += mul(skinNorm, g_mLocalMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
    }
    LastWeight = 1.0f - LastWeight; 

    // Now that we have the calculated weight, add in the final influence
    Pos += (mul(float4(skinPos,1), g_mLocalMatrixArray[IndexArray[3]]) * LastWeight);
    Normal += (mul(skinNorm, g_mLocalMatrixArray[IndexArray[3]]) * LastWeight); 
}   

void skinP( float3 skinPos, float BlendWeightsArray[4], int IndexArray[4], out float3 Pos )
{
    // calculate the pos/normal using the "normal" weights 
    // and accumulate the weights to calculate the last weight
    Pos = 0.0f;
    float LastWeight = 0.0f;
    for (int iBone = 0; iBone < 3; iBone++)
    {
        LastWeight = LastWeight + BlendWeightsArray[iBone];
        Pos += mul( float4(skinPos,1), g_mLocalMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
    }
    LastWeight = 1.0f - LastWeight; 

    // Now that we have the calculated weight, add in the final influence
    Pos += (mul(float4(skinPos,1), g_mLocalMatrixArray[IndexArray[3]]) * LastWeight);
}   
    
// 
// NO SHADOWS
//

struct VS_INPUT
{
    float3  Pos             : POSITION;
    float4  BlendWeights    : BLENDWEIGHT;
#if defined(HKG_DX10)
    uint4	BlendIndices    : BLENDINDICES;
#else
	float4  BlendIndices    : BLENDINDICES;
#endif
	float3  Normal          : NORMAL;
    float3  Tex0            : TEXCOORD0;
};

struct VS_OUTPUT
{
    float4  Pos     : POSITION;
    float4  Diffuse : COLOR;
    float2  Tex0    : TEXCOORD0;
	float3  posView : TEXCOORD1;
};

struct PS_OUTPUT
{
    float4 RGBAColor : COLOR0;  // Pixel color    
	float4 pzDepth : COLOR1;  // Linear pixel depth (for SSAO etc)
};


VS_OUTPUT mainVS(VS_INPUT i)
{
    VS_OUTPUT   o;
  
	float BlendWeightsArray[4] = (float[4])i.BlendWeights;
     
    // Compensate for lack of UBYTE4 on Geforce3
#if defined(HKG_DX10)
	int   IndexArray[4] = (int[4])i.BlendIndices;    
#else
	int4 IndexVector = D3DCOLORtoUBYTE4(i.BlendIndices);
    int   IndexArray[4] = (int[4])IndexVector;    
#endif

    float3 Pos = 0;
    float3 Normal = 0;   
    skinPN( i.Pos, i.Normal, BlendWeightsArray, IndexArray, Pos, Normal );
    
    // transform position from world space into view and then projection space
	float4 viewPos = mul(float4(Pos.xyz, 1.0f), g_mWorldView);
	o.Pos = mul( viewPos, g_mProj);
    o.posView = viewPos;
    
    // normalize normals
    Normal = mul(float4(Normal.xyz, 1.0f), g_mWorldInvTranspose);
    Normal = normalize(Normal);

    // Shade (Ambient + etc.)
    float4 diffuseLight = max(0.0f, dot(Normal, g_vLightDir.xyz)) * g_cLightColor;
 
	if (g_iNumLights > 1)
	{
		diffuseLight += max(0.0f, dot(Normal, g_vLight1Dir.xyz)) * g_cLight1Color;
	}

    o.Diffuse.xyz = g_cAmbientColor.xyz + ( diffuseLight * g_cDiffuseColor.xyz );
    o.Diffuse.w = 1.0f;

    // copy the input texture coordinate through
    o.Tex0  = i.Tex0.xy;

    return o;
}


PS_OUTPUT mainPS( VS_OUTPUT In ) 
{ 
    PS_OUTPUT Output;

    Output.RGBAColor = tex2D(g_sSamplerZero, In.Tex0) * In.Diffuse; 

    if ( g_iFogParams.x > 0)
	{
		Output.RGBAColor = computeFog( In.posView.z, Output.RGBAColor );
	}

	Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x;
    Output.pzDepth.a = Output.RGBAColor.a;

	return Output;
}

// 
// SHADOW PASS 0 (to depth map)
//

struct vertexInputPosOnly {
    float3 position			: POSITION;
	float2  Tex0    : TEXCOORD0;
    float4 BlendWeights    : BLENDWEIGHT;

#if defined(HKG_DX10)
    uint4	BlendIndices    : BLENDINDICES;
#else
	float4  BlendIndices    : BLENDINDICES;
#endif

};

struct vertexOutputShadowDepth {
    float4 position			: POSITION;
    float4 depthZZZW		: TEXCOORD0;
};

struct vertexOutputShadowDepthVSM {
    float4 position			: POSITION;
    float3 posWorld		    : TEXCOORD0;
};

#ifdef HKG_SHADOWS_VSM

	vertexOutputShadowDepthVSM mainVS_ToDepth(vertexInputPosOnly In)
	{
		vertexOutputShadowDepthVSM Output;
		
		#if defined(HKG_DX10)
			int   IndexArray[4] = (int[4])In.BlendIndices;    
		#else
			// Compensate for lack of UBYTE4 on Geforce3
			int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);
			int   IndexArray[4] = (int[4])IndexVector; 
		#endif
			
		float BlendWeightsArray[4] = (float[4])In.BlendWeights;
	  
        float3 localPos;
        skinP( In.position, BlendWeightsArray, IndexArray, localPos );
        
		float3 worldVertPos = mul( float4(localPos,1), g_mWorld);
		
		Output.position = mul( float4(worldVertPos,1), g_mViewProj ); // Light VP in this case
		Output.posWorld = worldVertPos;
		return Output;
	}

	PS_OUTPUT mainPS_ToDepth( vertexOutputShadowDepthVSM In )
	{
		PS_OUTPUT Output;
	    
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
		
		Output.RGBAColor = depth;
		return Output;
	}

#else

	// Vertex transform only, with tcoord0 the enough to work out the transformed depth (no bias)
	vertexOutputShadowDepth mainVS_ToDepth(vertexInputPosOnly In)
	{
		vertexOutputShadowDepth Output;
		
		#if defined(HKG_DX10)
			int   IndexArray[4] = (int[4])In.BlendIndices;    
		#else
			// Compensate for lack of UBYTE4 on Geforce3
			int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);
			int   IndexArray[4] = (int[4])IndexVector; 
		#endif
	
		float BlendWeightsArray[4] = (float[4])In.BlendWeights;
	  
        float3 localPos;
        skinP( In.position, BlendWeightsArray, IndexArray, localPos );
      
        Output.position = mul( float4(localPos,1), g_mWorldViewProj); // Light WVP in this case
		Output.depthZZZW = float4(Output.position.zzz, Output.position.w);
		return Output;
	}
   
	PS_OUTPUT mainPS_ToDepth( vertexOutputShadowDepth In )
	{
		PS_OUTPUT Output;
		float depth = (In.depthZZZW.b / In.depthZZZW.a);
		Output.RGBAColor = float4( depth.xxx, 1.0f );
		return Output;
	}

#endif


// 
// SHADOW PASS 1 (normal render, based on depth map)
//

struct VS_OUTPUT_S
{
    float4  Pos     : POSITION;
    float2  Tex0    : TEXCOORD0;
    float4  posLight			: TEXCOORD1; // ShadowMap 0 lookup coords
    float3 posView          : TEXCOORD5; 
    #ifdef HKG_SHADOWS_VSM
  		float4 posLight1		: TEXCOORD2; // ShadowMap 1 lookup coords
		float4 posLight2		: TEXCOORD3; // ShadowMap 2 lookup coords
        float4 posLight3		: TEXCOORD4; // ShadowMap 3 lookup coords
    #endif
    float4  Diffuse : COLOR0;
    float4  L1      : COLOR1;
};


VS_OUTPUT_S mainVS_Shadow(VS_INPUT i)
{
    VS_OUTPUT_S   o;
     
#if defined(HKG_DX10)
	int   IndexArray[4] = (int[4])i.BlendIndices;    
#else
    // Compensate for lack of UBYTE4 on Geforce3
	int4 IndexVector = D3DCOLORtoUBYTE4(i.BlendIndices);
    int   IndexArray[4] = (int[4])IndexVector; 
#endif

    	// cast the vectors to arrays for use in the for loop below
    float BlendWeightsArray[4] = (float[4])i.BlendWeights;
   
   
    float3 Pos;
    float3 Normal;  
    skinPN( i.Pos, i.Normal, BlendWeightsArray, IndexArray, Pos, Normal );
  
    float4 viewPos = mul(float4(Pos.xyz, 1.0f), g_mWorldView);

	o.Pos = mul( viewPos, g_mProj);
	o.posLight = mul( viewPos, g_mViewToLightProj );
    o.posView = viewPos;
    
    #ifdef HKG_SHADOWS_VSM
		o.posLight1 = mul( viewPos, g_mViewToLightProj1 );
		o.posLight2 = mul( viewPos, g_mViewToLightProj2 );
		o.posLight3 = mul( viewPos, g_mViewToLightProj3 );
    #endif
	
	
    // normalize normals
    Normal = mul(float4(Normal.xyz, 1.0f), g_mWorldInvTranspose);
    Normal = normalize(Normal);

    // Shade (Ambient + etc.)
    float4 diffuseLight = max(0.0f, dot(Normal, g_vLightDir.xyz)) * g_cLightColor;
	o.L1 = float4(0,0,0,1);
	if (g_iNumLights > 1)
	{
		o.L1 = max(0.0f, dot(Normal, g_vLight1Dir.xyz)) * g_cLight1Color;
		diffuseLight += o.L1;
	}

    o.Diffuse.xyz = g_cAmbientColor.xyz + ( diffuseLight * g_cDiffuseColor.xyz );
    o.Diffuse.w = 1.0f;
 
    // copy the input texture coordinate through
    o.Tex0  = i.Tex0.xy;

    return o;
}



float getLightAmountNoHW( float4 posLight )
{
	float2 shadowTexCoord = posLight.xy / posLight.w;
	float  shadowTestDepth = (posLight.z / posLight.w) - SHADOW_EPSILON; //-->make it a bit closer, only use if no way to use _proper_ depth bias etc
				
    // transform to texel space
    float2 texelpos = g_iShadowMapSize * shadowTexCoord;
        
    // Determine the lerp amounts           
    float2 lerps = frac( texelpos );

    //read in bilerp stamp, doing the shadow checks
    float sourcevals[4];
    float oneTexel = 1.0/g_iShadowMapSize;
    
    sourcevals[0] = (tex2D( g_sSamplerZero, shadowTexCoord ).r < shadowTestDepth)? 0.0f: 1.0f;  
    sourcevals[1] = (tex2D( g_sSamplerZero, shadowTexCoord + float2(oneTexel, 0) ).r < shadowTestDepth)? 0.0f: 1.0f;  
    sourcevals[2] = (tex2D( g_sSamplerZero, shadowTexCoord + float2(0, oneTexel) ).r < shadowTestDepth)? 0.0f: 1.0f;  
    sourcevals[3] = (tex2D( g_sSamplerZero, shadowTexCoord + float2(oneTexel, oneTexel) ).r < shadowTestDepth)? 0.0f: 1.0f;  
        
    // lerp between the shadow values to calculate our light amount
    float lightAmount = lerp( lerp( sourcevals[0], sourcevals[1], lerps.x ),
                                lerp( sourcevals[2], sourcevals[3], lerps.x ),
                                lerps.y );

	return lightAmount;                                                       
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

	#ifdef HKG_SHADOWS_DISTRIBUTE_16F_OUTPUTS 
		  moments.xy += (moments.zw / SHADOW_16F_DISTRIBUTE_FACTOR);
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

PS_OUTPUT mainPS_Shadow( VS_OUTPUT_S In ) 
{ 
    PS_OUTPUT Output;
	#ifdef HKG_SHADOWS_VSM 
        float lightAmount = 1;
		if ( In.posView.z < m_fShadowSplitDistances.x)
			lightAmount = getLightAmountVSM( In.posLight, In.posView, g_sSamplerZero );
		else if ( In.posView.z < m_fShadowSplitDistances.y)
			lightAmount = getLightAmountVSM( In.posLight1, In.posView, g_sSamplerOne );
		else if ( In.posView.z < m_fShadowSplitDistances.z)
			lightAmount = getLightAmountVSM( In.posLight2, In.posView, g_sSamplerTwo );
		else 
			lightAmount = getLightAmountVSM( In.posLight3, In.posView, g_sSamplerThree );
    #elif HKG_SHADOWS_HARDWARE // NV h/w lookup of depth buffer
		float lightAmount = tex2Dproj(g_sSamplerZero, In.posLight).r; // white or black, so red is all we need.
	#else
		float lightAmount = getLightAmountNoHW( In.posLight ); 
	#endif
	
	float4 tex0 = tex2D(g_sSamplerFour, In.Tex0);
    Output.RGBAColor.rgb = tex0.rgb * (( lightAmount * In.Diffuse.rgb ) + ((1 - lightAmount)*( g_cAmbientColor.xyz + In.L1 )) ); 
	Output.RGBAColor.a = tex0.a * In.Diffuse.a;

     if ( g_iFogParams.x > 0)
    {
		Output.RGBAColor = computeFog( In.posView.z, Output.RGBAColor );
    }

	Output.pzDepth.rgb = In.posView.z * g_iDepthParams.x;
    Output.pzDepth.a = Output.RGBAColor.a;

    return Output;
}