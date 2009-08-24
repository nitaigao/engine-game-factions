/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkSystemServerComponent.h
*  @date   2009/08/16
*/
#pragma once
#ifndef NETWORKSYSTEMSERVERCOMPONENT_H
#define NETWORKSYSTEMSERVERCOMPONENT_H

#include "System/ISystemComponent.hpp"

#include "INetworkServerController.hpp"

#include "Export.hpp"

namespace Network
{
	/*! 
	 *  An Entity Component that exists purely on the Server
	 */
	class NetworkSystemServerComponent : public ISystemComponent
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~NetworkSystemServerComponent( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		NetworkSystemServerComponent( INetworkServerController* messageDispatcher )
			: m_observer( 0 )
			, m_messageDispatcher( messageDispatcher )
		{

		}


		/*! Initializes the Component
		*
		*  @param[in] AnyType::AnyValueMap properties
		*  @return (void)
		*/
		void Initialize( ) { };


		/*! Steps the internal data of the Component
		*
		*  @param[in] float deltaMilliseconds
		*  @return (void)
		*/
		void Update( float deltaMilliseconds ) { };


		/*! Destroys the Component
		*
		*  @return (void)
		*/
		void Destroy( ) { };


		/*! Adds an Observer to the Component
		*
		*  @param[in] IObserver * observer
		*  @return (void)
		*/
		inline void AddObserver( IObserver* observer ) { m_observer = observer; };


		/*! Gets the properties of the Component
		*
		*  @return (AnyTypeKeyMap)
		*/
		AnyType::AnyTypeMap GetAttributes( ) const { return m_attributes; };


		/*! Sets an Attribute on the Component *
		*
		*  @param[in] const unsigned int attributeId
		*  @param[in] const AnyType & value
		*/
		inline void SetAttribute( const System::Attribute& attributeId, const AnyType& value ) { m_attributes[ attributeId ] = value; };


		/*! Posts a message to observers
		*
		*  @param[in] const std::string & message
		*  @param[in] AnyType::AnyValueMap parameters
		*  @return (AnyType)
		*/
		inline AnyType PushMessage( const System::MessageType& message, AnyType::AnyTypeMap parameters ) { return m_observer->Observe( this, message, parameters ); };


		/*! Messages the Component to influence its internal state
		*
		*  @param[in] const std::string & message
		*  @return (AnyType)
		*/
		GAMEAPI AnyType Observe( const ISubject* subject, const System::MessageType& message, AnyType::AnyTypeMap parameters );

	private:

		NetworkSystemServerComponent( const NetworkSystemServerComponent & copy ) { };
		NetworkSystemServerComponent & operator = ( const NetworkSystemServerComponent & copy ) { return *this; };

		AnyType::AnyTypeMap m_attributes;
		IObserver* m_observer;
		INetworkServerController* m_messageDispatcher;
		
	};
};

#endif