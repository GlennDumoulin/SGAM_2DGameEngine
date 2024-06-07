#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <json.hpp>

#include "GameObject.h"
#include "GridComponent.h"
#include "Texture2D.h"

namespace digdug
{
	class LevelFileLoader final
	{
	public:
		struct LevelInfo final
		{
			std::vector<std::string> layerTextures;
			std::vector<glm::ivec2> tunnels;
		};

		static void Load(const std::string& filename, GridComponent* pGrid);

    private:
        static void CreateGridTile(sgam::GameObject* pObject, const glm::vec2& tilePos, std::shared_ptr<sgam::Texture2D> pTexture, const int& dstSize);
	};
}

namespace nlohmann
{
    template <>
    struct adl_serializer<glm::ivec2>
    {
        static void from_json(const nlohmann::json& j, glm::ivec2& v)
        {
            j.at("x").get_to(v.x);
            j.at("y").get_to(v.y);
        }
    };

    template <>
    struct adl_serializer<digdug::LevelFileLoader::LevelInfo>
    {
        static void from_json(const nlohmann::json& j, digdug::LevelFileLoader::LevelInfo& l)
        {
            j.at("layerTextures").get_to(l.layerTextures);
            j.at("tunnels").get_to(l.tunnels);
        }
    };
}
