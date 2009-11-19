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
	INetworkProvider* NetworkFactory::CreateNetworkProvider( NetworkProviderType type, INetworkSystemScene* scene, IConfiguration* configuration )
	{
		switch ( type )
		{

		case CLIENT:
			{
				INetworkInterface* networkInterface = new NetworkInterface( );

				return new NetworkClientProvider( 
					configuration,
					networkInterface, 
					new NetworkClientController( networkInterface ),
					new NetworkClientEndpoint( networkInterface, scene, Management::Get( )->GetEventManager( ), Management::Get( )->GetServiceManager( ) )	
					);
			}

		case SERVER:
			{
				INetworkInterface* networkInterface = new NetworkInterface( );
				INetworkServerController* controller = new NetworkServerController( networkInterface, Management::Get( )->GetServiceManager( ) );

				return new NetworkServerProvider( 
					configuration,
					networkInterface, 
					controller,
					new NetworkServerEndpoint( networkInterface, scene, controller )
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

	INetworkSystem* NetworkFactory::CreateNetworkSystem( IConfiguration* configuration )
	{
		INetworkSystemScene* scene = this->CreateNetworkSystemScene( );

		return new NetworkSystem( 
			Management::Get( )->GetServiceManager( ), 
			Management::Get( )->GetInstrumentation( ),
			scene,
			static_cast< INetworkClientProvider* >( this->CreateNetworkProvider( CLIENT, scene, configuration ) ),
			static_cast< INetworkServerProvider* >( this->CreateNetworkProvider( SERVER, scene, configuration ) ),
			Management::Get( )->GetEventManager( ),
			configuration
			);
	}

	
}