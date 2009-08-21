#include "NetworkFactory.h"

#include "NetworkInterface.h"

#include "NetworkClientProvider.h"
#include "NetworkClientController.h"
#include "NetworkClientEndpoint.h"

#include "NetworkServerProvider.h"
#include "NetworkServerController.h"
#include "NetworkServerEndpoint.h"

#include "NetworkSystemScene.h"
#include "NetworkSystemComponentFactory.hpp"

#include "ServerCache.h"

#include "NetworkSystem.h"

#include "Management/Management.h"

#include "Configuration/Configuration.h"
using namespace Configuration;

namespace Network
{
	INetworkProvider* NetworkFactory::CreateNetworkProvider( NetworkProviderType type )
	{
		switch ( type )
		{

		case CLIENT:
			{
				INetworkInterface* networkInterface = new NetworkInterface( );
				IServerCache* serverCache = new ServerCache( );

				return new NetworkClientProvider( 
					networkInterface, 
					new NetworkClientController( networkInterface ),
					new NetworkClientEndpoint( networkInterface, serverCache, Management::Get( )->GetEventManager( ), Management::Get( )->GetServiceManager( ) ),
					serverCache
					);
			}

		case SERVER:
			{
				INetworkInterface* networkInterface = new NetworkInterface( );
				INetworkServerController* controller = new NetworkServerController( networkInterface, Management::Get( )->GetServiceManager( ) );

				return new NetworkServerProvider( 
					new ClientConfiguration( ),
					networkInterface, 
					controller,
					new NetworkServerEndpoint( networkInterface, controller )
					);
			}

		default:

			return 0;
		}
	}

	INetworkSystemScene* NetworkFactory::CreateNetworkSystemScene()
	{
		return new NetworkSystemScene( new NetworkSystemComponentFactory( ) );
	}

	INetworkSystem* NetworkFactory::CreateNetworkSystem()
	{
		return new NetworkSystem( 
			Management::Get( )->GetServiceManager( ), 
			Management::Get( )->GetInstrumentation( ),
			this->CreateNetworkSystemScene( ),
			static_cast< INetworkClientProvider* >( this->CreateNetworkProvider( CLIENT ) ),
			static_cast< INetworkServerProvider* >( this->CreateNetworkProvider( SERVER ) ),
			Management::Get( )->GetEventManager( )
			);
	}

	
}