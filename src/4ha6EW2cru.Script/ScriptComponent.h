/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ScriptComponent.h
*  @date   2009/04/27
*/
#pragma once
#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include "Events/IEventManager.hpp"

#include "IScriptComponent.hpp"
#include "IScriptFacade.hpp"
#include "IScriptFunctionHandler.hpp"
#include "IScriptFacadeManager.hpp"
#include "ILuaState.hpp"

#include "ScriptEvent.hpp"

#include <luabind/luabind.hpp>

namespace Script
{
	/*!
	 *  A Script System Component 
	 */
	class GAMEAPI ScriptComponent : public IScriptComponent
	{

	public:

		/*! Default Destructor
		*
		*  @return ()
		*/
		~ScriptComponent( );


		/*! Default Constructor
		*
		*  @param[in] const std::string & name
		*  @return ()
		*/
		ScriptComponent( ILuaState* state, Events::IEventManager* eventManager, IScriptFacadeManager* facadeManager )
			: m_state( state )
			, m_eventManager( eventManager )
			, m_facadeManager( facadeManager )
			, m_observer( 0 )
			, m_eventHandlers( 0 )
		{

		};


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


		/*! Pushes any Changes to the Observers
		*
		*  @param[in] const unsigned int& systemChanges
		*  @return (void)
		*/
		void PushChanges( const unsigned int& systemChanges );


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


		/*! Messages the Component to influence its internal state
		*
		*  @param[in] const std::string & message
		*  @return (AnyType)
		*/
		AnyType Observe( const ISubject* subject, const System::MessageType& message, AnyType::AnyTypeMap parameters );


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


		/*! Posts a message to the parent Entity
		 *
		 *  @param[in] const std::string & message
		 *  @param[in] AnyType::AnyValueMap parameters
		 *  @return (AnyType)
		 */
		AnyType PushMessage( const System::MessageType& message, AnyType::AnyTypeMap parameters ) { return m_observer->Observe( this, message, parameters ); };


		/*! Generic Event Handler to Forward Game Events to the Script
		 *
		 *  @param[in] const Events::IEvent * event
		 *  @return (void)
		 */
		void OnEvent( const Events::IEvent* event );


		/* Script Handlers */

		/*! Runs the Loaded Script
		 *
		 *  @return (void)
		 */
		void RunScript( );


		/*! Includes a script into the current LUA State
		 *
		 *  @param[in] const std::string & scriptPath
		 *  @return (void)
		 */
		void IncludeScript( const std::string& scriptPath );


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


		/*!  Registers an LUA function to receive messages
		*
		*  @param[in] luabind::object function
		*  @return (void)
		*/
		void SubscribeMessage( const System::MessageType& message, const luabind::object& function );


		/*! UnRegisters an LUA function from receiving messages
		*
		*  @param[in] luabind::object function
		*  @return (void)
		*/
		void UnSubscribeMessage( const System::MessageType& message,  const luabind::object& function );


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


		/*! Executed the given string as LUA code against the components LUA State
		 *
		 *  @param[in] const std::string & input
		 *  @return (void)
		 */
		void ExecuteString( const std::string& input );

		/*! Gets the Name of the Component
		*
		*  @return (const std::string&)
		*/
		inline std::string GetName( ) { return m_attributes[ System::Attributes::Name ].As< std::string >( ); };


		/*! Broadcasts an Event to the LUA State with no parameters
		*
		*  @param[in] const std::string & eventName
		*  @return (void)
		*/
		void BroadcastEvent( const std::string& eventName )
		{
			m_eventManager->QueueEvent( new ScriptEventT0<>( eventName ) ); 
		}


		/*!  Broadcasts an Event with the given parameters
		*
		* @param[in] const std::string & eventName
		* @param[in] const T1 & param1
		* @return ( void )
		*/
		template < class T1 >
		void BroadcastEvent( const std::string& eventName, const T1& param1 )
		{
			Events::IEvent* event = new ScriptEventT1< T1 >( eventName, param1 );
			m_eventManager->QueueEvent( event );
		}


		/*!  Broadcasts an Event with the given parameters
		 *
		 * @param[in] const std::string & eventName
		 * @param[in] const T1 & param1
		 * @param[in] const T2 & param2
		 * @return ( void )
		 */
		template < class T1, class T2 >
		void BroadcastEvent( const std::string& eventName, const T1& param1, const T2& param2 )
		{
			Events::IEvent* event = new ScriptEventT2< T1, T2 >( eventName, param1, param2 );
			m_eventManager->QueueEvent( event );
		}


		inline Maths::MathVector3 GetLookAt( ) const { return m_lookAt; };

		inline Maths::MathVector3 GetPosition( ) { return m_attributes[ System::Attributes::Position ].As< Maths::MathVector3 >( ); };

		inline void SetPosition( const Maths::MathVector3& position );

	private:

		ScriptComponent( const ScriptComponent & copy ) { };
		ScriptComponent & operator = ( const ScriptComponent & copy ) { return *this; };

		ILuaState* m_state;
		Events::IEventManager* m_eventManager;
		IScriptFacadeManager* m_facadeManager;

		IScriptFunctionHandler::FunctionMap m_messageHandlers;
		IScriptFunctionHandler::FunctionList m_eventHandlers;
		IScriptFunctionHandler::FunctionList m_updateHandlers;

		IScriptFacade::ScriptFacadeList m_facades;

		IObserver* m_observer;

		AnyType::AnyTypeMap m_attributes;

		Maths::MathVector3 m_lookAt;

	};
};

#endif
