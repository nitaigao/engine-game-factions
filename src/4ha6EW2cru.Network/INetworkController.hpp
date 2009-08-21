/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkController.hpp
*  @date   2009/08/19
*/
#pragma once
#ifndef INETWORKCONTROLLER_HPP
#define INETWORKCONTROLLER_HPP

#include "Export.hpp"

namespace Network
{
	/*! 
	 *  Sends information across the Network
	 */
	class GAMEAPI INetworkController
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~INetworkController( ) { };


		/*! Initializes the Controller
		*
		* @return ( void )
		*/
		virtual void Initialize( ) = 0;
		
	};
};

#endif