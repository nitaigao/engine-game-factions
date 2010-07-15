/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   WorldEntity.h
*  @date   2009/04/27
*/
#pragma once
#ifndef WORLDENTITY_H
#define WORLDENTITY_H

#include "IWorldEntity.hpp"

namespace State
{
  /*!
   *  A container for components that make up an Entity 
   */
  class GAMEAPI WorldEntity : public IWorldEntity
  {

  public:

    /*! Default Destructor
    *
    *  @return ()
    */
    ~WorldEntity() { };


    /*! Default Constructor
     *
     *  @param[in] const std::string & name
     *  @return ()
     */
    WorldEntity(const std::string& name)
      : m_name(name)
    {

    }


    /*! Returns the name of the Entity
    *
    *  @return (const std::string&)
    */
    inline std::string GetName() const { return m_name; };


    /*! Adds an Observer to the Subject
    *
    *  @param[in] IObserver * observer
    *  @return (void)
    */
    void AddObserver(const System::MessageType& message, IObserver* observer) { m_observers.insert(std::make_pair(message, observer)); };


    /*! Initializes all of the components contained by the entity
    *
    * @return (void)
    */
    void Initialize();


    /*! Adds a System Component to the Entity
    *
    *  @param[in] ISystemComponent * component
    *  @return (void)
    */
    void AddComponent(ISystemComponent* component);


    /*! Get a list of all System Components inside the Entity
    *
    *  @return (ISystemComponent::SystemComponentList&)
    */
    inline ISystemComponent::SystemComponentList GetComponents() const { return m_components; };


    /*! Sets an Attribute on all of the sub components
    *
    * @param[in] const System::Attribute & attribute
    * @param[in] AnyType value
    * @return (void)
    */
    void SetAttribute(const System::Attribute& attribute, const AnyType& value);


    /*! Messages the Component to influence its internal state
     *
     *  @param[in] const std::string & message
     *  @return (AnyType)
     */
    AnyType Observe(const ISubject* subject, const System::MessageType& message, AnyType::AnyTypeMap parameters);


    /*! Writes the contents of the entity to the given stream
    *
    * @param[in] IStream * stream
    * @return (void)
    */
    void Serialize(IO::IStream* stream);


    /*! Reads the contents of the entity from the stream
    *
    * @param[in] IStream * stream
    * @return (void)
    */
    void DeSerialize(IO::IStream* stream);

  private:

    WorldEntity(const WorldEntity & copy) { };
    WorldEntity & operator = (const WorldEntity & copy) { return *this; };

    std::string m_name;
    ISystemComponent::SystemComponentList m_components;
    ObserverMap m_observers;
    AnyType::AnyTypeMap m_attributes;

  };
};

#endif
