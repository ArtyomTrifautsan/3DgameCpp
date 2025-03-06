#include "AiryEngineCore/Rendering/OpenGL/Mesh.hpp"

#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_float4x4.hpp>

#include "AiryEngineCore/Log.hpp"

#include "AiryEngineCore/Camera.hpp"
#include "AiryEngineCore/Rendering/OpenGL/Renderer_OpenGL.hpp"
#include "AiryEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "AiryEngineCore/Rendering/OpenGL/VertexBuffer.hpp"
#include "AiryEngineCore/Rendering/OpenGL/IndexBuffer.hpp"
#include "AiryEngineCore/Rendering/OpenGL/VertexArray.hpp"
#include "AiryEngineCore/Rendering/OpenGL/Texture2D.hpp"


namespace AiryEngine {

    Mesh::Mesh(std::shared_ptr<std::vector<float>> vertices, 
                std::shared_ptr<std::vector<unsigned int>> indices, 
                std::shared_ptr<Material> material)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->material = material;

        setup_render_data_mesh();
    }


    void Mesh::setup_render_data_mesh()
    {
        BufferLayout bufferLayout_vec3_vec3_vec2
        {
            ShaderDataType::Float3,
            ShaderDataType::Float3,
            ShaderDataType::Float2
        };

        this->vertex_buffer = std::make_shared<VertexBuffer>(this->vertices->data(), this->vertices->size() * sizeof(float), bufferLayout_vec3_vec3_vec2);
        this->vertex_array = std::make_shared<VertexArray>();
        this->index_buffer = std::make_shared<IndexBuffer>(this->indices->data(), this->indices->size());
        vertex_array->add_vertex_buffer(*this->vertex_buffer);
        vertex_array->set_index_buffer(*this->index_buffer);

        this->vertex_array->unbind();
    }


    void Mesh::set_texture(std::shared_ptr<Texture2D> texture)
    {
        this->texture = texture;
    }


    void Mesh::set_has_texture(bool has_texture)
    {
        this->has_texture = has_texture;
    }


    void Mesh::set_material(std::shared_ptr<Material> material)
    {
        this->material = material;
    }


    void Mesh::set_diffuse_color(float r, float g, float b)
    {
        this->material->diffuse_color = glm::vec3(r, g, b);
    }


    //====================SET TRANSLATE====================
    void Mesh::set_translate(glm::vec3& translate)
    {
        this->translate = translate;
    }


    void Mesh::set_translate(float translate_x, float translate_y, float translate_z)
    {
        this->translate = glm::vec3(translate_x, translate_y, translate_z);
    }


    void Mesh::set_translate_x(float value)
    {
        this->translate.x = value;
    }


    void Mesh::set_translate_y(float value)
    {
        this->translate.y = value;
    }


    void Mesh::set_translate_z(float value)
    {
        this->translate.z = value;
    }


    //====================SET SCALE====================
    void Mesh::set_scale(glm::vec3& scale)
    {
        this->scale = scale;
    }


    void Mesh::set_scale(float scale_x, float scale_y, float scale_z)
    {
        this->scale = glm::vec3(scale_x, scale_y, scale_z);
    }


    void Mesh::set_scale_x(float scale_x)
    {
        this->scale.x = scale_x;
    }


    void Mesh::set_scale_y(float scale_y)
    {
        this->scale.y = scale_y;
    }


    void Mesh::set_scale_z(float scale_z)
    {
        this->scale.z = scale_z;
    }


    //====================SET ROTATE====================
    void Mesh::set_rotate(glm::vec3& rotate)
    {
        this->rotate = rotate;
    }


    void Mesh::set_rotate(float rotate_x, float rotate_y, float rotate_z)
    {
        this->rotate = glm::vec3(rotate_x, rotate_y, rotate_z);
    }


    void Mesh::set_rotate_x(float rotate_x)
    {
        this->rotate.x = rotate_x;
    }


    void Mesh::set_rotate_y(float rotate_y)
    {
        this->rotate.y = rotate_y;
    }


    void Mesh::set_rotate_z(float rotate_z)
    {
        this->rotate.z = rotate_z;
    }    


    //====================MOVE====================
    void Mesh::move_mesh(glm::vec3& delta)
    {
        this->translate = this->translate + delta;
    }


    void Mesh::move_mesh(float delta_move_x, float delta_move_y, float delta_move_z)
    {
        this->translate = glm::vec3(
            this->translate.x + delta_move_x,
            this->translate.y + delta_move_y,
            this->translate.z + delta_move_z
        );
    }


    void Mesh::move_mesh_x(float delta_move_x)
    {
        this->translate.x = this->translate.x + delta_move_x;
    }


    void Mesh::move_mesh_y(float delta_move_y)
    {
        this->translate.y = this->translate.y + delta_move_y;
    }


    void Mesh::move_mesh_z(float delta_move_z)
    {
        this->translate.y = this->translate.y + delta_move_z;
    }


    //====================SCALE====================
    void Mesh::scale_mesh(glm::vec3& scale)
    {
        this->scale = glm::vec3(
            this->scale.x * scale.x,
            this->scale.y * scale.y,
            this->scale.z * scale.z
        );
    }


    void Mesh::scale_mesh(float scale_x, float scale_y, float scale_z)
    {
        this->scale = glm::vec3(
            this->scale.x * scale_x,
            this->scale.y * scale_y,
            this->scale.z * scale_z
        );
    }


    void Mesh::scale_mesh_x(float scale_x)
    {
        this->scale.x = this->scale.x * scale_x;
    }


    void Mesh::scale_mesh_y(float scale_y)
    {
        this->scale.y = this->scale.y * scale_y;
    }


    void Mesh::scale_mesh_z(float scale_z)
    {
        this->scale.z = this->scale.z * scale_z;
    }


    //====================ROTATE====================
    void Mesh::rotate_mesh(glm::vec3& delta_rotate)
    {
        this->rotate = glm::vec3(
            this->rotate.x + delta_rotate.x,
            this->rotate.y + delta_rotate.y,
            this->rotate.z + delta_rotate.z
        );
    }


    void Mesh::rotate_mesh(float delta_angle_x, float delta_angle_y, float delta_angle_z)
    {
        this->rotate = glm::vec3(
            this->rotate.x + delta_angle_x,
            this->rotate.y + delta_angle_y,
            this->rotate.z + delta_angle_z
        );
    }


    void Mesh::rotate_mesh_x(float delta_angle_x)
    {
        this->rotate.x = this->rotate.x + delta_angle_x;
    }


    void Mesh::rotate_mesh_y(float delta_angle_y)
    {
        this->rotate.y = this->rotate.y + delta_angle_y;
    }


    void Mesh::rotate_mesh_z(float delta_angle_z)
    {
        this->rotate.z = this->rotate.z + delta_angle_z;
    }
}