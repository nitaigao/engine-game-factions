#include "precompiled.h"

#include "PhysicsSystemComponent.h"

#include "Maths/MathTools.hpp"
using namespace Maths;

#include "IO/IResource.hpp"
using namespace Resources;

namespace Physics
{
  PhysicsSystemComponent::~PhysicsSystemComponent( )
  {
    std::string name = _name;
    if ( m_body != 0 )
    {
      _scene->GetSystem( )->GetWorld( )->removeEntity( m_body );
    }

    if ( m_loadedData != 0 )
    {
      m_loadedData->removeReference( );
    }
  }

  void PhysicsSystemComponent::Initialize( )
  {
    std::string bodyPath = m_attributes[ System::Parameters::Body ].As< std::string >( );

    IResource* resource = m_resourceCache->GetResource( bodyPath );

    hkIstream istreamFromMemory( resource->GetFileBuffer( )->fileBytes, resource->GetFileBuffer( )->fileLength );
    hkStreamReader* streamReader = istreamFromMemory.getStreamReader( );

    hkBinaryPackfileReader reader;
    reader.loadEntireFile( streamReader );

    hkVersionUtil::updateToCurrentVersion( reader, hkVersionRegistry::getInstance() );

    m_loadedData = reader.getPackfileData( );
    m_loadedData->addReference( );

    hkRootLevelContainer* container = static_cast< hkRootLevelContainer* >( reader.getContents( "hkRootLevelContainer" ) );
    hkpPhysicsData* physicsData = static_cast< hkpPhysicsData* >( container->findObjectByType( "hkpPhysicsData" ) );

    m_body = physicsData->findRigidBodyByName( _name.c_str( ) );
    _scene->GetSystem( )->GetWorld( )->addEntity( m_body );
  }

  AnyType PhysicsSystemComponent::PushMessage( const System::MessageType& message, AnyType::AnyTypeMap parameters )
  {
    return m_observer->Observe( this, message, parameters );
  }

  AnyType PhysicsSystemComponent::Observe( const ISubject* subject, const System::MessageType& message, AnyType::AnyTypeMap parameters )
  {
    if ( m_body )
    {
      if ( message == System::Messages::SetPosition )
      {
        MathVector3 position = parameters[ System::Attributes::Position ].As< MathVector3 >( );
        m_body->setPosition( MathTools::AshkVector4( position ) );
      }

      if ( message == System::Messages::SetOrientation )
      {
        m_body->setRotation( MathTools::AshkQuaternion( parameters[ System::Attributes::Orientation ].As< MathQuaternion >( ) ) );
      }
    }

    return AnyType( );
  }
}