/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkSystem.hpp
*  @date   2009/04/27
*/
#pragma once
#ifndef INETWORKSYSTEM_HPP
#define INETWORKSYSTEM_HPP

#include <System/ISystem.hpp>

#include <RakNetTypes.h>

namespace Network
{
	/*!
	*  The Sound System 
	*/
	class INetworkSystem : public ISystem
	{

	public:

		/*! Default Destructor
		*
		*  @return ()
		*/
		virtual ~INetworkSystem( ) { };

		/*! Sends a message to a single client across the network
		*
		* @param[in] const std::string & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		virtual void PushMessage( const SystemAddress& address, const System::MessageType& message, AnyType::AnyTypeMap parameters ) = 0;


		/*! Sends a message to all clients across the network
		*
		* @param[in] const std::string & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		virtual void PushMessage( const System::MessageType& message, AnyType::AnyTypeMap parameters ) = 0;


		/*! Sends a message to a local component
		*
		* @param[in] const std::string & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		virtual void MessageComponent( const std::string& componentName, const std::string& message, AnyType::AnyTypeMap parameters ) = 0;

	};
};

#endif
