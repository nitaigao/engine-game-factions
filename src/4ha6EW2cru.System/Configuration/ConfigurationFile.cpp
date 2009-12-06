#include "ConfigurationFile.h"

#include <sstream>

#include "../IO/IResource.hpp"
using namespace IO;

namespace Configuration
{
	ConfigurationFile::~ConfigurationFile()
	{
		if( m_ini != 0 )
		{
			delete m_ini;
		}
	}

	ConfigurationFile::ConfigurationFile( Platform::IPlatformManager* platformManager, IO::IFileSystem *fileSystem )
		: m_platformManager( platformManager )
		, m_fileSystem( fileSystem )
	{
		m_ini = new CSimpleIni( true );
	}

	void ConfigurationFile::Load( const std::string& fileName )
	{
		std::stringstream configPath;
		configPath << m_platformManager->GetPathInformation( )->GetLocalConfigPath( ) << "/" << fileName;

		if ( !m_fileSystem->FileExists( configPath.str( ) ) )
		{
			FileBuffer fileBuffer( 0, 0, configPath.str( ) );
			m_fileSystem->SaveFile( fileBuffer );
		}

		FileBuffer* buffer = m_fileSystem->GetFile( configPath.str( ), true );

		m_ini->Load( buffer->fileBytes );
		m_filePath = buffer->filePath;

		delete buffer;
	}

	AnyType ConfigurationFile::FindConfigItem( const std::string& section, const std::string& key, const AnyType& defaultValue )
	{
		AnyType result;
		AnyType& unConstDefaultValue = const_cast< AnyType& >( defaultValue );

		if ( unConstDefaultValue.GetType( ) == typeid( bool ) )
		{
			result = m_ini->GetBoolValue( section.c_str( ), key.c_str( ), unConstDefaultValue.As< bool >( ) );
		}

		if ( unConstDefaultValue.GetType( ) == typeid( int ) )
		{
			result = static_cast< int >( m_ini->GetLongValue( section.c_str( ), key.c_str( ), unConstDefaultValue.As< int >( ) ) );
		}

		if ( unConstDefaultValue.GetType( ) == typeid( std::string ) )
		{
			result = m_ini->GetValue( section.c_str( ), key.c_str( ), unConstDefaultValue.As< std::string >( ).c_str( ) );
		}

		return result;
	}

	void ConfigurationFile::Update( const std::string& section, const std::string& key, const AnyType& value )
	{
		AnyType& unConstValue = const_cast< AnyType& >( value );

		if ( unConstValue.GetType( ) == typeid( bool ) )
		{
			m_ini->SetBoolValue( section.c_str( ), key.c_str( ), unConstValue.As< bool >( ) );
		}

		if ( unConstValue.GetType( ) == typeid( int ) )
		{
			m_ini->SetLongValue( section.c_str( ), key.c_str( ), unConstValue.As< int >( ) );
		}

		if ( unConstValue.GetType( ) == typeid( std::string ) )
		{
			m_ini->SetValue( section.c_str( ), key.c_str( ), unConstValue.As< std::string >( ).c_str( ) );
		}
	}

	void ConfigurationFile::Save( )
	{
		std::string output;
		m_ini->Save( output );

		char* outputBuffer = new char[ output.length( ) + 1 ];
		memcpy( outputBuffer, output.c_str( ), output.length( ) );
		outputBuffer[ output.length( ) ] = '\0';

		FileBuffer fileBuffer( outputBuffer, output.length( ), m_filePath );
		m_fileSystem->SaveFile( fileBuffer );
	}

	AnyType::AnyTypeMap ConfigurationFile::FindConfigSection( const std::string& section )
	{
		AnyType::AnyTypeMap items;

		const CSimpleIni::TKeyVal* results =  m_ini->GetSection( section.c_str( ) );

		if ( results )
		{
			for ( CSimpleIni::TKeyVal::const_iterator i = results->begin( ); i != results->end( ); ++i )
			{
				items[ ( *i ).first.pItem ] = ( *i ).second;
			}
		}

		return items;
	}
}