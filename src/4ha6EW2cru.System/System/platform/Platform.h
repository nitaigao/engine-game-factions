/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   Platform.hpp
*  @date   2010/07/17
*/
#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H

#include "../../Export.hpp"
#include "IPlatform.hpp"

namespace Platform 
{
    /*! Creates an instance of a platform for that the software is running on
    *
    *  @return (IPlatform*)
    */
    IPlatform* Local();
};

#endif
