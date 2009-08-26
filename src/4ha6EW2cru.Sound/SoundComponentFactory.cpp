#include "SoundComponentFactory.h"

#include "SoundSystemComponent.h"

namespace Sound
{
	ISoundSystemComponent* SoundComponentFactory::CreateComponent( const std::string& name, const std::string& type )
	{
		ISoundSystemComponent* component = new SoundSystemComponent( name, m_eventSystem );

		component->SetAttribute( System::Attributes::Name, name );
		component->SetAttribute( System::Attributes::ComponentType, type );

		return component;
	}
}