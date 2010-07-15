#include "precompiled.h"

#include "GeometrySystemComponent.h"

using namespace Maths;

namespace Geometry
{
  AnyType GeometrySystemComponent::Observe(const ISubject* subject, const System::MessageType& message, AnyType::AnyTypeMap parameters)
  {
    if (message == System::Messages::SetPosition)
    {
      m_attributes[ System::Attributes::Position ] = parameters[ System::Attributes::Position ].As< MathVector3 >();
    }

    if (message == System::Messages::SetOrientation)
    {
      m_attributes[ System::Attributes::Orientation ] = parameters[ System::Attributes::Orientation ].As< MathQuaternion >();
    }

    if(message == System::Messages::PostInitialize)
    {
      this->PushMessage(System::Messages::SetPosition, m_attributes);
      this->PushMessage(System::Messages::SetOrientation, m_attributes);
    }

    return AnyType();
  }

  AnyType GeometrySystemComponent::PushMessage(const System::MessageType& message, AnyType::AnyTypeMap parameters)
  {
    for(ObserverList::iterator i = m_observers.begin(); i != m_observers.end(); ++i)
    {
      (*i)->Observe(this, message, m_attributes);
    }

    return AnyType();
  }

  void GeometrySystemComponent::Serialize(IO::IStream* stream)
  {
    System::Types::Type systemType = m_attributes[ System::Attributes::SystemType ].As< System::Types::Type >();
    stream->Write(static_cast< int >(systemType));
    stream->Write(m_attributes[ System::Attributes::Position ].As< MathVector3 >());
    stream->Write(m_attributes[ System::Attributes::Orientation ].As< MathQuaternion >());
  }

  void GeometrySystemComponent::DeSerialize(IO::IStream* stream)
  {
    MathVector3 position;
    stream->Read(position);
    m_attributes[ System::Attributes::Position ] = position;

    MathQuaternion orientation;
    stream->Read(orientation);
    m_attributes[ System::Attributes::Orientation ] = orientation;

    this->Observe(0, System::Messages::PostInitialize, AnyType::AnyTypeMap());
  }
};