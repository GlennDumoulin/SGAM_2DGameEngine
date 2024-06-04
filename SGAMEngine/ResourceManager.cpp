#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

void sgam::ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<sgam::Texture2D> sgam::ResourceManager::LoadTexture(const std::string& filename) const
{
	const auto fullPath = m_DataPath + filename;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_shared<Texture2D>(texture);
}

std::shared_ptr<sgam::Font> sgam::ResourceManager::LoadFont(const std::string& filename, unsigned int size) const
{
	return std::make_shared<Font>(m_DataPath + filename, size);
}

std::ifstream sgam::ResourceManager::LoadFile(const std::string& filename) const
{
	std::ifstream file{ m_DataPath + filename };
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to load file!");
	}

	return file;
}
