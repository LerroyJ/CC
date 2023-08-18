#include "ccpch.h"
#include "Scene.h"
#include "Component.h"
#include "CEngine/Renderer/Renderer2D.h"
#include "CEngine/Renderer/Renderer3D.h"
#include "Entity.h"
namespace CEngine {

	Scene::Scene()
	{
	}
	Scene::~Scene()
	{
	}
	Entity& Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group) {
			auto [transform, sprite] = group.get<TransformComponent,SpriteRendererComponent>(entity);
			Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}
}