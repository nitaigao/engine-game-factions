#include "SoundFactory.h"

#include "SoundSystem.h"
#include "SoundScene.h"

namespace Sound
{
	ISoundSystem* SoundFactory::CreateSoundSystem()
	
		//TODO: This is a bug, remove it
		SoundScene* scene = new SoundScene( );
		ISoundSystem* system = new SoundSystem( scene );
		scene->SetSoundSystem( system );
		return system;
	}
}