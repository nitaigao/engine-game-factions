/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkSystemScene.h
*  @date   2009/07/06
*/
#pragma once
#ifndef NETWORKSYSTEMSCENE_H
#define NETWORKSYSTEMSCENE_H

#include "INetworkSystemScene.hpp"
#include "INetworkProvider.hpp"
#include "INetworkSystemComponentFactory.hpp"

namespace Network
{
	/*! 
	 *  A Network System Scene
	 */
	class NetworkSystemScene : public INetworkSystemScene
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		GAMEAPI ~NetworkSystemScene( );


		/*! Default Constructor
		*
		* @return (  )
		*/
		NetworkSystemScene( INetworkSystemComponentFactory* componentFactory )
			: m_componentFactory( componentFactory )
		{

		}


		/*! Initializes the System Scene
		*
		*  @return (void)
		*/
		void Initialize( ) { };


		/*! Steps internal data of the SystemScene
		*
		*  @param[in] float deltaMilliseconds
		*  @return (void)
		*/
		GAMEAPI void Update( float deltaMilliseconds );


		/*! Destroys the System Scene
		*
		*  @return (void)
		*/
		GAMEAPI void Destroy( );


		/*! Gets the System::Types::Type of the SystemScene
		*
		*  @return (System::Types::Type)
		*/
		inline System::Types::Type GetType( ) const { return System::Types::NETWORK; };


		/*! Creates a SystemComponent specific to the SystemScene
		*
		*  @param[in] const std::string & name
		*  @param[in] const std::string & type
		*  @return (ISystemComponent*)
		*/
		GAMEAPI ISystemComponent* CreateComponent( const std::string& name, const std::string& type );


		/*! Destroys a SystemComponent created by the SystemScene
		*
		*  @param[in] ISystemComponent * component
		*  @return (void)
		*/
		GAMEAPI void DestroyComponent( ISystemComponent* component );


		/*! Adds a Network provider to the Scene
		*
		* @param[in] INetworkProvider * provider
		* @return ( void )
		*/
		inline void AddNetworkProvider( INetworkProvider* provider ) { m_networkProviders.push_back( provider ); };


		/*! Returns the Network System
		*
		* @return ( INetworkSystem* )
		*/
		INetworkSystem* GetSystem( ) const { return 0; };


		/*! Messages a component within the Scene
		*
		* @param[in] const std::string componentId
		* @param[in] const System::MessageType & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		GAMEAPI void MessageComponent( const std::string& componentId, const System::MessageType& message, AnyType::AnyTypeMap parameters );

	private:

		NetworkSystemScene( const NetworkSystemScene & copy ) { };
		NetworkSystemScene & operator = ( const NetworkSystemScene & copy ) { return *this; };

		ISystemComponent::SystemComponentMap m_components;
		INetworkProvider::NetworkProviderList m_networkProviders;
		INetworkSystemComponentFactory* m_componentFactory;
		
	};
};

#endif
