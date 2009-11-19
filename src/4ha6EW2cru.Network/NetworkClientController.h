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

namespace Network
{
	/*! 
	 *  Sends Client Information across the Network
	 */
	class GAMEAPI NetworkClientController : public INetworkClientController
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
			, m_isPassive( false )
		{

		}


		/*! Initializes the Controller
		*
		* @return ( void )
		*/
		void Initialize( );


		/*! Selects a character within the game
		*
		* @return ( void )
		*/
		void SelectCharacter( const std::string& characterName );


		/*! Broadcasts the Network for Servers
		*
		* @return ( void )
		*/
		void FindServers( unsigned int port );


		/*! Tells the Server that the Client has finished loading the Level
		*
		* @return ( void )
		*/
		void LevelLoaded( );


		/*! Forwards the Message to the given Entity
		*
		* @param[in] const std::string & entityName
		* @param[in] const System::MessageType & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		void MessageEntity( const std::string& entityName, const System::MessageType& message, AnyType::AnyTypeMap parameters );


		/*! Stops the Controller from Sending client data
		*
		* @param[in] bool isPassive
		* @return ( void )
		*/
		inline void SetPassive( bool isPassive ) { m_isPassive = isPassive; };


		/*! Updates the internal state of the controller and processes the send queue at the send interval
		*
		* @param[in] float deltaMilliseconds
		* @return ( void )
		*/
		void Update( float deltaMilliseconds ) { };


	private:

		NetworkClientController( const NetworkClientController & copy ) { };
		NetworkClientController & operator = ( const NetworkClientController & copy ) { return *this; };

		INetworkInterface* m_networkInterface;
		bool m_isPassive;
		
	};
};

#endif