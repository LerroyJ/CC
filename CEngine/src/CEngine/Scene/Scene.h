#pragma once
#include "entt.hpp"
#include "CEngine/Core/Timestep.h"
namespace CEngine{
	class Entity;
	class Scene {
	public:
		Scene();
		~Scene();

		Entity& CreateEntity(const std::string& name = std::string());

		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;

		friend class Entity;
	};
}