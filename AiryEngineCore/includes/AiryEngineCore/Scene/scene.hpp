#pragma once

#include <memory>
#include <vector>


namespace AiryEngine
{
    class SceneEntity;
    // class LightSource;

    class Scene
    {
    public:
        Scene();
        Scene(std::shared_ptr<std::vector<std::shared_ptr<SceneEntity>>> scene_entities);

        void add_scene_entity(std::shared_ptr<SceneEntity> scene_entity);
        void remove_scene_entity(std::shared_ptr<SceneEntity> scene_entity);
        std::shared_ptr<std::vector<std::shared_ptr<SceneEntity>>> get_scene_entities() const { return this->scene_entities; }

        void set_light_source(std::shared_ptr<LightSource> light_source);
        void remove_light_source();
        std::shared_ptr<LightSource> get_light_source() const { return this->light_source; }
        bool has_light_source() const { return this->has_light_source_flag; }

    private:
        std::shared_ptr<std::vector<std::shared_ptr<SceneEntity>>> scene_entities;
        std::shared_ptr<LightSource> light_source;
        bool has_light_source_flag;
    };

} // namespace AiryEngine
