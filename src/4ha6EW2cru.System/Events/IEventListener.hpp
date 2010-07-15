/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IEventListener.hpp
*  @date   2009/04/25
*/
#pragma once
#ifndef IEVENTLISTENER_H
#define IEVENTLISTENER_H

#include "IEvent.hpp"
#include "EventType.hpp"

#include <map>

namespace Events
{
  /*! 
   *  Interface that listens for Events and handles the appropriate action
   */
  class IEventListener
  {

  public:

    typedef std::multimap<unsigned int, IEventListener*> EventListenerMultiMap;

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~IEventListener() { };

    
    /*! Handles the Event that is being listened for
     *
     *  @param[in] const IEvent *
     *  @return (void)
     */
    virtual void HandleEvent(const IEvent*) const = 0;

    
    /*! Marks the EventHandler for Deletion on the Next Update
     *
     *  @return (void)
     */
    virtual void MarkForDeletion() = 0;


    /*! Gets whether the EventHandler is marked for deletion
     *
     *  @return (bool)
     */
    virtual bool IsMarkedForDeletion() const = 0;


    /*! Returns the Address of the Class performing the Task
     *
     * @return (unsigned int)
     */
    virtual unsigned int GetHandlerAddress() const = 0;


    /*! Returns the name to the Function performing the Task
    *
    * @return (std::string)
    */
    virtual std::string GetHandlerFunctionName() const = 0;


    inline bool operator == (IEventListener* input) const
    {
      return (
        this->GetHandlerAddress() == input->GetHandlerAddress() &&
        this->GetHandlerFunctionName() == input->GetHandlerFunctionName()
       );
    }

  };
};

#endif

