/**/
#pragma once
#ifndef SYSTEMEXPORTS_HPP
#define SYSTEMEXPORTS_HPP

#include "ISystem.hpp"

extern "C"
{
	typedef void ( __stdcall* InitializeSystemFunction ) ( Management* management, Logger* logger );
	typedef ISystem* ( __stdcall* CreateSystemFunction ) ( );
	typedef void ( __stdcall* DestroySystemFunction ) ( ISystem* system );
};

#endif
