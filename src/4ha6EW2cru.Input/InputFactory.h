/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   InputFactory.h
*  @date   2009/11/07
*/
#pragma once
#ifndef INPUTFACTORY_H
#define INPUTFACTORY_H

#include "IInputFactory.hpp"

namespace Input
{
	/*! 
	 *  Creates Input Objects
	 */
	class InputFactory : public IInputFactory
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~InputFactory( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		InputFactory( ) { };


		/*! Creates an Input System
		*
		* @return ( IInputSystem* )
		*/
		IInputSystem* CreateInputSystem( );

	private:

		InputFactory( const InputFactory & copy ) { };
		InputFactory & operator = ( const InputFactory & copy ) { return *this; };
		
	};
};

#endif