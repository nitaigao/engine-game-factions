/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   PhysicsFacade.h
*  @date   2009/08/27
*/
#pragma once
#ifndef PHYSICSFACADE_H
#define PHYSICSFACADE_H

#include "IScriptFacade.hpp"
#include <luabind/luabind.hpp>

#include "Maths/MathVector3.hpp"

#include "Service/IServiceManager.h"

namespace Script
{
  /*! 
   *  A Facade for the Physics Service
   */
  class PhysicsFacade : public IScriptFacade
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    ~PhysicsFacade() { };


    /*! Default Constructor
    *
    * @return ()
    */
    PhysicsFacade(Services::IServiceManager* serviceManager)
      : m_serviceManager(serviceManager)
    {

    }


    /*! Registers the Script functions
    *
    * @return (void)
    */
    static luabind::scope RegisterFunctions();


    /*! Returns the Name that the Facade will use in script
    *
    * @return (std::string)
    */
    inline std::string GetName() { return "physics"; };


    /*! Casts a Ray and Returns the Hit Results
     *
     * @param[in] const Maths::MathVector3 & origin
     * @param[in] const Maths::MathVector3 & direction
     * @param[in] float length
     * @param[in] bool sortByDistance
     * @param[in] int maxResults
     * @return (std::vector<std::string>)
     */
    std::vector<std::string> RayQuery(const Maths::MathVector3& origin, const Maths::MathVector3& direction, float length, bool sortByDistance, int maxResults);


    /*! Initializes the Facade with the given ScriptComponent
    *
    * @return (void)
    */
    void Initialize() { };

  private:

    PhysicsFacade(const PhysicsFacade & copy) { };
    PhysicsFacade & operator = (const PhysicsFacade & copy) { return *this; };

    Services::IServiceManager* m_serviceManager;
    
  };
};

#endif