#pragma once
#include "SceneManager.h"

namespace sgam
{
	class GameObject;

	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::shared_ptr<GameObject> pObject);
		void Remove(std::shared_ptr<GameObject> pObject);
		void RemoveAll();

		void FixedUpdate();
		void Update();
		void LateUpdate();

		void Render() const;

		void Cleanup();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector<std::shared_ptr<GameObject>> m_pObjects{};

		static unsigned int m_IdCounter; 
	};
}
