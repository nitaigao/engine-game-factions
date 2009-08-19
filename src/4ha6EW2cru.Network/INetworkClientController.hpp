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
	class INetworkClientController : public INetworkController
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
		
	};
};

#endif