#include "precompiled.h"

#include "SoundScene.h"

#include "SoundSystemComponent.h"

namespace Sound
{
  SoundScene::~SoundScene()
  {
    delete m_componentFactory;
  }

  ISystemComponent* SoundScene::CreateComponent( const std::string& name, const std::string& type )
  {
    ISoundSystemComponent* component = m_componentFactory->CreateComponent( name, type );

    component->SetAttribute( System::Attributes::SystemType, System::Types::SOUND );
    component->SetAttribute( System::Attributes::Parent, this );

    return component;
  }

  void SoundScene::DestroyComponent( ISystemComponent* component )
  {
    component->Destroy( ); 
    delete component;
  };
}