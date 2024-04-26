#pragma once
#include <string>
#include <memory>

#include "Singleton.h"

namespace sgam
{
	class Texture2D;
	class Font;

	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;

	private:
		friend class Singleton<ResourceManager>;
		explicit ResourceManager() = default;
		~ResourceManager() = default;
		ResourceManager(const ResourceManager& other) = delete;
		ResourceManager(ResourceManager&& other) = delete;
		ResourceManager& operator=(const ResourceManager& other) = delete;
		ResourceManager& operator=(ResourceManager&& other) = delete;

		std::string m_dataPath{};
	};
}
