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

///////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////

struct smokeVpOut
{
	float4 worldPos	: POSITION;
	float angle		: TEXCOORD0;
	float radius	: TEXCOORD1;
	float sprite	: TEXCOORD2;
	float4 color    : COLOR0;
};

struct smokeGsOut
{
	float4 pos		: SV_Position;
	float2 texcoord	: TEXCOORD0;
	float4 color	: COLOR;
};

// This requires smokeFrontLitColor and smokeBackLitColor to be set externally
void smoke_particle_vp(in float4 pos : POSITION, in float4 userData : TEXCOORD1, out smokeVpOut output)
{
	// Inputs:
	// pos.w is angle (in radians)
	// userData.x is sprite (in {0,1,2,3} for "smoke_4x1.png")
	// userData.y is size
	// userData.z is age fraction

	const float size = userData.y;
	const float ageFrac = userData.z;

	output.angle = pos.w;
	output.radius = size * ramp(ageFrac, 0.f, 1.f, 0.2f, 2.f);
	output.sprite = userData.x;

    float alpha = 1.f;
	if(ageFrac >= 0.5f)
		alpha = ramp(ageFrac, 0.5f, 1.f, 1.f, 0.f);

	float4 frontLitColor = smokeFrontLitColor;
	float4 backLitColor = smokeBackLitColor;
	frontLitColor.a *= alpha;
	backLitColor.a *= alpha;
	output.color = getHemisphericalLitColor(frontLitColor, backLitColor);

	pos.w = 1.0;
    output.worldPos = pos;

#ifdef LIMIT_DX10_PARTICLE_SIZE
	float4 wpos = mul(pos, g_mView);	// transform to view space 
	float dist = length(wpos.xyz);		// distance from camera
	float scale = viewportHeight / (tanfov * dist);
	if(output.radius*scale > 256)
		output.radius = 256/scale;
#endif
}

[maxvertexcount(4)]
void smoke_particle_gs(point smokeVpOut input[1], inout TriangleStream<smokeGsOut> spriteStream)
{
    smokeGsOut output;
	output.color = input[0].color;	

    float sa, ca;
    sincos(input[0].angle, sa, ca);
	sa *= 0.82842712474619;	// This scaling is only for consistency with the pre-DX10 shaders
	ca *= 0.82842712474619;
	float2x2 xform = { 0.25*ca, 0.25*sa, -sa, ca };
	float2 trans = { 0.25*(input[0].sprite+1.0) - 0.125*(ca+sa+1.0), -0.5*(-sa+ca+1.0) };

    float3 position = mul(float3(-1,1,0)*input[0].radius, (float3x3)g_mViewInv) + input[0].worldPos;
	output.pos = mul(float4(position,1.0), g_mViewProj);
	output.texcoord = mul(xform, float2(0,0)) + trans;
	spriteStream.Append(output);

    position = mul(float3(1,1,0)*input[0].radius, (float3x3)g_mViewInv) + input[0].worldPos;
	output.pos = mul(float4(position,1.0), g_mViewProj);
	output.texcoord = mul(xform, float2(1,0)) + trans;
	spriteStream.Append(output);

    position = mul(float3(-1,-1,0)*input[0].radius, (float3x3)g_mViewInv) + input[0].worldPos;
	output.pos = mul(float4(position,1.0), g_mViewProj);
	output.texcoord = mul(xform, float2(0,1)) + trans;
	spriteStream.Append(output);

    position = mul(float3(1,-1,0)*input[0].radius, (float3x3)g_mViewInv) + input[0].worldPos;
	output.pos = mul(float4(position,1.0), g_mViewProj);
	output.texcoord = mul(xform, float2(1,1)) + trans;
	spriteStream.Append(output);

    spriteStream.RestartStrip();
}

float4 smoke_particle_fp(in smokeGsOut gsOut) : COLOR
{
	float4 color = gsOut.color;
	color.a *= tex2D(samplerZero, gsOut.texcoord).a;
	return color;
}

///////////////////////////////////////////////////////////////////////////////

struct dustVpOut
{
	float4 worldPos	: POSITION;
	float angle		: TEXCOORD0;
	float radius	: TEXCOORD1;
	float sprite	: TEXCOORD2;
	float4 color    : COLOR0;
};

struct dustGsOut
{
	float4 pos		: SV_Position;
	float2 texcoord	: TEXCOORD0;
	float4 color	: COLOR;
};

// This requires dustColor1, dustColor2, nearFadeDist and farFadeDist to be set externally
void dust_particle_vp(in float4 pos : POSITION, in float4 userData : TEXCOORD1, out dustVpOut output)
{
	// Inputs:
	// pos.w is angle (in radians)
	// userData.x is sprite (in {0,1,2,3} for "dust_4x1.png")
	// userData.y is size
	// userData.z is age fraction
	// userData.w is color lerp fraction (in [0,1])

	const float ageFrac = userData.z;

	output.angle = pos.w;
	output.sprite = userData.x;

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
	output.radius = radius;

	// Alpha fades from black at birth to white at 0.1 and back to black at death
	float alpha;
    if(ageFrac < 0.1f)
		alpha = ramp(ageFrac, 0.f, 0.1f, 0.f, 1.f);
	else
		alpha = ramp(ageFrac, 0.1f, 1.f, 1.f, 0.f);
    alpha *= 0.25f;

	float4 color = dustColor1 + userData.w*(dustColor2-dustColor1);
	float4 frontLitColor = color;
	float4 backLitColor = float4(color.xyz*0.2, color.w);
	frontLitColor.a *= alpha;
	backLitColor.a *= alpha;
	output.color = getHemisphericalLitColor(frontLitColor, backLitColor);

	pos.w = 1.0;
    output.worldPos = pos;
    
    // Skip particles very close to camera and fade them out near to camera so that they don't pop
	// (nearFadeDist is the distance from the camera at which particle alpha goes to zero;
	// farFadeDist is the distance from the camera at which particle alpha is unmodified)
    float4 wpos = mul(pos, g_mView);	// transform to view space 
    float dist = length(wpos.xyz);		// distance from camera
	if(dist < nearFadeDist)
		output.worldPos.w = -1;//o_color = float4(1, 0, 0, 1);	// useful for visualizing distances
	else if(dist < farFadeDist)
		output.color.a *= (dist - nearFadeDist) / (farFadeDist - nearFadeDist);

#ifdef LIMIT_DX10_PARTICLE_SIZE
	float scale = viewportHeight / (tanfov * dist);
	if(output.radius*scale > 256)
		output.radius = 256/scale;
#endif
}

// This requires rollingDustColor1, rollingDustColor2, nearFadeDist and farFadeDist to be set externally
void rolling_dust_particle_vp(in float4 pos : POSITION, in float4 userData : TEXCOORD1, out dustVpOut output)
{
	// Inputs:
	// pos.w is angle (in radians)
	// userData.x is sprite (in {0,1,2,3} for "dust_4x1.png")
	// userData.y is size
	// userData.z is age fraction
	// userData.w is color lerp fraction (in [0,1])

	const float size = userData.y;
	const float ageFrac = userData.z;

	output.angle = pos.w;
	output.sprite = userData.x;

	if(ageFrac < 0.3f)
		output.radius = size * ramp(ageFrac, 0.f, 0.3f, 0.1f, 1.8f);
	else
		output.radius = size * ramp(ageFrac, 0.3f, 1.f, 1.8f, 2.6f);

    // Alpha decreases from 100% to 0% over lifetime
    float alpha = 1.f - ageFrac;
    if(userData.x > 2.9f)	// splash
		alpha *= 0.5f;

	float4 color = rollingDustColor1 + userData.w*(rollingDustColor2-rollingDustColor1);
	float4 frontLitColor = color;
	float4 backLitColor = float4(color.xyz*0.2, color.w);
	frontLitColor.a *= alpha;
	backLitColor.a *= alpha;
	output.color = getHemisphericalLitColor(frontLitColor, backLitColor);

	pos.w = 1.0;
    output.worldPos = pos;

    // Skip particles very close to camera and fade them out near to camera so that they don't pop
	// (nearFadeDist is the distance from the camera at which particle alpha goes to zero;
	// farFadeDist is the distance from the camera at which particle alpha is unmodified)
    float4 wpos = mul(pos, g_mView);	// transform to view space 
    float dist = length(wpos.xyz);		// distance from camera
	if(dist < nearFadeDist)
		output.worldPos.w = -1;//o_color = float4(0, 1, 0, 1);	// useful for visualizing distances
	else if(dist < farFadeDist)
		output.color.a *= (dist - nearFadeDist) / (farFadeDist - nearFadeDist);

#ifdef LIMIT_DX10_PARTICLE_SIZE
	float scale = viewportHeight / (tanfov * dist);
	if(output.radius*scale > 256)
		output.radius = 256/scale;
#endif
}

[maxvertexcount(4)]
void dust_particle_gs(point dustVpOut input[1], inout TriangleStream<dustGsOut> spriteStream)
{
	// Skip this particle if the vertex shader told us to
	if(input[0].worldPos.w < 0)
		return;
	input[0].worldPos.w = 1;

    dustGsOut output;
	output.color = input[0].color;	

    float sa, ca;
    sincos(input[0].angle, sa, ca);
	sa *= 0.82842712474619;	// This scaling is only for consistency with the pre-DX10 shaders
	ca *= 0.82842712474619;
	float2x2 xform = { 0.25*ca, 0.25*sa, -sa, ca };
	float2 trans = { 0.25*(input[0].sprite+1.0) - 0.125*(ca+sa+1.0), -0.5*(-sa+ca+1.0) };

    float3 position = mul(float3(-1,1,0)*input[0].radius, (float3x3)g_mViewInv) + input[0].worldPos;
	output.pos = mul(float4(position,1.0), g_mViewProj);
	output.texcoord = mul(xform, float2(0,0)) + trans;
	spriteStream.Append(output);

    position = mul(float3(1,1,0)*input[0].radius, (float3x3)g_mViewInv) + input[0].worldPos;
	output.pos = mul(float4(position,1.0), g_mViewProj);
	output.texcoord = mul(xform, float2(1,0)) + trans;
	spriteStream.Append(output);

    position = mul(float3(-1,-1,0)*input[0].radius, (float3x3)g_mViewInv) + input[0].worldPos;
	output.pos = mul(float4(position,1.0), g_mViewProj);
	output.texcoord = mul(xform, float2(0,1)) + trans;
	spriteStream.Append(output);

    position = mul(float3(1,-1,0)*input[0].radius, (float3x3)g_mViewInv) + input[0].worldPos;
	output.pos = mul(float4(position,1.0), g_mViewProj);
	output.texcoord = mul(xform, float2(1,1)) + trans;
	spriteStream.Append(output);

    spriteStream.RestartStrip();
}

float4 dust_particle_fp(in dustGsOut gsOut) : COLOR
{
	float4 color = gsOut.color;
	color.a *= tex2D(samplerZero, gsOut.texcoord).a;
	return color;
}

///////////////////////////////////////////////////////////////////////////////

struct sparksVpOut
{
	float4 worldPos	: POSITION;
	float angle		: TEXCOORD0;
	float radius	: TEXCOORD1;
	float4 color    : COLOR0;
};

struct sparksGsOut
{
	float4 pos		: SV_Position;
	float2 texcoord	: TEXCOORD0;
	float4 color	: COLOR;
};

// This requires sparkSize to be set externally
void sparks_particle_vp(in float4 pos : POSITION, in float4 userData : TEXCOORD1, out sparksVpOut output)
{
	// Inputs:
	// userData.xyz is velocity
	// userData.w is age fraction

	output.radius = sparkSize;

	// This will ramp down from 1.0 at birth to 0.0 at death
	float decay = 1.f - userData.w;
	output.color = float4(decay, 0.67*decay, 0.0, decay);

	// Fade particles out as they come to rest
	// (This is only really necessary for collidable sparks)
	float speed = length(userData.xyz);
	if(speed < 0.5)
		output.color.a *= speed;

	pos.w = 1.0;
    output.worldPos = pos;

    // Compute "previous" position
	float4 prevpos = pos - userData;
	prevpos.w = 1.0;

    // Transform pos and prevpos to clip space
    float4 hpos = mul(pos, g_mViewProj);
	float4 hprevpos = mul(prevpos, g_mViewProj);

	// Compute angle by which to rotate sprite
	float dx = hpos.x - hprevpos.x;
	float dy = hpos.y - hprevpos.y;
	output.angle = -atan(dy/dx);
}

[maxvertexcount(4)]
void sparks_particle_gs(point sparksVpOut input[1], inout TriangleStream<sparksGsOut> spriteStream)
{
    sparksGsOut output;
	output.color = input[0].color;	

    float sa, ca;
    sincos(input[0].angle, sa, ca);
	sa *= 0.82842712474619;	// This scaling is only for consistency with the pre-DX10 shaders
	ca *= 0.82842712474619;
	float2x2 xform = { ca, sa, -sa, ca };
	float2 trans = { -0.5*(ca+sa+1.0), -0.5*(-sa+ca+1.0) };

    float3 position = mul(float3(-1,1,0)*input[0].radius, (float3x3)g_mViewInv) + input[0].worldPos;
	output.pos = mul(float4(position,1.0), g_mViewProj);
	output.texcoord = mul(xform, float2(0,0)) + trans;
	spriteStream.Append(output);

    position = mul(float3(1,1,0)*input[0].radius, (float3x3)g_mViewInv) + input[0].worldPos;
	output.pos = mul(float4(position,1.0), g_mViewProj);
	output.texcoord = mul(xform, float2(1,0)) + trans;
	spriteStream.Append(output);

    position = mul(float3(-1,-1,0)*input[0].radius, (float3x3)g_mViewInv) + input[0].worldPos;
	output.pos = mul(float4(position,1.0), g_mViewProj);
	output.texcoord = mul(xform, float2(0,1)) + trans;
	spriteStream.Append(output);

    position = mul(float3(1,-1,0)*input[0].radius, (float3x3)g_mViewInv) + input[0].worldPos;
	output.pos = mul(float4(position,1.0), g_mViewProj);
	output.texcoord = mul(xform, float2(1,1)) + trans;
	spriteStream.Append(output);

    spriteStream.RestartStrip();
}

float4 sparks_particle_fp(in sparksGsOut gsOut) : COLOR
{
	float4 color = gsOut.color;
	color.a *= tex2D(samplerZero, gsOut.texcoord).a;
	return color;
}

///////////////////////////////////////////////////////////////////////////////

struct debrisVpOut
{
	float4 worldPos	: POSITION;
	float angle		: TEXCOORD0;
	float radius	: TEXCOORD1;
	float sprite	: TEXCOORD2;
	float4 color    : COLOR0;
};

struct debrisGsOut
{
	float4 pos		: SV_Position;
	float2 texcoord	: TEXCOORD0;
	float4 color	: COLOR;
};

// This requires debrisFrontLitColor and debrisBackLitColor to be set externally
void debris_particle_vp(in float4 pos : POSITION, in float4 userData : TEXCOORD1, out debrisVpOut output)
{
	// Inputs:
	// pos.w is angle (in radians)
	// userData.x is sprite (in {0,..,7} for "debris_4x2.png")
	// userData.y is size
	// userData.z is age fraction

	const float ageFrac = userData.z;

	output.angle = pos.w;
	output.radius = userData.y;
	output.sprite = userData.x;

	// Fade out from 0.8 to 1.0
    float alpha = 1.f;
	if(ageFrac > 0.8f)
		alpha = ramp(ageFrac, 0.5f, 1.f, 1.f, 0.f);

	float4 frontLitColor = debrisFrontLitColor;
	float4 backLitColor = debrisBackLitColor;
	frontLitColor.a *= alpha;
	backLitColor.a *= alpha;
	output.color = getHemisphericalLitColor(frontLitColor, backLitColor);

	pos.w = 1.0;
    output.worldPos = pos;
}

[maxvertexcount(4)]
void debris_particle_gs(point debrisVpOut input[1], inout TriangleStream<debrisGsOut> spriteStream)
{
    debrisGsOut output;
	output.color = input[0].color;

    float sa, ca;
    sincos(input[0].angle, sa, ca);
	sa *= 0.82842712474619;	// This scaling is only for consistency with the pre-DX10 shaders
	ca *= 0.82842712474619;
	float sprite_row = floor(input[0].sprite / 4.0);		// sprite row in {0,1}
	float sprite_col = input[0].sprite - sprite_row*4.0;	// sprite column in {0,1,2,3}
	float2x2 xform = { 0.25*ca, 0.25*sa, -0.5*sa, 0.5*ca };
	float2 trans = { 0.25*(sprite_col+1.0) - 0.125*(ca+sa+1.0), 0.5*sprite_row - 0.25*(-sa+ca+1.0) };

    float3 position = mul(float3(-1,1,0)*input[0].radius, (float3x3)g_mViewInv) + input[0].worldPos;
	output.pos = mul(float4(position,1.0), g_mViewProj);
	output.texcoord = mul(xform, float2(0,0)) + trans;
	spriteStream.Append(output);

    position = mul(float3(1,1,0)*input[0].radius, (float3x3)g_mViewInv) + input[0].worldPos;
	output.pos = mul(float4(position,1.0), g_mViewProj);
	output.texcoord = mul(xform, float2(1,0)) + trans;
	spriteStream.Append(output);

    position = mul(float3(-1,-1,0)*input[0].radius, (float3x3)g_mViewInv) + input[0].worldPos;
	output.pos = mul(float4(position,1.0), g_mViewProj);
	output.texcoord = mul(xform, float2(0,1)) + trans;
	spriteStream.Append(output);

    position = mul(float3(1,-1,0)*input[0].radius, (float3x3)g_mViewInv) + input[0].worldPos;
	output.pos = mul(float4(position,1.0), g_mViewProj);
	output.texcoord = mul(xform, float2(1,1)) + trans;
	spriteStream.Append(output);

    spriteStream.RestartStrip();
}

float4 debris_particle_fp(in debrisGsOut gsOut) : COLOR
{
	return gsOut.color * tex2D(samplerZero, gsOut.texcoord);
}

///////////////////////////////////////////////////////////////////////////////

struct explosionVpOut
{
	float4 worldPos	: POSITION;
	float angle		: TEXCOORD0;
	float radius	: TEXCOORD1;
	float sprite	: TEXCOORD2;
	float4 color    : COLOR0;
};

struct explosionGsOut
{
	float4 pos		: SV_Position;
	float2 texcoord	: TEXCOORD0;
	float4 color	: COLOR;
};

// This requires explosionAlpha to be set externally
void dusty_explosion_particle_vp(in float4 pos : POSITION, in float4 userData : TEXCOORD1, out explosionVpOut output)
{
	// Inputs:
	// pos.w is angle (in radians)
	// userData.x is sprite (in {0,1,2,3} for "explosion_4x1.png")
	// userData.y is size
	// userData.z is age fraction
	// userData.w is color lerp fraction (in [0,1])

	const float size = userData.y;
	const float ageFrac = userData.z;
	const float lerpFrac = userData.w;

	output.angle = pos.w;
	output.sprite = userData.x;

	if(ageFrac < 0.1)
		output.radius = size * ramp(ageFrac, 0.0, 0.1, 0.0, 1.0);
	else
		output.radius = size * ramp(ageFrac, 0.1, 1.0, 1.0, 2.0);

	float alpha = explosionAlpha;
	if(ageFrac < 0.3)
		alpha *= ramp(ageFrac, 0.0, 0.3, 0.6, 1.5);
	else if(ageFrac < 0.7)
		alpha *= 1.5;
	else
		alpha *= ramp(ageFrac, 0.7, 1.0, 1.5, 0.0);

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
//        float r2 = ramp(lerpFrac, 0.0, 1.0, 75/255.0, 20/255.0);
//        float g2 = ramp(lerpFrac, 0.0, 1.0, 25/255.0, 15/255.0);
//        float b2 = ramp(lerpFrac, 0.0, 1.0, 25/255.0, 15/255.0);

		// dusty
		float r2 = (130/255.0) + lerpFrac * ((60/255.0) - (130/255.0));
		float g2 = (110/255.0) + lerpFrac * ((48/255.0) - (110/255.0));
		float b2 = (81/255.0) + lerpFrac * ((41/255.0) - (81/255.0));

        if(ageFrac < 0.3f)
		{
			float frac = (ageFrac-0.15f) / (0.3f-0.15f);
			r = (75/255.f) + frac * (r2-(75/255.f));
			g = (25/255.f) + frac * (g2-(25/255.f));
			b = (25/255.f) + frac * (b2-(25/255.f));
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

	output.color = float4(r, g, b, alpha);

#if defined(ENABLE_FOG) || defined(LIMIT_DX10_PARTICLE_SIZE)
    float4 wpos = mul(pos, g_mView);	// transform position to view space
#endif

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
	output.color *= scl;
	output.color += (1 - scl) * float4(g_cFogColor.xyz,0);
#endif

	pos.w = 1.0;
    output.worldPos = pos;

#ifdef LIMIT_DX10_PARTICLE_SIZE
	float dist = length(wpos.xyz);	// distance from camera
	float scale = viewportHeight / (tanfov * dist);
	if(output.radius*scale > 256)
		output.radius = 256/scale;
#endif
}

[maxvertexcount(4)]
void explosion_particle_gs(point explosionVpOut input[1], inout TriangleStream<explosionGsOut> spriteStream)
{
    explosionGsOut output;
	output.color = input[0].color;	

    float sa, ca;
    sincos(input[0].angle, sa, ca);
	sa *= 0.82842712474619;	// This scaling is only for consistency with the pre-DX10 shaders
	ca *= 0.82842712474619;
	float2x2 xform = { 0.25*ca, 0.25*sa, -sa, ca };
	float2 trans = { 0.25*(input[0].sprite+1.0) - 0.125*(ca+sa+1.0), -0.5*(-sa+ca+1.0) };

    float3 position = mul(float3(-1,1,0)*input[0].radius, (float3x3)g_mViewInv) + input[0].worldPos;
	output.pos = mul(float4(position,1.0), g_mViewProj);
	output.texcoord = mul(xform, float2(0,0)) + trans;
	spriteStream.Append(output);

    position = mul(float3(1,1,0)*input[0].radius, (float3x3)g_mViewInv) + input[0].worldPos;
	output.pos = mul(float4(position,1.0), g_mViewProj);
	output.texcoord = mul(xform, float2(1,0)) + trans;
	spriteStream.Append(output);

    position = mul(float3(-1,-1,0)*input[0].radius, (float3x3)g_mViewInv) + input[0].worldPos;
	output.pos = mul(float4(position,1.0), g_mViewProj);
	output.texcoord = mul(xform, float2(0,1)) + trans;
	spriteStream.Append(output);

    position = mul(float3(1,-1,0)*input[0].radius, (float3x3)g_mViewInv) + input[0].worldPos;
	output.pos = mul(float4(position,1.0), g_mViewProj);
	output.texcoord = mul(xform, float2(1,1)) + trans;
	spriteStream.Append(output);

    spriteStream.RestartStrip();
}

float4 explosion_particle_fp(in explosionGsOut gsOut) : COLOR
{
	float4 color = gsOut.color;
	color.a *= tex2D(samplerZero, gsOut.texcoord).a;
	return color;
}

///////////////////////////////////////////////////////////////////////////////

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
