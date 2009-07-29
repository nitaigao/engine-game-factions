#include "GeometrySystem.h"

#include "GeometrySystemScene.h"

#include "Maths/MathQuaternion.hpp"
#include "Maths/MathVector3.hpp"
using namespace Maths;

#include "System/SystemTypeMapper.hpp"
using namespace System;

#include "Management/Management.h"

namespace Geometry
{
	ISystemScene* GeometrySystem::CreateScene( )
	{
		return new GeometrySystemScene( this );
	}
};