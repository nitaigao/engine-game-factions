#include "precompiled.h"

#include "NetworkSystemComponent.h"

#include "Maths/MathVector3.hpp"
using namespace Maths;

#include "Logging/Logger.h"
using namespace Logging;

namespace Network
{
  AnyType NetworkSystemComponent::Observe(const ISubject* subject, const System::MessageType& message, AnyType::AnyTypeMap parameters)
  {
    if (message == System::Messages::SetPosition)
    {
      m_attributes[ System::Attributes::Position ] = parameters[ System::Attributes::Position ].As<MathVector3>();

      if (m_accumulator * 1000>= 33.3f)
      {
        for (INetworkProvider::NetworkProviderList::iterator i = m_networkProviders.begin(); i != m_networkProviders.end(); ++i)
        {
          (*i)->Message(this, System::Messages::Network::Server::SetServerPosition, parameters);
        }

        m_accumulator = 0;
      }
    }

    if (message == System::Messages::SetOrientation)
    {
      m_attributes[ System::Attributes::Orientation ] = parameters[ System::Attributes::Orientation ].As<MathQuaternion>();

      if (m_accumulator * 1000>= 33.3f)
      {
        for (INetworkProvider::NetworkProviderList::iterator i = m_networkProviders.begin(); i != m_networkProviders.end(); ++i)
        {
          (*i)->Message(this, System::Messages::Network::Server::SetServerOrientation, parameters);
        }

        m_accumulator = 0;
      }
    }

    for (INetworkProvider::NetworkProviderList::iterator i = m_networkProviders.begin(); i != m_networkProviders.end(); ++i)
    {
      (*i)->Message(this, message, parameters);
    }

    return AnyType();
  }

  void NetworkSystemComponent::Initialize()
  {
    for (INetworkProvider::NetworkProviderList::iterator i = m_networkProviders.begin(); i != m_networkProviders.end(); ++i)
    {
      (*i)->Message(this, System::Messages::Entity::CreateEntity, m_attributes);
    }
  }

  void NetworkSystemComponent::Destroy()
  {
    for (INetworkProvider::NetworkProviderList::iterator i = m_networkProviders.begin(); i != m_networkProviders.end(); ++i)
    {
      (*i)->Message(this, System::Messages::Entity::DestroyEntity, m_attributes);
    }
  }

  AnyType NetworkSystemComponent::PushMessage(const System::MessageType& message, AnyType::AnyTypeMap parameters)
  {
    if (message == System::Messages::SetPosition)
    {
      MathVector3 networkPosition = parameters[ System::Attributes::Position ].As<MathVector3>();
      MathVector3 currentPosition = m_attributes[ System::Attributes::Position ].As<MathVector3>();

      MathVector3 positionDifference = networkPosition - currentPosition;
      float distanceApart = positionDifference.Length();

      if (distanceApart> 2.0f)
      {
        parameters[ System::Attributes::Orientation ] = networkPosition;
        //Net("Snapped Position - Old:", currentPosition, "New:", networkPosition);
      }
      else if(distanceApart> 0.1f)
      {
        MathVector3 newPosition = currentPosition + (positionDifference * 0.05f); // smooth the difference by 10%
        //Net("Smoothed Position - Old:", currentPosition, "New:", networkPosition, "Smooth:", newPosition);
      }
    }

    if (message == System::Messages::SetOrientation)
    {
      MathQuaternion networkOrientation = parameters[ System::Attributes::Orientation ].As<MathQuaternion>();

      MathVector3 networkAxis;
      float networkAngle;
      networkOrientation.ToAngleAxis(networkAngle, networkAxis);

      MathQuaternion currentOrientation = m_attributes[ System::Attributes::Orientation ].As<MathQuaternion>();
      
      MathVector3 currentAxis;
      float currentAngle;
      currentOrientation.ToAngleAxis(currentAngle, currentAxis);

      float angleDifference = networkAngle - currentAngle;

      if (angleDifference> 0.3f)
      {
        parameters[ System::Attributes::Orientation ] = networkOrientation;
        //Net("Snapped Orientation - Old:", currentAngle, "New:", networkAngle);
      }
      else if (angleDifference> 0.05f)
      {
        float newAngle = currentAngle + (angleDifference * 0.05f);
        MathQuaternion newOrientation = MathQuaternion(networkAxis, newAngle);
        parameters[ System::Attributes::Orientation ] = newOrientation;
        //Net("Smoothed Orientation - Old:", currentAngle, "New:", networkAngle, "Smooth:", newAngle);
      }
    }

    return m_observer->Observe(this, message, parameters);
  }

  void NetworkSystemComponent::Update(float deltaMilliseconds)
  {
     m_accumulator += deltaMilliseconds;
  }
}