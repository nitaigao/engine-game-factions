#include "precompiled.h"
#include "ProgramOptions.h"

#ifdef WIN32
#include <windows.h>
#include <shellapi.h>
#endif

#include <tclap/CmdLine.h>
using namespace TCLAP;

#include <boost/program_options.hpp>
using namespace boost::program_options;

#include "../System/SystemType.hpp"

namespace Platform
{
	bool ProgramOptions::HasOption(const std::string& optionName) const
	{
		ProgramOptionMap::const_iterator i = m_programOptions.find(optionName);

		return i != m_programOptions.end();
	}

	std::string ProgramOptions::GetOption(const std::string& optionName) const
	{
		ProgramOptionMap::const_iterator i = m_programOptions.find(optionName);

		return (*i).second;
	}

	void ProgramOptions::Initialize()
	{
		/*int argc = 0;
		LPWSTR* args = CommandLineToArgvW(GetCommandLineW(), &argc);

		char** argv = new char*[ argc ];

		for (int i = 0; i <argc; i++)
		{
			argv[ i ] = new char[ 20480 ];
			WideCharToMultiByte(CP_UTF8, 0, args[ i ], -1, (LPSTR) argv[ i ], 20480, 0, 0);
		}

		CmdLine cmd("Command Line Options");

		ValueArg<std::string> levelNameArg("l", System::Options::LevelName.c_str(), "The Level to Load", false, "", "string");
		cmd.add(levelNameArg);

		SwitchArg dedicatedServerArg("d", System::Options::DedicatedServer.c_str(), "Run as a Dedicated Server", false);
		cmd.add(dedicatedServerArg);

		cmd.parse(argc, argv);

		if (!levelNameArg.getValue().empty())
		{
			m_programOptions[ System::Options::LevelName.c_str() ] = levelNameArg.getValue();
		}

		if (dedicatedServerArg.getValue())
		{
			m_programOptions[ System::Options::DedicatedServer.c_str() ] = dedicatedServerArg.getValue();
		}

		for (int i = 0; i <argc; i++)
		{
			delete[ ] argv[ i ];
		}

		delete[ ] argv;*/
	}
}