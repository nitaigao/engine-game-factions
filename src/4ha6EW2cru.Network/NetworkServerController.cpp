#include "precompiled.h"

#include "NetworkServerController.h"

#include "NetworkClientEndpoint.h"
#include "NetworkStream.h"
using namespace RakNet;

#include "IO/IStream.hpp"
using namespace IO;

#include "Maths/MathVector3.hpp"
using namespace Maths;

namespace Network
{
  void NetworkServerController::Initialize()
  {
    RPC3_REGISTER_FUNCTION(m_networkInterface->GetRPC(), &NetworkClientEndpoint::Net_LoadLevel);
    RPC3_REGISTER_FUNCTION(m_networkInterface->GetRPC(), &NetworkClientEndpoint::Net_UpdateWorld);
    RPC3_REGISTER_FUNCTION(m_networkInterface->GetRPC(), &NetworkClientEndpoint::Net_CreateEntity);
    RPC3_REGISTER_FUNCTION(m_networkInterface->GetRPC(), &NetworkClientEndpoint::Net_DestroyEntity);
    RPC3_REGISTER_FUNCTION(m_networkInterface->GetRPC(), &NetworkClientEndpoint::Net_MessageEntity);
  }

  void NetworkServerController::ClientConnected(const SystemAddress& clientAddress)
  {
    m_networkInterface->GetRPC()->SetRecipientAddress(clientAddress, false);
    m_networkInterface->GetRPC()->CallC("&NetworkClientEndpoint::Net_LoadLevel", RakString(m_instrumentation->GetLevelName()));
  }

  void NetworkServerController::CreateEntity(const std::string& entityName, const std::string& entityType)
  {
    m_networkInterface->GetRPC()->SetRecipientAddress(UNASSIGNED_SYSTEM_ADDRESS, true);
    m_networkInterface->GetRPC()->CallC("&NetworkClientEndpoint::Net_CreateEntity", RakString(entityName), RakString(entityType));
  }

  void NetworkServerController::DestroyEntity(const std::string& entityName)
  {
    m_networkInterface->GetRPC()->SetRecipientAddress(UNASSIGNED_SYSTEM_ADDRESS, true);
    m_networkInterface->GetRPC()->CallC("NetworkClientEndpoint::Net_DestroyEntity", RakString(entityName));
  }

  void NetworkServerController::SendWorldUpdate(const SystemAddress& address)
  {
    m_networkInterface->GetRPC()->SetRecipientAddress(address, false);
    
    BitStream stream;
    NetworkStream networkStream(&stream);

    AnyType::AnyTypeMap parameters;
    parameters[ System::Parameters::IO::Stream ] = static_cast<IStream*>(&networkStream);

    m_serviceManager->FindService(System::Types::ENTITY)
      ->ProcessMessage(System::Messages::Entity::SerializeWorld, parameters);

    m_networkInterface->GetRPC()->CallC("&NetworkClientEndpoint::Net_UpdateWorld", stream);
  }

  void NetworkServerController::ClientDisconnected(const SystemAddress& clientAddress)
  {
    AnyType::AnyTypeMap parameters;
    parameters[ System::Attributes::Name ] = std::string(clientAddress.ToString());

    m_serviceManager->FindService(System::Types::ENTITY)
      ->ProcessMessage(System::Messages::Entity::DestroyEntity, parameters);
  }

  void NetworkServerController::MessageEntity(const std::string& entityName, const System::MessageType& message, AnyType::AnyTypeMap parameters)
  {
    BitStream stream;

    if (message == System::Messages::Mouse_Moved)
    {
      float deltaX = parameters[ System::Parameters::DeltaX ].As<float>();
      stream.Write(deltaX);

      float deltaY = parameters[ System::Parameters::DeltaY ].As<float>();
      stream.Write(deltaY);
    }

    if (message == System::Messages::SetPosition)
    {
      MathVector3 position = parameters[ System::Attributes::Position ].As<MathVector3>();
      stream.WriteVector(position.X, position.Y, position.Z);
    }

    if (message == System::Messages::SetOrientation)
    {
      MathQuaternion orientation = parameters[ System::Attributes::Orientation ].As<MathQuaternion>();
      stream.WriteNormQuat(orientation.W, orientation.X, orientation.Y, orientation.Z);
    }

    m_networkInterface->GetRPC()->SetSendParams(PacketPriority::MEDIUM_PRIORITY, PacketReliability::RELIABLE_SEQUENCED, 0);
    m_networkInterface->GetRPC()->CallC("&NetworkClientEndpoint::Net_MessageEntity", RakString(entityName), RakString(message), stream);  
  }
}