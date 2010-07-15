#include "precompiled.h"
#include "WorldEntityFactory.h"

#include "WorldEntity.h"

namespace State
{
	IWorldEntity* WorldEntityFactory::CreateEntity(const std::string& name) const
	{
		return new WorldEntity(name);
	}
}