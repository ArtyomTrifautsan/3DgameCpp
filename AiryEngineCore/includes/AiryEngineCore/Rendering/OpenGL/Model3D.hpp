#pragma once

#include <glm/vec3.hpp>

#include <string>
#include <vector>
#include <memory>


namespace AiryEngine {

    struct Material;
    class Mesh;

    class Model3D
    {
    public:
        Model3D(std::vector<std::shared_ptr<Mesh>> meshes = {});

        void add_mesh(std::shared_ptr<Mesh> mesh);
        void add_meshes(std::vector<std::shared_ptr<Mesh>> meshes);

        std::vector<std::shared_ptr<Mesh>> get_meshes() const {return this->meshes; }

        void set_material(std::shared_ptr<Material> material);
        void set_diffuse_color(float r, float g, float b);

        void set_translate(glm::vec3& translate);
        void set_translate(float translate_x, float translate_y, float translate_z);
        void set_translate_x(float translate_x);
        void set_translate_y(float translate_y);
        void set_translate_z(float translate_z);

        void set_scale(glm::vec3& scale);
        void set_scale(float scale_x, float scale_y, float scale_z);
        void set_scale_x(float scale_x);
        void set_scale_y(float scale_y);
        void set_scale_z(float scale_z);

        void set_rotate(glm::vec3& rotate);
        void set_rotate(float rotate_x, float rotate_y, float rotate_z);
        void set_rotate_x(float rotate_x);
        void set_rotate_y(float rotate_y);
        void set_rotate_z(float rotate_z);

        void move_model(glm::vec3& delta);
        void move_model(float delta_move_x, float delta_move_y, float delta_move_z);
        void move_model_x(float delta_move_x);
        void move_model_y(float delta_move_y);
        void move_model_z(float delta_move_z);

        void scale_model(glm::vec3& scale);
        void scale_model(float scale_x, float scale_y, float scale_z);
        void scale_model_x(float scale_x);
        void scale_model_y(float scale_y);
        void scale_model_z(float scale_z);

        void rotate_model(glm::vec3& delta_rotate);
        void rotate_model(float delta_angle_x, float delta_angle_y, float delta_angle_z);
        void rotate_model_x(float delta_angle_x);
        void rotate_model_y(float delta_angle_y);
        void rotate_model_z(float delta_angle_z);

        glm::vec3 get_translate() const { return this->translate; }
        glm::vec3 get_scale() const { return this->scale; }
        glm::vec3 get_rotate() const { return this->rotate; }

    private:
        std::vector<std::shared_ptr<Mesh>> meshes;

        glm::vec3 translate = { 0, 0, 0 };
        glm::vec3 scale = { 1, 1, 1 };
        glm::vec3 rotate = { 0, 0, 0 };
    };
    
}
