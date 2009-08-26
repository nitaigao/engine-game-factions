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
#include "System/IInstrumentation.hpp"

namespace Network
{
	/*! 
	 *  The Network System
	 */
	class GAMEAPI NetworkSystem : public INetworkSystem, public Services::IService
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~NetworkSystem( );


		/*! Default Constructor
		*
		* @return (  )
		*/
		NetworkSystem( Services::IServiceManager* serviceManager, System::IInstrumentation* instrumentation, 
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
		void Initialize( Configuration::IConfiguration* configuration );


		/*! Steps the System's internal data
		*
		*  @param[in] float deltaMilliseconds
		*  @return (void)
		*/
		void Update( float deltaMilliseconds );


		/*! Releases internal data of the System
		*
		*  @return (System::Types::Type)
		*/
		void Release( );


		/*! Messages the system with a command
		*
		* @param[in] const std::string & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		AnyType::AnyTypeMap ProcessMessage( const System::MessageType& message, AnyType::AnyTypeMap parameters );


		/*! Returns the type of the System
		*
		*  @return (System::Types::Type)
		*/
		inline System::Types::Type GetType( ) const { return System::Types::NETWORK; };


		/*! Creates a System Scene
		*
		*  @return (ISystemScene*)
		*/
		ISystemScene* CreateScene( );


		/*! Gets the System's Properties
		*
		*  @return (AnyTypeMap)
		*/
		inline AnyType::AnyTypeMap GetAttributes( ) const { return m_attributes; };


		/*! Sets a System Property
		*
		*  @param[in] const std::string & name
		*  @param[in] AnyType value
		*  @return (void)
		*/
		inline void SetAttribute( const std::string& name, AnyType value ) { m_attributes[ name ] = value; };

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
