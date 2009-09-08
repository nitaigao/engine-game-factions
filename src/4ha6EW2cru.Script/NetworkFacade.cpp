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
				.def( "getServerAd", &NetworkFacade::GetServerAd, copy_table_assoc( result ) )
				.def( "createServer", &NetworkFacade::CreateServer )
				.def( "getServerMaps", &NetworkFacade::GetServerMaps, copy_table( result ) )
				;
	}

	void NetworkFacade::Connect( const std::string& hostAddress, unsigned int port )
	{
		AnyType::AnyTypeMap parameters;
		parameters[ System::Parameters::Network::HostAddress ] = hostAddress;
		parameters[ System::Parameters::Network::Port ] = port;

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

	StringUtils::StringMap NetworkFacade::GetServerAd( int cacheIndex )
	{
		AnyType::AnyTypeMap parameters;
		parameters[ System::Parameters::Network::Client::ServerCacheIndex ] = cacheIndex;

		AnyType::AnyTypeMap results = Management::Get( )->GetServiceManager( )->FindService( System::Types::NETWORK )
			->ProcessMessage( System::Messages::Network::Client::GetServerAd, parameters ); 

		StringUtils::StringMap serverAd;

		for ( AnyType::AnyTypeMap::iterator i = results.begin( ); i != results.end( ); ++i )
		{
			serverAd[ ( *i ).first ] = ( *i ).second.As< std::string >( );
		}

		std::stringstream players;
		players 
			<< results[ System::Parameters::Network::Server::PlayerCount ].As< std::string >( ) 
			<< "/" 
			<< results[ System::Parameters::Network::Server::MaxPlayers ].As< std::string >( );

		serverAd[ "players" ] = players.str( );

		return serverAd;
	}

	void NetworkFacade::Disconnect()
	{
		Management::Get( )->GetServiceManager( )->FindService( System::Types::NETWORK )
			->ProcessMessage( System::Messages::Network::Disconnect, AnyType::AnyTypeMap( ) ); 
	}

	void NetworkFacade::CreateServer( const std::string& levelName, unsigned int port, int botCount, const std::string& serverName, int timeLimit, int fragLimit, int maxPlayers )
	{
		AnyType::AnyTypeMap parameters;
		parameters[ System::Parameters::Network::Port ] = port;
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