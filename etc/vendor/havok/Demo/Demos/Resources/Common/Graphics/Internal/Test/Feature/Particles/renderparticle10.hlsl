/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

float4x4 g_mViewProj; // well known name
float4x4 g_mView; 
float4x4 g_mViewInv;  
float4x4 g_mProj;
float4x4 g_mProjInv;

float tanfov;
float viewportWidth;
float viewportHeight;

float particlemode;
float time;
float life_time = 500.0;
float4 g_vLightDir; //wkn
float3 customLightDir;
float4 g_cDiffuseColor;//wkn
float pointsize = 2.0;
float pointsizeGrowthRate = 20.0;
float pointsizeMax = 10.0;
        
sampler samplerZero : register(s0);
   
// Sparks:  "particle_quad_vp", "particle_quad_gs", "particle_fp" 
// Balls:    "particle_vp", "particle_gs", "particle_sphere_fp" 
// Smoke:  "particle_grow_vp", "particle_grow_gs", "particle_lit_fp"

void particle_simple_vp(
    in float4 pos : POSITION,
    in float4 velocity : TEXCOORD1,
 
    out float4 o_hpos : POSITION,
    out float4 o_velocity : TEXCOORD0,
    out float o_pointsize : PSIZE,
    out float4 o_color : COLOR0
      )
{
    o_velocity = velocity;
    o_color = g_cDiffuseColor;

    float radius = pos.w;
    if (pos.w > 0) pos.w = 1.0;

    o_pointsize = pointsize;

    // transform to clip space
    o_hpos = mul(pos, g_mViewProj);
}

float4 particle_simple_fp(
    in float4 color : COLOR0,
    in float4 velocity : TEXCOORD0
    ) : COLOR
{
    return color;
}


struct particleVpOut
{
	float4 worldPos	: POSITION;
    float4 velocity : TEXCOORD0;
    float  radius   : TEXCOORD1;
	float4 color    : COLOR0;
};


void particle_vp(
	in float4 pos : POSITION,
    in float4 velocity : TEXCOORD0,
                     
	out particleVpOut output
    )
{
    
    float radius = pos.w;
    if (pos.w > 0) pos.w = 1.0;     // negative pos.w means don't render particle

    output.radius = radius*pointsize;
    output.worldPos = pos;
	output.color = g_cDiffuseColor;
    output.velocity = velocity;
}


// as above, point size grows over time
void particle_grow_vp(
    in float4 pos : POSITION,
    in float4 velocity : TEXCOORD0,
        
	out particleVpOut output
    )
{
    
    // extract data from input texcoords
    float radius = pos.w;
    if (pos.w > 0) pos.w = 1.0;     // negative pos.w means don't render particle

	float birth_time = velocity.w;
    float age = (time - birth_time) / life_time;
	float fPointAgeScale = 1.0 + (1.0 * age);
	
	output.worldPos = pos;
	 output.radius = radius * fPointAgeScale;
   	output.color = g_cDiffuseColor;
	output.velocity = velocity;    
}



struct particleVpQuadOut
{
	float4 worldCurPos	: POSITION;
    float4 worldPrevPos	: TEXCOORD0;
	float4 color    : COLOR0;
};

void particle_quad_vp(
	in float4 currentPos : POSITION,
    in float4 prevPos : TEXCOORD0,
                                       
	out particleVpQuadOut output
    )
{
    output.worldCurPos = currentPos;
	output.worldPrevPos = prevPos;
	output.color = g_cDiffuseColor;
}

struct particleGsOut
{
	float4 pos		: SV_Position;
	float2 texcoord : TEXCOORD0;
    float4 velocity : TEXCOORD1;
    float4 epos		: TEXCOORD2;
	float3 N		: TEXCOORD3;
	float4 color	: COLOR;
};


[maxvertexcount(4)]
void particle_gs(point particleVpOut input[1], inout TriangleStream<particleGsOut> spriteStream)
{
    particleGsOut output;

	float4 eposCent = mul( input[0].worldPos, g_mView );

	output.color = input[0].color;
	output.velocity = input[0].velocity;
	output.epos = eposCent;

	for(int i=0; i<4; i++)
    {
        float2 tc = float2(i/2, i%2); // 0..1
		float3 p = float3((tc * 2) - 1, 0);  //-1..1
        float3 position = mul( p, (float3x3)g_mViewInv )*input[0].radius + input[0].worldPos;

		output.pos = mul( float4(position,input[0].worldPos.w), g_mViewProj );
       	output.N = p;
		output.texcoord = tc;

		spriteStream.Append(output);
	}
    spriteStream.RestartStrip();	
}

struct particleGsSimpleOut
{
	float4 pos  : SV_Position;
	float2 texcoord : TEXCOORD0;
	float4 color : COLOR0;
};

[maxvertexcount(4)]
void particle_quad_gs(point particleVpQuadOut input[1], inout TriangleStream<particleGsSimpleOut> spriteStream)
{
    particleGsSimpleOut output;

	float3 viewDir = mul( float3(0, 0, 1), (float3x3) g_mViewInv );

    // create perpendicular vector
    float3 delta = input[0].worldCurPos.xyz - input[0].worldPrevPos.xyz;
    float len = length(delta);
    float width = len * input[0].worldCurPos.w; // radius
    float4 perp = float4(  normalize(cross(delta / len, viewDir)) * width, 0);
	
	if (input[0].worldCurPos.w > 0) 
	{
		input[0].worldCurPos.w = 1.0;   
	}

	float4 curPos = input[0].worldCurPos;
    float4 prevPos = input[0].worldCurPos - float4(delta*2,0);

	output.color = input[0].color;

	output.pos = curPos + perp;
	output.pos = mul( output.pos, g_mViewProj ); 
	output.texcoord = float2(1,1);
	spriteStream.Append(output);
	output.pos = curPos - perp;
	output.pos = mul( output.pos, g_mViewProj ); 
	output.texcoord = float2(1,0);
	spriteStream.Append(output);
	output.pos = prevPos + perp;
	output.pos = mul( output.pos, g_mViewProj ); 
	output.texcoord = float2(0,1);
	spriteStream.Append(output);
	output.pos = prevPos - perp;
	output.pos = mul( output.pos, g_mViewProj ); 
	output.texcoord = float2(0,0);
	spriteStream.Append(output);
	spriteStream.RestartStrip();	



}



float4 particle_fp(in particleGsSimpleOut particle
                   ) : COLOR
{
    float4 sprite = tex2D(samplerZero, particle.texcoord);
    return sprite * particle.color;
}

// lit particle with normal map
float4 particle_lit_fp(in particleGsOut gsOut,
					   uniform float depthScale = 0.002
                       ) : COLOR
{
	float birth_time = gsOut.velocity.w;
    float age = (time - birth_time) / life_time;
	
	//point sprite texcoord expansion emulation using vPos

	float2 vTexCoord = (gsOut.N * 0.5) + 0.5;
	float4	sprite = tex2D( samplerZero, vTexCoord );

	//texkill completely transparent regions of sprite
	clip( sprite.a - 0.01 );

    // compute sphere normal
    float3 vViewSpaceNormal;
	vViewSpaceNormal.xy = gsOut.N.xy;
    float vMag = min( dot( vViewSpaceNormal.xy, vViewSpaceNormal.xy ), 1.0 );
    vViewSpaceNormal.z = sqrt( 1.0 - vMag );

    // bump map
    vViewSpaceNormal += sprite.xyz * 2.0 - 1.0;
    vViewSpaceNormal = normalize( vViewSpaceNormal );
    float3 vWorldSpaceNormal = mul(vViewSpaceNormal, (float3x3) g_mView);

    //just a hack to make it look good for now
    float NdotL = dot( vViewSpaceNormal, float3(0.00, 0.90, 0.40) );  //g_vLightDir);    
    float lighting = 0.7 * NdotL; 
    
    float fAgeFade = sqrt( 1.0 - age );  //speed up fade near the end
    return float4( lighting.xxx, sprite.a * fAgeFade  ); 
}


// render particle as lit sphere
float4 particle_sphere_fp(in particleGsOut gsOut,
                          out float o_depth : DEPTH
                          ) : COLOR
{
    float	birth_time = gsOut.velocity.w;
    float4 color = tex2D(samplerZero, float2(birth_time, 0));

	o_depth = 0.5;

    // compute sphere normal
	float3 N = float3(gsOut.N.x, gsOut.N.y,0);
    float mag = dot(N.xy, N.xy);
    if ( mag > 1.0) 
    {
		discard;   // kill pixels outside circle
    }
    N.z = -sqrt(1.0-mag);

    // compute sphere depth
	float4 epos = gsOut.epos / gsOut.epos.w;
    float4 hpos = mul( float4(epos.xyz + N, 1), g_mProj  );
    o_depth = (hpos.z / hpos.w);
	
	// transform from eye back to world space
    N = mul(N, (float3x3) g_mViewInv );

    // lighting
    float3 L = g_vLightDir.xyz; 
	float3 V = mul(float3(0,0,-1), (float3x3) g_mViewInv  );
    float3 H = normalize(L + V);
    float NdotL = dot(N, L);
    float NdotH = dot(N, H);
    float4 light = lit(NdotL, NdotH, 60.0);
    float3 ambient = 0.1;
    
	return float4(ambient*color.xyz + light.yyy*color.xyz + light.zzz, 1.0);
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
