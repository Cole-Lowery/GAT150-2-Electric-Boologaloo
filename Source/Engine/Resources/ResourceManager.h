#pragma once
#include "Core/StringHelper.h"
#include "Resource.h"
#include "Core/Singleton.h"
#include "Core/Logger.h"

#include <string>
#include <map>
#include <memory>
#include <iostream>

namespace viper {
	class ResourceManager : public Singleton<ResourceManager> {
	public:
		void Clear() { m_resources.clear(); }

		template<typename T, typename ... TArgs>
			requires std::derived_from<T, Resource>
		res_t<T> Get(const std::string& name, TArgs&& ... args);

		template<typename T, typename ... TArgs>
		res_t<T> GetWithID(const std::string& id, const std::string& name, TArgs&& ... args);


	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;

		std::map<std::string, res_t<Resource>> m_resources;


	};



	template<typename T, typename ... TArgs>
		requires std::derived_from<T, Resource>
	inline res_t<T> ResourceManager::Get(const std::string& name, TArgs&& ... args) {
		return GetWithID<T>(name, name, std::forward<TArgs>(args)...);
	}

	template<typename T, typename ...TArgs>
	inline res_t<T> ResourceManager::GetWithID(const std::string& id, const std::string& name, TArgs && ...args) {
		std::string key = toLower(id);

		auto iter = m_resources.find(key);
		//check if exists
		if (iter != m_resources.end()) {
			//get value in iterator
			auto base = iter->second;
			//cast to data type T
			auto derived = std::dynamic_pointer_cast<T>(base);
			//check if cas was successful
			if (derived == nullptr) {
			Logger::Error("Resource type mismatch: {}", key);
				
				return res_t<T>();
			}
			//return resource
			return derived;

			return res_t<T>();


		}

		//load resource
		res_t<T> resource = std::make_shared<T>();
		if (resource->Load(name, std::forward<TArgs>(args) ...) == false) {
			Logger::Error("Could not load resource: {}", name );
			return res_t<T>();
		}
		//add resource to resource manager
		m_resources[key] = resource;

		return resource;


	}
		inline ResourceManager& Resources() { return ResourceManager::Instance(); }

}