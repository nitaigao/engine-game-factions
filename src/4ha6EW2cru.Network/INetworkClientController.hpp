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

#include "System/SystemType.hpp"
#include "System/AnyType.hpp"

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


		/*! Forwards the Message to the given Entity
		*
		* @param[in] const std::string & entityName
		* @param[in] const System::MessageType & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		virtual void MessageEntity( const std::string& entityName, const System::MessageType& message, AnyType::AnyTypeMap parameters ) = 0;


		/*! Stops the Controller from Sending client data
		*
		* @param[in] bool isPassive
		* @return ( void )
		*/
		virtual void SetPassive( bool isPassive ) = 0;
	};
};

#endif