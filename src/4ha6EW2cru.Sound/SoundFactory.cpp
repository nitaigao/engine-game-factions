#include "SoundFactory.h"

#include "SoundSystem.h"
#include "SoundScene.h"
#include "SoundEventSystem.h"
#include "SoundComponentFactory.h"

namespace Sound
{
	ISoundSystem* SoundFactory::CreateSoundSystem()
	{	
		SoundEventSystem* eventSystem = new SoundEventSystem( );
		SoundScene* scene = new SoundScene( new SoundComponentFactory( eventSystem ) );
		ISoundSystem* system = new SoundSystem( m_serviceManager, m_resourceCache, scene, eventSystem );
		return system;
	}
}