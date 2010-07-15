#include "precompiled.h"

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

#include "NetworkSystem.h"

namespace Network
{
  INetworkSystem* NetworkFactory::CreateNetworkSystem()
  {
    INetworkSystemComponentFactory* componentFactory = new NetworkSystemComponentFactory();
    INetworkSystemScene* scene = new NetworkSystemScene(componentFactory);

    INetworkInterface* clientInterface = new NetworkInterface();
    INetworkClientController* clientController = new NetworkClientController(clientInterface);
    INetworkClientEndpoint* clientEndpoint = new NetworkClientEndpoint(clientInterface, scene, m_eventManager, m_serviceManager)  ;
    INetworkClientProvider* clientProvider = new NetworkClientProvider(m_configuration, clientInterface, clientController, clientEndpoint );

    INetworkInterface* serverInterface = new NetworkInterface();
    INetworkServerController* serverController = new NetworkServerController(serverInterface, m_serviceManager, m_instrumentation);
    INetworkServerEndpoint* serverEndpoint = new NetworkServerEndpoint(serverInterface, scene, serverController, m_serviceManager);
    INetworkServerProvider* serverProvider = new NetworkServerProvider(m_configuration, serverInterface, serverController, serverEndpoint );

    return new NetworkSystem(m_serviceManager, m_instrumentation, scene, clientProvider, serverProvider, m_eventManager, m_configuration);
  }
}