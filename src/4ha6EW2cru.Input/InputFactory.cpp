#include "InputFactory.h"

#include "InputSystem.h"
#include "Management/Management.h"

namespace Input
{
	IInputSystem* InputFactory::CreateInputSystem()
	{
		return new InputSystem( Management::Get( )->GetEventManager( ) );
	}
}