/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkSystemComponent.hpp
*  @date   2009/07/06
*/
#pragma once
#ifndef INETWORKSYSTEMCOMPONENT_HPP
#define INETWORKSYSTEMCOMPONENT_HPP

#include "System/ISystemComponent.hpp"
#include "INetworkProvider.hpp"

namespace Network
{
	/*! 
	 *  A Network System Component
	 */
	class INetworkSystemComponent : public ISystemComponent
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~INetworkSystemComponent( ) { };


		/*! Adds a Network Provider to the Component
		 *
		 * @param[in] INetworkProvider * provider
		 * @return ( void )
		 */
		virtual void AddProvider( INetworkProvider* provider ) = 0;


		/*! Receives Messages from an inbound network connection
		*
		* @param[in] const std::string & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		virtual void MessageFromNetwork( const System::MessageType& message, AnyType::AnyTypeMap parameters ) = 0;
		
	};
};

#endif
