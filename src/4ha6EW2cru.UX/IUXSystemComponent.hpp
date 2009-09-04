/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IUXSystemComponent.hpp
*  @date   2009/04/26
*/
#pragma once
#ifndef IUXSYSTEMCOMPONENT_H
#define IUXSYSTEMCOMPONENT_H

#include "IScriptComponent.hpp"

namespace UX
{
	/*! 
	*  A UX System Scene Component
	*/
	class GAMEAPI IUXSystemComponent : public Script::IScriptComponent
	{

	public:

		typedef std::deque< IUXSystemComponent* > UXSystemComponentList;

		virtual ~IUXSystemComponent( ) { };

	};
};

#endif
