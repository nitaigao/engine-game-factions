/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   Configuration.h
*  @date   2009/04/25
*/
#pragma once
#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#pragma warning(disable : 4251)

#include "IConfiguration.hpp"
#include "IConfigurationFile.hpp"

namespace Configuration
{
  /*! 
   *  Contains configuration items from the file system
   */
  class GAMEAPI ClientConfiguration : public IConfiguration
  {
    typedef std::pair<std::string, AnyType> KeyValuePair;
    typedef std::multimap<std::string, KeyValuePair> DefaultPropertyList;

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    ~ClientConfiguration();


    ClientConfiguration(Configuration::IConfigurationFile* configurationFile)
      : m_configFile(configurationFile)
    {

    };


    /*! Initializes the Configuration from the given file path, if it doesn't exist it will be created
    *
    * @param[in] const std::string & filePath
    * @return (void)
    */
    void Initialize(const std::string& filePath);


    /*! Finds a configuration item based on the specified section and key
     *
     *  @param[in] const std::string & section
     *  @param[in] const std::string & key
     *  @return (AnyType)
     */
    AnyType Find(const std::string& section, const std::string& key);


    /*! Finds an entire section
    *
    * @param[in] const std::string & section
    * @return (AnyType::AnyTypeMap)
    */
    AnyType::AnyTypeMap FindSection(const std::string& section);


    /*! Sets the default value for a configuration item
     *
     *  @param[in] const std::string & section
     *  @param[in] const std::string & key
     *  @param[in] const AnyType & value
     *  @return (void)
     */
    void SetDefault(const std::string& section, const std::string& key, const AnyType& value);


    /*! Sets the value for a configuration item
     *
     *  @param[in] const std::string & section
     *  @param[in] const std::string & key
     *  @param[in] const AnyType & value
     *  @return (void)
     */
    void Set(const std::string& section, const std::string& key, const AnyType& value);

  private:

    IConfigurationFile* m_configFile;
    DefaultPropertyList m_defaultPropertyList;

    ClientConfiguration(const ClientConfiguration & copy) { };
    ClientConfiguration & operator = (const ClientConfiguration & copy) { return *this; };
    
  };
};

#endif
