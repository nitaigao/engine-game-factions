/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkSystem.h
*  @date   2009/07/06
*/
#pragma once
#ifndef NETWORKSYSTEM_H
#define NETWORKSYSTEM_H

#include "Events/EventManager.h"

#include "Service/IService.hpp"

#include "INetworkSystem.hpp"
#include "INetworkSystemScene.hpp"
#include "INetworkClientProvider.hpp"
#include "INetworkServerProvider.hpp"

#include "Configuration/IConfiguration.hpp"
#include "Service/IServiceManager.h"
#include "System/Instrumentation.hpp"
#include "System/IInstrumentation.hpp"

namespace Network
{
	/*! 
	 *  The Network System
	 */
	class NetworkSystem : public INetworkSystem, public Services::IService
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		GAMEAPI ~NetworkSystem( );


		/*! Default Constructor
		*
		* @return (  )
		*/
		GAMEAPI NetworkSystem( Services::IServiceManager* serviceManager, System::IInstrumentation* instrumentation, 
			INetworkSystemScene* scene, INetworkClientProvider* clientProvider, INetworkServerProvider* serverProvider
			, Events::EventManager* eventManager )
			: m_instrumentation( instrumentation )
			, m_serviceManager( serviceManager )
			, m_scene( scene )
			, m_clientProvider( clientProvider )
			, m_serverProvider( serverProvider )
			, m_eventManager( eventManager )
		{
			m_attributes[ System::Attributes::Network::IsServer ] = false;
		}


		/*! Initializes the System
		*
		*  @return (void)
		*/
		GAMEAPI void Initialize( Configuration::IConfiguration* configuration );


		/*! Steps the System's internal data
		*
		*  @param[in] float deltaMilliseconds
		*  @return (void)
		*/
		GAMEAPI void Update( float deltaMilliseconds );


		/*! Releases internal data of the System
		*
		*  @return (System::Types::Type)
		*/
		GAMEAPI void Release( );


		/*! Messages the system with a command
		*
		* @param[in] const std::string & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		GAMEAPI AnyType::AnyTypeMap Message( const System::Message& message, AnyType::AnyTypeMap parameters );


		/*! Returns the type of the System
		*
		*  @return (System::Types::Type)
		*/
		GAMEAPI inline System::Types::Type GetType( ) const { return System::Types::NETWORK; };


		/*! Creates a System Scene
		*
		*  @return (ISystemScene*)
		*/
		GAMEAPI ISystemScene* CreateScene( );


		/*! Gets the System's Properties
		*
		*  @return (AnyTypeMap)
		*/
		GAMEAPI inline AnyType::AnyTypeMap GetAttributes( ) const { return m_attributes; };


		/*! Sets a System Property
		*
		*  @param[in] const std::string & name
		*  @param[in] AnyType value
		*  @return (void)
		*/
		GAMEAPI inline void SetAttribute( const std::string& name, AnyType value ) { m_attributes[ name ] = value; };


		/*! Sends a message to a single client across the network
		*
		* @param[in] const std::string & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		GAMEAPI void PushMessage( const SystemAddress& address, const System::Message& message, AnyType::AnyTypeMap parameters );


		/*! Sends a message across the network
		*
		* @param[in] const SystemAddress & networkAddress
		* @param[in] const std::string & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		GAMEAPI void PushMessage( const System::Message& message, AnyType::AnyTypeMap parameters );


		/*! Sends a message to a local component
		*
		* @param[in] const std::string & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		GAMEAPI void MessageComponent( const std::string& componentName, const std::string& message, AnyType::AnyTypeMap parameters );

	private:

		NetworkSystem( const NetworkSystem & copy ) { };
		NetworkSystem & operator = ( const NetworkSystem & copy ) { return *this; };
	
		AnyType::AnyTypeMap m_attributes;

		Services::IServiceManager* m_serviceManager;
		System::IInstrumentation* m_instrumentation;
		INetworkSystemScene* m_scene;
		INetworkClientProvider* m_clientProvider;
		INetworkServerProvider* m_serverProvider;
		Events::EventManager* m_eventManager;
	};
};

#endif
