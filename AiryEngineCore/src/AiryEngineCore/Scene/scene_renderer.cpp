#include "scene_renderer.hpp"

#include <glm/trigonometric.hpp>

#include <AiryEngineCore/Camera.hpp>
#include <AiryEngineCore/Log.hpp>
#include <AiryEngineCore/ResourceManager.hpp>

#include <AiryEngineCore/Rendering/OpenGL/ShaderProgram.hpp>
#include <AiryEngineCore/Rendering/OpenGL/Model3D.hpp>
#include <AiryEngineCore/Rendering/OpenGL/Mesh.hpp>
#include "AiryEngineCore/Rendering/OpenGL/Renderer_OpenGL.hpp"
#include "AiryEngineCore/Rendering/OpenGL/VertexArray.hpp"
#include "AiryEngineCore/Rendering/OpenGL/Texture2D.hpp"
// #include <AiryEngineCore/Rendering/OpenGL/LightSource.hpp>

#include <AiryEngineCore/Scene/scene.hpp>
#include <AiryEngineCore/Scene/scene_entity.hpp>

#include <AiryEngineCore/Physics/SolidObjects/CubeSolid.hpp>


namespace AiryEngine {

    SceneRenderer::SceneRenderer(std::shared_ptr<ResourceManager> resource_manager)
    {
        // LOG_INFO("Start shaders");

        this->default_shader_program = resource_manager->load_shaders("default_shaders", "default_vertex_shader.txt", "default_fragment_shader.txt");
        if (!this->default_shader_program->is_compiled()) 
        {
            LOG_CRITICAL("Failed to compile Default Shader Program");
        }

        // this->light_source_shader_program = resource_manager->load_shaders("light_source_shaders", "light_source_vertex_shader.txt", "light_source_fragment_shader.txt");
        // if (!this->light_source_shader_program->is_compiled()) 
        // {
        //     LOG_CRITICAL("Failed to compile Light Shader Program");
        // }

        this->collision_shader_program = resource_manager->load_shaders("collision_shaders", "collision_vertex_shader.txt", "collision_fragment_shader.txt");
        if (!this->collision_shader_program->is_compiled()) 
        {
            LOG_CRITICAL("Failed to compile Light Shader Program");
        }

        this->model3D_material_shader_program = resource_manager->load_shaders("model3D_material_shaders", "vertex_model3D_material.txt", "fragment_model3D_material.txt");
        if (!this->model3D_material_shader_program->is_compiled()) 
        {
            LOG_CRITICAL("Failed to compile model3D_material Shader Program");
        }

        this->model3D_texture_shader_program = resource_manager->load_shaders("model3D_texture_shaders", "vertex_model3D_texture.txt", "fragment_model3D_texture.txt");
        if (!this->model3D_texture_shader_program->is_compiled()) 
        {
            LOG_CRITICAL("Failed to compile model3D_texture Shader Program");
        }


        // БЛЯТЬ ТОЛЬКО НЕ ЗАБУДЬ ЗАГРУЗИТЬ ЭТУ МОДЕЛЬКУ
        // БЛЯТЬ ТОЛЬКО НЕ ЗАБУДЬ ЗАГРУЗИТЬ ЭТУ МОДЕЛЬКУ
        // БЛЯТЬ ТОЛЬКО НЕ ЗАБУДЬ ЗАГРУЗИТЬ ЭТУ МОДЕЛЬКУ
        // БЛЯТЬ ТОЛЬКО НЕ ЗАБУДЬ ЗАГРУЗИТЬ ЭТУ МОДЕЛЬКУ
        // БЛЯТЬ ТОЛЬКО НЕ ЗАБУДЬ ЗАГРУЗИТЬ ЭТУ МОДЕЛЬКУ
        // БЛЯТЬ ТОЛЬКО НЕ ЗАБУДЬ ЗАГРУЗИТЬ ЭТУ МОДЕЛЬКУ
        this->solid_cube_model = resource_manager->get_model3D("solid_cube_model");

        init_temp_data();

        // LOG_INFO("Finish shaders");
    }


    void SceneRenderer::init_temp_data()
    {
        this->temp_mesh_translate = glm::vec3(0, 0, 0);
        this->temp_mesh_scale = glm::vec3(0, 0, 0);
        this->temp_mesh_rotate = glm::vec3(0, 0, 0);

        this->temp_translate_matrix = glm::mat4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,  
            0, 0, 0, 1
        );
        this->temp_scale_matrix = glm::mat4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,  
            0, 0, 0, 1
        );
        this->temp_rotate_x_matrix = glm::mat4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,  
            0, 0, 0, 1
        );
        this->temp_rotate_y_matrix = glm::mat4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,  
            0, 0, 0, 1
        );
        this->temp_rotate_z_matrix = glm::mat4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,  
            0, 0, 0, 1
        );
        this->temp_rotate_matrix = glm::mat4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,  
            0, 0, 0, 1
        );
        this->model_matrix = glm::mat4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,  
            0, 0, 0, 1
        );
    }


    void SceneRenderer::render_scene(std::shared_ptr<Camera> camera, std::shared_ptr<Scene> scene)
    {
        std::shared_ptr<std::vector<std::shared_ptr<SceneEntity>>> scene_entities = scene->get_scene_entities();
        for (std::shared_ptr<SceneEntity> current_scene_entity : *scene_entities)
        {
            render_scene_entity(camera, current_scene_entity);
        }
    }


    void SceneRenderer::render_scene_entity(std::shared_ptr<Camera> camera, std::shared_ptr<SceneEntity> scene_entity)
    {
        std::shared_ptr<std::vector<std::shared_ptr<Model3D>>> scene_entity_models = scene_entity->get_models();
        for (std::shared_ptr<Model3D> current_model : *scene_entity_models)
        {
            render_model3D(camera, current_model);
        }

        std::shared_ptr<std::vector<std::shared_ptr<SolidCube>>> scene_entity_solid_cubes = scene_entity->get_solid_cubes();
        for (std::shared_ptr<SolidCube> current_solid_cube : *scene_entity_solid_cubes)
        {
            render_solid_cube(camera, current_solid_cube);
        }
    }


    void SceneRenderer::render_model3D(std::shared_ptr<Camera> camera, std::shared_ptr<Model3D> model)
    {
        std::vector<std::shared_ptr<Mesh>> model_meshes = model->get_meshes();

        for (std::shared_ptr<Mesh> current_mesh : model_meshes) 
        {
            render_mesh(camera, current_mesh);
        }
    }


    void SceneRenderer::render_solid_cube(std::shared_ptr<Camera> camera, std::shared_ptr<SolidCube> solid_cube)
    {
        // Выставляем цвет куба
        if (solid_cube->get_is_collided()) this->solid_cube_model->set_diffuse_color(1.0f, 0.0f, 0.0f);
        else this->solid_cube_model->set_diffuse_color(0.0f, 1.0f, 0.0f);

        // Ставим модельку куба в нужное место и правильно скалируем
        this->solid_cube_model->set_translate(solid_cube->get_translate());
        this->solid_cube_model->set_scale(solid_cube->get_scale());

        // Рендерим
        std::vector<std::shared_ptr<Mesh>> solid_cube_model_meshes = this->solid_cube_model->get_meshes();
        for (std::shared_ptr<Mesh> current_mesh : solid_cube_model_meshes) 
        {
            render_collision_mesh(camera, current_mesh);
        }
    }


    void SceneRenderer::render_mesh(std::shared_ptr<Camera> camera, std::shared_ptr<Mesh> mesh)
    {
        this->temp_mesh_material = mesh->get_material();

        choose_temp_shader_programm(mesh);

        mesh->get_vertex_array()->bind();

        send_factors_to_shaders();
        send_light_source_data_to_shaders();
        send_mesh_data_to_shaders(this->temp_mesh_material);
        send_camera_data_to_shaders(camera);

        make_model_matrix(mesh);
        this->temp_shader_program->set_matrix4("model_matrix", this->model_matrix);

        Renderer_OpenGL::draw_vertex_elements(*mesh->get_vertex_array());

        mesh->get_vertex_array()->unbind();
    }


    void SceneRenderer::render_collision_mesh(std::shared_ptr<Camera> camera, std::shared_ptr<Mesh> collision_mesh)
    {
        this->temp_mesh_material = collision_mesh->get_material();

        this->collision_shader_program->bind();

        collision_mesh->get_vertex_array()->bind();

        send_factors_to_shaders();
        // send_light_source_data_to_shaders();
        send_mesh_data_to_shaders(this->temp_mesh_material);
        send_camera_data_to_shaders(camera);

        make_model_matrix(collision_mesh);
        this->collision_shader_program->set_matrix4("model_matrix", model_matrix);

        Renderer_OpenGL::draw_vertex_elements(*collision_mesh->get_vertex_array());
        
        collision_mesh->get_vertex_array()->unbind();
    }


    void SceneRenderer::choose_temp_shader_programm(std::shared_ptr<Mesh> mesh)
    {
        if (this->temp_mesh_material->has_duffuse_map)
        {
            std::shared_ptr<Texture2D> mesh_texture = mesh->get_texture();
            
            this->temp_shader_program = this->model3D_texture_shader_program;

            // Сначала биндим shader_program, а затем уже текстуру
            this->temp_shader_program->bind();
            mesh_texture->bind(0);
        }
        else
        {
            this->temp_shader_program = this->model3D_material_shader_program;
            this->temp_shader_program->bind();
        }
    }


    void SceneRenderer::send_factors_to_shaders()
    {
        this->temp_shader_program->set_float("ambient_factor",  this->ambient_factor);
        this->temp_shader_program->set_float("diffuse_factor",  this->diffuse_factor);
        this->temp_shader_program->set_float("specular_factor",  this->specular_factor);
    }


    void SceneRenderer::send_camera_data_to_shaders(std::shared_ptr<Camera> camera)
    {
        this->temp_shader_program->set_matrix4("view_projection_matrix", camera->get_projection_matrix() * camera->get_view_matrix());
        this->temp_shader_program->set_vec3("camera_position", camera->get_camera_position());
    }


    void SceneRenderer::send_light_source_data_to_shaders()
    {
        this->temp_shader_program->set_vec3("light_position", this->light_source_position);
        this->temp_shader_program->set_vec3("light_color", this->light_source_color);
    }


    void SceneRenderer::send_mesh_data_to_shaders(std::shared_ptr<Material> mesh_material)
    {
        this->temp_shader_program->set_vec3("ambient_color", mesh_material->ambient_color);
        this->temp_shader_program->set_vec3("diffuse_color", mesh_material->diffuse_color);
        this->temp_shader_program->set_vec3("specular_color", mesh_material->specular_color);
        this->temp_shader_program->set_float("shininess",  mesh_material->shininess);
        this->temp_shader_program->set_float("alpha_channel",  mesh_material->alpha_channel);
    }


    void SceneRenderer::make_model_matrix(std::shared_ptr<Mesh> mesh)
    {
        // Делаем translate матрицу
        this->temp_mesh_translate = mesh->get_translate();
        // glm::mat4 translate_matrix(
        //     1,            0,            0,            0,
        //     0,            1,            0,            0,
        //     0,            0,            1,            0,  
        //     translate[0], translate[1], translate[2], 1
        // );
        this->temp_translate_matrix[0][3] = this->temp_mesh_translate[0];
        this->temp_translate_matrix[1][3] = this->temp_mesh_translate[1];
        this->temp_translate_matrix[2][3] = this->temp_mesh_translate[2];

        // Делаем scale матрицу
        this->temp_mesh_scale = mesh->get_scale();
        // glm::mat4 scale_matrix(
        //     scale[0], 0,        0,        0,
        //     0,        scale[1], 0,        0,
        //     0,        0,        scale[2], 0,
        //     0,        0,        0,        1
        // );
        this->temp_scale_matrix[0][0] = this->temp_mesh_scale[0];
        this->temp_scale_matrix[1][1] = this->temp_mesh_scale[1];
        this->temp_scale_matrix[2][2] = this->temp_mesh_scale[2];

        // Делаем rotate матрицу
        this->temp_mesh_rotate = mesh->get_rotate();
        // float rotate_x_in_radians = glm::radians(rotate[0]);
        // glm::mat4 rotate_x_matrix(
        //      1,  0,                        0,                        0,
        //      0,  cos(rotate_x_in_radians), sin(rotate_x_in_radians), 0,
        //      0, -sin(rotate_x_in_radians), cos(rotate_x_in_radians), 0,
        //      0,  0,                        0,                        1
        // );
        this->temp_rotate_x_in_radians = glm::radians(this->temp_mesh_rotate[0]);
        this->temp_cos = cos(this->temp_rotate_x_in_radians);
        this->temp_sin = sin(this->temp_rotate_x_in_radians);
        this->temp_rotate_x_matrix[1][1] = this->temp_cos;
        this->temp_rotate_x_matrix[1][2] = -this->temp_sin;
        this->temp_rotate_x_matrix[2][1] = this->temp_sin;
        this->temp_rotate_x_matrix[2][2] = this->temp_cos;

        // float rotate_y_in_radians = glm::radians(rotate[1]);
        // glm::mat4 rotate_y_matrix(
        //      cos(rotate_y_in_radians), 0, -sin(rotate_y_in_radians), 0,
        //      0,                        1,  0,                        0,
        //      sin(rotate_y_in_radians), 0,  cos(rotate_y_in_radians), 0,
        //      0,                        0,  0,                        1
        // );
        this->temp_rotate_y_in_radians = glm::radians(this->temp_mesh_rotate[1]);
        this->temp_cos = cos(this->temp_rotate_y_in_radians);
        this->temp_sin = sin(this->temp_rotate_y_in_radians);
        this->temp_rotate_y_matrix[0][0] = this->temp_cos;
        this->temp_rotate_y_matrix[0][2] = this->temp_sin;
        this->temp_rotate_y_matrix[2][0] = -this->temp_sin;
        this->temp_rotate_y_matrix[2][2] = this->temp_cos;

        // float rotate_z_in_radians = glm::radians(rotate[2]);
        // glm::mat4 rotate_z_matrix(
        //      cos(rotate_z_in_radians), sin(rotate_z_in_radians), 0, 0,
        //     -sin(rotate_z_in_radians), cos(rotate_z_in_radians), 0, 0,
        //      0,                      0,                      1, 0,
        //      0,                      0,                      0, 1
        // );
        this->temp_rotate_z_in_radians = glm::radians(this->temp_mesh_rotate[2]);
        this->temp_cos = cos(this->temp_rotate_z_in_radians);
        this->temp_sin = sin(this->temp_rotate_z_in_radians);
        this->temp_rotate_y_matrix[0][0] = this->temp_cos;
        this->temp_rotate_y_matrix[0][1] = -this->temp_sin;
        this->temp_rotate_y_matrix[1][0] = this->temp_sin;
        this->temp_rotate_y_matrix[1][1] = this->temp_cos;

        this->temp_rotate_matrix = this->temp_rotate_z_matrix * this->temp_rotate_y_matrix * this->temp_rotate_x_matrix;

        // Делаем model матрицу
        this->model_matrix = this->temp_translate_matrix * this->temp_scale_matrix * this->temp_rotate_matrix;
    }


    void SceneRenderer::set_ambient_factor(float ambient_factor)
    {
        this->ambient_factor = ambient_factor;
    }


    void SceneRenderer::set_diffuse_factor(float diffuse_factor)
    {
        this->diffuse_factor = diffuse_factor;
    }


    void SceneRenderer::set_specular_factor(float specular_factor)
    {
        this->specular_factor = specular_factor;
    }

}