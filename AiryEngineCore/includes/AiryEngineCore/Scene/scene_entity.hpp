/*
Реализовать движение объекта по направлению вектора
*/


#pragma once

#include <glm/vec3.hpp>

#include <memory>
#include <vector>
#include <string>


namespace AiryEngine {

    class Model3D;
    class SolidCube;
    class LightSource;

    class SceneEntity
    {
    public:
        SceneEntity();
        SceneEntity(std::shared_ptr<std::vector<std::shared_ptr<Model3D>>> models,
                    std::shared_ptr<std::vector<std::shared_ptr<SolidCube>>> solid_cubes,
                    std::shared_ptr<std::vector<std::shared_ptr<LightSource>>> light_sources);

        ~SceneEntity();

        bool change_name(std::string new_name);

        void add_model(std::shared_ptr<Model3D> model);
        void add_solid_cube(std::shared_ptr<SolidCube> colliding_cube);
        void add_light_source(std::shared_ptr<LightSource> light_source);

        void remove_model(std::shared_ptr<Model3D> model);
        void remove_solid_cube(std::shared_ptr<SolidCube> colliding_cube);
        void remove_light_source(std::shared_ptr<LightSource> light_source);

        std::shared_ptr<std::vector<std::shared_ptr<Model3D>>> get_models() const { return this->models; }
        std::shared_ptr<std::vector<std::shared_ptr<SolidCube>>> get_solid_cubes() const { return this->solid_cubes; }
        std::shared_ptr<std::vector<std::shared_ptr<LightSource>>> get_light_sources() const { return this->light_sources; }

        bool get_is_visible() const { return this->is_visible; }
        bool get_is_solid() const { return this->is_solid; }

        void set_is_visible(bool is_visible);
        void set_is_solid(bool is_solid);

        void set_translate(const glm::vec3 translate);
        void set_translate(float translate_x, float translate_y, float translate_z);
        void set_translate_x(float translate_x);
        void set_translate_y(float translate_y);
        void set_translate_z(float translate_z);

        void set_scale(const glm::vec3 scale);
        void set_scale(float scale_x, float scale_y, float scale_z);
        void set_scale_x(float scale_x);
        void set_scale_y(float scale_y);
        void set_scale_z(float scale_z);

        void set_rotate(const glm::vec3 rotate);
        void set_rotate(float rotate_x, float rotate_y, float rotate_z);
        void set_rotate_x(float rotate_x);
        void set_rotate_y(float rotate_y);
        void set_rotate_z(float rotate_z);

        void move_scene_entity(const glm::vec3 delta);
        void move_scene_entity(float delta_move_x, float delta_move_y, float delta_move_z);
        void move_scene_entity_x(float delta_move_x);
        void move_scene_entity_y(float delta_move_y);
        void move_scene_entity_z(float delta_move_z);

        void scale_scene_entity(const glm::vec3 scale);
        void scale_scene_entity(float scale_x, float scale_y, float scale_z);
        void scale_scene_entity_x(float scale_x);
        void scale_scene_entity_y(float scale_y);
        void scale_scene_entity_z(float scale_z);

        void rotate_scene_entity(const glm::vec3 delta_rotate);
        void rotate_scene_entity(float delta_angle_x, float delta_angle_y, float delta_angle_z);
        void rotate_scene_entity_x(float delta_angle_x);
        void rotate_scene_entity_y(float delta_angle_y);
        void rotate_scene_entity_z(float delta_angle_z);

        glm::vec3 get_translate() const { return this->translate; }
        glm::vec3 get_scale() const { return this->scale; }
        glm::vec3 get_rotate() const { return this->rotate; }

    private:
        static inline int number_of_scene_entities = 0;

        std::string name;

        std::shared_ptr<std::vector<std::shared_ptr<Model3D>>> models;
        std::shared_ptr<std::vector<std::shared_ptr<SolidCube>>> solid_cubes;
        std::shared_ptr<std::vector<std::shared_ptr<LightSource>>> light_sources;  

        glm::vec3 translate = { 0, 0, 0 };
        glm::vec3 scale = { 1, 1, 1 };
        glm::vec3 rotate = { 0, 0, 0 };

        bool is_visible = true;
        bool is_solid = true;   // Отвечает за физические взаимодействия

    };

}