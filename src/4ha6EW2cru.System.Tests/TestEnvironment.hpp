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
#include "Platform/Win32PlatformManager.h"

using namespace Platform;

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
			m_platformManager = new Win32PlatformManager( );
			Logging::Logger::Initialize( m_platformManager );
		}

		virtual void TearDown( )
		{
			Logging::Logger::Get( )->Release( );
			delete m_platformManager;
		}

	private:

		Environment( const Environment & copy ) { };
		Environment & operator = ( const Environment & copy ) { return *this; };

		Platform::Win32PlatformManager* m_platformManager;
		
	};
};

#endif