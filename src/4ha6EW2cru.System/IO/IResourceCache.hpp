/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IResourceManager.hpp
*  @date   2009/04/26
*/
#pragma once
#ifndef IRESOURCECACHE_H
#define IRESOURCECACHE_H

#include "IResource.hpp"
#include "../Export.hpp"

#include "FileSearchResult.hpp"

namespace Resources
{
	/*! 
	 *  A Cache of data retrieved from the FileSystem for fast access
	 */
	class GAMEAPI IResourceCache
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~IResourceCache() { };


		/*! Returns a Resource from the given file path
		 *
		 *  @param[in] const std::string & filePath
		 *  @return (Resources::IResource*)
		 */
		virtual Resources::IResource* GetResource(const std::string& filePath) = 0;


		/*! Checks to see if the Resource Exists
		 *
		 * @param[in] const std::string & filePath
		 * @return (bool)
		 */
		virtual bool ResourceExists(const std::string& filePath) = 0;


		/*! Steps the internal data of the cache
		 *
		 *  @param[in] float deltaMilliseconds
		 *  @return (void)
		 */
		virtual void Update(float deltaMilliseconds) = 0;


		/*! Searches for a Resource in the cache
		 *
		 * @param[in] const std::string & path
		 * @param[in] const std::string & searchPattern
		 * @param[in] bool recursive
		 * @return (FileSearchResult::FileSearchResultList*)
		 */
		virtual IO::FileSearchResult::FileSearchResultList* ResourceSearch(const std::string& path, const std::string& searchPattern, bool recursive) const = 0;

	};
};

#endif
