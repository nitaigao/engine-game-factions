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
#include "IScriptUpdateDispatcher.hpp"
#include "IScriptEventDispatcher.hpp"
#include "IScriptMessageDispatcher.hpp"
#include "IScriptFacadeManager.hpp"
#include "IScriptFacade.hpp"

#include "System/AnyType.hpp"

namespace UX
{
  /*! 
  *  A UX System Scene Component
  */
  class GAMEAPI UXSystemComponent : public IUXSystemComponent
  {

  public:

    /*! Default Destructor
    *
    *  @return ()
    */
    ~UXSystemComponent();


    /*! Default Constructor
    *
    *  @param[in] ILuaState * state
    *  @return ()
    */
    UXSystemComponent(
      Script::ILuaState* state, 
      Script::IScriptFacadeManager* facadeManager, 
      Script::IScriptMessageDispatcher* messageDispatcher, 
      Script::IScriptEventDispatcher* eventDispatcher, 
      Script::IScriptUpdateDispatcher* updateDispatcher 
     )
      : m_state(state)
      , m_facadeManager(facadeManager)
      , m_messageDispatcher(messageDispatcher)
      , m_eventDispatcher(eventDispatcher)
      , m_updateDispatcher(updateDispatcher)
      , m_observer(0)
    {

    };

    /*! Posts a message to observers
    *
    *  @param[in] const std::string & message
    *  @param[in] AnyType::AnyValueMap parameters
    *  @return (AnyType)
    */
    inline AnyType PushMessage(const System::MessageType& message, AnyType::AnyTypeMap parameters) { return AnyType(); };


    /*! Messages the Component to influence its internal state
    *
    *  @param[in] const std::string & message
    *  @return (AnyType)
    */
    inline AnyType Observe(const ISubject* subject, const System::MessageType& message, AnyType::AnyTypeMap parameters) { return AnyType(); };

    /* Inherited from ISystemComponent */

    /*! Initializes the Component
    *
    *  @param[in] AnyType::AnyValueMap properties
    *  @return (void)
    */
    void Initialize();


    /*! Steps the internal data of the Component
    *
    *  @param[in] float deltaMilliseconds
    *  @return (void)
    */
    void Update(float deltaMilliseconds);


    /*! Destroys the Component
    *
    *  @return (void)
    */
    void Destroy();


    /*! Adds an Observer to the Component
    *
    *  @param[in] IObserver * observer
    *  @return (void)
    */
    inline void AddObserver(IObserver* observer) { };


    /*! Gets the properties of the Component
    *
    *  @return (AnyTypeKeyMap)
    */
    AnyType::AnyTypeMap GetAttributes() const { return m_attributes; };


    /*! Sets an Attribute on the Component *
    *
    *  @param[in] const unsigned int attributeId
    *  @param[in] const AnyType & value
    */
    inline void SetAttribute(const System::Attribute& attributeId, const AnyType& value) { m_attributes[ attributeId ] = value; };


    /*! Writes the contents of the object to the given stream
    *
    * @param[in] IStream * stream
    * @return (void)
    */
    void Serialize(IO::IStream* stream) { };


    /*! Reads the contents of the object from the stream
    *
    * @param[in] IStream * stream
    * @return (void)
    */
    void DeSerialize(IO::IStream* stream) { };


    /*!  Registers an LUA function to be included in the Game Update Loop
    *
    *  @param[in] luabind::object function
    *  @return (void)
    */
    void RegisterUpdate(const luabind::object& function);


    /*! UnRegisters an LUA function from being included in the Game Update Loop
    *
    *  @param[in] luabind::object function
    *  @return (void)
    */
    void UnRegisterUpdate(const luabind::object& function);


    /*! Registers a Script Function to receive Events
    *
    * @param[in] const std::string & eventType
    * @param[in] luabind::object handlerFunction
    * @return (void)
    */
    void RegisterEventHandler(const std::string& eventType, const luabind::object& handlerFunction);


    /*! Unregisters a Script Function from receiving Events
    *
    * @param[in] const std::string & eventType
    * @param[in] luabind::object handlerFunction
    * @return (void)
    */
    void UnregisterEventHandler(const std::string& eventType, const luabind::object& handlerFunction);


    /*! Runs the given input as LUA code
    *
    * @param[in] const std::string & input
    * @return (void)
    */
    void ExecuteString(const std::string& input);


    /*! Returns the Name of the Component
    *
    * @return (std::string)
    */
    inline std::string GetName() const { return (*m_attributes.find(System::Attributes::Name)).second.As<std::string>(); };

  private:


    Script::ILuaState* m_state;

    Script::IScriptFacadeManager* m_facadeManager;
    Script::IScriptMessageDispatcher* m_messageDispatcher;
    Script::IScriptEventDispatcher* m_eventDispatcher;
    Script::IScriptUpdateDispatcher* m_updateDispatcher;

    Script::IScriptFacade::ScriptFacadeList m_facades;

    IObserver* m_observer;
    Maths::MathVector3 m_lookAt;

    AnyType::AnyTypeMap m_attributes;
  };
}

#endif
