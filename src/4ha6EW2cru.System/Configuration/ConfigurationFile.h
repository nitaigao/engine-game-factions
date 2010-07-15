  /*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ConfigurationFile.h
*  @date   2009/04/25
*/
#pragma once
#ifndef CONFIGURATIONFILE_H
#define CONFIGURATIONFILE_H

#include "IConfigurationFile.hpp"

#include "../IO/FileBuffer.hpp"
#include "../Utility/SimpleIni.h"

#include "../Platform/IPlatformManager.h"
#include "../IO/IFileSystem.hpp"

namespace Configuration
{
  /*! 
   *  Loads and Saves Configuration Information to the File System
   */
  class ConfigurationFile : public IConfigurationFile
  {

  public:

    /*! Default Destructor
     *
     *  @return ()
     */
    ~ConfigurationFile();


    ConfigurationFile(Platform::IPlatformManager* platformManager, IO::IFileSystem* fileSyostem);


    /*! Loads the given file contents into the configuration
    *
    * @param[in] const std::string & fileName
    * @return (void)
    */
    void Load(const std::string& fileName);
    

    /*! Finds a Configuration Item based on the given section and key
     *
     *  @param[in] const std::string & section
     *  @param[in] const std::string & key
     *  @param[in] const AnyType & defaultValue
     *  @return (AnyType)
     */
    AnyType FindConfigItem(const std::string& section, const std::string& key, const AnyType& defaultValue);


    /*! Returns an Entire Config Section
    *
    * @param[in] const std::string & section
    * @return (AnyType::AnyTypeMap)
    */
    AnyType::AnyTypeMap FindConfigSection(const std::string& section);


    /*! Updates a configuration item based on the given section and key
     *
     *  @param[in] const std::string & section
     *  @param[in] const std::string & key
     *  @param[in] const AnyType & value
     *  @return (void)
     */
    void Update(const std::string& section, const std::string& key, const AnyType& value);


    /*! Saves the configuration file to the File System
     *
     *  @return (void)
     */
    void Save();

  private:

    CSimpleIni* m_ini;
    std::string m_filePath;

    Platform::IPlatformManager* m_platformManager;
    IO::IFileSystem* m_fileSystem;

    ConfigurationFile(const ConfigurationFile & copy) { };
    ConfigurationFile & operator = (const ConfigurationFile & copy) { return *this; };

  };
};

#endif

