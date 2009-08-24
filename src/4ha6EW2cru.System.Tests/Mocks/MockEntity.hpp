/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockEntity.h
*  @date   2009/08/13
*/
#pragma once
#ifndef MOCKENTITY_H
#define MOCKENTITY_H

#include "State/IWorldEntity.hpp"

namespace 
{
	/*! 
	 *  
	 */
	class MockEntity : public IWorldEntity
	{

	public:

		MOCK_CONST_METHOD0( GetName, std::string( ) );
		MOCK_METHOD0( Initialize, void( ) );
		MOCK_METHOD1( AddComponent, void( ISystemComponent* ) );
		MOCK_CONST_METHOD0( GetComponents, ISystemComponent::SystemComponentList( ) );
		MOCK_METHOD2( AddObserver, void( const System::MessageType&, IObserver* ) );
		MOCK_METHOD2( SetAttribute, void( const System::Attribute&, const AnyType& ) );
		MOCK_METHOD1( Serialize, void( IO::IStream* ) );
		MOCK_METHOD1( DeSerialize, void( IO::IStream* ) );

		MOCK_METHOD3( Observe, AnyType( const ISubject*, const System::MessageType&, AnyType::AnyTypeMap ) );
		
	};
};

#endif