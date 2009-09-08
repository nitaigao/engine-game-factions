/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkFacade.h
*  @date   2009/07/06
*/
#pragma once
#ifndef NETWORKFACADE_H
#define NETWORKFACADE_H

#include "INetworkFacade.h"

#include <luabind/luabind.hpp>

#include "System/ISystemComponent.hpp"

#include "Utility/StringUtils.h"

namespace Script
{
	/*! 
	 *  A Facade interface to interact with the Network System from Script
	 */
	class GAMEAPI NetworkFacade : public INetworkFacade
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~NetworkFacade( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		NetworkFacade( ) { };


		/*! Registers the Script functions with the given state
		*
		* @param[in] lua_State * state
		* @return ( void )
		*/
		static luabind::scope RegisterFunctions( );


		/*! Returns the Name that the Facade will use in script
		*
		* @return ( std::string )
		*/
		inline std::string GetName( ) { return "network"; };


		/*! Requests the Game connects to the specified server
		*
		* @param[in] const std::string & serverAddress
		* @param[in] const int & port
		* @return ( void )
		*/
		void Connect( const std::string& hostAddress, unsigned int port );


		/*! Disconnects if connected to a server
		*
		* @return ( void )
		*/
		void Disconnect( );


		/*! Messages the Server that a character has been selected
		*
		* @param[in] const std::string & characterName
		* @return ( void )
		*/
		void SelectCharacter( const std::string& characterName );


		/*! Instructs the Network Stack to look for Game Servers
		*
		* @return ( void )
		*/
		void FindServers( );


		/*! Returns the Server Advertisement at the given Cache Index within the Client Server Cache
		*
		* @param[in] const int & cacheIndex
		* @return ( ServerAdvertisement* )
		*/
		Utility::StringUtils::StringMap GetServerAd( int cacheIndex );


		
		/*! Creates a Local Server running within the game client
		 *
		 * @param[in] const std::string & levelName
		 * @param[in] unsigned int port
		 * @param[in] int botCount
		 * @param[in] const std::string & serverName
		 * @param[in] int timeLimit
		 * @param[in] int fragLimit
		 * @param[in] int maxPlayers
		 * @return ( void )
		 */
		void CreateServer( const std::string& levelName, unsigned int port, int botCount, const std::string& serverName, int timeLimit, int fragLimit, int maxPlayers );


		/*! Initializes the Facade with the given ScriptComponent
		*
		* @return ( void )
		*/
		void Initialize( ) { };


		/*! Returns a list of available maps to play on the Server
		 *
		 * @return ( StringUtils::StringList )
		 */
		Utility::StringUtils::StringList GetServerMaps( ) const;


	private:

		NetworkFacade( const NetworkFacade & copy ) { };
		NetworkFacade & operator = ( const NetworkFacade & copy ) { return *this; };
		
	};
};

#endif
