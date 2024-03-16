/**
 * @file Scene.cpp
 * @author flexhaufen
 * @brief Sceen Class
 * @version 0.1
 * @date 2024-01-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// *** INCLUDES ***
#include "Lychee/Scene/Scene.h"
#include "Lychee/Scene/Entity/Entity.h"


// *** DEFINE ***

// *** NAMESPACE ***
namespace Lychee {

    Scene::Scene()
    : m_Camera(glm::radians(60.0f), 1920.0f / 1080.0f, 0.1f, 1000.0f) {
        LY_CORE_INFO("Scene: Initializing");
    }

    Scene::~Scene() {
        LY_CORE_INFO("Scene: Terminating");
    }

    Entity Scene::CreateEntity(const std::string& name) {
        return CreateEntityWithUUID(UUID(), name);
	}

    Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string& name) {
        Entity entity = { m_Registry.create(), this };
		auto& tag = entity.AddComponent<Component::Tag>();
        tag.uuid = uuid;
		tag.tag = name;

		auto& transform = entity.AddComponent<Component::Transform>();

        // m_EntityMap[uuid] = entity;

		return entity;
    }

    void Scene::DestroyEntity(Entity &entity) {

        // Destory Body from registry
        m_Registry.destroy(entity);
    }

    // *** Scene Handling ***


    void Scene::OnRuntimeStart() {
        m_IsRuntimeRunning = true;
    
        m_Renderer.Init();
    }

    void Scene::OnRuntimeStop() {
        m_IsRuntimeRunning = false;
    }



    void Scene::OnRuntimeUpdate(DeltaTime dt) {
        m_Camera.OnUpdate(dt);
        m_Renderer.Clear();
        m_Renderer.Render(m_Camera.GetViewProjectionMatrix());
    }

    void Scene::OnEditorUpdate(DeltaTime dt) {
        
    }
}