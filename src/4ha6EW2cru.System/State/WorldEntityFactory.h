/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   WorldEntityFactory.h
*  @date   2009/08/13
*/
#pragma once
#ifndef WORLDENTITYFACTORY_H
#define WORLDENTITYFACTORY_H

#include "IWorldEntityFactory.hpp"

namespace State
{
  /*! 
   *  A Factory for creating entities
   */
  class WorldEntityFactory : public IWorldEntityFactory
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    ~WorldEntityFactory() { };


    /*! Default Constructor
    *
    * @return ()
    */
    WorldEntityFactory() { };


    /*! Creates an Entity
    *
    * @param[in] const std::string & name
    * @return (IWorldEntity*)
    */
    IWorldEntity* CreateEntity(const std::string& name) const;

  private:

    WorldEntityFactory(const WorldEntityFactory & copy) { };
    WorldEntityFactory & operator = (const WorldEntityFactory & copy) { return *this; };
    
  };
};

#endif