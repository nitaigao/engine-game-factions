/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Demos/Physics/UseCase/CharacterControl/CharacterRigidBody/StairClimbingRb/StairClimbingRbDemo.h'
#include <Demos/demos.h>
#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Demos/Physics/UseCase/CharacterControl/CharacterRigidBody/StairClimbingRb/StairClimbingRbDemo.h>
#define True true
#define False false



// External pointer and enum types
extern const hkClass hkLoaderClass;
extern const hkClass hkpCharacterContextClass;
extern const hkClass hkpCharacterRigidBodyClass;
extern const hkClass hkpShapeClass;

//
// Class StairClimbingRbDemo::Options
//
static const hkInternalClassMember StairClimbingRbDemo_OptionsClass_Members[] =
{
	{ "worldCollisionTolerance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(StairClimbingRbDemo::Options,m_worldCollisionTolerance), HK_NULL },
	{ "characterCylinderHeight", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(StairClimbingRbDemo::Options,m_characterCylinderHeight), HK_NULL },
	{ "characterRadius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(StairClimbingRbDemo::Options,m_characterRadius), HK_NULL },
	{ "allowedPenetrationDepth", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(StairClimbingRbDemo::Options,m_allowedPenetrationDepth), HK_NULL },
	{ "supportDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(StairClimbingRbDemo::Options,m_supportDistance), HK_NULL },
	{ "hardSupportDistance", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(StairClimbingRbDemo::Options,m_hardSupportDistance), HK_NULL },
	{ "maxSlope", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(StairClimbingRbDemo::Options,m_maxSlope), HK_NULL },
	{ "numStaircases", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(StairClimbingRbDemo::Options,m_numStaircases), HK_NULL },
	{ "numStepsStart", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(StairClimbingRbDemo::Options,m_numStepsStart), HK_NULL },
	{ "numStepsIncrement", HK_NULL, HK_NULL, hkClassMember::TYPE_INT32, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(StairClimbingRbDemo::Options,m_numStepsIncrement), HK_NULL },
	{ "stairsRun", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(StairClimbingRbDemo::Options,m_stairsRun), HK_NULL },
	{ "stairsRise", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(StairClimbingRbDemo::Options,m_stairsRise), HK_NULL },
	{ "stepConvexRadius", HK_NULL, HK_NULL, hkClassMember::TYPE_REAL, hkClassMember::TYPE_VOID, 0, 0, HK_OFFSET_OF(StairClimbingRbDemo::Options,m_stepConvexRadius), HK_NULL }
};
namespace
{
	struct StairClimbingRbDemoOptions_DefaultStruct
	{
		int s_defaultOffsets[13];
		typedef hkInt8 _hkBool;
		typedef hkReal _hkVector4[4];
		typedef hkReal _hkQuaternion[4];
		typedef hkReal _hkMatrix3[12];
		typedef hkReal _hkRotation[12];
		typedef hkReal _hkQsTransform[12];
		typedef hkReal _hkMatrix4[16];
		typedef hkReal _hkTransform[16];
		hkReal m_worldCollisionTolerance;
		hkReal m_characterCylinderHeight;
		hkReal m_characterRadius;
		hkReal m_allowedPenetrationDepth;
		hkReal m_supportDistance;
		hkReal m_maxSlope;
		int m_numStaircases;
		int m_numStepsStart;
		int m_numStepsIncrement;
		hkReal m_stairsRun;
		hkReal m_stairsRise;
		hkReal m_stepConvexRadius;
	};
	const StairClimbingRbDemoOptions_DefaultStruct StairClimbingRbDemoOptions_Default =
	{
		{HK_OFFSET_OF(StairClimbingRbDemoOptions_DefaultStruct,m_worldCollisionTolerance),HK_OFFSET_OF(StairClimbingRbDemoOptions_DefaultStruct,m_characterCylinderHeight),HK_OFFSET_OF(StairClimbingRbDemoOptions_DefaultStruct,m_characterRadius),HK_OFFSET_OF(StairClimbingRbDemoOptions_DefaultStruct,m_allowedPenetrationDepth),HK_OFFSET_OF(StairClimbingRbDemoOptions_DefaultStruct,m_supportDistance),-1,HK_OFFSET_OF(StairClimbingRbDemoOptions_DefaultStruct,m_maxSlope),HK_OFFSET_OF(StairClimbingRbDemoOptions_DefaultStruct,m_numStaircases),HK_OFFSET_OF(StairClimbingRbDemoOptions_DefaultStruct,m_numStepsStart),HK_OFFSET_OF(StairClimbingRbDemoOptions_DefaultStruct,m_numStepsIncrement),HK_OFFSET_OF(StairClimbingRbDemoOptions_DefaultStruct,m_stairsRun),HK_OFFSET_OF(StairClimbingRbDemoOptions_DefaultStruct,m_stairsRise),HK_OFFSET_OF(StairClimbingRbDemoOptions_DefaultStruct,m_stepConvexRadius)},
		0.1f,0.8f,0.6f,-0.1f,0.1f,1.05f,5,5,4,5.f,3.f,0.05f
	};
}
extern const hkClass StairClimbingRbDemoOptionsClass;
const hkClass StairClimbingRbDemoOptionsClass(
	"StairClimbingRbDemoOptions",
	HK_NULL, // parent
	sizeof(StairClimbingRbDemo::Options),
	HK_NULL,
	0, // interfaces
	HK_NULL,
	0, // enums
	reinterpret_cast<const hkClassMember*>(StairClimbingRbDemo_OptionsClass_Members),
	HK_COUNT_OF(StairClimbingRbDemo_OptionsClass_Members),
	&StairClimbingRbDemoOptions_Default,
	HK_NULL, // attributes
	0, // flags
	0 // version
	);
HK_REFLECTION_DEFINE_SCOPED_SIMPLE(StairClimbingRbDemo,Options);

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
