#include "barrier.hpp"


Barrier::Barrier(const std::string& model_name,
    const std::string& model_filename,
    const std::string& model_path_to_file,
    std::shared_ptr<AiryEngine::ResourceManager> resource_manager) : GameObject(model_name, 
                                                                                model_filename, 
                                                                                model_path_to_file,
                                                                                resource_manager)
{
    set_model_start_offset(glm::vec3(0, -0.503f, 0));

    set_model_start_scale(glm::vec3(0.270f, 0.270f, 0.270f));

    set_model_start_rotate(glm::vec3(0, 0, 0));

    set_colliding_cube_start_offset(glm::vec3(0, 0.202f, 0));

    set_colliding_cube_start_scale(glm::vec3(0.849f, 0.446f, 0.246f));
}


Barrier::Barrier(const std::string& model_name,
    std::shared_ptr<AiryEngine::ResourceManager> resource_manager) : GameObject(model_name,
                                                                                resource_manager)
{
    set_model_start_offset(glm::vec3(0, -0.503f, 0));

    set_model_start_scale(glm::vec3(0.270f, 0.270f, 0.270f));

    set_model_start_rotate(glm::vec3(0, 0, 0));

    set_colliding_cube_start_offset(glm::vec3(0, 0.202f, 0));

    set_colliding_cube_start_scale(glm::vec3(0.849f, 0.446f, 0.246f));
}
