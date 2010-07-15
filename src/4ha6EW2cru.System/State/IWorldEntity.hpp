/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IWorldEntity.hpp
*  @date   2009/04/27
*/
#pragma once
#ifndef IWORLDENTITY_HPP
#define IWORLDENTITY_HPP

#include "../System/ISystemComponent.hpp"
#include "../System/ISerializable.hpp"

namespace State
{
  /*!
   *  A World Entity Container 
   */
  class GAMEAPI IWorldEntity : public IObserver, public System::ISerializable
  {

  public:

    typedef std::deque<IWorldEntity*> WorldEntityList;
    typedef std::map<std::string, IWorldEntity*> WorldEntityMap;

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~IWorldEntity() { };


    /*! Returns the name of the Entity
     *
     *  @return (const std::string&)
     */
    virtual std::string GetName() const = 0;


    /*! Initializes all of the components contained by the entity
    *
    * @return (void)
    */
    virtual void Initialize() = 0;


    /*! Adds a System Component to the Entity
     *
     *  @param[in] ISystemComponent * component
     *  @return (void)
     */
    virtual void AddComponent(ISystemComponent* component) = 0;


    /*! Get a list of all System Components inside the Entity
     *
     *  @return (ISystemComponent::SystemComponentList&)
     */
    virtual ISystemComponent::SystemComponentList GetComponents() const = 0;


    /*! Adds a Foreign Observer to the Entity
    *
    *  @param[in] IObserver * observer
    *  @return (void)
    */
    virtual void AddObserver(const System::MessageType& message, IObserver* observer) = 0;


    /*! Sets an Attribute on all of the sub components
    *
    * @param[in] const System::Attribute & attribute
    * @param[in] AnyType value
    * @return (void)
    */
    virtual void SetAttribute(const System::Attribute& attribute, const AnyType& value) = 0;

  };
};

#endif
