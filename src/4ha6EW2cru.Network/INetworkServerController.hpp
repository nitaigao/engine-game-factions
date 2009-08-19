/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkServerController.hpp
*  @date   2009/08/16
*/
#pragma once
#ifndef INETWORKSERVERCONTROLLER_HPP
#define INETWORKSERVERCONTROLLER_HPP

#include <string>

#include "Maths/MathVector3.hpp"
#include "Maths/MathQuaternion.hpp"

#include <RakNetTypes.h>

namespace Network
{
	/*! 
	 *  Dispatches Server Messages to the Network
	 */
	class INetworkServerController
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~INetworkServerController( ) { };


		/*! Initialized the Server Controller
		 *
		 * @return ( void )
		 */
		virtual void Initialize( ) = 0;


		/*! Sends the SetPosition message for an Entity across the Network
		 *
		 * @param[in] const std::string & name
		 * @param[in] const Maths::MathVector3 & position
		 * @return ( void )
		 */
		virtual void SetPosition( const std::string& name, const Maths::MathVector3& position ) = 0;


		/*! Sends the SetOrientation message for an given Entity across the network
		 *
		 * @param[in] const std::string & name
		 * @param[in] const Maths::MathQuaternion & orientation
		 * @return ( void )
		 */
		virtual void SetOrientation( const std::string& name, const Maths::MathQuaternion& orientation ) = 0;

		
		/*! Instructs the Controller that a client has connected
		 *
		 * @param[in] const SystemAddress & clientAddress
		 * @return ( void )
		 */
		virtual void ClientConnected( const SystemAddress& clientAddress ) = 0;
		
	};
};

#endif