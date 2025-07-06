/*

Этот класс может быть статическим

Здесь не хватает объекта LightSource - класс, который будет отвечать за источник освещения.

*/


#pragma once

#include <memory>


namespace AiryEngine {

    class Scene;
    class SceneEntity;
    class Camera;
    class ShaderProgram;
    class Model3D;
    class Mesh;
    class SolidCube;
    class ResourceManager;

    class SceneRenderer
    {
    public:
        SceneRenderer(std::shared_ptr<ResourceManager> resource_manager);

        void render_scene(std::shared_ptr<Camera> camera, std::shared_ptr<Scene> scene);
        void render_scene_entity(std::shared_ptr<Camera> camera, std::shared_ptr<SceneEntity> scene_entity);

        void render_model3D(std::shared_ptr<Camera> camera, std::shared_ptr<Model3D> model);
        void render_solid_cube(std::shared_ptr<Camera> camera, std::shared_ptr<SolidCube> solid_cube);
        void use_light_source();

        void set_ambient_factor(float ambient_factor);
        void set_diffuse_factor(float diffuse_factor);
        void set_specular_factor(float specular_factor);

    private:
        void render_mesh(std::shared_ptr<Camera> camera, std::shared_ptr<Mesh> mesh);
        void render_collision_mesh(std::shared_ptr<Camera> camera, std::shared_ptr<Mesh> collision_mesh);

        void init_temp_data();
        void choose_temp_shader_programm(std::shared_ptr<Mesh> mesh);
        void send_factors_to_shaders();
        void send_light_source_data_to_shaders();
        void send_mesh_data_to_shaders(std::shared_ptr<Material> mesh_material);
        void send_camera_data_to_shaders(std::shared_ptr<Camera> camera);
        void make_model_matrix(std::shared_ptr<Mesh> mesh);

        std::shared_ptr<ShaderProgram> default_shader_program;
        std::shared_ptr<ShaderProgram> collision_shader_program;
        std::shared_ptr<ShaderProgram> model3D_material_shader_program;
        std::shared_ptr<ShaderProgram> model3D_texture_shader_program;

        float ambient_factor = 0.1f;
        float diffuse_factor = 1.0f;
        float specular_factor = 0.5f;
        glm::vec3 light_source_position = { 0.f, 3.f, 0.f };
        glm::vec3 light_source_color = { 1.f, 1.f, 1.f };

        std::shared_ptr<Model3D> solid_cube_model;


        // Это вспомогательные переменные, которые я завел здесь чтобы не
        // аллоцировать память на каждом цикле. Вместо этого я один раз 
        // создаю эти переменные и постоянно перезаписываю их
        std::shared_ptr<Material> temp_mesh_material;
        std::shared_ptr<ShaderProgram> temp_shader_program;

        glm::vec3 temp_mesh_translate;
        glm::vec3 temp_mesh_scale;
        glm::vec3 temp_mesh_rotate;

        glm::mat4 temp_translate_matrix;
        glm::mat4 temp_scale_matrix;

        float temp_rotate_x_in_radians;
        float temp_rotate_y_in_radians;
        float temp_rotate_z_in_radians;
        float temp_cos;
        float temp_sin;
        glm::mat4 temp_rotate_x_matrix;
        glm::mat4 temp_rotate_y_matrix;
        glm::mat4 temp_rotate_z_matrix;
        glm::mat4 temp_rotate_matrix;

        glm::mat4 model_matrix;
    };

}