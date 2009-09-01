
// A big thanks to Inigo Quilez http://rgba.scenesp.org/iq/computer/articles/ssao/ssao.htm, 
// and Crytek's 2007 Siggraph session for explaining the workings of SSAO

float4 ClearColor0 : DIFFUSE = { 0.0f, 0.0f, 0.0f, 1.0f};
float4 ClearColor1= { 0.0f, 0.0f, 0.0f, 0.0f};
float ClearDepth = 1.0f;
float DepthClip = 3000.0f;

float Script : STANDARDSGLOBAL
<
	string UIWidget = "none";
	string ScriptClass = "scene";
	string ScriptOrder = "postprocess";
	string ScriptOutput = "color";
	
	// We just call a script in the main technique.
#ifdef HKG_DX10
	string Script = "Technique=SSAO10;";
#else
	string Script = "Technique=SSAO;";
#endif
> = 0.8;

float4x4 g_mProjInv; // Scene's camera view 
float4x4 g_mProj;

float4 g_cFogColor = { 0,0,0,1 };
float4 g_iFogParams = { 0,0,0,0 };

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

float2 WindowSize : VIEWPORTPIXELSIZE < string UIWidget = "none"; >;

texture SceneMap : RENDERCOLORTARGET
<
	string source = "SCENE";
>;

texture SSAOMap : RENDERCOLORTARGET
< 
    float2 ViewportRatio = { 1.0, 1.0 };
    int MIPLEVELS = 1;
    string format = "R32F";
>;

texture SSAOMap_Temp: RENDERCOLORTARGET
< 
    float2 ViewportRatio = { 1.0, 1.0 };
    int MIPLEVELS = 1;
    string format = "R32F";
>;

texture ViewDepthMap : RENDERCOLORTARGET
< 
	string source = "DEPTH";
>;

sampler SceneMapSampler = sampler_state 
{
    texture = <SceneMap>;
    AddressU  = CLAMP;        
    AddressV  = CLAMP;
    AddressW  = CLAMP;
	FILTER = MIN_MAG_MIP_POINT;
 //   MIPFILTER = NONE;
 //   MINFILTER = POINT;
 //   MAGFILTER = POINT;
};

sampler SSAOMapSampler = sampler_state 
{
    texture = <SSAOMap>;
    AddressU  = CLAMP;        
    AddressV  = CLAMP;
    AddressW  = CLAMP;
	FILTER = MIN_MAG_LINEAR_MIP_POINT;
  //  MIPFILTER = NONE;
  //  MINFILTER = LINEAR;
  //  MAGFILTER = LINEAR;
};


sampler SSAOMap_TempSampler = sampler_state 
{
    texture = <SSAOMap_Temp>;
    AddressU  = CLAMP;        
    AddressV  = CLAMP;
    AddressW  = CLAMP;
   	FILTER = MIN_MAG_LINEAR_MIP_POINT;
//	MIPFILTER = NONE;
//    MINFILTER = LINEAR;
//    MAGFILTER = LINEAR;
};

sampler ViewDepthMapSampler = sampler_state 
{
    texture = <ViewDepthMap>;
    AddressU  = CLAMP;        
    AddressV  = CLAMP;
    AddressW  = CLAMP;
 	FILTER = MIN_MAG_LINEAR_MIP_POINT;
//   MIPFILTER = NONE;
//    MINFILTER = LINEAR;
//    MAGFILTER = LINEAR;
};


struct VS_OUTPUT
{
   	float4 Position   : POSITION;
    float2 TexCoord0  : TEXCOORD0;
    float2 TexCoord1  : TEXCOORD1;
};

VS_OUTPUT VS_Quad(float4 Position : POSITION, 
				  float2 TexCoord : TEXCOORD0)
{
    VS_OUTPUT OUT;

	float2 texelSize = 1.0 / WindowSize;
 
	OUT.Position = Position; 
	
#ifndef HKG_DX10
	float2 dxHalfTexelPos = float2( -texelSize.x, texelSize.y ); // [-1,1] -> WindowSize  ==  2/WindowSize,  so half texel = 1/windowize
	OUT.Position.xy += (dxHalfTexelPos * Position.w);
#endif

	OUT.TexCoord0 = TexCoord;
	OUT.TexCoord1 = TexCoord;

    return OUT;
}

float4 PS_Display(VS_OUTPUT IN,
			  uniform sampler2D tex) : COLOR
{   
	float r = tex2D(tex, IN.TexCoord0).r;
	return float4(r,r,r,1);
}


struct VSS_OUTPUT
{
   	float4 Position   : POSITION;
    float2 TexCoord0  : TEXCOORD0;
    float4 EyeDir     : TEXCOORD1;
};

VSS_OUTPUT VS_Ssao(float4 Position : POSITION, 
				  float2 TexCoord : TEXCOORD0)
{
    VSS_OUTPUT OUT;
	float2 texelSize = 1.0 / WindowSize;
   
	OUT.Position = Position; 
	
    // Want to work out eye dir before we adjust for dx half texel 
    OUT.EyeDir = mul( float4(Position.xyz,1), g_mProjInv );

#ifndef HKG_DX10	
	float2 dxHalfTexelPos = float2( -texelSize.x, texelSize.y ); // [-1,1] -> WindowSize  ==  2/WindowSize,  so half texel = 1/windowize    
	OUT.Position.xy += (dxHalfTexelPos * Position.w);
#endif

	OUT.TexCoord0 = TexCoord;
    
    return OUT;
}

float g_rad = 0.01;
float g_rangeMin = 0.1;
float g_rangeMax = 0.8;
float4 g_sphericalSampling[32];
float BlurWidth = 2;
float SceneScale = 0.8;
float g_blurDepthLimit = 5; // times g_rad
float g_ssaoDepthDiffLimit = 8; // times g_rad
float g_ssaoLightenLimit = 0.5;

// blur filter weights
const half weights7[7] = {
	0.05,
	0.1,
	0.2,
	0.3,
	0.2,
	0.1,
	0.05,
};	

float smoothstep(float min, float max, float input)
{
	return (clamp((input - min) / (max - min), 0, 1));
}

float4 PS_Ssao(VSS_OUTPUT IN,
			  uniform sampler2D texZ) : COLOR
{   
	float ez = tex2D(texZ, IN.TexCoord0).r;
	float3 edir = IN.EyeDir.xyz / IN.EyeDir.z;
	float3 ep = ez * edir;
	
	float isClearDepth = ez < 0.0001; 

	float bl = 0.0;
	//float distCuttoff = g_rad * 3000;
	float diffCuttoff = g_rad * 50 * g_ssaoDepthDiffLimit; 
	float2 texelOffset = float2(0.5, 0.5);
	
	for( int i=0; i<32; i++ )
	{
		float4 se = float4(ep + g_rad*g_sphericalSampling[i].xyz, 1);
		float4 ss = mul(se, g_mProj); // back into projection space
		ss.xyz /= ss.w;
		
		float2 sn = float2(ss.x*(0.5), ss.y*(-0.5)) + texelOffset;
		float4 sz = tex2D( texZ, sn );
		float zd = 50*max( se.z - sz.x, 0 );
		// if zd is greater than a certain amount then the ssoa should actually decrease as it is then most likely not local, but perhaps areas then too bright I think
		float zdDiffCuttoff = clamp( (zd - diffCuttoff) / (g_ssaoDepthDiffLimit*2), 0, g_ssaoLightenLimit );
		//float zdDisatanceCuttoff = saturate( (ez - distCuttoff) / 100 );
		bl += ( 1.0 / (1.0 + zd*zd) ) + zdDiffCuttoff;       // + zdDisatanceCuttoff;
   }
   
   bl /= 32.0;
   bl = smoothstep(g_rangeMin, g_rangeMax, bl + isClearDepth); // clip off top to lighten, as most flat surfaces will be .5 occluded (by themselves)
   return float4(bl,0,0,0);
}

struct VS_OUTPUT_BLUR
{
    float4 Position   : POSITION;
    float2 TexCoord0  : TEXCOORD0;
    float4 TexCoord12 : TEXCOORD1;
    float4 TexCoord34 : TEXCOORD2;
    float4 TexCoord56 : TEXCOORD3;
};

VS_OUTPUT_BLUR VS_Blur(float4 Position : POSITION, 
					   float2 TexCoord : TEXCOORD0,
					   uniform int nsamples, // always 7 now
					   uniform float2 direction
					   )
{
    VS_OUTPUT_BLUR OUT = (VS_OUTPUT_BLUR)0;
    float2 texelSize = 1.0 / WindowSize;

	OUT.Position = Position; 

#ifdef HKG_DX10
	// DX9 has hald texel offset already (so we get some linear bluring)
	// DX10 is centered, so we can offset the lookup texels 
	TexCoord.xy += direction*float2( -texelSize.x, -texelSize.y)*0.5 ;
#else
 	float2 dxHalfTexelPos = float2( -texelSize.x, texelSize.y ); // [-1,1] -> WindowSize  ==  2/WindowSize,  so half texel = 1/windowize
 	OUT.Position.xy += (dxHalfTexelPos * Position.w);
#endif	

	float2 blurDir = BlurWidth * texelSize * direction;
    float2 s = TexCoord - (nsamples-1)*0.5*blurDir;
    
	OUT.TexCoord0     = s;
	OUT.TexCoord12.xy = s + blurDir*1;
	OUT.TexCoord12.zw = s + blurDir*2;
	OUT.TexCoord34.xy = s + blurDir*3;
	OUT.TexCoord34.zw = s + blurDir*4;
	OUT.TexCoord56.xy = s + blurDir*5;
	OUT.TexCoord56.zw = s + blurDir*6;
	
	return OUT;
}

float4 PS_Blur7(VS_OUTPUT_BLUR IN,
			   uniform sampler2D ssaotex,
			   uniform sampler2D depthtex,
			   uniform half weight[7]
			   ) : COLOR
{
    float c = 0;
    

    float2 centerSampleCoord = IN.TexCoord34.xy;

#ifdef HKG_DX10
    // undo blur offset
    float2 texelSize = 1.0 / WindowSize; 
    centerSampleCoord += float2( texelSize.x, 0 )*0.5 ;
#endif

	float ourDepth =  tex2D(depthtex, centerSampleCoord ).x;
    float centreSsao = tex2D(ssaotex, centerSampleCoord).r; 
	
	float blurLimit = 0.5;//g_rad*5;
	
	if (abs(ourDepth - tex2D(depthtex, IN.TexCoord0).x) < blurLimit)
    	c += tex2D(ssaotex, IN.TexCoord0).r * weight[0];
    else
    	c += centreSsao * weight[0];
   	
	if (abs(ourDepth - tex2D(depthtex, IN.TexCoord12.xy).x) < blurLimit)
    	c += tex2D(ssaotex, IN.TexCoord12.xy).r * weight[1];
    else
    	c += centreSsao * weight[1];
   	
	if (abs(ourDepth - tex2D(depthtex, IN.TexCoord12.zw).x) < blurLimit)
    	c += tex2D(ssaotex, IN.TexCoord12.zw).r * weight[2];
    else
    	c += centreSsao * weight[2];
   	
	if (abs(ourDepth - tex2D(depthtex, IN.TexCoord34.xy).x) < blurLimit)
    	c += tex2D(ssaotex, IN.TexCoord34.xy).r * weight[3];
    else
    	c += centreSsao * weight[3];
   	
	if (abs(ourDepth - tex2D(depthtex, IN.TexCoord34.zw).x) < blurLimit)
    	c += tex2D(ssaotex, IN.TexCoord34.zw).r * weight[4];
    else
    	c += centreSsao * weight[4];

	if (abs(ourDepth - tex2D(depthtex, IN.TexCoord56.xy).x) < blurLimit)
    	c += tex2D(ssaotex, IN.TexCoord56.xy).r * weight[5];
    else
    	c += centreSsao * weight[5];
   	
	if (abs(ourDepth - tex2D(depthtex, IN.TexCoord56.zw).x) < blurLimit)
    	c += tex2D(ssaotex, IN.TexCoord56.zw).r * weight[6];
    else
    	c += centreSsao * weight[6];
   	
	return float4(c,0,0,1);
} 

float4 PS_Blur7AndCombine(VS_OUTPUT_BLUR IN,
			   uniform sampler2D ssaotex,
			   uniform sampler2D depthtex,
			   uniform sampler2D scene,
			   uniform half weight[7]
			   ) : COLOR
{
    float c = 0;

    float2 centerSampleCoord = IN.TexCoord34.xy;

#ifdef HKG_DX10
    // undo blur offset
    float2 texelSize = 1.0 / WindowSize; 
    centerSampleCoord += float2( 0, texelSize.y)*0.5 ;
#endif

    float ourDepth = tex2D(depthtex, centerSampleCoord ).x;
    float centreSsao = tex2D(ssaotex, centerSampleCoord ).r; 

    float4 rendererdSceneColor = tex2D(scene, centerSampleCoord );
    float blurLimit = g_rad*g_blurDepthLimit;
  
    if (abs(ourDepth - tex2D(depthtex, IN.TexCoord0).x) < blurLimit)
    	c += tex2D(ssaotex, IN.TexCoord0).r * weight[0];
    else
    	c += centreSsao * weight[0];
   	
	if (abs(ourDepth - tex2D(depthtex, IN.TexCoord12.xy).x) < blurLimit)
    	c += tex2D(ssaotex, IN.TexCoord12.xy).r * weight[1];
    else
    	c += centreSsao * weight[1];
   	
	if (abs(ourDepth - tex2D(depthtex, IN.TexCoord12.zw).x) < blurLimit)
    	c += tex2D(ssaotex, IN.TexCoord12.zw).r * weight[2];
    else
    	c += centreSsao * weight[2];
   	
	if (abs(ourDepth - tex2D(depthtex, IN.TexCoord34.xy).x) < blurLimit)
    	c += tex2D(ssaotex, IN.TexCoord34.xy).r * weight[3];
    else
    	c += centreSsao * weight[3];
   	
	if (abs(ourDepth - tex2D(depthtex, IN.TexCoord34.zw).x) < blurLimit)
    	c += tex2D(ssaotex, IN.TexCoord34.zw).r * weight[4];
    else
    	c += centreSsao * weight[4];

	if (abs(ourDepth - tex2D(depthtex, IN.TexCoord56.xy).x) < blurLimit)
    	c += tex2D(ssaotex, IN.TexCoord56.xy).r * weight[5];
    else
    	c += centreSsao * weight[5];
   	
	if (abs(ourDepth - tex2D(depthtex, IN.TexCoord56.zw).x) < blurLimit)
    	c += tex2D(ssaotex, IN.TexCoord56.zw).r * weight[6];
    else
    	c += centreSsao * weight[6];

   	float4 occlusion = float4(c,c,c,1);
	float4 color = (1-SceneScale)*occlusion + SceneScale*(rendererdSceneColor * occlusion);
	if ( g_iFogParams.x > 0)
    {
		color = computeFog( ourDepth, color );
    }    

	return color;
} 

technique SSAO
<
	string Script = "ClearColor0=ClearColor0;"
					"ClearColor1=ClearColor1;"
					"Clear=WipeAll;";
			
>
{
    pass SSOA
    <
		string Script = "RenderColorTarget0=SSAOMap;"
						"Draw=Buffer;";
	>
    {
		cullmode = none;
		ZEnable = false;
		ZWriteEnable = false;		
		VertexShader = compile vs_3_0 VS_Ssao();
		PixelShader  = compile ps_3_0 PS_Ssao(ViewDepthMapSampler);
    }
    
    pass BlurSSOA_H
    <
    	string Script = "RenderColorTarget0=SSAOMap_Temp;"
						"Draw=Buffer;";
	>
	{
		cullmode = none;
		ZEnable = false;
		ZWriteEnable = false;		
		VertexShader = compile vs_3_0 VS_Blur(7,float2(1, 0));
		PixelShader  = compile ps_3_0 PS_Blur7(SSAOMapSampler, ViewDepthMapSampler, weights7);
    }
    
    pass BlurSSOA_V_AndCombine
    <
    	string Script = "RenderColorTarget0=;"
						"Draw=Buffer;";
	>
	{
		cullmode = none;
		ZEnable = false;
		ZWriteEnable = false;		
		VertexShader = compile vs_3_0 VS_Blur(7,float2(0, 1));
		PixelShader  = compile ps_3_0 PS_Blur7AndCombine(SSAOMap_TempSampler, ViewDepthMapSampler, SceneMapSampler, weights7);
	//	VertexShader = compile vs_3_0 VS_Quad();
	//	PixelShader  = compile ps_3_0 PS_Display(SSAOMapSampler);
    }
}


RasterizerState DisableCulling
{
    CullMode = NONE;
	MultisampleEnable = FALSE;
};

DepthStencilState DepthEnabling
{
	DepthEnable = FALSE;
	DepthWriteMask = ZERO;
};

BlendState DisableBlend
{
	BlendEnable[0] = FALSE;
};

technique10 SSAO10
<
	string Script = "ClearColor0=ClearColor0;"
					"ClearColor1=ClearColor1;"
					"Clear=WipeAll;";
>
{
   pass SSOA
    <
		string Script = "RenderColorTarget0=SSAOMap;"
						"Draw=Buffer;";
	>
    {
		SetVertexShader( CompileShader( vs_4_0, VS_Ssao() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_Ssao(ViewDepthMapSampler) ) );
	
		SetRasterizerState(DisableCulling);       
		SetDepthStencilState(DepthEnabling, 0);
		SetBlendState(DisableBlend, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF);
    }
    
    pass BlurSSOA_H
    <
    	string Script = "RenderColorTarget0=SSAOMap_Temp;"
						"Draw=Buffer;";
	>
	{
		SetVertexShader( CompileShader( vs_4_0, VS_Blur(7,float2(1, 0) ) ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_Blur7(SSAOMapSampler, ViewDepthMapSampler, weights7) ) );
	
		SetRasterizerState(DisableCulling);       
		SetDepthStencilState(DepthEnabling, 0);
		SetBlendState(DisableBlend, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF);
    }
   
	pass BlurSSOA_V_AndCombine
    <
    	string Script = "RenderColorTarget0=;"		
						"Draw=Buffer;";
	>
	{
		SetVertexShader( CompileShader( vs_4_0, VS_Blur(7,float2(0, 1)) ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_Blur7AndCombine(SSAOMap_TempSampler, ViewDepthMapSampler, SceneMapSampler, weights7) ) );
	
		SetRasterizerState(DisableCulling);       
		SetDepthStencilState(DepthEnabling, 0);
		SetBlendState(DisableBlend, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF);
    }
}