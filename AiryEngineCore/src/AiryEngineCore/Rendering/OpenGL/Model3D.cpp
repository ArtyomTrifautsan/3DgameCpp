#include "AiryEngineCore/Rendering/OpenGL/Model3D.hpp"

#include "AiryEngineCore/Rendering/OpenGL/Mesh.hpp"
#include "AiryEngineCore/Rendering/OpenGL/ShaderProgram.hpp"


namespace AiryEngine {

    Model3D::Model3D(std::vector<std::shared_ptr<Mesh>> _meshes)
    {
        add_meshes(_meshes);
    }


    void Model3D::add_mesh(std::shared_ptr<Mesh> _mesh)
    {
        this->meshes.push_back(_mesh);
    }


    void Model3D::add_meshes(std::vector<std::shared_ptr<Mesh>> _meshes)
    {
        for (std::shared_ptr<Mesh> current_mesh : _meshes) 
            add_mesh(current_mesh);
    }


    void Model3D::set_material(std::shared_ptr<Material> material)
    {
        for (std::shared_ptr<Mesh> current_mesh : this->meshes)
            current_mesh->set_material(material);
    }


    void Model3D::set_diffuse_color(float r, float g, float b)
    {
        for (std::shared_ptr<Mesh> current_mesh : this->meshes)
            current_mesh->set_diffuse_color(r, g, b);
    }


    //====================SET TRANSLATE====================
    void Model3D::set_translate(glm::vec3& translate)
    {
        this->translate = translate;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_translate(translate);
    }


    void Model3D::set_translate(float translate_x, float translate_y, float translate_z)
    {
        this->translate = glm::vec3(translate_x, translate_y, translate_z);

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_translate(translate_x, translate_x, translate_x);
    }


    void Model3D::set_translate_x(float value)
    {
        this->translate.x = value;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_translate_x(value);
    }


    void Model3D::set_translate_y(float value)
    {
        this->translate.y = value;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_translate_y(value);
    }


    void Model3D::set_translate_z(float value)
    {
        this->translate.z = value;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_translate_z(value);
    }


    //====================SET SCALE====================
    void Model3D::set_scale(glm::vec3& scale)
    {
        this->scale = scale;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_scale(scale);
    }


    void Model3D::set_scale(float scale_x, float scale_y, float scale_z)
    {
        this->scale = glm::vec3(scale_x, scale_y, scale_z);

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_scale(scale_x, scale_y, scale_z);
    }


    void Model3D::set_scale_x(float scale_x)
    {
        this->scale.x = scale_x;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_scale_x(scale_x);
    }


    void Model3D::set_scale_y(float scale_y)
    {
        this->scale.y = scale_y;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_scale_y(scale_y);
    }


    void Model3D::set_scale_z(float scale_z)
    {
        this->scale.z = scale_z;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_scale_z(scale_z);
    }


    //====================SET ROTATE====================
    void Model3D::set_rotate(glm::vec3& rotate)
    {
        this->rotate = rotate;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_rotate(rotate);
    }


    void Model3D::set_rotate(float rotate_x, float rotate_y, float rotate_z)
    {
        this->rotate = glm::vec3(rotate_x, rotate_y, rotate_z);

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_rotate(rotate_x, rotate_y, rotate_z);
    }


    void Model3D::set_rotate_x(float rotate_x)
    {
        this->rotate.x = rotate_x;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_rotate_x(rotate_x);
    }


    void Model3D::set_rotate_y(float rotate_y)
    {
        this->rotate.y = rotate_y;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_rotate_y(rotate_y);
    }


    void Model3D::set_rotate_z(float rotate_z)
    {
        this->rotate.z = rotate_z;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_rotate_z(rotate_z);
    } 


    //====================MOVE====================
    void Model3D::move_model(glm::vec3& delta)
    {
        this->translate = this->translate + delta;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->move_mesh(delta);
    }


    void Model3D::move_model(float delta_move_x, float delta_move_y, float delta_move_z)
    {
        this->translate = glm::vec3(
            this->translate.x + delta_move_x,
            this->translate.y + delta_move_y,
            this->translate.z + delta_move_z
        );

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->move_mesh(delta_move_x, delta_move_y, delta_move_z);
    }


    void Model3D::move_model_x(float delta_move_x)
    {
        this->translate.x = this->translate.x + delta_move_x;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->move_mesh_x(delta_move_x);
    }


    void Model3D::move_model_y(float delta_move_y)
    {
        this->translate.y = this->translate.y + delta_move_y;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->move_mesh_y(delta_move_y);
    }


    void Model3D::move_model_z(float delta_move_z)
    {
        this->translate.y = this->translate.y + delta_move_z;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->move_mesh_z(delta_move_z);
    }


    //====================SCALE====================
    void Model3D::scale_model(glm::vec3& scale)
    {
        this->scale = glm::vec3(
            this->scale.x * scale.x,
            this->scale.y * scale.y,
            this->scale.z * scale.z
        );

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->scale_mesh(scale);
    }


    void Model3D::scale_model(float scale_x, float scale_y, float scale_z)
    {
        this->scale = glm::vec3(
            this->scale.x * scale_x,
            this->scale.y * scale_y,
            this->scale.z * scale_z
        );

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->scale_mesh(scale_x, scale_y, scale_z);
    }


    void Model3D::scale_model_x(float scale_x)
    {
        this->scale.x = this->scale.x * scale_x;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->scale_mesh_x(scale_x);
    }


    void Model3D::scale_model_y(float scale_y)
    {
        this->scale.y = this->scale.y * scale_y;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->scale_mesh_y(scale_y);
    }


    void Model3D::scale_model_z(float scale_z)
    {
        this->scale.z = this->scale.z * scale_z;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->scale_mesh_z(scale_z);
    }


    //====================ROTATE====================
    void Model3D::rotate_model(glm::vec3& delta_rotate)
    {
        this->rotate = glm::vec3(
            this->rotate.x + delta_rotate.x,
            this->rotate.y + delta_rotate.y,
            this->rotate.z + delta_rotate.z
        );

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->rotate_mesh(delta_rotate);
    }


    void Model3D::rotate_model(float delta_angle_x, float delta_angle_y, float delta_angle_z)
    {
        this->rotate = glm::vec3(
            this->rotate.x + delta_angle_x,
            this->rotate.y + delta_angle_y,
            this->rotate.z + delta_angle_z
        );

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->rotate_mesh(delta_angle_x, delta_angle_y, delta_angle_z);
    }


    void Model3D::rotate_model_x(float delta_angle_x)
    {
        this->rotate.x = this->rotate.x + delta_angle_x;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->rotate_mesh_x(delta_angle_x);
    }


    void Model3D::rotate_model_y(float delta_angle_y)
    {
        this->rotate.y = this->rotate.y + delta_angle_y;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->rotate_mesh_y(delta_angle_y);
    }


    void Model3D::rotate_model_z(float delta_angle_z)
    {
        this->rotate.z = this->rotate.z + delta_angle_z;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->rotate_mesh_z(delta_angle_z);
    }
}