/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ResourceManager.h
*  @date   2009/04/26
*/
#pragma once
#ifndef RESOURCECACHE_H
#define RESOURCECACHE_H

#include <map>

#include "IResourceCache.hpp"
#include "IFileSystem.hpp"

namespace Resources
{
	/*! 
	*  A Cache of data retrieved from the FileSystem for fast access
	*/
	class GAMEAPI ResourceCache : public IResourceCache
	{

	public:

		/*! Default Destructor
		*
		*  @return ()
		*/
		~ResourceCache();


		/*! Default Constructor
		 *
		 *  @return ()
		 */
		ResourceCache(IO::IFileSystem* fileSystem)
			: m_fileSystem(fileSystem)
		{

		}


		/*! Returns a Resource from the given file path
		*
		*  @param[in] const std::string & filePath
		*  @return (Resources::IResource*)
		*/
		IResource* GetResource(const std::string& filePath);


		/*! Checks to see if the Resource Exists
		*
		* @param[in] const std::string & filePath
		* @return (bool)
		*/
		bool ResourceExists(const std::string& filePath);


		/*! Steps the internal data of the cache, may perform cache releases depending on resource age
		*
		*  @param[in] float deltaMilliseconds
		*  @return (void)
		*/
		inline void Update(float deltaMilliseconds) { };


		/*! Searches for a Resource in the cache
		*
		* @param[in] const std::string & path
		* @param[in] const std::string & searchPattern
		* @param[in] bool recursive
		* @return (FileSearchResult::FileSearchResultList*)
		*/
		IO::FileSearchResult::FileSearchResultList* ResourceSearch(const std::string& path, const std::string& searchPattern, bool recursive) const;

	private:

		IResource::ResourceMap m_resourceCache;
		IO::IFileSystem* m_fileSystem;

	};
};

#endif
