#include "precompiled.h"

#include "InputFactory.h"

#include "InputSystem.h"

namespace Input
{
	IInputSystem* InputFactory::CreateInputSystem()
	{
		return new InputSystem( m_eventManager, m_platformManager, m_serviceManager );
	}
}