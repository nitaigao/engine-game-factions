/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   UXFactory.h
*  @date   2009/09/02
*/
#pragma once
#ifndef UXFACTORY_H
#define UXFACTORY_H

#include "IUXSystem.hpp"
#include "IGUI.hpp"

namespace UX
{
	class IUXFactory
	{
		/*! Creates a UX System
		 *
		 * @return ( IUXSystem* )
		 */
		virtual IUXSystem* CreateUXSystem( ) = 0;


		/*! Creates a UX GUI
		 *
		 * @return ( IGUI* )
		 */
		virtual IGUI* CreateUXGUI( ) = 0;

	};


	/*! 
	 *  Creates UX Classes
	 */
	class UXFactory : public IUXFactory
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~UXFactory( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		UXFactory( ) { };


		/*! Creates a UX System
		*
		* @return ( IUXSystem* )
		*/
		IUXSystem* CreateUXSystem( );


		/*! Creates a UX GUI
		*
		* @return ( IGUI* )
		*/
		IGUI* CreateUXGUI( );

	private:

		UXFactory( const UXFactory & copy ) { };
		UXFactory & operator = ( const UXFactory & copy ) { return *this; };
		
	};
};

#endif