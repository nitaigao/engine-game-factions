/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkServerController.h
*  @date   2009/08/17
*/
#pragma once
#ifndef NETWORKSERVERCONTROLLER_H
#define NETWORKSERVERCONTROLLER_H

#include "INetworkServerController.hpp"

#include <RPC3.h>

namespace Network
{
	/*! 
	 *  A Controller that transmits messages across the network
	 */
	class NetworkServerController : public INetworkServerController
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		GAMEAPI ~NetworkServerController( );


		/*! Default Constructor
		*
		* @return (  )
		*/
		NetworkServerController( )
			: m_rpc( new RakNet::RPC3( ) )
		{

		}


		/*! Initialized the Server Controller
		*
		* @return ( void )
		*/
		GAMEAPI void Initialize( );


		/*! Sends the SetPosition message for an Entity across the Network
		*
		* @param[in] const std::string & name
		* @param[in] const Maths::MathVector3 & position
		* @return ( void )
		*/
		GAMEAPI void SetPosition( const std::string& name, const Maths::MathVector3& position );


		/*! Sends the SetOrientation message for an given Entity across the network
		*
		* @param[in] const std::string & name
		* @param[in] const Maths::MathQuaternion & orientation
		* @return ( void )
		*/
		GAMEAPI void SetOrientation( const std::string& name, const Maths::MathQuaternion& orientation );


		/*! Advertises the System to the given Network Address
		*
		* @param[in] const SystemAddress & clientAddress
		* @param[in] const RakTime & clientTime
		* @return ( void )
		*/
		GAMEAPI void AdvertiseSystem( const SystemAddress& clientAddress, const RakNetTime& clientTime );

	private:

		NetworkServerController( const NetworkServerController & copy ) { };
		NetworkServerController & operator = ( const NetworkServerController & copy ) { return *this; };

		RakNet::RPC3* m_rpc;
		
	};
};

#endif