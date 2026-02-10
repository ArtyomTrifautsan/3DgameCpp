
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
    float m_cube_color[3] = {0, 0, 0};
    glm::vec3 cube_rotation_axis = { 0,0,0 };
    float cube_rotation_angle = 0.0f;

    std::shared_ptr<AiryEngine::Renderer> m_renderer = nullptr;
    std::shared_ptr<AiryEngine::CubeMesh> m_studing_cube = nullptr;
    std::shared_ptr<AiryEngine::ShaderProgram> m_shader = nullptr;

    virtual void on_start(std::shared_ptr<AiryEngine::ResourceManager> resource_manager) override
    {
        // m_shader = _resource_manager->load_shaders("shader_for_cube", )
        m_shader = resource_manager->load_shaders("shader_for_cube", "default_vertex_shader copy.txt", "default_fragment_shader copy.txt");
        if (!m_shader->is_compiled()) 
        {
            // LOG_CRITICAL("Failed to compile Default Shader Program");
            cout << "Failed to compile Default Shader Program" <<std::endl;
        }
        // cout << "Перед созданием модели" <<std::endl;
        m_renderer = std::make_shared<AiryEngine::Renderer>();
        m_studing_cube = AiryEngine::create_cube_mesh_from_points();
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
        m_renderer->use_shader(m_shader);
        // cout << "Прицепили шейдер" <<std::endl;
        // m_renderer->render_model3D(*camera, m_studing_cube);
        m_renderer->render_cube_mesh(*camera, m_studing_cube);
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
