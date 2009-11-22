/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   NetworkSystemComponent.h
*  @date   2009/07/06
*/
#pragma once
#ifndef NETWORKSYSTEMCOMPONENT_H
#define NETWORKSYSTEMCOMPONENT_H

#include "INetworkSystemComponent.hpp"

namespace Network
{
	/*! 
	 *  A Network System Component
	 */
	class GAMEAPI NetworkSystemComponent : public INetworkSystemComponent
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~NetworkSystemComponent( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		NetworkSystemComponent( )
			: m_observer( 0 )
			, m_accumulator( 0 )
		{

		}


		/*! Initializes the Component
		*
		*  @param[in] AnyType::AnyValueMap properties
		*  @return (void)
		*/
		void Initialize( );


		/*! Steps the internal data of the Component
		*
		*  @param[in] float deltaMilliseconds
		*  @return (void)
		*/
		void Update( float deltaMilliseconds );


		/*! Destroys the Component
		*
		*  @return (void)
		*/
		void Destroy( );


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
		inline AnyType PushMessage( const System::MessageType& message, AnyType::AnyTypeMap parameters );


		/*! Messages the Component to influence its internal state
		*
		*  @param[in] const std::string & message
		*  @return (AnyType)
		*/
		AnyType Observe( const ISubject* subject, const System::MessageType& message, AnyType::AnyTypeMap parameters );


		/*! Adds a Network Provider to the Component
		*
		* @param[in] INetworkProvider * provider
		* @return ( void )
		*/
		void AddProvider( INetworkProvider* provider ) { m_networkProviders.push_back( provider ); };


		/*! Writes the contents of the object to the given stream
		*
		* @param[in] IStream * stream
		* @return ( void )
		*/
		void Serialize( IO::IStream* stream ) { };


		/*! Reads the contents of the object from the stream
		*
		* @param[in] IStream * stream
		* @return ( void )
		*/
		void DeSerialize( IO::IStream* stream ) { };


		/*! Returns the Name of the Component
		*
		* @return ( std::string )
		*/
		inline std::string GetName( ) const { return ( *m_attributes.find( System::Attributes::Name ) ).second.As< std::string >( ); };


		/*! Returns the Position of the parent Entity in the scene
		*
		* @return ( Maths::MathVector3& )
		*/
		inline Maths::MathVector3 GetPosition( ) const { return ( *m_attributes.find( System::Attributes::Position ) ).second.As< Maths::MathVector3 >( ); };

	private:

		NetworkSystemComponent( const NetworkSystemComponent & copy ) { };
		NetworkSystemComponent & operator = ( const NetworkSystemComponent & copy ) { return *this; };

		AnyType::AnyTypeMap m_attributes;
		IObserver* m_observer;
		INetworkProvider::NetworkProviderList m_networkProviders;
		float m_accumulator;
		
	};
};

#endif
