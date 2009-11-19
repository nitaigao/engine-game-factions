#include "NetworkFacade.h"

#include <luabind/table_policy.hpp>
using namespace luabind;

#include "Management/Management.h"
#include "IO/FileSearchResult.hpp"
using namespace IO;

using namespace Utility;

namespace Script
{
	scope NetworkFacade::RegisterFunctions( )
	{
		return
			class_< NetworkFacade >( "NetworkFacade" )
				.def( constructor< >( ) )
				.def( "connect", &NetworkFacade::Connect )
				.def( "disconnect", &NetworkFacade::Disconnect )
				.def( "selectCharacter", &NetworkFacade::SelectCharacter )
				.def( "findServers", &NetworkFacade::FindServers )
				.def( "createServer", &NetworkFacade::CreateServer )
				.def( "getServerMaps", &NetworkFacade::GetServerMaps, copy_table( result ) )
				;
	}

	void NetworkFacade::Connect( const std::string& hostAddress )
	{
		AnyType::AnyTypeMap parameters;
		parameters[ System::Parameters::Network::HostAddress ] = hostAddress;

		Management::Get( )->GetServiceManager( )->FindService( System::Types::NETWORK )
			->ProcessMessage( System::Messages::Network::Connect, parameters );
	}

	void NetworkFacade::SelectCharacter( const std::string& characterName )
	{
		AnyType::AnyTypeMap parameters;
		parameters[ System::Parameters::Network::Client::CharacterName ] = characterName;

		Management::Get( )->GetServiceManager( )->FindService( System::Types::NETWORK )
			->ProcessMessage( System::Messages::Network::Client::CharacterSelected, parameters );
	}

	void NetworkFacade::FindServers( )
	{
		Management::Get( )->GetServiceManager( )->FindService( System::Types::NETWORK )
			->ProcessMessage( System::Messages::Network::Client::FindServers, AnyType::AnyTypeMap( ) );
	}

	void NetworkFacade::Disconnect()
	{
		Management::Get( )->GetServiceManager( )->FindService( System::Types::NETWORK )
			->ProcessMessage( System::Messages::Network::Disconnect, AnyType::AnyTypeMap( ) ); 
	}

	void NetworkFacade::CreateServer( const std::string& levelName, int botCount, const std::string& serverName, int timeLimit, int fragLimit, int maxPlayers )
	{
		AnyType::AnyTypeMap parameters;
		parameters[ System::Parameters::Network::Server::MaxPlayers ] = maxPlayers;
		parameters[ System::Parameters::Game::LevelName ] = levelName;

		Management::Get( )->GetServiceManager( )->FindService( System::Types::NETWORK )
			->ProcessMessage( System::Messages::Network::CreateServer, parameters );
	}

	StringUtils::StringList NetworkFacade::GetServerMaps() const
	{
		FileSearchResult::FileSearchResultList* results = Management::Get( )->GetFileManager( )->FileSearch( "/data/levels", "*.xml", false );

		StringUtils::StringList maps;

		for( FileSearchResult::FileSearchResultList::iterator i = results->begin( ); i != results->end( ); ++i )
		{
			std::string mapName = StringUtils::Replace( ( *i ).FileName, ".xml", "" );
			maps.push_back( mapName );
		}

		delete results;

		return maps;
	}
}