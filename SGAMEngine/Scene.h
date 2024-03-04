#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace sgam
{
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		GameObject* CreateGameObject(const std::string& name = "");
		void Add(std::unique_ptr<GameObject> pObject);
		std::unique_ptr<GameObject> Remove(GameObject* pObject);
		void RemoveAll();

		void FixedUpdate();
		void Update();
		void LateUpdate();

		void Render() const;

		void Cleanup();

		~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name) : m_Name(name) {}

		std::string m_Name;
		std::vector<std::unique_ptr<GameObject>> m_pObjects{};

		static unsigned int m_IdCounter; 
	};
}
