/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkServerEndpoint.hpp
*  @date   2009/08/17
*/
#pragma once
#ifndef INETWORKSERVERENDPOINT_HPP
#define INETWORKSERVERENDPOINT_HPP

#include "INetworkEndpoint.hpp"

namespace Network
{
	/*! 
	 *  An endpoint that receives client information
	 */
	class INetworkServerEndpoint : public INetworkEndpoint
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~INetworkServerEndpoint( ) { };
		
	};
};

#endif