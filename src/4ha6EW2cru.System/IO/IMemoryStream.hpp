/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IMemoryStream.h
*  @date   2009/07/27
*/
#pragma once
#ifndef IMEMORYSTREAM_HPP
#define IMEMORYSTREAM_HPP

#include "IStream.hpp"

namespace IO
{
	/*! 
	 *  A Stream that stores data in Memory
	 */
	class IMemoryStream : public IO::IStream
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~IMemoryStream( ) { };
		
	};
};

#endif