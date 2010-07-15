#include "precompiled.h"
#include "ResourceCache.h"

using namespace IO;

#include "Resource.h"

#include "../Logging/Logger.h"
using namespace Logging;

namespace Resources
{
	static const int MAX_RESOURCE_CACHE_SIZE = 50;

	ResourceCache::~ResourceCache()
	{
		for (IResource::ResourceMap::iterator i = m_resourceCache.begin(); i != m_resourceCache.end(); ++i)
		{
			delete (*i).second;
		}
	}	

	IResource* ResourceCache::GetResource(const std::string& filePath)
	{
		IResource::ResourceMap::iterator result = m_resourceCache.find(filePath);

		if (result != m_resourceCache.end())
		{
			Debug("Cache hit for", filePath);
			return (*result).second;
		}

		FileBuffer* fileBuffer = m_fileSystem->GetFile(filePath, true);
		IResource* resource = new Resource(fileBuffer);

		m_resourceCache.insert(std::make_pair(filePath, resource));

		Debug("Cache miss for", filePath);

		return resource;
	}

	bool ResourceCache::ResourceExists(const std::string& filePath)
	{
		return m_fileSystem->FileExists(filePath);
	}

	IO::FileSearchResult::FileSearchResultList* ResourceCache::ResourceSearch(const std::string& path, const std::string& searchPattern, bool recursive) const
	{
		return m_fileSystem->FileSearch(path, searchPattern, recursive);
	}
};