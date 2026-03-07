#include "AiryEngineCore/Renderer.hpp"

// #include <glm/trigonometric.hpp>

#include "AiryEngineCore/Log.hpp"
#include "AiryEngineCore/Camera.hpp"

#include "AiryEngineCore/ResourceManager.hpp"
#include "AiryEngineCore/Rendering/OpenGL/Model3D.hpp"
#include "AiryEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "AiryEngineCore/Rendering/OpenGL/Renderer_OpenGL.hpp"
#include "AiryEngineCore/Rendering/OpenGL/Mesh.hpp"
#include "AiryEngineCore/Rendering/OpenGL/VertexArray.hpp"
#include "AiryEngineCore/Rendering/OpenGL/Texture2D.hpp"

#include <iostream>

namespace AiryEngine {

    // Renderer::Renderer(std::shared_ptr<ResourceManager> resource_manager)
    // {
    //     // LOG_INFO("Start shaders");
    //     // this->default_shader_program = resource_manager->load_shaders("default_shaders", "default_vertex_shader.txt", "default_fragment_shader.txt");
    //     // if (!this->default_shader_program->is_compiled()) 
    //     // {
    //     //     LOG_CRITICAL("Failed to compile Default Shader Program");
    //     // }

    //     // this->light_source_shader_program = resource_manager->load_shaders("light_source_shaders", "light_source_vertex_shader.txt", "light_source_fragment_shader.txt");
    //     // if (!this->light_source_shader_program->is_compiled()) 
    //     // {
    //     //     LOG_CRITICAL("Failed to compile Light Shader Program");
    //     // }

    //     // this->collision_shader_program = resource_manager->load_shaders("collision_shaders", "collision_vertex_shader.txt", "collision_fragment_shader.txt");
    //     // if (!this->light_source_shader_program->is_compiled()) 
    //     // {
    //     //     LOG_CRITICAL("Failed to compile Light Shader Program");
    //     // }

    //     // this->model3D_material_shader_program = resource_manager->load_shaders("model3D_material_shaders", "vertex_model3D_material.txt", "fragment_model3D_material.txt");
    //     // if (!this->light_source_shader_program->is_compiled()) 
    //     // {
    //     //     LOG_CRITICAL("Failed to compile model3D_material Shader Program");
    //     // }

    //     // this->model3D_texture_shader_program = resource_manager->load_shaders("model3D_texture_shaders", "vertex_model3D_texture.txt", "fragment_model3D_texture.txt");
    //     // if (!this->light_source_shader_program->is_compiled()) 
    //     // {
    //     //     LOG_CRITICAL("Failed to compile model3D_texture Shader Program");
    //     // }

    //     // LOG_INFO("Finish shaders");
    // }

    void Renderer::use_shader(std::shared_ptr<ShaderProgram> _shader)
    {
        // LOG_INFO("Хотим прикрепить шейдер");
        m_shader = _shader;
        // LOG_INFO("Прикрепили");
    }

    void Renderer::render_model3D(class Camera& camera, std::shared_ptr<Model3D> model)
    {
        std::vector<std::shared_ptr<Mesh>> model_meshes = model->get_meshes();
        for (std::shared_ptr<Mesh> current_mesh : model_meshes) 
        {
            render_mesh(camera, current_mesh);
        }
    }

    /*
    void Renderer::render_mesh(class Camera& camera, std::shared_ptr<Mesh> mesh)
    {
        std::shared_ptr<Material> mesh_material = mesh->get_material();
        std::shared_ptr<ShaderProgram> current_shader;

        if (mesh_material->has_duffuse_map)
        {
            std::shared_ptr<Texture2D> mesh_texture = mesh->get_texture();
            
            // this->model3D_texture_shader_program->bind();
            current_shader = this->model3D_texture_shader_program;
            current_shader->bind();
            mesh_texture->bind(0);
            // current_shader = this->model3D_material_shader_program;

            // std::cout << "Texture binded" << std::endl;
        }
        else
        {
            // std::cout << "NO Texture" << std::endl;
            // this->model3D_material_shader_program->bind();
            current_shader = this->model3D_material_shader_program;
            current_shader->bind();
        }

        // this->default_shader_program->bind();
        // current_shader->bind();

        mesh->get_vertex_array()->bind();

        // this->default_shader_program->set_matrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());
        // this->default_shader_program->set_vec3("camera_position", camera.get_camera_position());
        // this->default_shader_program->set_vec3("light_position", this->light_source_position);
        // this->default_shader_program->set_vec3("light_color", this->light_source_color);
        // this->default_shader_program->set_vec3("ambient_color", mesh_material->ambient_color);
        // this->default_shader_program->set_float("ambient_factor",  this->ambient_factor);
        // this->default_shader_program->set_vec3("diffuse_color", mesh_material->diffuse_color);
        // this->default_shader_program->set_float("diffuse_factor",  this->diffuse_factor);
        // this->default_shader_program->set_vec3("specular_color", mesh_material->specular_color);
        // this->default_shader_program->set_float("specular_factor",  this->specular_factor);
        // this->default_shader_program->set_float("shininess",  mesh_material->shininess);
        // this->default_shader_program->set_float("alpha_channel",  mesh_material->alpha_channel);
        current_shader->set_matrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());
        current_shader->set_vec3("camera_position", camera.get_camera_position());
        current_shader->set_vec3("light_position", this->light_source_position);
        current_shader->set_vec3("light_color", this->light_source_color);
        current_shader->set_vec3("ambient_color", mesh_material->ambient_color);
        current_shader->set_float("ambient_factor",  this->ambient_factor);
        current_shader->set_vec3("diffuse_color", mesh_material->diffuse_color);
        current_shader->set_float("diffuse_factor",  this->diffuse_factor);
        current_shader->set_vec3("specular_color", mesh_material->specular_color);
        current_shader->set_float("specular_factor",  this->specular_factor);
        current_shader->set_float("shininess",  mesh_material->shininess);
        current_shader->set_float("alpha_channel",  mesh_material->alpha_channel);

        float scale[3] = {0};
        float rotate[3] = {0};
        float translate[3] = {0};
        mesh->get_scale(scale);
        mesh->get_rotate(rotate);
        mesh->get_translate(translate);

        glm::mat4 scale_matrix(
            scale[0], 0,        0,        0,
            0,        scale[1], 0,        0,
            0,        0,        scale[2], 0,
            0,        0,        0,        1
        );

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


        // this->default_shader_program->set_matrix4("model_matrix", model_matrix);
        current_shader->set_matrix4("model_matrix", model_matrix);

        Renderer_OpenGL::draw_vertex_elements(*mesh->get_vertex_array());
        
        mesh->get_vertex_array()->unbind();
    }   
    */

    // void Renderer::send_uniform_data_to_shader(class Camera& camera, std::shared_ptr<Mesh> mesh)
    // {
    //     std::shared_ptr<Material> mesh_material = mesh->get_material();

    //     m_shader->set_matrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());
    //     m_shader->set_vec3("camera_position", camera.get_camera_position());
    //     m_shader->set_vec3("light_position", this->light_source_position);
    //     m_shader->set_vec3("light_color", this->light_source_color);
    //     m_shader->set_vec3("ambient_color", mesh_material->ambient_color);
    //     m_shader->set_float("ambient_factor",  this->ambient_factor);
    //     m_shader->set_vec3("diffuse_color", mesh_material->diffuse_color);
    //     m_shader->set_float("diffuse_factor",  this->diffuse_factor);
    //     m_shader->set_vec3("specular_color", mesh_material->specular_color);
    //     m_shader->set_float("specular_factor",  this->specular_factor);
    //     m_shader->set_float("shininess",  mesh_material->shininess);
    //     m_shader->set_float("alpha_channel",  mesh_material->alpha_channel);
    // }

    // void Renderer::send_model_matrix_to_shader(std::shared_ptr<Mesh> mesh)
    // {
    //     // float scale[3] = {0};
    //     // float rotate[3] = {0};
    //     // float translate[3] = {0};
    //     mesh->get_scale(m_scale);
    //     mesh->get_rotate(m_rotate);
    //     mesh->get_translate(m_translate);

    //     // glm::mat4 scale_matrix(
    //     //     scale[0], 0,        0,        0,
    //     //     0,        scale[1], 0,        0,
    //     //     0,        0,        scale[2], 0,
    //     //     0,        0,        0,        1
    //     // );
    //     m_scale_matrix[0][0] = m_scale[0];
    //     m_scale_matrix[1][1] = m_scale[1];
    //     m_scale_matrix[2][2] = m_scale[2];

    //     m_rotate_x_in_radians = glm::radians(m_rotate[0]);
    //     // glm::mat4 rotate_x_matrix(
    //     //      1,  0,                        0,                        0,
    //     //      0,  cos(rotate_x_in_radians), sin(rotate_x_in_radians), 0,
    //     //      0, -sin(rotate_x_in_radians), cos(rotate_x_in_radians), 0,
    //     //      0,  0,                        0,                        1
    //     // );
    //     m_rotate_x_matrix[1][1] = cos(m_rotate_x_in_radians);
    //     m_rotate_x_matrix[2][1] = sin(m_rotate_x_in_radians);
    //     m_rotate_x_matrix[1][2] = -sin(m_rotate_x_in_radians);
    //     m_rotate_x_matrix[2][2] = cos(m_rotate_x_in_radians);

    //     m_rotate_y_in_radians = glm::radians(m_rotate[1]);
    //     // glm::mat4 rotate_y_matrix(
    //     //      cos(rotate_y_in_radians), 0, -sin(rotate_y_in_radians), 0,
    //     //      0,                        1,  0,                        0,
    //     //      sin(rotate_y_in_radians), 0,  cos(rotate_y_in_radians), 0,
    //     //      0,                        0,  0,                        1
    //     // );
    //     m_rotate_y_matrix[0][0] = cos(m_rotate_y_in_radians);
    //     m_rotate_y_matrix[2][0] = -sin(m_rotate_y_in_radians);
    //     m_rotate_y_matrix[0][2] = sin(m_rotate_y_in_radians);
    //     m_rotate_y_matrix[2][2] = cos(m_rotate_y_in_radians);

    //     m_rotate_z_in_radians = glm::radians(m_rotate[2]);
    //     // glm::mat4 rotate_z_matrix(
    //     //      cos(rotate_z_in_radians), sin(rotate_z_in_radians), 0, 0,
    //     //     -sin(rotate_z_in_radians), cos(rotate_z_in_radians), 0, 0,
    //     //      0,                      0,                      1, 0,
    //     //      0,                      0,                      0, 1
    //     // );
    //     m_rotate_z_matrix[0][0] = cos(m_rotate_z_in_radians);
    //     m_rotate_z_matrix[1][0] = sin(m_rotate_z_in_radians);
    //     m_rotate_z_matrix[0][1] = -sin(m_rotate_z_in_radians);
    //     m_rotate_z_matrix[1][1] = cos(m_rotate_z_in_radians);

    //     m_rotate_matrix = m_rotate_z_matrix * m_rotate_y_matrix * m_rotate_x_matrix;

    //     // glm::mat4 translate_matrix(
    //     //     1,            0,            0,            0,
    //     //     0,            1,            0,            0,
    //     //     0,            0,            1,            0,  
    //     //     translate[0], translate[1], translate[2], 1
    //     // );
    //     m_translate_matrix[0][3] = m_translate[0];
    //     m_translate_matrix[1][3] = m_translate[1];
    //     m_translate_matrix[2][3] = m_translate[2];

    //     m_model_matrix = m_translate_matrix * m_rotate_matrix * m_scale_matrix;

    //     // this->default_shader_program->set_matrix4("model_matrix", model_matrix);
    //     m_shader->set_matrix4("model_matrix", m_model_matrix);
    // }
    

    void Renderer::send_uniform_data_to_shader(class Camera& camera, std::shared_ptr<Mesh> mesh)
    {
        std::shared_ptr<Material> mesh_material = mesh->get_material();

        // m_shader->set_matrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());
        m_shader->set_matrix4("view_projection_matrix", camera.get_view_projection_matrix());
        m_shader->set_vec3("color", mesh_material->diffuse_color);
    }


    void Renderer::send_model_matrix_to_shader(std::shared_ptr<Mesh> mesh)
    {
        mesh->get_scale(m_scale);
        mesh->get_rotate(m_rotate);
        mesh->get_translate(m_translate);

        m_scale_matrix[0][0] = m_scale[0];
        m_scale_matrix[1][1] = m_scale[1];
        m_scale_matrix[2][2] = m_scale[2];

        m_rotate_x_in_radians = glm::radians(m_rotate[0]);
        m_rotate_x_matrix[1][1] = cos(m_rotate_x_in_radians);
        m_rotate_x_matrix[2][1] = sin(m_rotate_x_in_radians);
        m_rotate_x_matrix[1][2] = -sin(m_rotate_x_in_radians);
        m_rotate_x_matrix[2][2] = cos(m_rotate_x_in_radians);

        m_rotate_y_in_radians = glm::radians(m_rotate[1]);
        m_rotate_y_matrix[0][0] = cos(m_rotate_y_in_radians);
        m_rotate_y_matrix[2][0] = -sin(m_rotate_y_in_radians);
        m_rotate_y_matrix[0][2] = sin(m_rotate_y_in_radians);
        m_rotate_y_matrix[2][2] = cos(m_rotate_y_in_radians);

        m_rotate_z_in_radians = glm::radians(m_rotate[2]);
        m_rotate_z_matrix[0][0] = cos(m_rotate_z_in_radians);
        m_rotate_z_matrix[1][0] = sin(m_rotate_z_in_radians);
        m_rotate_z_matrix[0][1] = -sin(m_rotate_z_in_radians);
        m_rotate_z_matrix[1][1] = cos(m_rotate_z_in_radians);

        m_rotate_matrix = m_rotate_z_matrix * m_rotate_y_matrix * m_rotate_x_matrix;

        m_translate_matrix[0][3] = m_translate[0];
        m_translate_matrix[1][3] = m_translate[1];
        m_translate_matrix[2][3] = m_translate[2];

        m_model_matrix = m_translate_matrix * m_rotate_matrix * m_scale_matrix;

        m_shader->set_matrix4("model_matrix", m_model_matrix);
    }

    void Renderer::render_mesh(class Camera& camera, std::shared_ptr<Mesh> mesh)
    {
        m_shader->bind();
        mesh->get_vertex_array()->bind();

        send_uniform_data_to_shader(camera, mesh);
        send_model_matrix_to_shader(mesh);
        Renderer_OpenGL::draw_vertex_elements(*mesh->get_vertex_array());
        
        mesh->get_vertex_array()->unbind();
        m_shader->unbind();
    }

    void Renderer::render_collision_model(class Camera& camera, std::shared_ptr<Model3D> model)
    {
        Renderer_OpenGL::enable_alpha_channel();

        std::vector<std::shared_ptr<Mesh>> model_meshes = model->get_meshes();
        for (std::shared_ptr<Mesh> current_mesh : model_meshes) 
            render_collision_mesh(camera, current_mesh);

        Renderer_OpenGL::disable_alpha_channel();
    }

    void Renderer::render_collision_mesh(class Camera& camera, std::shared_ptr<Mesh> mesh)
    {
        std::shared_ptr<Material> mesh_material = mesh->get_material();

        // mesh->get_texture()->bind(0);
        this->collision_shader_program->bind();
        mesh->get_vertex_array()->bind();

        // this->collision_shader_program->set_matrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());
        this->collision_shader_program->set_matrix4("view_projection_matrix", camera.get_view_projection_matrix());
        this->collision_shader_program->set_vec3("camera_position", camera.get_camera_position());
        this->collision_shader_program->set_vec3("ambient_color", mesh_material->ambient_color);
        this->collision_shader_program->set_float("ambient_factor",  this->ambient_factor);
        this->collision_shader_program->set_vec3("diffuse_color", mesh_material->diffuse_color);
        this->collision_shader_program->set_float("diffuse_factor",  this->diffuse_factor);
        this->collision_shader_program->set_vec3("specular_color", mesh_material->specular_color);
        this->collision_shader_program->set_float("specular_factor",  this->specular_factor);
        this->collision_shader_program->set_float("shininess",  mesh_material->shininess);
        this->collision_shader_program->set_float("alpha_channel",  mesh_material->alpha_channel);

        float scale[3] = {0};
        float rotate[3] = {0};
        float translate[3] = {0};
        mesh->get_scale(scale);
        mesh->get_rotate(rotate);
        mesh->get_translate(translate);

        glm::mat4 scale_matrix(
            scale[0], 0,        0,        0,
            0,        scale[1], 0,        0,
            0,        0,        scale[2], 0,
            0,        0,        0,        1
        );

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
        this->collision_shader_program->set_matrix4("model_matrix", model_matrix);

        Renderer_OpenGL::draw_vertex_elements(*mesh->get_vertex_array());
        
        mesh->get_vertex_array()->unbind();
    }


    void Renderer::render_light_model(class Camera& camera, std::shared_ptr<Model3D> model)
    {
        std::vector<std::shared_ptr<Mesh>> model_meshes = model->get_meshes();
        for (std::shared_ptr<Mesh> current_mesh : model_meshes) 
            render_light_mesh(camera, current_mesh);
    }


    void Renderer::render_light_mesh(class Camera& camera, std::shared_ptr<Mesh> mesh)
    {
        light_source_shader_program->bind();
        mesh->get_vertex_array()->bind();

        // light_source_shader_program->set_matrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());
        light_source_shader_program->set_matrix4("view_projection_matrix", camera.get_view_projection_matrix());
        light_source_shader_program->set_vec3("light_color", light_source_color);

        float scale[3];
        float rotate[3];
        float translate[3];
        mesh->get_scale(scale);
        mesh->get_rotate(rotate);
        mesh->get_translate(translate);

        glm::mat4 scale_matrix(
            scale[0], 0,        0,        0,
            0,        scale[1], 0,        0,
            0,        0,        scale[2], 0,
            0,        0,        0,        1
        );
            
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
        light_source_shader_program->set_matrix4("model_matrix", model_matrix);

        Renderer_OpenGL::draw_vertex_elements(*mesh->get_vertex_array());
        
        mesh->get_vertex_array()->unbind();
    }

    void Renderer::render_cube_mesh(class Camera& camera, std::shared_ptr<CubeMesh> mesh)
    {
        m_shader->bind();
        mesh->get_vertex_array()->bind();

        std::shared_ptr<Material> mesh_material = mesh->get_material();

        m_shader->set_matrix4("view_projection_matrix", camera.get_view_projection_matrix());
        m_shader->set_vec3("color", mesh_material->diffuse_color);

        send_cube_mesh_model_matrix_to_shader(mesh);
        Renderer_OpenGL::draw_vertex_elements(*mesh->get_vertex_array());

        mesh->get_vertex_array()->unbind();
        m_shader->unbind();
    }

    void Renderer::send_cube_mesh_model_matrix_to_shader(std::shared_ptr<CubeMesh> mesh)
    {
        // Получаем параметры трансформации
        float scale_arr[3], translate_arr[3];
        mesh->get_scale(scale_arr);
        mesh->get_translate(translate_arr);
        glm::quat rotation = mesh->get_rotation();

        // Формируем матрицу в порядке: Scale → Rotate → Translate
        glm::mat4 model_matrix = glm::mat4(1.0f);
        model_matrix = glm::translate(model_matrix, 
            glm::vec3(translate_arr[0], translate_arr[1], translate_arr[2]));
        model_matrix = model_matrix * glm::mat4_cast(rotation); // quat → mat4
        model_matrix = glm::scale(model_matrix, 
            glm::vec3(scale_arr[0], scale_arr[1], scale_arr[2]));

        m_shader->set_matrix4("model_matrix", model_matrix);
    }

    void Renderer::render_cube_mesh_2(class Camera& camera, std::shared_ptr<CubeMesh> mesh, float uMorphFactor)
    {
        m_shader->bind();
        mesh->get_vertex_array()->bind();

        std::shared_ptr<Material> mesh_material = mesh->get_material();

        m_shader->set_matrix4("view_projection_matrix", camera.get_view_projection_matrix());
        m_shader->set_vec3("color", mesh_material->diffuse_color);
        m_shader->set_float("uMorphFactor", uMorphFactor);

        send_cube_mesh_model_matrix_to_shader(mesh);
        // Renderer_OpenGL::draw_vertex_elements_lines(*mesh->get_vertex_array());
        Renderer_OpenGL::draw_vertex_elements(*mesh->get_vertex_array());

        mesh->get_vertex_array()->unbind();
        m_shader->unbind();
    }

    void Renderer::set_ambient_factor(float factor)
    {
        this->ambient_factor = factor;
    }

    void Renderer::set_diffuse_factor(float factor)
    {
        this->diffuse_factor = factor;
    }

    void Renderer::set_specular_factor(float factor)
    {
        this->specular_factor = factor;
    }

}