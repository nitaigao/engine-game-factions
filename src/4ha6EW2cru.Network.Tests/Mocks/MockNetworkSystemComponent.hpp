/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockNetworkSystemComponent.hpp
*  @date   2009/08/17
*/
#pragma once
#ifndef MOCKNETWORKSYSTEMCOMPONENT_HPP
#define MOCKNETWORKSYSTEMCOMPONENT_HPP

#include "INetworkSystemComponent.hpp"

namespace
{
	class MockNetworkSystemComponent : public INetworkSystemComponent
	{

	public:

		MOCK_METHOD0( Initialize, void( ) );
		MOCK_METHOD1( Update, void( float ) );
		MOCK_METHOD0( Destroy, void( ) );
		MOCK_CONST_METHOD0( GetAttributes, AnyType::AnyTypeMap( ) );
		MOCK_METHOD2( SetAttribute, void( const System::Attribute&, const AnyType& ) );
		MOCK_METHOD1( AddProvider, void( INetworkProvider* ) );
		MOCK_METHOD2( MessageFromNetwork, void( const System::MessageType&, AnyType::AnyTypeMap ) );
		MOCK_METHOD3( Observe, AnyType( const ISubject*, const System::MessageType&, AnyType::AnyTypeMap ) );
		MOCK_METHOD1( AddObserver, void( IObserver* ) );
		MOCK_METHOD2( PushMessage, AnyType( const System::MessageType&, AnyType::AnyTypeMap ) );
		MOCK_METHOD1( Serialize, void( IO::IStream* ) );
		MOCK_METHOD1( DeSerialize, void( IO::IStream* ) );
		MOCK_CONST_METHOD0( GetName, std::string( ) );
		MOCK_CONST_METHOD0( GetPosition, Maths::MathVector3( ) );
		
	};
};

#endif