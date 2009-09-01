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

// Fog support
float4 g_cFogColor;
float4 g_iFogParams;

float time;
float life_time = 500.0;
float4 g_vLightDir; //wkn
float3 customLightDir;
float4 g_cDiffuseColor;//wkn
float pointsize = 2.0;
float pointsizeGrowthRate = 20.0;
float pointsizeMax = 10.0;

float4 smokeFrontLitColor;	// used by smoke_particle_vp
float4 smokeBackLitColor;	// used by smoke_particle_vp
float sparkSize;			// used by sparks_particle_vp
float4 debrisFrontLitColor;	// used by debris_particle_vp
float4 debrisBackLitColor;	// used by debris_particle_vp
float4 dustColor1;			// used by dust_particle_vp
float4 dustColor2;			// used by dust_particle_vp
float4 rollingDustColor1;	// used by rolling_dust_particle_vp
float4 rollingDustColor2;	// used by rolling_dust_particle_vp
float nearFadeDist;			// used by dust_particle_vp and rolling_dust_particle_vp
float farFadeDist;			// used by dust_particle_vp and rolling_dust_particle_vp
float explosionAlpha;		// used by dusty_explosion_particle_vp

sampler samplerZero : register(s0);
sampler samplerFour : register(s4);	// Tex 0 if shadows used

struct pixelOutput
{
	float4 color			: COLOR0;  
	float4 pzDepth			: COLOR1; // We normally ourput posView.z in X, so that we can use it for SSAO later on (if wanted). For particles, we don't really want any SSAO alteration, so can just output 0,0,0,0 which will usually not get enter the depth texture at all as particles have modulate blend on. 
};


float ramp(float x, float min, float max, float min_val, float max_val)
{
//	assert(x >= min && x <= max);
    float frac = (x-min) / (max-min);
    return min_val + frac * (max_val-min_val);
}


float getWarpAroundLightingAmount()
{
#ifdef Z_IS_UP
	float3 viewDir = mul(float3(0.0, 1.0, 0.0), (float3x3)g_mView);
#else
	float3 viewDir = mul(float3(0.0, 0.0, -1.0), (float3x3)g_mView);
#endif

	float dotProduct = dot(g_vLightDir, viewDir);

	const float wrap_factor = 1.0, ambient = 0.1;
	float brightness = (dotProduct + wrap_factor) / (1.0 + wrap_factor);
	brightness = max(0.0, brightness);
	brightness += ambient;

	return brightness;
}


float4 getHemisphericalLitColor(float4 frontLitColor, float4 backLitColor)
{
#ifdef Z_IS_UP
	float3 viewDir = mul(float3(0.0, 1.0, 0.0), (float3x3)g_mView);
#else
	float3 viewDir = mul(float3(0.0, 0.0, -1.0), (float3x3)g_mView);
#endif

	float dotProduct = dot(g_vLightDir, viewDir);

	return lerp(backLitColor, frontLitColor, (dotProduct+1.0)/2.0);
}


// This requires smokeFrontLitColor and smokeBackLitColor to be set externally
void smoke_particle_vp
(
	in float4 pos : POSITION,
	in float4 userData : TEXCOORD0,
	out float4 o_hpos : POSITION,
	out float4 o_vPSCenterPos : TEXCOORD0,
	out float4 o_userData : TEXCOORD1,
	out float4 o_color : TEXCOORD2,    
	out float o_pointsize : PSIZE
)
{
	// Inputs:
	// userData.x is sprite
	// userData.y is size
	// userData.z is age fraction
	// pos.w is angle

	o_userData = userData;
    float sine, cosine;
    sincos(pos.w, sine, cosine);
    o_userData.y = cosine * 0.82842712474619;	// 2 / (sqrt(2) + 1)
    o_userData.z = sine * 0.82842712474619;		// 2 / (sqrt(2) + 1)
	pos.w = 1.0;

	const float ageFrac = userData.z;

	float radius = userData.y * ramp(ageFrac, 0.f, 1.f, 0.2f, 2.f);

    float alpha = 1.f;
	if(ageFrac >= 0.5f)
		alpha *= ramp(ageFrac, 0.5f, 1.f, 1.f, 0.f);
//	const float visibility = 0.25;//0.5;
//	o_color = float4(alpha, alpha, alpha, alpha*visibility);
//	o_color = float4(1.0, 1.0, 1.0, alpha*visibility);

//	alpha *= visibility;
	float4 frontLitColor = smokeFrontLitColor;//float4(1.f, 1.f, 1.f, alpha);
	float4 backLitColor = smokeBackLitColor;//float4(0.5f, 0.5f, 0.6f, alpha);
	frontLitColor.a *= alpha;
	backLitColor.a *= alpha;
	o_color = getHemisphericalLitColor(frontLitColor, backLitColor);

    // Compute point size in pixels from size in world space
    float4 wpos = mul(pos, g_mView);	// transform to view space 
    float dist = length(wpos.xyz);		// distance from camera
    float scale = viewportHeight / (tanfov * dist);
    o_pointsize = min(radius*scale, 256);

    // Transform to clip space
    o_hpos = mul(pos, g_mViewProj);
    
    // Output center position and inverse point size to compute tex coords in pixel shader
    o_vPSCenterPos.xy = ((o_hpos.xy / o_hpos.w) * float2(0.5, -0.5) + 0.5);
	o_vPSCenterPos.x *= viewportWidth;
	o_vPSCenterPos.y *= viewportHeight;
    o_vPSCenterPos.z = 1.0 / o_pointsize;
    o_vPSCenterPos.w = 1.0;
}


pixelOutput smoke_particle_fp
(
	in float2 vPos : VPOS,				// screenspace position
	in float4 vPSCenterPos: TEXCOORD0,	// center pos in pixel coordinates (fractional), pointsprite size encoded in z
	in float4 userData : TEXCOORD1,
	in float4 color : TEXCOORD2
) 
{
	// Point sprite texcoord expansion emulation using vPos
	float2 vTexCoord = (vPos.xy - vPSCenterPos.xy) * vPSCenterPos.z + 0.5;

/*
	OLD VERSION:

    // Assumes 4x1 sprite layout
    float tsx = 0.25;
    float tox = (sprite+1.0)*0.25;
    float tsy = 1.0;
    float toy = 0.0;

    float scale = 0.82842712474619;	// 2 / (sqrt(2) + 1)
    float ca = cos(angle) * scale;
    float sa = sin(angle) * scale;

    float a = tsx*ca;
    float b = tsx*sa;
    float c = tox - 0.5*tsx*(ca+sa+1.0);

    float d = -tsy*sa;
    float e = tsy*ca;
    float f = toy - 0.5*tsy*(-sa+ca+1.0);

    float nu = a*vTexCoord.x + b*vTexCoord.y + c;
    float nv = d*vTexCoord.x + e*vTexCoord.y + f;
    
    vTexCoord = float2(nu, nv);
    
    return tex2D(samplerZero, vTexCoord);
*/

    float sprite = userData.x;	// should be in {0,1,2,3} for "smoke_4x1.png"
	float ca = userData.y;
	float sa = userData.z;
	float2x2 xform = { 0.25*ca, 0.25*sa, -sa, ca };
	float2 trans = { 0.25*(sprite+1.0) - 0.125*(ca+sa+1.0), -0.5*(-sa+ca+1.0) };

	vTexCoord = mul(xform, vTexCoord) + trans;

	color.a *= tex2D(samplerZero, vTexCoord).a;

	pixelOutput po;
	po.color = color;
	po.pzDepth = 0;
    return po;
}


// This requires dustColor1, dustColor2, nearFadeDist and farFadeDist to be set externally
void dust_particle_vp
(
	in float4 pos : POSITION,
	in float4 userData : TEXCOORD0,
	out float4 o_hpos : POSITION,
	out float4 o_vPSCenterPos : TEXCOORD0,
	out float4 o_userData : TEXCOORD1,
	out float4 o_color : TEXCOORD2,    
	out float o_pointsize : PSIZE
)
{
	// Inputs:
	// userData.x is sprite
	// userData.y is size
	// userData.z is age fraction
	// pos.w is angle

	o_userData = userData;
    float sine, cosine;
    sincos(pos.w, sine, cosine);
    o_userData.y = cosine * 0.82842712474619;	// 2 / (sqrt(2) + 1)
    o_userData.z = sine * 0.82842712474619;		// 2 / (sqrt(2) + 1)
	pos.w = 1.0;

	const float ageFrac = userData.z;

    float radius = userData.y;
    if(userData.x > 2.9f)	// splash
    {
		// Size increases from 70% to 200% over lifetime
		radius *= ramp(ageFrac, 0.f, 1.f, 0.7f, 2.f);
    }
    else	// fluffy/jets
    {
		// Size is 200% until 0.25 and then decreases to 0% at death
		if(ageFrac < 0.25f)
			radius *= 2.f;
		else
			radius *= ramp(ageFrac, 0.25f, 1.f, 2.f, 0.f);
    }

	// Alpha fades from black at birth to white at 0.1 and back to black at death
	float alpha;
    if(ageFrac < 0.1f)
		alpha = ramp(ageFrac, 0.f, 0.1f, 0.f, 1.f);
	else
		alpha = ramp(ageFrac, 0.1f, 1.f, 1.f, 0.f);
    alpha *= 0.25f;

//	o_color = float4(0.5f, 0.41f, 0.31f, alpha);

//	float brightness = getWarpAroundLightingAmount();
//	o_color = float4(0.5f*brightness, 0.41f*brightness, 0.31f*brightness, alpha);

//	float4 frontLitColor = float4(0.6f, 0.49f, 0.37f, alpha);//float4(1.f, 0.f, 0.f, alpha);
//	float4 backLitColor = float4(0.05f, 0.04f, 0.03f, alpha);//float4(0.f, 1.f, 0.f, alpha);
//	o_color = getHemisphericalLitColor(frontLitColor, backLitColor);

	float frac = userData.w;
//	float r = (130/255.0) + frac * ((60/255.0) - (130/255.0));	// ramp(userData.w, 0.0, 1.0, 130/255.0, 60/255.0);
//	float g = (110/255.0) + frac * ((48/255.0) - (110/255.0));	// ramp(userData.w, 0.0, 1.0, 110/255.0, 48/255.0);
//	float b = (81/255.0) + frac * ((41/255.0) - (81/255.0));	// ramp(userData.w, 0.0, 1.0, 81/255.0, 41/255.0);
//	float4 frontLitColor = float4(r, g, b, alpha);
//	float4 backLitColor = float4(r*0.2f, g*0.2f, b*0.2f, alpha);
	float4 color = dustColor1 + frac*(dustColor2-dustColor1);
	float4 frontLitColor = color;
	float4 backLitColor = float4(color.xyz*0.2, color.w);
	frontLitColor.a *= alpha;
	backLitColor.a *= alpha;
	o_color = getHemisphericalLitColor(frontLitColor, backLitColor);

	// Compute point size in pixels from size in world space
    float4 wpos = mul(pos, g_mView);	// transform to view space 
    float dist = length(wpos.xyz);		// distance from camera
    float scale = viewportHeight / (tanfov * dist);
    o_pointsize = min(radius*scale, 256);

    // Skip particles very close to camera and fade them out near to camera so that they don't pop
	// (nearFadeDist is the distance from the camera at which particle alpha goes to zero;
	// farFadeDist is the distance from the camera at which particle alpha is unmodified)
	if(dist < nearFadeDist)
		pos.w = -1;//o_color = float4(1, 0, 0, 1);	// useful for visualizing distances
	else if(dist < farFadeDist)
		o_color.a *= (dist - nearFadeDist) / (farFadeDist - nearFadeDist);

    // Transform position to clip space
    o_hpos = mul(pos, g_mViewProj);

    // Output center position and inverse point size to compute tex coords in pixel shader
    o_vPSCenterPos.xy = ((o_hpos.xy / o_hpos.w) * float2(0.5, -0.5) + 0.5);
	o_vPSCenterPos.x *= viewportWidth;
	o_vPSCenterPos.y *= viewportHeight;
    o_vPSCenterPos.z = 1.0 / o_pointsize;
    o_vPSCenterPos.w = 1.0;
}


// This requires rollingDustColor1, rollingDustColor2, nearFadeDist and farFadeDist to be set externally
void rolling_dust_particle_vp
(
	in float4 pos : POSITION,
	in float4 userData : TEXCOORD0,
	out float4 o_hpos : POSITION,
	out float4 o_vPSCenterPos : TEXCOORD0,
	out float4 o_userData : TEXCOORD1,
	out float4 o_color : TEXCOORD2,    
	out float o_pointsize : PSIZE
)
{
	// Inputs:
	// userData.x is sprite
	// userData.y is size
	// userData.z is age fraction
	// pos.w is angle

	o_userData = userData;
    float sine, cosine;
    sincos(pos.w, sine, cosine);
    o_userData.y = cosine * 0.82842712474619;	// 2 / (sqrt(2) + 1)
    o_userData.z = sine * 0.82842712474619;		// 2 / (sqrt(2) + 1)
	pos.w = 1.0;

	const float ageFrac = userData.z;

    float radius = userData.y, alpha;

    // Alpha decreases from 100% to 0% over lifetime
    alpha = 1.f - ageFrac;

    if(userData.x > 2.9f)	// splash
		alpha *= 0.5f;

	if(ageFrac < 0.3f)
		radius *= ramp(ageFrac, 0.f, 0.3f, 0.1f, 1.8f);
	else
		radius *= ramp(ageFrac, 0.3f, 1.f, 1.8f, 2.6f);

	float frac = userData.w;
//	float r = (130/255.0) + frac * ((60/255.0) - (130/255.0));	// ramp(userData.w, 0.0, 1.0, 130/255.0, 60/255.0);
//	float g = (110/255.0) + frac * ((48/255.0) - (110/255.0));	// ramp(userData.w, 0.0, 1.0, 110/255.0, 48/255.0);
//	float b = (81/255.0) + frac * ((41/255.0) - (81/255.0));	// ramp(userData.w, 0.0, 1.0, 81/255.0, 41/255.0);
//	float4 frontLitColor = float4(r, g, b, alpha);
//	float4 backLitColor = float4(r*0.2f, g*0.2f, b*0.2f, alpha);
	float4 color = rollingDustColor1 + frac*(rollingDustColor2-rollingDustColor1);
	float4 frontLitColor = color;
	float4 backLitColor = float4(color.xyz*0.2, color.w);
	frontLitColor.a *= alpha;
	backLitColor.a *= alpha;
	o_color = getHemisphericalLitColor(frontLitColor, backLitColor);

	// Compute point size in pixels from size in world space
    float4 wpos = mul(pos, g_mView);	// transform to view space 
    float dist = length(wpos.xyz);		// distance from camera
    float scale = viewportHeight / (tanfov * dist);
    o_pointsize = min(radius*scale, 256);

    // Skip particles very close to camera and fade them out near to camera so that they don't pop
	// (nearFadeDist is the distance from the camera at which particle alpha goes to zero;
	// farFadeDist is the distance from the camera at which particle alpha is unmodified)
	if(dist < nearFadeDist)
		pos.w = -1;//o_color = float4(0, 1, 0, 1);	// useful for visualizing distances
	else if(dist < farFadeDist)
		o_color.a *= (dist - nearFadeDist) / (farFadeDist - nearFadeDist);

    // Transform position to clip space
    o_hpos = mul(pos, g_mViewProj);
    
    // Output center position and inverse point size to compute tex coords in pixel shader
    o_vPSCenterPos.xy = ((o_hpos.xy / o_hpos.w) * float2(0.5, -0.5) + 0.5);
	o_vPSCenterPos.x *= viewportWidth;
	o_vPSCenterPos.y *= viewportHeight;
    o_vPSCenterPos.z = 1.0 / o_pointsize;
    o_vPSCenterPos.w = 1.0;
}


pixelOutput dust_particle_fp
(
	in float2 vPos : VPOS,				// screenspace position
	in float4 vPSCenterPos: TEXCOORD0,	// center pos in pixel coordinates (fractional), pointsprite size encoded in z
	in float4 userData : TEXCOORD1,
	in float4 color : TEXCOORD2
)
{
	// Point sprite texcoord expansion emulation using vPos
	float2 vTexCoord = (vPos.xy - vPSCenterPos.xy) * vPSCenterPos.z + 0.5;

	float sprite = userData.x;	// should be in {0,1,2,3} for "dust_4x1.png"
	float ca = userData.y;
	float sa = userData.z;
	float2x2 xform = { 0.25*ca, 0.25*sa, -sa, ca };
	float2 trans = { 0.25*(sprite+1.0) - 0.125*(ca+sa+1.0), -0.5*(-sa+ca+1.0) };

	vTexCoord = mul(xform, vTexCoord) + trans;

	color.a *= tex2D(samplerZero, vTexCoord).a;

	// Useful for visualizing particle sizes
	//if(color.a < 0.00001)
		//color.a = 1.0;

	pixelOutput po;
	po.color = color;
	po.pzDepth = 0;
    return po;
}


// This requires sparkSize to be set externally
void sparks_particle_vp
(
	in float4 pos : POSITION,
	in float4 userData : TEXCOORD0,
	out float4 o_hpos : POSITION,
	out float4 o_vPSCenterPos : TEXCOORD0,
	out float4 o_userData : TEXCOORD1,
	out float4 o_color : TEXCOORD2,    
	out float o_pointsize : PSIZE
)
{
	// userData.xyz is velocity
	// userData.w is age fraction

	pos.w = 1.0;

	// This will ramp down from 1.0 at birth to 0.0 at death
	float decay = 1.f - userData.w;

	o_color = float4(decay, 0.67*decay, 0.0, decay);

	// Fade particles out as they come to rest
	// (This is only really necessary for collidable sparks)
	float speed = length(userData.xyz);
	if(speed < 0.5)
		o_color.a *= speed;

    // Compute point size in pixels from size in world space
    float4 wpos = mul(pos, g_mView);	// transform to view space 
    float dist = length(wpos.xyz);		// distance from camera
    float scale = viewportHeight / (tanfov * dist);
    o_pointsize = min(sparkSize*scale, 256);

    // Transform position to clip space
    o_hpos = mul(pos, g_mViewProj);

    // Compute "previous" position and transform to clip space
	float4 prevpos = pos - userData;
	prevpos.w = 1.0;
	float4 hprevpos = mul(prevpos, g_mViewProj);

	// Compute angle by which to rotate sprite
	float dx = o_hpos.x - hprevpos.x;
	float dy = o_hpos.y - hprevpos.y;
	float angle = -atan(dy/dx);

    float sine, cosine;
    sincos(angle, sine, cosine);
    o_userData.y = cosine * 0.82842712474619;	// 2 / (sqrt(2) + 1)
    o_userData.z = sine * 0.82842712474619;		// 2 / (sqrt(2) + 1)

    // Output center position and inverse point size to compute tex coords in pixel shader
    o_vPSCenterPos.xy = ((o_hpos.xy / o_hpos.w) * float2(0.5, -0.5) + 0.5);
	o_vPSCenterPos.x *= viewportWidth;
	o_vPSCenterPos.y *= viewportHeight;
    o_vPSCenterPos.z = 1.0 / o_pointsize;
    o_vPSCenterPos.w = 1.0;
}


pixelOutput sparks_particle_fp
(
	in float2 vPos : VPOS,				// screenspace position
	in float4 vPSCenterPos: TEXCOORD0,	// center pos in pixel coordinates (fractional), pointsprite size encoded in z
	in float4 userData : TEXCOORD1,
	in float4 color : TEXCOORD2
)
{
	// Point sprite texcoord expansion emulation using vPos
	float2 vTexCoord = (vPos.xy - vPSCenterPos.xy) * vPSCenterPos.z + 0.5;

	float ca = userData.y;
	float sa = userData.z;
	float2x2 xform = { ca, sa, -sa, ca };
	float2 trans = { -0.5*(ca+sa+1.0), -0.5*(-sa+ca+1.0) };

	vTexCoord = mul(xform, vTexCoord) + trans;

	color.a *= tex2D(samplerZero, vTexCoord).a;

	pixelOutput po;
	po.color = color;
	po.pzDepth = 0;
    return po;
}


// This requires debrisFrontLitColor and debrisBackLitColor to be set externally
void debris_particle_vp
(
	in float4 pos : POSITION,
	in float4 userData : TEXCOORD0,
	out float4 o_hpos : POSITION,
	out float4 o_vPSCenterPos : TEXCOORD0,
	out float4 o_userData : TEXCOORD1,
	out float4 o_color : TEXCOORD2,    
	out float o_pointsize : PSIZE
)
{
	// pos.xyz is position
	// pos.w is angle
	
	// userData.x is sprite
	// userData.y is size
	// userData.z is age fraction
	
	// o_userData.x is sprite column
	// o_userData.y is scaled cosine of angle
	// o_userData.z is scaled sine of angle
	// o_userData.w is sprite row

	o_userData = userData;
    float sine, cosine;
    sincos(pos.w, sine, cosine);
    o_userData.y = cosine * 0.82842712474619;		// 2 / (sqrt(2) + 1)
    o_userData.z = sine * 0.82842712474619;			// 2 / (sqrt(2) + 1)
	o_userData.w = floor(userData.x / 4.0);			// sprite row in {0,1}
	o_userData.x = userData.x - o_userData.w*4.0;	// sprite column in {0,1,2,3}
	pos.w = 1.0;

	const float ageFrac = userData.z;

    float radius = userData.y;

	// Fade out from 0.8 to 1.0
	float alpha;
    if(ageFrac < 0.8f)
		alpha = 1.f;
	else
		alpha = ramp(ageFrac, 0.8f, 1.f, 1.f, 0.f);

//	o_color = float4(1.0, 1.0, 1.0, alpha);

//	float brightness = getWarpAroundLightingAmount();
//	o_color = float4(0.5*brightness, 0.4*brightness, 0.3*brightness, alpha);

	float4 frontLitColor = debrisFrontLitColor;//float4(1.0, 0.8, 0.6, alpha);
	float4 backLitColor = debrisBackLitColor;//float4(0.5, 0.45, 0.4, alpha);
	frontLitColor.a *= alpha;
	backLitColor.a *= alpha;
	o_color = getHemisphericalLitColor(frontLitColor, backLitColor);

    // Compute point size in pixels from size in world space
    float4 wpos = mul(pos, g_mView);	// transform to view space 
    float dist = length(wpos.xyz);		// distance from camera
    float scale = viewportHeight / (tanfov * dist);
    o_pointsize = min(radius*scale, 256);

    // Transform to clip space
    o_hpos = mul(pos, g_mViewProj);
    
    // Output center position and inverse point size to compute tex coords in pixel shader
    o_vPSCenterPos.xy = ((o_hpos.xy / o_hpos.w) * float2(0.5, -0.5) + 0.5);
	o_vPSCenterPos.x *= viewportWidth;
	o_vPSCenterPos.y *= viewportHeight;
    o_vPSCenterPos.z = 1.0 / o_pointsize;
    o_vPSCenterPos.w = 1.0;
}


pixelOutput debris_particle_fp
(
	in float2 vPos : VPOS,				// screenspace position
	in float4 vPSCenterPos: TEXCOORD0,	// center pos in pixel coordinates (fractional), pointsprite size encoded in z
	in float4 userData : TEXCOORD1,
	in float4 color : TEXCOORD2
) 
{
	// Point sprite texcoord expansion emulation using vPos
	float2 vTexCoord = (vPos.xy - vPSCenterPos.xy) * vPSCenterPos.z + 0.5;

    float sprite_column = userData.x;	// in {0,1,2,3}
    float sprite_row = userData.w;		// in {0,1}
	float ca = userData.y;
	float sa = userData.z;
	float2x2 xform = { 0.25*ca, 0.25*sa, -0.5*sa, 0.5*ca };
	float2 trans = { 0.25*(sprite_column+1.0) - 0.125*(ca+sa+1.0), 0.5*sprite_row - 0.25*(-sa+ca+1.0) };

	vTexCoord = mul(xform, vTexCoord) + trans;

    float4 texColor = tex2D(samplerZero, vTexCoord);

	pixelOutput po;
	po.color = texColor * color;
	po.pzDepth = 0;
    return po;
}


// This requires explosionAlpha to be set externally
void dusty_explosion_particle_vp
(
	in float4 pos : POSITION,
	in float4 userData : TEXCOORD0,
	out float4 o_hpos : POSITION,
	out float4 o_vPSCenterPos : TEXCOORD0,
	out float4 o_userData : TEXCOORD1,
	out float4 o_color : TEXCOORD2,    
	out float o_pointsize : PSIZE
)
{
	// Inputs:
	// userData.x is sprite
	// userData.y is size
	// userData.z is age fraction
	// pos.w is angle

	o_userData = userData;
    float sine, cosine;
    sincos(pos.w, sine, cosine);
    o_userData.y = cosine * 0.82842712474619;	// 2 / (sqrt(2) + 1)
    o_userData.z = sine * 0.82842712474619;		// 2 / (sqrt(2) + 1)
	pos.w = 1.0;

	const float ageFrac = userData.z;

    float radius = userData.y;
	if(ageFrac < 0.1)
		radius *= ramp(ageFrac, 0.0, 0.1, 0.0, 1.0);
	else
		radius *= ramp(ageFrac, 0.1, 1.0, 1.0, 2.0);

	// TODO: This is ridiculous. It should be replaced with a lookup table in code or perferably a 1D texture map lookup.
    float r, g, b;
    if(ageFrac < 0.03f)
    {
		r = 1.f;
		g = 1.f;
		b = 1.f;
	}
    else if(ageFrac < 0.045f)
	{
        r = ramp(ageFrac, 0.03f, 0.045f, 255/255.f, 255/255.f);
        g = ramp(ageFrac, 0.03f, 0.045f, 255/255.f, 255/255.f);
        b = ramp(ageFrac, 0.03f, 0.045f, 255/255.f, 0/255.f);
	}
    else if(ageFrac < 0.06f)
	{
        r = ramp(ageFrac, 0.045f, 0.06f, 255/255.f, 255/255.f);
        g = ramp(ageFrac, 0.045f, 0.06f, 255/255.f, 128/255.f);
        b = ramp(ageFrac, 0.045f, 0.06f, 0/255.f, 0/255.f);
	}
    else if(ageFrac < 0.08f)
	{
        r = ramp(ageFrac, 0.06f, 0.08f, 255/255.f, 200/255.f);
        g = ramp(ageFrac, 0.06f, 0.08f, 128/255.f, 0/255.f);
        b = ramp(ageFrac, 0.06f, 0.08f, 0/255.f, 0/255.f);
	}
    else if(ageFrac < 0.15f)
	{
        r = ramp(ageFrac, 0.08f, 0.15f, 200/255.f, 75/255.f);
        g = ramp(ageFrac, 0.08f, 0.15f, 0/255.f, 25/255.f);
        b = ramp(ageFrac, 0.08f, 0.15f, 0/255.f, 25/255.f);
	}
	else
	{
		// smokey
//        float r2 = ramp(userData.w, 0.0, 1.0, 75/255.0, 20/255.0);
//        float g2 = ramp(userData.w, 0.0, 1.0, 25/255.0, 15/255.0);
//        float b2 = ramp(userData.w, 0.0, 1.0, 25/255.0, 15/255.0);

		// dusty
		float frac = userData.w;
		float r2 = (130/255.0) + frac * ((60/255.0) - (130/255.0));	// ramp(userData.w, 0.0, 1.0, 130/255.0, 60/255.0);
		float g2 = (110/255.0) + frac * ((48/255.0) - (110/255.0));	// ramp(userData.w, 0.0, 1.0, 110/255.0, 48/255.0);
		float b2 = (81/255.0) + frac * ((41/255.0) - (81/255.0));	// ramp(userData.w, 0.0, 1.0, 81/255.0, 41/255.0);

        if(ageFrac < 0.3f)
		{
			float frac = (ageFrac-0.15f) / (0.3f-0.15f);
			r = (75/255.f) + frac * (r2-(75/255.f));	// ramp(ageFrac, 0.15f, 0.3f, 75/255.f, r2);
			g = (25/255.f) + frac * (g2-(25/255.f));	// ramp(ageFrac, 0.15f, 0.3f, 25/255.f, g2);
			b = (25/255.f) + frac * (b2-(25/255.f));	// ramp(ageFrac, 0.15f, 0.3f, 25/255.f, b2);
		}
		else
		{
			r = r2;
			g = g2;
			b = b2;
		}

#if 1
		// lighting
		float4 frontLitColor = float4(r, g, b, 0);
		float4 backLitColor = float4(r*0.4f, g*0.4f, b*0.4f, 0);
		float3 viewDir = mul(float3(0.0, 1.0, 0.0), (float3x3)g_mView);
		float dotProduct = dot(g_vLightDir, viewDir);
		float4 col = lerp(backLitColor, frontLitColor, (dotProduct+1.0)/2.0);
		r = col.r;
		g = col.g;
		b = col.b;
#endif		
	}

	float alpha = explosionAlpha;
	if(ageFrac < 0.3)
		alpha *= ramp(userData.z, 0.0, 0.3, 0.6, 1.5);
	else if(ageFrac < 0.7)
		alpha *= 1.5;
	else
		alpha *= ramp(ageFrac, 0.7, 1.0, 1.5, 0.0);

	o_color = float4(r, g, b, alpha);

    // Compute point size in pixels from size in world space
    float4 wpos = mul(pos, g_mView);	// transform to view space 
    float dist = length(wpos.xyz);		// distance from camera
    float scale = viewportHeight / (tanfov * dist);
    o_pointsize = min(radius*scale, 256);

#ifdef ENABLE_FOG
	// Modify o_color due to fog. This could be done in the fragment program but it makes no perceptible difference.
	// TODO: I had to hardcode the fog for now. I can't rely on g_iFogParams because if SSAO is
	// enabled then that does the fogging. But particles are drawn after SSAO so they need to do
	// the fog themselves. But I don’t want to set HKG_ENABLED_FOG to true if SSAO is also on
	// since then non-particle objects will be fogged twice. This issue will need to be revisited.
	const float density = 0.002;
	float depth = wpos.z;
	float ddensity = depth*density;
	float scl = 1.0 / exp( ddensity*ddensity ); // 1/(e^((d*density)^2))
	scl = clamp(scl, 0, 1);
	o_color *= scl;
	o_color += (1 - scl) * float4(g_cFogColor.xyz,0);
#endif

    // Transform to clip space
    o_hpos = mul(pos, g_mViewProj);
    
    // Output center position and inverse point size to compute tex coords in pixel shader
    o_vPSCenterPos.xy = ((o_hpos.xy / o_hpos.w) * float2(0.5, -0.5) + 0.5);
	o_vPSCenterPos.x *= viewportWidth;
	o_vPSCenterPos.y *= viewportHeight;
    o_vPSCenterPos.z = 1.0 / o_pointsize;
    o_vPSCenterPos.w = 1.0;
}


pixelOutput explosion_particle_fp
(
	in float2 vPos : VPOS,				// screenspace position
	in float4 vPSCenterPos: TEXCOORD0,	// center pos in pixel coordinates (fractional), pointsprite size encoded in z
	in float4 userData : TEXCOORD1,
	in float4 color : TEXCOORD2
) 
{
	// Point sprite texcoord expansion emulation using vPos
	float2 vTexCoord = (vPos.xy - vPSCenterPos.xy) * vPSCenterPos.z + 0.5;

	float sprite = userData.x;	// should be in {0,1,2,3} for "explosion_4x1.png"
	float ca = userData.y;
	float sa = userData.z;
	float2x2 xform = { 0.25*ca, 0.25*sa, -sa, ca };
	float2 trans = { 0.25*(sprite+1.0) - 0.125*(ca+sa+1.0), -0.5*(-sa+ca+1.0) };

	vTexCoord = mul(xform, vTexCoord) + trans;

	color.a *= tex2D(samplerZero, vTexCoord).a;

	pixelOutput po;
	po.color = color;
	po.pzDepth = 0;
    return po;
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
