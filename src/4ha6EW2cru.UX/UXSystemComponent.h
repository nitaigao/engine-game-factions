/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   UXSystemComponent.h
*  @date   2009/04/26
*/
#pragma once
#ifndef UXSYSTEMCOMPONENT_H
#define UXSYSTEMCOMPONENT_H

#include <vector>

#include "IUXSystemComponent.hpp"
#include "IUXSystemScene.hpp"

#include "ILuaState.hpp"
#include "IScriptFunctionHandler.hpp"

namespace UX
{
	/*! 
	*  A UX System Scene Component
	*/
	class UXSystemComponent : public IUXSystemComponent
	{

	public:

		/*! Default Destructor
		*
		*  @return ()
		*/
		~UXSystemComponent( );


		/*! Default Constructor
		*
		*  @param[in] ILuaState * state
		*  @return ()
		*/
		UXSystemComponent( Script::ILuaState* state )
			: m_state( state )
		{

		}

		/*! Posts a message to observers
		*
		*  @param[in] const std::string & message
		*  @param[in] AnyType::AnyValueMap parameters
		*  @return (AnyType)
		*/
		inline AnyType PushMessage( const System::MessageType& message, AnyType::AnyTypeMap parameters ) { return AnyType( ); };


		/*! Messages the Component to influence its internal state
		*
		*  @param[in] const std::string & message
		*  @return (AnyType)
		*/
		inline AnyType Observe( const ISubject* subject, const System::MessageType& message, AnyType::AnyTypeMap parameters ) { return AnyType( ); };

		/* Inherited from ISystemComponent */

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
		inline void AddObserver( IObserver* observer ) { };


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


		/*!  Registers an LUA function to be included in the Game Update Loop
		*
		*  @param[in] luabind::object function
		*  @return (void)
		*/
		void RegisterUpdate( const luabind::object& function );


		/*! UnRegisters an LUA function from being included in the Game Update Loop
		*
		*  @param[in] luabind::object function
		*  @return (void)
		*/
		void UnRegisterUpdate( const luabind::object& function );


		/*! Registers an LUA function to receive in Game Events
		*
		*  @param[in] luabind::object function
		*  @return (void)
		*/
		void RegisterEvent( const luabind::object& function );


		/*! UnRegisters an LUA function from receiving in Game Events
		*
		*  @param[in] luabind::object function
		*  @return (void)
		*/
		void UnRegisterEvent( const luabind::object& function );


		/*! Generic Event Handler to Forward Game Events to the Script
		*
		*  @param[in] const Events::IEvent * event
		*  @return (void)
		*/
		void OnEvent( const Events::IEvent* event );

	private:

		Script::ILuaState* m_state;
		AnyType::AnyTypeMap m_attributes;

		Script::IScriptFunctionHandler::FunctionList m_eventHandlers;
		Script::IScriptFunctionHandler::FunctionList m_updateHandlers;

	};
}

#endif
