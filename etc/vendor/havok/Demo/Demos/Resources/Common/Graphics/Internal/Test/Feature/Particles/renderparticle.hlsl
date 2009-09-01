/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

float4x4 g_mViewProj; // well known name
float4x4 g_mView; //wkn
float4x4 g_mProj;//wkn
float tanfov;
float viewportWidth;
float viewportHeight;

float time;
float life_time = 500.0;
float4 g_vLightDir; //wkn
float3 customLightDir;
float4 g_cDiffuseColor;//wkn
float pointsize = 2.0;
float pointsizeGrowthRate = 20.0;
float pointsizeMax = 10.0;
        
sampler samplerZero : register(s0);
     

void particle_simple_vp(
    in float4 pos : POSITION,
    in float4 velocity : TEXCOORD1,
 //   in float4 color : COLOR0,

    out float4 o_hpos : POSITION,
    out float4 o_velocity : TEXCOORD0,
    out float o_pointsize : PSIZE,
    out float4 o_color : COLOR0
      )
{
    o_velocity = velocity;
    //o_color = color;
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

void particle_vp(in float4 pos : POSITION,
                 in float4 texcoord : TEXCOORD0,
                 in float4 velocity : TEXCOORD1,
                        
                 out float4 o_hpos : POSITION,
                 out float4 o_texcoord : TEXCOORD0,
                 out float4 o_velocity : TEXCOORD1,
                 out float4 o_epos : TEXCOORD2,
                 out float o_pointsize : PSIZE,
                 out float4 o_color : COLOR0
                 )
{
    o_color = g_cDiffuseColor;
    o_velocity = velocity;
    
    // extract data from input texcoords
    float radius = pos.w;
    if (pos.w > 0) pos.w = 1.0;     // negative pos.w means don't render particle
    
    float birth_time = velocity.w;
    float age = (time - birth_time) / life_time;

//    o_pointsize = 1.0 + age*pointsize;
//    o_pointsize = radius * pointsize;
//    o_pointsize = pointsize;

    // compute point size in pixels from size in world space
    float4 wpos = mul(pos, g_mView);   // transform to eye space
    float dist = length(wpos.xyz);  // distance from camera
    float scale = viewportHeight / (tanfov*dist);
    o_pointsize = radius*pointsize*scale;

    // transform to clip space
    o_hpos = mul(pos, g_mViewProj);

	// normalized pixel coords
	o_texcoord.xy = ((o_hpos.xy / o_hpos.w) + float2(1,1)) * 0.5;
	// scale to screen resolution and flip top/bottom
	o_texcoord.y = 1.0 - o_texcoord.y;
	o_texcoord.xy *= float2(viewportWidth,viewportHeight);
	o_texcoord.z = 1.0 / o_pointsize;
	o_texcoord.w = 0;

    // output position in eye space
    o_epos = wpos;
}


// as above, point size grows over time
void particle_grow_vp(
    in float4 pos : POSITION,
    in float2 texcoord : TEXCOORD0,	
    in float4 velocity : TEXCOORD1,
    //in float4 color : COLOR0,
        
    out float4 o_hpos : POSITION,
    out float4 o_vPSCenterPos : TEXCOORD0,
    out float4 o_velocity : TEXCOORD1,
    out float4 o_epos : TEXCOORD2,
    out float4 o_color : TEXCOORD3, //no COLOR0 interp for ps_3_0
    out float  o_age   : TEXCOORD4, //
    out float  o_pointsize : PSIZE
    )
{
    //o_color = color;
    o_color = g_cDiffuseColor;
    
    // extract data from input texcoords
    float radius = pos.w;
    if (pos.w > 0) pos.w = 1.0;     // negative pos.w means don't render particle
    float birth_time = velocity.w;
    float age = (time - birth_time) / life_time;

	o_age = age;

	//pass through velocity, fourth component of velocity is the birth_time
    o_velocity = velocity;

    /*pointsize = pointsize + age * pointsizeGrowthRate; //pointsizeGrowthRate;
    if ( pointsize > pointsizeMax ) 
    {
		pointsize = pointsizeMax; //pointsizeMax;
	}*/	
	float fPointAgeScale = 1.0 + (1.0 * age);
	
    // compute point size in pixels from size in world space
    float4 wpos = mul( pos, g_mView );   // transform to view space 
    float dist = length( wpos.xyz );  // distance from camera
    float scale = viewportHeight / ( tanfov * dist );
    o_pointsize = min(radius * scale * fPointAgeScale, 256);  // radius * pointsize * scale;

    // transform to clip space
    o_hpos = mul(pos, g_mViewProj);
    
    // output position in eye space
    o_epos = mul(pos, g_mView);
    
    //output center position and inverse point size to compute tex coords in pixel shader 
    o_vPSCenterPos.xy = ( (o_hpos.xy / o_hpos.w) * float2(0.5, -0.5) + 0.5 );
	o_vPSCenterPos.x *= viewportWidth;
	o_vPSCenterPos.y *= viewportHeight;
    o_vPSCenterPos.z = 1.0 / o_pointsize;
    o_vPSCenterPos.w = 1.0;
    
}


// generate quad geometry from current and previous position, plus flags
void particle_quad_vp(in float4 currentPos : POSITION,
                      in float4 prevPos : TEXCOORD1,
                      //in float4 color : COLOR0,
                                       
                      out float4 o_hpos : POSITION,                      
                      out float2 o_texcoord : TEXCOORD0,
                      out float4 o_color : COLOR0
                      )
{
    o_color = g_cDiffuseColor; //color;

 	float3 viewDir = mul( float3(0, 0, 1), (float3x3) g_mView );
   
   
    // create perpendicular vector
    float3 delta = currentPos.xyz - prevPos.xyz;
    float len = length(delta);
    float width = len * currentPos.w; // radius
    float3 perp = normalize(cross(delta / len, viewDir)) * width;

	if (currentPos.w > 0) currentPos.w = 1.0;     // negative pos.w means don't render particle
  
    prevPos.xyz = currentPos.xyz - delta*2;

    // which vertex are we?
    half v = prevPos.w;
    half xflag = (v >= 0.5);
    half yflag = (v >= 0.25) && (v <= 0.75);
    
    float3 pos = xflag ? currentPos.xyz : prevPos.xyz;
    pos += yflag ? perp : -perp;

    o_texcoord = float2(xflag, yflag);
    
    // transform to clip space
    o_hpos = mul( float4(pos, currentPos.w), g_mViewProj  );
}

float4 particle_fp(in float4 color : COLOR0,
                   in float2 texcoord : TEXCOORD0,
                   in float4 velocity : TEXCOORD1
                   ) : COLOR
{
    float birth_time = velocity.w;
    float age = (time - birth_time) / life_time;

#if 0
    // rotate sprite
    float ang = age * 5.0;
    float2 centre = { 0.5, 0.5 };
    float2x2 mat;
    mat[0] = float2(cos(ang), sin(ang));
    mat[1] = float2(-sin(ang), cos(ang));
    texcoord = mul(mat, texcoord - centre) + centre;
#endif

    float4 sprite = tex2D(samplerZero, texcoord);

    return sprite * color;
//    return color;
//    return sprite;
}

// alpha decays based on age
float4 particle_decay_fp(in float4 color : COLOR0,
                         in float2 texcoord : TEXCOORD0,
                         in float4 velocity : TEXCOORD1
                         ) : COLOR
{
    float birth_time = velocity.w;
    float age = (time - birth_time) / life_time;

    float4 sprite = tex2D(samplerZero, texcoord);
       
    color.a *= (1.0 - age);

    return sprite * color;
//    return age;
//    return velocity;
}

// lit particle with normal map
float4 particle_lit_fp(in float2 vPos : VPOS,	//screenspace position
                       //in float2 texcoord : TEXCOORD0,
                       in float4 vPSCenterPos: TEXCOORD0,  //center pos in pixel coordinates (fractional)
														   //pointsprite size encoded in z
                       in float4 velocity : TEXCOORD1,
                       in float4 ePos	  : TEXCOORD2,
                       in float4 color    : TEXCOORD3,
                       in float  age      : TEXCOORD4,
                       //out float o_depth : DEPTH,
                       uniform float depthScale = 0.002
                       ) : COLOR
{
	float2	vTexCoord;

    float	birth_time = velocity.w;
    //float	age = (time - birth_time) / 200.0f; //life_time;

	//point sprite texcoord expansion emulation using vPos
	vTexCoord = ( vPos.xy - vPSCenterPos.xy ) * 2.0 * vPSCenterPos.z;
	vTexCoord = vTexCoord * 0.5 + 0.5;
	
#if 0
    // look up in sprite atlas
    float	spriteno = velocity.w;
    float2	atlasCoords = float2( (spriteno * 0.25) + (vTexCoord.x * 0.25), vTexCoord.y );
    float4	sprite = tex2D( samplerZero, atlasCoords );
#else
    float4	sprite = tex2D( samplerZero, vTexCoord );
#endif

	//texkill completely transparent regions of sprite
	clip( sprite.a - 0.01 );

    // compute sphere normal
    float3 vViewSpaceNormal;
    //N.xy = texcoord * float2(2, -2) + float2(-1, 1);    
    vViewSpaceNormal.xy = vTexCoord * float2(2, -2) + float2(-1, 1);
    
    float vMag = min( dot( vViewSpaceNormal.xy, vViewSpaceNormal.xy ), 1.0 );
    vViewSpaceNormal.z = sqrt( 1.0 - vMag );

    // bump map
    vViewSpaceNormal += sprite.xyz * 2.0 - 1.0;
    vViewSpaceNormal = normalize( vViewSpaceNormal );

    // depth replace using eye space depth
    //o_depth = ePos.z - ( sprite.a * depthScale );

    // transform from eye back to world space
    // TODO - pass in eye space light vector to save these instructions
    float3 vWorldSpaceNormal;
    
    vWorldSpaceNormal = mul(vViewSpaceNormal, (float3x3) g_mView);

    //float NdotL = dot( vWorldSpaceNormal, g_vLightDir );    
    
    //just a hack to make it look good for now
    float NdotL = dot( vViewSpaceNormal, float3(0.00, 0.90, 0.40) );  //g_vLightDir);    
    float lighting = 0.7 * NdotL; //( NdotL + 1 ) * 0.5;
    
    //return float4( lighting.xxx, sprite.a ); // * color;
	float fAgeFade = sqrt( 1.0 - age );  //speed up fade near the end
    
    //birth_time
    
    //return float4( frac(0.01 * time.xxx) , sprite.a  ); 
    //return float4( lighting.xxx, sprite.a ); //fAgeFade  ); 
    //return float4( 0.01 * time.xxx, sprite.a ); //fAgeFade  ); 
    return float4( lighting.xxx, sprite.a * fAgeFade  ); //fAgeFade  ); 
    
}


// render particle as lit sphere
float4 particle_sphere_fp(in float2 vPos : VPOS,
//                          in float4 color : COLOR0,
                          in float4 vPSCenterPos : TEXCOORD0,
                          in float4 velocity : TEXCOORD1,
                          in float4 epos : TEXCOORD2,
                          out float o_depth : DEPTH
                          ) : COLOR
{
//    float birth_time = velocity.w;
//    float age = (time - birth_time) / life_time;

	float2	texcoord;

    float	birth_time = velocity.w;
    //float	age = (time - birth_time) / 200.0f; //life_time;

	//point sprite texcoord expansion emulation using vPos
	texcoord = ( vPos - vPSCenterPos.xy ) * 2.0 * vPSCenterPos.z;

    float4 color = tex2D(samplerZero, float2(velocity.w, 0));

	o_depth = 0.5;
    // compute sphere normal
	float3 N = float3(texcoord,0);
    float mag = dot(N.xy, N.xy);
    if ( mag > 1.0) 
    {
#ifdef HKG_PLATFORM_XBOX360
		return float4(0,0,0,0); // discard not supported on xbox
#else
		discard;   // kill pixels outside circle
#endif
    }
    N.z = sqrt(1.0-mag);

    // compute sphere depth
    float4 hpos = mul( float4(epos.xyz - N, 1), g_mProj  );
    o_depth = (hpos.z / hpos.w);
	
	// transform from eye back to world space
    N = mul((float3x3) g_mView, N );

    // lighting
    float3 L = g_vLightDir; L.y = -L.y;
    float3 V = mul((float3x3) g_mView, float3(0,0,1) );
    float3 H = normalize(L + V);
    float NdotL = dot(N, L);
    float NdotH = dot(N, H);
    float4 light = lit(NdotL, NdotH, 60.0);
    float3 ambient = 0.1;
    
	return float4(ambient*color.xyz + light.yyy*color.xyz + light.zzz, 1.0);
}

// render particle as lit sphere
float4 particle_sphere_custom_fp(in float2 vPos : VPOS,
//                          in float4 color : COLOR0,
                          in float4 vPSCenterPos : TEXCOORD0,
                          in float4 velocity : TEXCOORD1,
                          in float4 epos : TEXCOORD2,
                          out float o_depth : DEPTH
                          ) : COLOR
{
//    float birth_time = velocity.w;
//    float age = (time - birth_time) / life_time;

	float2	texcoord;

    float	birth_time = velocity.w;
    //float	age = (time - birth_time) / 200.0f; //life_time;

	//point sprite texcoord expansion emulation using vPos
	texcoord = ( vPos - vPSCenterPos.xy ) * 2.0 * vPSCenterPos.z;

    float4 color = tex2D(samplerZero, float2(velocity.w, 0));

	o_depth = 1;
    // compute sphere normal
	float3 N = float3(texcoord,0);
    float mag = dot(N.xy, N.xy);
    if (mag > 1.0) {
#ifdef HKG_PLATFORM_XBOX360
		return float4(0,0,0,0); // discard not supported on xbox
#else
		discard;   // kill pixels outside circle
#endif
    }
    N.z = sqrt(1.0-mag);

	// compute sphere depth
	float4 hpos = mul( g_mProj, float4(epos.xyz - N, 1) );
    o_depth = (hpos.z / hpos.w);// *0.5+0.5;
	//o_depth = (epos.z / epos.w);

    // transform from eye back to world space
    N = mul((float3x3) g_mView, N );

    // lighting
    float3 L = customLightDir; L.y = -L.y;
    float3 V = mul((float3x3) g_mView, float3(0,0,1) );
    float3 H = normalize(L + V);
    float NdotL = dot(N, L);
    float NdotH = dot(N, H);
    float4 light = lit(NdotL, NdotH, 60.0);
    float3 ambient = 0.1;
    
     return float4(ambient*color.xyz + light.yyy*color.xyz + light.zzz, 1.0);
}

// optimized version without depth replace and simple lighting
float4 particle_sphere_fast_fp(in float4 wpos : WPOS,
//                               in float4 color : COLOR0,
                               in float2 texcoord : TEXCOORD0,
                               in float4 velocity : TEXCOORD1,
                               in float4 epos : TEXCOORD2
                               //out float o_depth : DEPTH
                               ) : COLOR
{
    float4 color = tex2D(samplerZero, float2(velocity.w, 0));

    // compute sphere normal
    float3 N;
    N.xy = texcoord*float2(2,-2) + float2(-1,1);
    float mag = dot(N.xy, N.xy);
    if (mag > 1) discard;   // kill pixels outside circle
    N.z = sqrt(1-mag);

    // compute sphere depth
//    float4 hpos = mul(g_mProj, float4(epos.xyz + N, 1.0));
//    o_depth = (hpos.z / hpos.w)*0.5+0.5;

    // transform from eye back to world space
    N = mul(N, (float3x3) g_mView);

    // lighting
    float3 L = g_vLightDir;     
    float NdotL = dot(N, L);
    
    return float4((NdotL+1)*0.5*color.xyz, 1.0);
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
