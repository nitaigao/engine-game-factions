/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IConfiguration.hpp
*  @date   2009/04/25
*/
#pragma once
#ifndef ICONFIGURATION_H
#define ICONFIGURATION_H

#include "../System/AnyType.hpp"
#include "../Export.hpp"

namespace Configuration
{
	/*! 
	 *  The Game Configuration Source
	 */
	class GAMEAPI IConfiguration
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~IConfiguration( ) { };


		/*! Initializes the Configuration from the given file path, if it doesn't exist it will be created
		 *
		 * @param[in] const std::string & filePath
		 * @return ( void )
		 */
		virtual void Initialize( const std::string& filePath ) = 0;


		/*! Finds the value for the given section and key
		 *
		 *  @param[in] const std::string & section
		 *  @param[in] const std::string & key
		 *  @return (void)
		 */
		virtual AnyType Find( const std::string& section, const std::string& key ) = 0;


		/*! Finds an entire section
		*
		* @param[in] const std::string & section
		* @return ( AnyType::AnyTypeMap )
		*/
		virtual AnyType::AnyTypeMap FindSection( const std::string& section ) = 0;


		/*! Sets the Default value of an Item
		 *
		 *  @param[in] const std::string & section
		 *  @param[in] const std::string & key
		 *  @param[in] const boost::any & value
		 *  @return (void)
		 */
		virtual void SetDefault( const std::string& section, const std::string& key, const AnyType& value ) = 0;


		/*! Sets the value of an already defaulted item
		 *
		 *  @param[in] const std::string & section
		 *  @param[in] const std::string & key
		 *  @param[in] const std::string & value
		 *  @return (void)
		 */
		virtual void Set( const std::string& section, const std::string& key, const AnyType& value ) = 0;

	};
};

#endif
