/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IProgramOptions.hpp
*  @date   2009/11/24
*/
#pragma once
#ifndef IPROGRAMOPTIONS_HPP
#define IPROGRAMOPTIONS_HPP

#include <string>
#include <map>

namespace Platform
{
	/*! 
	 *  Keeps the command line options given to the program at launch
	 */
	class IProgramOptions
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~IProgramOptions() { };


		/*! Initializes the program options from the command line arguments
		 *
		 * @return (void)
		 */
		virtual void Initialize() = 0;


		/*! Detects whether the given option was passed to the program command line
		 *
		 * @param[in] const std::string & optionName
		 * @return (bool)
		 */
		virtual bool HasOption(const std::string& optionName) const = 0;


		/*! Returns an option specified on the command line
		 *
		 * @param[in] const std::string & optionName
		 * @return (std::string)
		 */
		virtual std::string GetOption(const std::string& optionName) const = 0;
		
	};
};

#endif