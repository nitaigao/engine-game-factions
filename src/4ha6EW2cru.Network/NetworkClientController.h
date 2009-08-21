/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkClientController.h
*  @date   2009/08/19
*/
#pragma once
#ifndef NETWORKCLIENTCONTROLLER_H
#define NETWORKCLIENTCONTROLLER_H

#include "INetworkClientController.hpp"
#include "INetworkInterface.hpp"

#include "Export.hpp"

namespace Network
{
	/*! 
	 *  Sends Client Information across the Network
	 */
	class NetworkClientController : public INetworkClientController
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~NetworkClientController( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		NetworkClientController( INetworkInterface* networkInterface )
			: m_networkInterface( networkInterface )
		{

		}


		/*! Initializes the Controller
		*
		* @return ( void )
		*/
		GAMEAPI void Initialize( );


		/*! Selects a character within the game
		*
		* @return ( void )
		*/
		GAMEAPI void SelectCharacter( const std::string& characterName );


		/*! Broadcasts the Network for Servers
		*
		* @return ( void )
		*/
		GAMEAPI void FindServers( );


	private:

		NetworkClientController( const NetworkClientController & copy ) { };
		NetworkClientController & operator = ( const NetworkClientController & copy ) { return *this; };

		INetworkInterface* m_networkInterface;
		
	};
};

#endif