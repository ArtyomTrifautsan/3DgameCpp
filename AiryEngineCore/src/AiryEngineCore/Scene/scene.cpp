#include "scene.hpp"

#include <AiryEngineCore/Scene/scene_entity.hpp>


namespace AiryEngine {

    Scene::Scene()
    {
        this->scene_entities = std::make_shared<std::vector<std::shared_ptr<SceneEntity>>>();

        this->light_source = std::make_shared<LightSource>();
        this->has_light_source_flag = false;
    }


    Scene::Scene(std::shared_ptr<std::vector<std::shared_ptr<SceneEntity>>> scene_entities)
    {
        this->scene_entities = scene_entities;

        this->light_source = std::make_shared<LightSource>();
        this->has_light_source_flag = false;
    }


    void Scene::add_scene_entity(std::shared_ptr<SceneEntity> scene_entity)
    {
        this->scene_entities->push_back(scene_entity);
    }


    void Scene::remove_scene_entity(std::shared_ptr<SceneEntity> scene_entity)
    {
        for (std::vector<std::shared_ptr<SceneEntity>>::iterator curr_scene_entity_ptr = this->scene_entities->begin(); 
            curr_scene_entity_ptr != this->scene_entities->end();)
        {
            if (*curr_scene_entity_ptr == scene_entity)
                curr_scene_entity_ptr = this->scene_entities->erase(curr_scene_entity_ptr);
            else
                ++curr_scene_entity_ptr;
        }
    }


    void Scene::set_light_source(std::shared_ptr<LightSource> light_source)
    {
        this->light_source = light_source;
        this->has_light_source_flag = true;
    }


    void Scene::remove_light_source()
    {
        this->light_source = nullptr;
        this->has_light_source_flag = false;
    }

}