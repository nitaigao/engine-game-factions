/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkClientEndpoint.hpp
*  @date   2009/08/19
*/
#pragma once
#ifndef INETWORKCLIENTENDPOINT_HPP
#define INETWORKCLIENTENDPOINT_HPP

#include "INetworkEndpoint.hpp"

namespace Network
{
	/*! 
	 *  Receives traffic from the Server
	 */
	class INetworkClientEndpoint : public INetworkEndpoint
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~INetworkClientEndpoint( ) { };
		
	};
};

#endif