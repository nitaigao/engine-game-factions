#include "ClientMessageRouter.h"

#include <BitStream.h>
#include <GetTime.h>
using namespace RakNet;

#include "Utility/StringUtils.h"
using namespace Utility;

#include "NetworkUtils.h"

#include "ServerCache.h"

namespace Network
{
	void ClientMessageRouter::FindServers( )
	{
		//ServerCache::Get( )->Clear( );

		BitStream stream;
		stream.WriteCompressed( RakNet::GetTime( ) );

		m_networkInterface->AdvertiseSystem( 
			NetworkUtils::BROADCAST_ADDRESS.ToString( false ), 
			NetworkUtils::BROADCAST_ADDRESS.port,
			( const char* ) stream.GetData( ), 
			stream.GetNumberOfBitsUsed( ) 
			);
	}

	void ClientMessageRouter::SelectCharacter( const System::MessageType& message, AnyType::AnyTypeMap &parameters )
	{
		BitStream stream;
		stream.Write( RakString( message ) );

		std::string characterName = parameters[ System::Parameters::Network::Client::CharacterName ].As< std::string >( );
		stream.Write( RakString( characterName ) );

		NetworkUtils::SendNetworkMessage( stream, m_serverAddress, m_networkInterface );
	}

	void ClientMessageRouter::GetServerAdvertisement( AnyType::AnyTypeMap& parameters, AnyType::AnyTypeMap& results )
	{
		int serverCacheIndex = 0;

		IServerAdvertisement* serverAd = 0;//ServerCache::Get( )->Find( parameters[ System::Parameters::Network::Client::ServerCacheIndex ].As< int >( ) );

		if ( serverAd )
		{
			results[ System::Parameters::Network::Server::ServerName ] = serverAd->GetServerName( );
			results[ System::Parameters::Network::Server::LevelName ] = serverAd->GetLevelName( );
			results[ System::Parameters::Network::Server::MaxPlayers ] = StringUtils::ToString( serverAd->GetMaxPlayers( ) );
			results[ System::Parameters::Network::Server::PlayerCount ] = StringUtils::ToString( serverAd->GetPlayerCount( ) );
			results[ System::Parameters::Network::Server::Ping ] = StringUtils::ToString( serverAd->GetPing( ) );
			results[ System::Parameters::Network::HostAddress ] = serverAd->GetServerAddress( );
			results[ System::Parameters::Network::Port ] = StringUtils::ToString( serverAd->GetServerPort( ) );
		}
	}

	void ClientMessageRouter::Connect( AnyType::AnyTypeMap& parameters )
	{
		m_serverAddress = SystemAddress(
			parameters[ System::Parameters::Network::HostAddress ].As< std::string >( ).c_str( ),
			parameters[ System::Parameters::Network::Port ].As< int >( )
			);

		m_networkInterface->Connect( 
			m_serverAddress.ToString( false ),
			m_serverAddress.port,
			0, 0
			);
	}

	void ClientMessageRouter::Disconnect( )
	{
		m_networkInterface->CloseConnection( m_serverAddress, true );
	}

	void ClientMessageRouter::PushMessage( const System::MessageType& message, AnyType::AnyTypeMap parameters )
	{
		if ( 
			message == System::Messages::Move_Forward_Pressed ||
			message == System::Messages::Move_Backward_Pressed ||
			message == System::Messages::Move_Forward_Released ||
			message == System::Messages::Move_Backward_Released ||
			message == System::Messages::Strafe_Right_Pressed ||
			message == System::Messages::Strafe_Left_Pressed ||
			message == System::Messages::Strafe_Right_Released ||
			message == System::Messages::Strafe_Left_Released ||
			message == System::Messages::Jump ||
			message == System::Messages::Mouse_Moved
			)
		{
			std::string entityName = parameters[ System::Attributes::Name ].As< std::string >( );

			BitStream stream;

			stream.Write( System::Messages::Network::ComponentUpdate.c_str( ) );
			stream.Write( message.c_str( ) );
			stream.Write( entityName.c_str( ) );

			if ( message == System::Messages::Mouse_Moved )
			{
				float deltaX = parameters[ System::Parameters::DeltaX ].As< float >( );
				stream.Write( deltaX );
			}

			m_sendBuffer.Write( stream );
		}
	}

	void ClientMessageRouter::UpdateServer( float deltaMilliseconds, float updateRate )
	{
		m_tickRate = 1.0f / updateRate ;

		if ( m_tickTotal >= m_tickRate && m_sendBuffer.GetNumberOfBitsUsed( ) > 0 )
		{
			m_sendBuffer.ResetReadPointer( );
			NetworkUtils::SendNetworkMessage( m_sendBuffer, m_serverAddress, m_networkInterface );

			m_sendBuffer.Reset( );
			m_tickTotal = 0.0f;
		}

		m_tickTotal += deltaMilliseconds;
	}

	void ClientMessageRouter::LevelLoaded( )
	{
		BitStream stream;
		stream.Write( System::Messages::Network::Client::LevelLoaded.c_str( ) );
		m_sendBuffer.Write( stream );
	}
}