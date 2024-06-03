#pragma once
#include <functional>

#include "GameObject.h"

namespace sgam
{
	class Scene final
	{
	public:
		GameObject* CreateGameObject(const std::string& name = "");
		void Add(std::unique_ptr<GameObject> pObject);
		std::unique_ptr<GameObject> Remove(GameObject* pObject);
		void RemoveAll() { m_pObjects.clear(); }

		bool Load();

		void FixedUpdate();
		void Update();
		void LateUpdate();

		void Render() const;
		void RenderGUI();

		void Cleanup();

		const std::string& GetName() const { return m_Name; }

	private:
		friend class SceneManager;
		explicit Scene(const std::function<void(Scene*)>& sceneLoader, const std::string& name)
			: m_SceneLoader{ sceneLoader }
			, m_Name{ name }
		{}
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		std::string m_Name{};
		std::vector<std::unique_ptr<GameObject>> m_pObjects{};

		const std::function<void(Scene*)> m_SceneLoader{};
	};
}
