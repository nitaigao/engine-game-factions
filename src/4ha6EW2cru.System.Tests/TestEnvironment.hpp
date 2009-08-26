/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   TestEnvironment.hpp
*  @date   2009/08/21
*/
#pragma once
#ifndef TESTENVIRONMENT_HPP
#define TESTENVIRONMENT_HPP

#include "Logging/Logger.h"

namespace Testing
{
	/*! 
	 *  The Global Test SetUp TearDown Container
	 */
	class Environment : public testing::Environment
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~Environment( ) { };


		/*! Default Constructor
		*
		* @return (  )
		*/
		Environment( ) { };

		virtual void SetUp( )
		{
			Logging::Logger::Initialize( );
		}

		virtual void TearDown( )
		{
			Logging::Logger::Get( )->Release( );
		}

	private:

		Environment( const Environment & copy ) { };
		Environment & operator = ( const Environment & copy ) { return *this; };
		
	};
};

#endif