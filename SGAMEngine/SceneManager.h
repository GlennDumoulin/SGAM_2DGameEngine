#pragma once
#include <vector>
#include <string>
#include <memory>
#include <functional>

#include "Singleton.h"
#include "Scene.h"

namespace sgam
{
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene* CreateScene(const std::function<void(Scene*)>& sceneLoader, const std::string& name = "defaultScene");

		bool SetNextScene(const std::string& sceneName = "defaultScene");
		void LoadNextScene();

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

		// Define a custom deleter for std::unique_ptr
		// This way only SceneManager can create and delete Scenes
		/* Credit to ChatGPT - https://en.cppreference.com/w/cpp/memory/unique_ptr/unique_ptr */
		struct SceneDeleter
		{
			void operator()(Scene* ptr) const
			{
				delete ptr;
			}
		};

		std::vector<std::unique_ptr<Scene, SceneDeleter>> m_pScenes{};
		
		Scene* m_pActiveScene{ nullptr };
		Scene* m_pNextScene{ nullptr };
	};
}
