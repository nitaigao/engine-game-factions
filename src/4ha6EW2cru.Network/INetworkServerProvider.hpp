/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkServerProvider.hpp
*  @date   2009/08/20
*/
#pragma once
#ifndef INETWORKSERVERPROVIDER_HPP
#define INETWORKSERVERPROVIDER_HPP

#include "INetworkProvider.hpp"

#include "Events/Event.h"

namespace Network
{
	/*! 
	 *  A provider to control Server network flow
	 */
	class GAMEAPI INetworkServerProvider : public INetworkProvider
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~INetworkServerProvider( ) { };


		virtual void OnGameLevelChanged( const Events::IEvent* event ) = 0;
		
	};
};

#endif