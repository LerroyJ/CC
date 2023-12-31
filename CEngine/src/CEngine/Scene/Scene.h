#pragma once
#include "entt.hpp"
#include "CEngine/Core/Timestep.h"
#include "CEngine/Renderer/EditorCamera.h"
namespace CEngine{
	class Entity;
	class Scene {
	public:
		Scene();
		~Scene();

		Entity& CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnViewportResize(uint32_t width, uint32_t height);

		void OnUpdate(Timestep ts);
		void OnUpdateEditor(Timestep ts, EditorCamera& camera);

		Entity GetPrimaryCameraEntity();
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};
}