#include "precompiled.h"

#include "NetworkFacade.h"

#include <luabind/table_policy.hpp>
using namespace luabind;

#include "IO/FileSearchResult.hpp"
using namespace IO;

using namespace Utility;

namespace Script
{
  scope NetworkFacade::RegisterFunctions()
  {
    return
      class_< NetworkFacade >("NetworkFacade")
        .def("connect", &NetworkFacade::Connect)
        .def("disconnect", &NetworkFacade::Disconnect)
        .def("selectCharacter", &NetworkFacade::SelectCharacter)
        .def("findServers", &NetworkFacade::FindServers)
        .def("createServer", &NetworkFacade::CreateServer)
        .def("getServerMaps", &NetworkFacade::GetServerMaps, copy_table(result))
        ;
  }

  void NetworkFacade::Connect(const std::string& hostAddress)
  {
    AnyType::AnyTypeMap parameters;
    parameters[ System::Parameters::Network::HostAddress ] = hostAddress;

    m_serviceManager->FindService(System::Types::NETWORK)
      ->ProcessMessage(System::Messages::Network::Connect, parameters);
  }

  void NetworkFacade::SelectCharacter(const std::string& characterName)
  {
    AnyType::AnyTypeMap parameters;
    parameters[ System::Parameters::Network::Client::CharacterName ] = characterName;

    m_serviceManager->FindService(System::Types::NETWORK)
      ->ProcessMessage(System::Messages::Network::Client::CharacterSelected, parameters);
  }

  void NetworkFacade::FindServers()
  {
    m_serviceManager->FindService(System::Types::NETWORK)
      ->ProcessMessage(System::Messages::Network::Client::FindServers, AnyType::AnyTypeMap());
  }

  void NetworkFacade::Disconnect()
  {
    m_serviceManager->FindService(System::Types::NETWORK)
      ->ProcessMessage(System::Messages::Network::Disconnect, AnyType::AnyTypeMap()); 
  }

  void NetworkFacade::CreateServer(const std::string& levelName, int botCount, const std::string& serverName, int timeLimit, int fragLimit, int maxPlayers)
  {
    AnyType::AnyTypeMap parameters;
    parameters[ System::Parameters::Network::Server::MaxPlayers ] = maxPlayers;
    parameters[ System::Parameters::Game::LevelName ] = levelName;

    m_serviceManager->FindService(System::Types::NETWORK)
      ->ProcessMessage(System::Messages::Network::CreateServer, parameters);
  }

  StringUtils::StringList NetworkFacade::GetServerMaps() const
  {
    FileSearchResult::FileSearchResultList* results = m_resourceCache->ResourceSearch("/data/levels", "*.xml", false);

    StringUtils::StringList maps;

    for(FileSearchResult::FileSearchResultList::iterator i = results->begin(); i != results->end(); ++i)
    {
      std::string mapName = StringUtils::Replace((*i).FileName, ".xml", "");
      maps.push_back(mapName);
    }

    delete results;

    return maps;
  }
}