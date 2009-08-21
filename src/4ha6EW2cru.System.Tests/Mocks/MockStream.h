/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   MockStream.h
*  @date   2009/08/13
*/
#pragma once
#ifndef MOCKSTREAM_H
#define MOCKSTREAM_H

#include "IO/IStream.hpp"

namespace 
{
	/*! 
	 *  
	 */
	class MockStream : public IO::IStream
	{

	public:

		MOCK_METHOD1(Write, void(const std::string&));
		MOCK_METHOD1(Read, void(std::string&));
		MOCK_METHOD1(Write, void(int));
		MOCK_METHOD1(Read, void(int&));
		
	};
};

#endif