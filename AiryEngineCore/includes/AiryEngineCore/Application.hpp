#pragma once

#include <memory>
#include <string>

#include "AiryEngineCore/Camera.hpp"
#include "AiryEngineCore/Event.hpp"
#include "AiryEngineCore/fps_keeper.hpp"


namespace AiryEngine {

    class Model3D;
    class Texture2D;
    class ResourceManager;

    class Application
    {
    public:
        Application(std::shared_ptr<ResourceManager> _resource_manager);  
        virtual ~Application();
        void set_executable_path(const std::string& executable_path);

        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = delete;

        virtual int start(unsigned int window_width, unsigned int window_height, const char* title);
        void close();

        virtual void on_start(std::shared_ptr<ResourceManager> _resource_manager) {}
        virtual void on_draw() {}
        virtual void on_update() {}
        virtual void on_ui_draw() {}
        virtual void on_mouse_button_pressed(const MouseButtonCode mouse_button_code, 
                                            const double x_pos, 
                                            const double y_pos, 
                                            const bool pressed) {}

        glm::vec2 get_current_cursor_position() const;

        std::shared_ptr<Camera> camera;

    private:
        std::unique_ptr<class Window> window;
        std::shared_ptr<class ResourceManager> resource_manager;

        EventDispatcher eventDispatcher;
        bool closeWindow = false;
        float background_color[4] = {0.33f, 0.33f, 0.33f, 0.f};

        std::unique_ptr<FpsKeeper> fps_keeper;

        std::vector<std::shared_ptr<Model3D>> models;

        std::string path_to_executable;
    };

}