/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   SoundSystemComponent.h
*  @date   2009/04/27
*/
#pragma once
#ifndef SOUNDSYSTEMCOMPONENT_H
#define SOUNDSYSTEMCOMPONENT_H

#include "ISoundSystemComponent.hpp"
#include "ISoundEventSystem.hpp"

#include <fmod.hpp>
#include <fmod_event.hpp>

namespace Sound
{
  /*!
   *  A Sound System Component 
   */
  class GAMEAPI SoundSystemComponent : public ISoundSystemComponent
  {
    typedef std::multiset< std::string > TriggerRequestList;
    typedef std::map< std::string, FMOD::Event* > SoundEventMap;

  public:

    /*! Default Destructor
    *
    *  @return ()
    */
    ~SoundSystemComponent() { };


    /*! Default Constructor
    *
    *  @param[in] const std::string & name
    *  @return ()
    */
    SoundSystemComponent(const std::string& name, ISoundEventSystem* eventSystem)
      : m_name(name)
      , m_eventSystem(eventSystem)
    {

    }

    /*! Initializes the Component
    *
    *  @param[in] AnyType::AnyValueMap properties
    *  @return (void)
    */
    inline void Initialize() { };


    /*! Steps the internal data of the Component
    *
    *  @param[in] float deltaMilliseconds
    *  @return (void)
    */
    void Update(float deltaMilliseconds) { };


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
    AnyType Observe(const ISubject* subject, const System::MessageType& message, AnyType::AnyTypeMap parameters);


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


    /*! Returns the Name of the Component
    *
    * @return (std::string)
    */
    inline std::string GetName() const { return (*m_attributes.find(System::Attributes::Name)).second.As< std::string >(); };


    void KeyoutEvent(const std::string& eventPath);

  private:

    SoundSystemComponent(const SoundSystemComponent & copy) { };
    SoundSystemComponent & operator = (const SoundSystemComponent & copy) { return *this; };

    ISoundEventSystem* m_eventSystem;

    std::string m_name;
    AnyType::AnyTypeMap m_attributes;

    TriggerRequestList m_triggerRequests;
    SoundEventMap m_activeEvents;

  };
};

#endif
