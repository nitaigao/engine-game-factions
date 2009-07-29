/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkMessage.hpp
*  @date   2009/07/22
*/
#pragma once
#ifndef NETWORKMESSAGE_HPP
#define NETWORKMESSAGE_HPP

#include <RakString.h>
#include "System/AnyType.hpp"

#include "System/SystemType.hpp"
#include "NetworkStream.h"

namespace Network
{
	/*! 
	 *  A Message to Send across the Network
	 */
	struct NetworkMessage
	{
		unsigned char message;
		RakNet::RakString messageId;
		AnyType::AnyTypeMap parameters;
	};

	struct NetworkMessageNew
	{
		~NetworkMessageNew( )
		{
			delete m_messageData;
			m_messageData = 0;
		}

		NetworkMessageNew( )
			: m_messageData( 0 )
		{

		}

		explicit NetworkMessageNew( const System::Message& messageType )
			: m_messageType( messageType )
			, m_messageData( 0 )
		{

		}

		NetworkMessageNew( const System::Message& messageType, NetworkStream* messageData )
			: m_messageType( messageType )
			, m_messageData( messageData )
		{

		}

		System::Message m_messageType;
		NetworkStream* m_messageData;
	};

	enum NetworkTypes
	{
		NETWORKTYPE_EMPTY = 0,
		NETWORKTYPE_STRING = 1,
		NETWORKTYPE_BOOL = 2,
		NETWORKTYPE_VECTOR = 3,
		NETWORKTYPE_QUATERNION = 4
	};
};

#endif