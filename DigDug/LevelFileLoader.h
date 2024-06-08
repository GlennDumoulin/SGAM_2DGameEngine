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
        enum class EntityType
        {
            Invalid,
            Player,
            Pooka,
            Fygar
        };

        struct Entity final
        {
            EntityType type;
            glm::ivec2 pos;
        };

        struct LevelInfo final
		{
			std::vector<std::string> layerTextures;
			std::vector<glm::ivec2> tunnels;
            std::vector<Entity> entities;
		};

		static void Load(const std::string& filename, GridComponent* pGrid);

        static EntityType ConvertToEntityType(const std::string& type);

    private:
        static void CreateGridTile(sgam::GameObject* pObject, const glm::vec2& tilePos, std::shared_ptr<sgam::Texture2D> pTexture, const int& dstSize);
        static void CreatePlayer(sgam::GameObject* pObject, const glm::vec2& tilePos, const int& dstSize, const int& playerIdx);
        static void CreatePooka(sgam::GameObject* pObject, const glm::vec2& tilePos, const int& dstSize);
        static void CreateFygar(sgam::GameObject* pObject, const glm::vec2& tilePos, const int& dstSize);
	};
}

// Define custom serializers for custom types
/* Credit to ChatGPT - https://json.nlohmann.me/features/arbitrary_types/ */
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
    struct adl_serializer<digdug::LevelFileLoader::Entity>
    {
        static void from_json(const nlohmann::json& j, digdug::LevelFileLoader::Entity& e)
        {
            std::string type{};
            j.at("type").get_to(type);
            e.type = digdug::LevelFileLoader::ConvertToEntityType(type);
            j.at("pos").get_to(e.pos);
        }
    };

    template <>
    struct adl_serializer<digdug::LevelFileLoader::LevelInfo>
    {
        static void from_json(const nlohmann::json& j, digdug::LevelFileLoader::LevelInfo& l)
        {
            j.at("layerTextures").get_to(l.layerTextures);
            j.at("tunnels").get_to(l.tunnels);
            j.at("entities").get_to(l.entities);
        }
    };
}
