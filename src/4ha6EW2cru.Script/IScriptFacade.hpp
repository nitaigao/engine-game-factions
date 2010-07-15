/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IScriptFacade.hpp
*  @date   2009/05/15
*/
#pragma once
#ifndef ISCRIPTFACADE_HPP
#define ISCRIPTFACADE_HPP

#include <deque>

#include "IScriptComponent.hpp"

#include "Export.hpp"

namespace Script
{
  /*!
   *  A Controller For Interfacing with different components from a Script 
   */
  class GAMEAPI IScriptFacade
  {

  public:

    typedef std::deque<IScriptFacade*> ScriptFacadeList;

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~IScriptFacade() { };


    /*! Initializes the Facade with the given ScriptComponent
     *
     * @param[in] IScriptComponent *
     * @return (void)
     */
    virtual void Initialize() = 0;


    /*! Returns the Name that the Facade will use in script
     *
     * @return (std::string)
     */
    virtual std::string GetName() = 0;


    enum FacadeType
    {
      ANIMATION = 0,
      INPUT = 1,
      INSTRUMENTATION = 2,
      NETWORK = 3,
      PHYSICS = 4,
      SOUND = 5,
      SYSTEM = 6,
      FACADETYPE_MAX = 7
    };

  };
};

#endif
