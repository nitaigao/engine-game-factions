/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkClientController.hpp
*  @date   2009/08/19
*/
#pragma once
#ifndef INETWORKCLIENTCONTROLLER_HPP
#define INETWORKCLIENTCONTROLLER_HPP

#include "INetworkController.hpp"

#include <string>

namespace Network
{
	/*! 
	 *  Sends Client Information to the Network
	 */
	class GAMEAPI INetworkClientController : public INetworkController
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~INetworkClientController( ) { };


		/*! Selects a character within the game
		 *
		 * @return ( void )
		 */
		virtual void SelectCharacter( const std::string& characterName ) = 0;


		/*! Broadcasts the Network for Servers
		 *
		 * @return ( void )
		 */
		virtual void FindServers( ) = 0;
		

		/*! Tells the Server that the Client has finished loading the Level
		 *
		 * @return ( void )
		 */
		virtual void LevelLoaded( ) = 0;
	};
};

#endif