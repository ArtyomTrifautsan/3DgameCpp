#pragma once

#include <glm/trigonometric.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "AiryEngineCore/Rendering/OpenGL/Model3D.hpp"

#include <memory>

namespace AiryEngine
{

    class ShaderProgram;
    class ResourceManager;
    class Model3D;
    class Mesh;

    class Renderer
    {
    public:
        // Renderer(std::shared_ptr<class ResourceManager> resource_manager);
        Renderer() = default;
        // ~Renderer();

        void use_shader(std::shared_ptr<ShaderProgram> _shader);
        void send_uniform_data_to_shader(class Camera& camera, std::shared_ptr<Mesh> mesh);
        void send_model_matrix_to_shader(std::shared_ptr<Mesh> mesh);

        void render_model3D(class Camera& camera, std::shared_ptr<Model3D> model);
        void render_collision_model(class Camera& camera, std::shared_ptr<Model3D> model);
        void render_light_model(class Camera& camera, std::shared_ptr<Model3D> model);

        void render_cube_mesh(class Camera& camera, std::shared_ptr<CubeMesh> mesh);
        void render_cube_mesh_2(class Camera& camera, std::shared_ptr<CubeMesh> mesh, float uMorphFactor);
        void render_cube_mesh_3(class Camera& camera, std::shared_ptr<CubeMesh> mesh);
        void send_cube_mesh_model_matrix_to_shader(std::shared_ptr<CubeMesh> mesh);
        void send_cube_mesh_model_matrix_to_shader_3(std::shared_ptr<CubeMesh> mesh);

        glm::vec3 get_light_source_position() { return light_source_position; }
        glm::vec3 get_light_source_color() { return light_source_color; }

        void set_light_source_position(glm::vec3 _light_source_position) { light_source_position = _light_source_position; }
        void set_light_source_color(glm::vec3 _light_source_color) { light_source_color = _light_source_color; }

        void set_ambient_factor(float factor); 
        void set_diffuse_factor(float factor);  
        void set_specular_factor(float factor); 

    private:
        std::shared_ptr<ShaderProgram> m_shader;

        std::shared_ptr<ShaderProgram> default_shader_program;
        std::shared_ptr<ShaderProgram> light_source_shader_program;
        std::shared_ptr<ShaderProgram> collision_shader_program;
        std::shared_ptr<ShaderProgram> model3D_material_shader_program;
        std::shared_ptr<ShaderProgram> model3D_texture_shader_program;

        glm::vec3 light_source_position = { 0.f, 3.f, 0.f };
        glm::vec3 light_source_color = { 1.f, 1.f, 1.f };

        float ambient_factor = 0.1f;
        float diffuse_factor = 1.0f;
        float specular_factor = 0.5f;

        // Эти данные вынесены сюда, чтобы не аллоцировать их при рендеринге каждого меша

        // Scale
        float m_scale[3] = {0};
        float m_rotate[3] = {0};
        float m_translate[3] = {0};
        glm::mat4 m_scale_matrix{
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
        /*
        glm::mat4 scale_matrix(
            scale[0], 0,        0,        0,
            0,        scale[1], 0,        0,
            0,        0,        scale[2], 0,
            0,        0,        0,        1
        );
        */

        // Rotate
        float m_rotate_x_in_radians = 0;
        float m_rotate_y_in_radians = 0;
        float m_rotate_z_in_radians = 0;
        glm::mat4 m_rotate_x_matrix{
            1,  0, 0, 0,
            0,  1, 1, 0,
            0, -1, 1, 0,
            0,  0, 0, 1
        };
        glm::mat4 m_rotate_y_matrix{
            1, 0, -1, 0,
            0, 1,  0, 0,
            1, 0,  1, 0,
            0, 0,  0, 1
        };
        glm::mat4 m_rotate_z_matrix{
             1, 1, 0, 0,
            -1, 1, 0, 0,
             0, 0, 1, 0,
             0, 0, 0, 1
        };
        glm::mat4 m_rotate_matrix{};

        // Translate
        glm::mat4 m_translate_matrix{
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,  
            1, 1, 1, 1
        };

        // Model
        glm::mat4 m_model_matrix{};

        /*
        float rotate_x_in_radians = glm::radians(rotate[0]);
        glm::mat4 rotate_x_matrix(
             1,  0,                        0,                        0,
             0,  cos(rotate_x_in_radians), sin(rotate_x_in_radians), 0,
             0, -sin(rotate_x_in_radians), cos(rotate_x_in_radians), 0,
             0,  0,                        0,                        1
        );

        float rotate_y_in_radians = glm::radians(rotate[1]);
        glm::mat4 rotate_y_matrix(
             cos(rotate_y_in_radians), 0, -sin(rotate_y_in_radians), 0,
             0,                        1,  0,                        0,
             sin(rotate_y_in_radians), 0,  cos(rotate_y_in_radians), 0,
             0,                        0,  0,                        1
        );

        float rotate_z_in_radians = glm::radians(rotate[2]);
        glm::mat4 rotate_z_matrix(
             cos(rotate_z_in_radians), sin(rotate_z_in_radians), 0, 0,
            -sin(rotate_z_in_radians), cos(rotate_z_in_radians), 0, 0,
             0,                      0,                      1, 0,
             0,                      0,                      0, 1
        );

        glm::mat4 rotate_matrix = rotate_z_matrix * rotate_y_matrix * rotate_x_matrix;

        glm::mat4 translate_matrix(
            1,            0,            0,            0,
            0,            1,            0,            0,
            0,            0,            1,            0,  
            translate[0], translate[1], translate[2], 1
        );

        glm::mat4 model_matrix = translate_matrix * rotate_matrix * scale_matrix;
        */
        

        void render_mesh(class Camera& camera, std::shared_ptr<Mesh> mesh);
        void render_collision_mesh(class Camera& camera, std::shared_ptr<Mesh> mesh);
        void render_light_mesh(class Camera& camera, std::shared_ptr<Mesh> mesh);
    };

}
