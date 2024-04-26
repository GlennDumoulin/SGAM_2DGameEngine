#pragma once
#include <vector>
#include <string>
#include <memory>

#include "Singleton.h"

namespace sgam
{
	class Scene;

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void FixedUpdate();
		void Update();
		void LateUpdate();

		void Render() const;
		void RenderGUI();

		void Cleanup();

	private:
		friend class Singleton<SceneManager>;
		explicit SceneManager() = default;
		~SceneManager() = default;
		SceneManager(const SceneManager& other) = delete;
		SceneManager(SceneManager&& other) = delete;
		SceneManager& operator=(const SceneManager& other) = delete;
		SceneManager& operator=(SceneManager&& other) = delete;

		std::vector<std::shared_ptr<Scene>> m_pScenes{};
	};
}
