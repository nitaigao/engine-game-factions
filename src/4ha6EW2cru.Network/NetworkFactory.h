/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkFactory.hpp
*  @date   2009/08/20
*/
#pragma once
#ifndef NETWORKFACTORY_HPP
#define NETWORKFACTORY_HPP

#include "INetworkProvider.hpp"
#include "INetworkSystem.hpp"
#include "INetworkSystemScene.hpp"

namespace Network
{
	enum NetworkProviderType
	{
		CLIENT,
		SERVER
	};

	class INetworkFactory
	{
		virtual INetworkProvider* CreateNetworkProvider( NetworkProviderType type ) = 0;
		virtual INetworkSystem* CreateNetworkSystem( ) = 0;
		virtual INetworkSystemScene* CreateNetworkSystemScene( ) = 0;
	};

	/*! 
	 *  Creates Network Objects
	 */
	class NetworkFactory : public INetworkFactory
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~NetworkFactory( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		NetworkFactory( ) { };

		INetworkProvider* CreateNetworkProvider( NetworkProviderType type );

		INetworkSystemScene* CreateNetworkSystemScene( );

		INetworkSystem* CreateNetworkSystem( );

	private:

		NetworkFactory( const NetworkFactory & copy ) { };
		NetworkFactory & operator = ( const NetworkFactory & copy ) { return *this; };
		
	};
};

#endif