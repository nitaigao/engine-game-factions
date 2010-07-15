/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   PhysicsSystemComponent.h
*  @date   2009/04/26
*/
#pragma once
#ifndef PHYSICSSYSTEMCOMPONENT_H
#define PHYSICSSYSTEMCOMPONENT_H

#include "IPhysicsSystemComponent.hpp"
#include "HavokPhysicsSystemScene.h"

#include "Maths/MathVector3.hpp"
#include "Maths/MathQuaternion.hpp"

#include <Common/Base/hkBase.h>
#include <Common/Serialize/Util/hkLoader.h>

#include "IO/IResourceCache.hpp"

namespace Physics
{
  /*! 
   *  A Standard Physics Component
   */
  class PhysicsSystemComponent : public IPhysicsSystemComponent
  {

  public:


    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~PhysicsSystemComponent();


    /*! Default Constructor
     *
     *  @param[in] const std::string & name
     *  @param[in] HavokPhysicsSystemScene * scene
     *  @param[in] int componentId
     *  @return ()
     */
    PhysicsSystemComponent(const std::string& name, HavokPhysicsSystemScene* scene, Resources::IResourceCache* resourceCache)
      : _name (name)
      , _scene(scene)
      , m_resourceCache(resourceCache)
      , m_loadedData(0)
      , m_body(0)
    {

    }


    /*! Initializes the Component
    *
    *  @param[in] AnyType::AnyValueMap properties
    *  @return (void)
    */
    virtual void Initialize();


    /*! Steps the internal data of the Component
    *
    *  @param[in] float deltaMilliseconds
    *  @return (void)
    */
    virtual void Update(float deltaMilliseconds) { };


    /*! Destroys the Component
    *
    *  @return (void)
    */
    void Destroy() { };


    /*! Adds an Observer to the Component
    *
    *  @param[in] IObserver * observer
    *  @return (void)
    */
    inline void AddObserver(IObserver* observer) { m_observer = observer; };


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
    AnyType PushMessage(const System::MessageType& message, AnyType::AnyTypeMap parameters);


    /*! Messages the Component to influence its internal state
    *
    *  @param[in] const std::string & message
    *  @return (AnyType)
    */
    virtual AnyType Observe(const ISubject* subject, const System::MessageType& message, AnyType::AnyTypeMap parameters);


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


    /*! Returns the RigidBody of the Component
    *
    *  @return (hkpRigidBody*)
    */
    inline hkpRigidBody* GetRigidBody() const { return m_body; };

  protected:

    std::string _name;
    AnyType::AnyTypeMap m_attributes;

    IObserver* m_observer;
    HavokPhysicsSystemScene* _scene;
    
    hkpRigidBody* m_body;
    hkPackfileData* m_loadedData;

    Resources::IResourceCache* m_resourceCache;

    PhysicsSystemComponent(const PhysicsSystemComponent & copy) { };
    PhysicsSystemComponent & operator = (const PhysicsSystemComponent & copy) { return *this; };

  };
};

#endif
