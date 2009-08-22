/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   UXSystem.h
*  @date   2009/04/26
*/
#pragma once
#ifndef UXSYSTEM_H
#define UXSYSTEM_H

#include "IUXSystem.hpp"
#include "IUXSystemScene.hpp"

#include "Service/IService.hpp"

namespace UX
{
	/*! 
	 *  The System that controls the User Experience ( ie. GUI Elements )
	 */
	class UXSystem : public IUXSystem, public Services::IService
	{

	public:

		/*! Default Destructor
		*
		*  @return ()
		*/
		~UXSystem( ) { };


		/*! Default Constructor
		 *
		 *  @return ()
		 */
		UXSystem( )
			: m_scene( 0 )
		{

		}


		/*! Initializes the System
		*
		*  @return (void)
		*/
		void Initialize( Configuration::IConfiguration* configuration );


		/*! Steps the System's internal data
		*
		*  @param[in] float deltaMilliseconds
		*  @return (void)
		*/
		void Update( float deltaMilliseconds );


		/*! Releases the System
		*
		*  @return (void)
		*/
		inline void Release( ) { };


		/*! Messages the system with a command
		*
		* @param[in] const std::string & message
		* @param[in] AnyType::AnyTypeMap parameters
		* @return ( void )
		*/
		AnyType::AnyTypeMap ProcessMessage( const System::MessageType& message, AnyType::AnyTypeMap parameters );


		/*! Returns the type of the System
		*
		*  @return (System::Types::Type)
		*/
		inline System::Types::Type GetType( ) const { return System::Types::UX; };


		/*! Creates a System Scene
		*
		*  @return (ISystemScene*)
		*/
		ISystemScene* CreateScene( );


		/*! Gets the System's Properties
		*
		*  @return (AnyTypeMap)
		*/
		inline AnyType::AnyTypeMap GetAttributes( ) const { return m_attributes; };


		/*! Sets a System Property
		*
		*  @param[in] const std::string & name
		*  @param[in] AnyType value
		*  @return (void)
		*/
		inline void SetAttribute( const std::string& name, AnyType value ) { };

	private:

		AnyType::AnyTypeMap m_attributes;

		IUXSystemScene* m_scene;

	};
};

#endif
