
#include <iostream>
#include <memory>
#include <imgui/imgui.h>
#include <glm/trigonometric.hpp>
#include <glm/gtc/type_ptr.hpp>
using std::cout;
using std::endl;

#include <AiryEngineCore/Application.hpp>
#include <AiryEngineCore/Input.hpp>
#include <AiryEngineCore/ResourceManager.hpp>
#include <AiryEngineCore/Renderer.hpp>
#include <AiryEngineCore/Rendering/OpenGL/Model3D.hpp>
#include <AiryEngineCore/Rendering/OpenGL/ShaderProgram.hpp>

class AiryEngineEditor : public AiryEngine::Application
{
public:
    AiryEngineEditor(std::shared_ptr<AiryEngine::ResourceManager> _resource_manager) : AiryEngine::Application(_resource_manager)
    {
        // set_executable_path(executable_path);
        // std::cout << "GameApplication constructor started" << std::endl;
    }
    double m_initial_mouse_pos_x = 0.0;
    double m_initial_mouse_pos_y = 0.0;

    float camera_position[3] = {0, 0, 0};
    float camera_rotation[3] = {0, 0, 0};

    std::shared_ptr<AiryEngine::Renderer> m_renderer = nullptr;

    // Задача 1
    bool checkbox_task_1 = false;
    std::shared_ptr<AiryEngine::ShaderProgram> m_shader = nullptr;
    std::shared_ptr<AiryEngine::CubeMesh> m_studing_cube = nullptr;
    float m_cube_color[3] = {0, 0, 0};
    glm::vec3 cube_rotation_axis = { 0,0,0 };
    float cube_rotation_angle = 0.0f;

    // Задача 2
    bool checkbox_task_2 = false;
    std::shared_ptr<AiryEngine::ShaderProgram> m_shader_2 = nullptr;
    std::shared_ptr<AiryEngine::CubeMesh> m_studing_cube_2 = nullptr;
    float uMorphFactor = 0.0f;

    // Задача 3
    bool checkbox_task_3 = true;
    inline static int light_type = 0;  // 0 - точечный, 1 - направленный, 2 - прожектор
    std::shared_ptr<AiryEngine::ShaderProgram> m_shader_3_1 = nullptr;
    std::shared_ptr<AiryEngine::ShaderProgram> m_shader_3_2 = nullptr;
    std::shared_ptr<AiryEngine::ShaderProgram> m_shader_3_3 = nullptr;
    std::shared_ptr<AiryEngine::CubeMesh> m_studing_cube_3 = nullptr;
    float cube_3_pos[3] = {0, 0, 0};
    float cube_3_scale[3] = {1, 1, 1};
    float cube_3_rotate[3] = {0, 0, 0};
    float light_pos[3] = {0, 0, 0};
    float light_dir[3] = {1, 0, 0};
    float light_color[3] = {1, 1, 1};
    float ambient_color[3] = {1, 1, 1};
    float diffuse_color[3] = {1, 1, 1};
    float specular_color[3] = {1, 1, 1};
    float ambient_factor = 1;
    float diffuse_factor = 1;
    float specular_factor = 1;
    float shininess = 30;
    float attenuation[3] = {1, 1, 1};
    float cutOff = 0;       // Внутренний угол (косинус)
    float outerCutOff = 0;  // Внешний угол (косинус) для мягких краев



    virtual void on_start(std::shared_ptr<AiryEngine::ResourceManager> resource_manager) override
    {
        // m_shader = _resource_manager->load_shaders("shader_for_cube", )
        m_shader = resource_manager->load_shaders("shader_for_cube", "default_vertex_shader copy.txt", "default_fragment_shader copy.txt");
        if (!m_shader->is_compiled()) 
        {
            // LOG_CRITICAL("Failed to compile Default Shader Program");
            cout << "Failed to compile Default Shader Program" <<std::endl;
        }

        m_shader_2 = resource_manager->load_shaders("shader_for_cube_2", "morfing_vertex.txt", "morfing_fragment.txt");
        if (!m_shader->is_compiled()) 
        {
            // LOG_CRITICAL("Failed to compile Default Shader Program");
            cout << "Failed to compile Default Shader Program 2" <<std::endl;
        }

        m_shader_3_1 = resource_manager->load_shaders("shader_for_task_3_1", "task3_vertex_point.txt", "task3_fragment_point.txt");
        if (!m_shader->is_compiled()) 
        {
            // LOG_CRITICAL("Failed to compile Default Shader Program");
            cout << "Failed to compile Shader Program for task 3" <<std::endl;
        }

        m_shader_3_2 = resource_manager->load_shaders("shader_for_task_3_2", "task3_vertex_directional.txt", "task3_fragment_point.txt");
        if (!m_shader->is_compiled()) 
        {
            // LOG_CRITICAL("Failed to compile Default Shader Program");
            cout << "Failed to compile Shader Program for task 3" <<std::endl;
        }

        m_shader_3_3 = resource_manager->load_shaders("shader_for_task_3_3", "task3_vertex_spot.txt", "task3_fragment_point.txt");
        if (!m_shader->is_compiled()) 
        {
            // LOG_CRITICAL("Failed to compile Default Shader Program");
            cout << "Failed to compile Shader Program for task 3" <<std::endl;
        }

        m_renderer = std::make_shared<AiryEngine::Renderer>();
        m_studing_cube = AiryEngine::create_cube_mesh_from_points();
        m_studing_cube_2 = AiryEngine::create_cube_mesh_from_points_2(4);
        // cout << "Перед созданием модели" <<std::endl;
        m_studing_cube_3 = AiryEngine::create_cube_mesh_from_points_3(16);
        // cout << "После" <<std::endl;
    }

    virtual void on_update() override
    {
        glm::vec3 movement_delta{ 0, 0, 0 };
        glm::vec3 rotation_delta{ 0, 0, 0 };

        // Go Forward
        if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_W))
        {
            movement_delta.x += 0.05f;
        }

        // Go Back
        if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_S))
        {
            movement_delta.x -= 0.05f;
        }

        // Go Left
        if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_A))
        {
            movement_delta.y -= 0.05f;
        }

        // Go Right
        if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_D))
        {
            movement_delta.y += 0.05f;
        }

        // Go Up
        if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_SPACE))
        {
            movement_delta.z += 0.05f;
        }

        // Go Down
        if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_LEFT_SHIFT))
        {
            movement_delta.z -= 0.05f;
        }

        // Rotation Up
        if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_UP))
        {
            rotation_delta.y -= 0.5f;
        }

        // Rotation Down
        if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_DOWN))
        {
            rotation_delta.y += 0.5f;
        }

        // Rotation Left
        if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_LEFT))
        {
            rotation_delta.z -= 0.5f;
        }

        // Rotation Right
        if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_RIGHT))
        {
            rotation_delta.z += 0.5f;
        }

        // Rotation 1
        if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_P))
        {
            rotation_delta.x += 0.5f;
        }

        // Rotation 2
        if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_O))
        {
            rotation_delta.x -= 0.5f;
        }


        if (AiryEngine::Input::IsMouseButtonPressed(AiryEngine::MouseButtonCode::MOUSE_BUTTON_RIGHT))
        {
            glm::vec2 current_cursor_position = get_current_cursor_position();

            if (AiryEngine::Input::IsMouseButtonPressed(AiryEngine::MouseButtonCode::MOUSE_BUTTON_LEFT))
            {
                camera->move_right(static_cast<float>(-(current_cursor_position.x - m_initial_mouse_pos_x)) / 100.f );
                camera->move_up(static_cast<float>(-(m_initial_mouse_pos_y - current_cursor_position.y)) / 100.f );
            }
            else
            {
                rotation_delta.y += static_cast<float>(m_initial_mouse_pos_x - current_cursor_position.x) / 5.f;
                rotation_delta.x += static_cast<float>(m_initial_mouse_pos_y - current_cursor_position.y) / 5.f;
            }

            m_initial_mouse_pos_x = current_cursor_position.x;
            m_initial_mouse_pos_y = current_cursor_position.y;
        }

        camera->add_movement_and_rotation(movement_delta, rotation_delta);   
    }

    virtual void on_mouse_button_pressed(const AiryEngine::MouseButtonCode mouse_button_code, 
                                        const double x_pos, 
                                        const double y_pos, 
                                        const bool pressed) override 
    {
        m_initial_mouse_pos_x = x_pos;
        m_initial_mouse_pos_y = y_pos;


    }

    virtual void on_draw() override 
    {
        // cout << "Начали он_дроу" <<std::endl;
        // if (m_shader == nullptr)
            // cout << "Проблема: m_shader == nullptr" <<std::endl;

        if (checkbox_task_1)
        {
            m_renderer->use_shader(m_shader);
            m_renderer->render_cube_mesh(*camera, m_studing_cube);
        }


        // cout << "Прицепили шейдер" <<std::endl;
        // m_renderer->render_model3D(*camera, m_studing_cube);
        if (checkbox_task_2)
        {
            m_renderer->use_shader(m_shader_2);
            m_renderer->render_cube_mesh_2(*camera, m_studing_cube_2, uMorphFactor);
        }

        if (checkbox_task_3)
        {
            if (light_type == 0)
            {
                m_renderer->use_shader(m_shader_3_1);
                m_shader_3_1->bind();
                m_shader_3_1->set_float("uMorphFactor", uMorphFactor);
                m_shader_3_1->set_vec3("camera_pos", glm::vec3(camera_position[0], camera_position[1], camera_position[2]));
                m_shader_3_1->set_vec3("light_pos", glm::vec3(light_pos[0], light_pos[1], light_pos[2]));
                m_shader_3_1->set_vec3("light_color", glm::vec3(light_color[0], light_color[1], light_color[2]));
                // m_shader_3_1->set_vec3("ambient_color", glm::vec3(ambient_color[0], ambient_color[1], ambient_color[2]));
                // m_shader_3_1->set_vec3("diffuse_color", glm::vec3(diffuse_color[0], diffuse_color[1], diffuse_color[2]));
                // m_shader_3_1->set_vec3("specular_color", glm::vec3(specular_color[0], specular_color[1], specular_color[2]));
                m_shader_3_1->set_float("ambient_factor", ambient_factor);
                m_shader_3_1->set_float("diffuse_factor", diffuse_factor);
                m_shader_3_1->set_float("specular_factor", specular_factor);
                m_shader_3_1->set_float("shininess", shininess);
                m_shader_3_1->set_vec3("attenuation", glm::vec3(attenuation[0], attenuation[1], attenuation[2]));

                glm::vec3 cube_pos = {0, 0, 0};
                glm::vec3 cube_scale = {0, 0, 0};

                // std::cout << "cube pos 1 = (" << cube_pos[0] << "; " << cube_pos[1] << "; " << cube_pos[2] << ")" << std::endl;
                // std::cout << "cube scale 1 = (" << cube_scale[0] << "; " << cube_scale[1] << "; " << cube_scale[2] << ")" << std::endl;

                cube_pos = m_studing_cube_3->get_translate();
                cube_scale = m_studing_cube_3->get_scale();

                // std::cout << "cube pos 2 = (" << cube_pos[0] << "; " << cube_pos[1] << "; " << cube_pos[2] << ")" << std::endl;
                // std::cout << "cube scale 2 = (" << cube_scale[0] << "; " << cube_scale[1] << "; " << cube_scale[2] << ")" << std::endl;

                m_shader_3_1->set_vec3("ambient_color", glm::vec3(light_color[0], light_color[1], light_color[2]));
                m_shader_3_1->set_vec3("diffuse_color", glm::vec3(light_color[0], light_color[1], light_color[2]));
                m_shader_3_1->set_vec3("specular_color", glm::vec3(light_color[0], light_color[1], light_color[2]));
                m_studing_cube_3->set_translate(light_pos[0], light_pos[1], light_pos[2]);
                m_studing_cube_3->set_scale(0.2, 0.2, 0.2);
                m_renderer->render_cube_mesh_3(*camera, m_studing_cube_3);

                // std::cout << "cube pos 3 = (" << cube_pos[0] << "; " << cube_pos[1] << "; " << cube_pos[2] << ")" << std::endl;
                // std::cout << "cube scale 3 = (" << cube_scale[0] << "; " << cube_scale[1] << "; " << cube_scale[2] << ")" << std::endl;

                m_shader_3_1->bind();
                m_shader_3_1->set_vec3("ambient_color", glm::vec3(ambient_color[0], ambient_color[1], ambient_color[2]));
                m_shader_3_1->set_vec3("diffuse_color", glm::vec3(diffuse_color[0], diffuse_color[1], diffuse_color[2]));
                m_shader_3_1->set_vec3("specular_color", glm::vec3(specular_color[0], specular_color[1], specular_color[2]));
                m_studing_cube_3->set_translate(cube_pos[0], cube_pos[1], cube_pos[2]);
                m_studing_cube_3->set_scale(cube_scale[0], cube_scale[1], cube_scale[2]);
                m_renderer->render_cube_mesh_3(*camera, m_studing_cube_3);

                // std::cout << "cube pos 4 = (" << cube_pos[0] << "; " << cube_pos[1] << "; " << cube_pos[2] << ")" << std::endl;
                // std::cout << "cube scale 4 = (" << cube_scale[0] << "; " << cube_scale[1] << "; " << cube_scale[2] << ")" << std::endl;
            }

            if (light_type == 1)
            {
                m_renderer->use_shader(m_shader_3_2);
                m_shader_3_2->bind();
                m_shader_3_2->set_float("uMorphFactor", uMorphFactor);
                m_shader_3_2->set_vec3("camera_pos", glm::vec3(camera_position[0], camera_position[1], camera_position[2]));
                m_shader_3_2->set_vec3("light_dir", glm::vec3(light_dir[0], light_dir[1], light_dir[2]));
                m_shader_3_2->set_vec3("light_color", glm::vec3(light_color[0], light_color[1], light_color[2]));
                // m_shader_3_2->set_vec3("ambient_color", glm::vec3(ambient_color[0], ambient_color[1], ambient_color[2]));
                // m_shader_3_2->set_vec3("diffuse_color", glm::vec3(diffuse_color[0], diffuse_color[1], diffuse_color[2]));
                // m_shader_3_2->set_vec3("specular_color", glm::vec3(specular_color[0], specular_color[1], specular_color[2]));
                m_shader_3_2->set_float("ambient_factor", ambient_factor);
                m_shader_3_2->set_float("diffuse_factor", diffuse_factor);
                m_shader_3_2->set_float("specular_factor", specular_factor);
                m_shader_3_2->set_float("shininess", shininess);
                m_shader_3_2->set_vec3("attenuation", glm::vec3(attenuation[0], attenuation[1], attenuation[2]));

                m_shader_3_2->bind();
                m_renderer->render_cube_mesh_3(*camera, m_studing_cube_3);
            }

            if (light_type == 2)
            {
                m_renderer->use_shader(m_shader_3_3);
                m_shader_3_3->bind();
                m_shader_3_3->set_float("uMorphFactor", uMorphFactor);
                m_shader_3_3->set_vec3("camera_pos", glm::vec3(camera_position[0], camera_position[1], camera_position[2]));
                m_shader_3_3->set_vec3("light_pos", glm::vec3(light_pos[0], light_pos[1], light_pos[2]));
                m_shader_3_3->set_vec3("light_dir", glm::vec3(light_dir[0], light_dir[1], light_dir[2]));
                m_shader_3_3->set_vec3("light_color", glm::vec3(light_color[0], light_color[1], light_color[2]));
                m_shader_3_3->set_vec3("ambient_color", glm::vec3(ambient_color[0], ambient_color[1], ambient_color[2]));
                m_shader_3_3->set_vec3("diffuse_color", glm::vec3(diffuse_color[0], diffuse_color[1], diffuse_color[2]));
                m_shader_3_3->set_vec3("specular_color", glm::vec3(specular_color[0], specular_color[1], specular_color[2]));
                m_shader_3_3->set_float("ambient_factor", ambient_factor);
                m_shader_3_3->set_float("diffuse_factor", diffuse_factor);
                m_shader_3_3->set_float("specular_factor", specular_factor);
                m_shader_3_3->set_float("shininess", shininess);
                m_shader_3_3->set_vec3("attenuation", glm::vec3(attenuation[0], attenuation[1], attenuation[2]));
                m_shader_3_3->set_float("cutOff", cutOff);
                m_shader_3_3->set_float("outerCutOff", outerCutOff);

                glm::vec3 cube_pos = m_studing_cube_3->get_translate();
                glm::vec3 cube_scale = m_studing_cube_3->get_scale();

                m_shader_3_3->set_vec3("ambient_color", glm::vec3(light_color[0], light_color[1], light_color[2]));
                m_shader_3_3->set_vec3("diffuse_color", glm::vec3(light_color[0], light_color[1], light_color[2]));
                m_shader_3_3->set_vec3("specular_color", glm::vec3(light_color[0], light_color[1], light_color[2]));
                m_studing_cube_3->set_translate(light_pos[0], light_pos[1], light_pos[2]);
                m_studing_cube_3->set_scale(0.2, 0.2, 0.2);
                m_renderer->render_cube_mesh_3(*camera, m_studing_cube_3);

                m_shader_3_3->bind();
                m_shader_3_3->set_vec3("ambient_color", glm::vec3(ambient_color[0], ambient_color[1], ambient_color[2]));
                m_shader_3_3->set_vec3("diffuse_color", glm::vec3(diffuse_color[0], diffuse_color[1], diffuse_color[2]));
                m_shader_3_3->set_vec3("specular_color", glm::vec3(specular_color[0], specular_color[1], specular_color[2]));
                m_studing_cube_3->set_translate(cube_pos[0], cube_pos[1], cube_pos[2]);
                m_studing_cube_3->set_scale(cube_scale[0], cube_scale[1], cube_scale[2]);
                m_renderer->render_cube_mesh_3(*camera, m_studing_cube_3);

                // m_shader_3_3->bind();
                // m_renderer->render_cube_mesh_3(*camera, m_studing_cube_3);
            }

            // m_renderer->render_cube_mesh_3(*camera, m_studing_cube_3);
        }
        // glm::vec3 center_of_cube = m_studing_cube->get_translate();
        // cout << "Нарисовали куб с центром в точке (" << center_of_cube[0] << ", " << center_of_cube[1] << ", " << center_of_cube[2] << ")." << std::endl;
    }

    virtual void on_ui_draw() override
    {
        camera_position[0] = camera->get_camera_position().x;
        camera_position[1] = camera->get_camera_position().y;
        camera_position[2] = camera->get_camera_position().z;

        camera_rotation[0] = camera->get_camera_rotation().x;
        camera_rotation[1] = camera->get_camera_rotation().y;
        camera_rotation[2] = camera->get_camera_rotation().z;

        ImGui::Begin("Editor");

        if (ImGui::SliderFloat3("camera position", camera_position, -10.0f, 10.0f))
        {
            camera->set_position(glm::vec3(camera_position[0], camera_position[1], camera_position[2]));
        }
        if (ImGui::SliderFloat3("camera rotation", camera_rotation, 0.0f, 360.0f))
        {
            camera->set_rotation(glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
        }
        // ImGui::Checkbox("Perspective camera", &perspective_camera);

        ImGui::Checkbox("Enable task 1", &checkbox_task_1);
        if (checkbox_task_1)
        {
            if (ImGui::SliderFloat3("Cube color", m_cube_color, 0.0f, 1.0f))
            {
                m_studing_cube->set_diffuse_color(m_cube_color[0], m_cube_color[1], m_cube_color[2]);
                // camera->set_rotation(glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
            }

            if (ImGui::InputFloat3("Cube rotation axis", glm::value_ptr(cube_rotation_axis)))
            {
                // camera->set_position(glm::vec3(camera_position[0], camera_position[1], camera_position[2]));
                m_studing_cube->set_rotation_axis_angle(cube_rotation_angle, cube_rotation_axis);
            }

            if (ImGui::SliderFloat("Cube rotation angle", &cube_rotation_angle, -180.0f, 180.0f))
            {
                // camera->set_position(glm::vec3(camera_position[0], camera_position[1], camera_position[2]));
                m_studing_cube->set_rotation_axis_angle(cube_rotation_angle, cube_rotation_axis);
            }
        }

        ImGui::Checkbox("Enable task 2", &checkbox_task_2);
        if (checkbox_task_2)
        {
            if (ImGui::SliderFloat("Cube morphing factor", &uMorphFactor, 0.0f, 1.0f))
            {
                // camera->set_position(glm::vec3(camera_position[0], camera_position[1], camera_position[2]));
                // m_studing_cube_2->set_rotation_axis_angle(cube_rotation_angle, cube_rotation_axis);
            }
        }

        ImGui::Checkbox("Enable task 3", &checkbox_task_3);
        if (checkbox_task_3)
        {
            ImGui::SliderFloat("Cube morphing factor", &uMorphFactor, 0.0f, 1.0f);

            if (ImGui::SliderFloat3("cube position", cube_3_pos, -10.0f, 10.0f))
                m_studing_cube_3->set_translate(cube_3_pos[0], cube_3_pos[1], cube_3_pos[2]);
            if (ImGui::SliderFloat3("cube scaling", cube_3_scale, 0.0f, 10.0f))
                m_studing_cube_3->set_scale(cube_3_scale[0], cube_3_scale[1], cube_3_scale[2]);
            if (ImGui::SliderFloat3("cube rotation", cube_3_rotate, -360.0f, 360.0f))
                m_studing_cube_3->set_rotate(cube_3_rotate[0], cube_3_rotate[1], cube_3_rotate[2]);

            if (ImGui::RadioButton("point source light", light_type == 0)) { light_type = 0; }
            if (ImGui::RadioButton("directional light", light_type == 1)) { light_type = 1; }
            if (ImGui::RadioButton("spot light", light_type == 2)) { light_type = 2; }

            if (light_type == 0)
            {
                ImGui::SliderFloat3("light pos", light_pos, -10.0f, 10.0f);
                ImGui::ColorEdit3("light color", light_color);
                ImGui::ColorEdit3("ambient color", ambient_color);
                ImGui::ColorEdit3("diffuse color", diffuse_color);
                ImGui::ColorEdit3("specular color", specular_color);
                ImGui::SliderFloat("ambient_factor", &ambient_factor, 0.0f, 1.0f);
                ImGui::SliderFloat("diffuse_factor", &diffuse_factor, 0.0f, 1.0f);
                ImGui::SliderFloat("specular_factor", &specular_factor, 0.0f, 1.0f);
                ImGui::SliderFloat("shininess", &shininess, 1.0f, 500.0f);
                ImGui::SliderFloat3("attenuation", attenuation, 0.0f, 10.0f);
            }

            else if (light_type == 1)
            {
                ImGui::SliderFloat3("light direction", light_dir, -1.0f, 1.0f);
                ImGui::ColorEdit3("light color", light_color);
                ImGui::ColorEdit3("ambient color", ambient_color);
                ImGui::ColorEdit3("diffuse color", diffuse_color);
                ImGui::ColorEdit3("specular color", specular_color);
                ImGui::SliderFloat("ambient_factor", &ambient_factor, 0.0f, 1.0f);
                ImGui::SliderFloat("diffuse_factor", &diffuse_factor, 0.0f, 1.0f);
                ImGui::SliderFloat("specular_factor", &specular_factor, 0.0f, 1.0f);
                ImGui::SliderFloat("shininess", &shininess, 1.0f, 500.0f);
            }

            else if (light_type == 2)
            {
                ImGui::SliderFloat3("light pos", light_pos, -10.0f, 10.0f);
                ImGui::SliderFloat3("light direction", light_dir, -1.0f, 1.0f);
                ImGui::ColorEdit3("light color", light_color);
                ImGui::ColorEdit3("ambient color", ambient_color);
                ImGui::ColorEdit3("diffuse color", diffuse_color);
                ImGui::ColorEdit3("specular color", specular_color);
                ImGui::SliderFloat("ambient_factor", &ambient_factor, 0.0f, 1.0f);
                ImGui::SliderFloat("diffuse_factor", &diffuse_factor, 0.0f, 1.0f);
                ImGui::SliderFloat("specular_factor", &specular_factor, 0.0f, 1.0f);
                ImGui::SliderFloat("shininess", &shininess, 1.0f, 500.0f);
                ImGui::SliderFloat3("attenuation", attenuation, 0.0f, 10.0f);
                ImGui::SliderFloat("cutOff", &cutOff, -1.0f, 1.0f);
                ImGui::SliderFloat("outerCutOff", &outerCutOff, -1.0f, 1.0f);
            }
        }

        ImGui::End();
    }   

    int frame = 0;
};

int main(int argc, char const *argv[])
{
    auto resource_manager = std::make_shared<AiryEngine::ResourceManager>(argv[0]);
    resource_manager->set_shaders_directory("Resources/Shaders");
    resource_manager->set_textures_directory("Resources/Textures");
    resource_manager->set_models_directory("Resources/Models");

    auto airyEngineEditor = std::make_unique<AiryEngineEditor>(resource_manager);
    int returnCode = airyEngineEditor->start(1024, 768, "AiryEngine Editor");

    return returnCode;
}
