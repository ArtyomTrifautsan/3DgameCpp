#pragma once

#include <string>
#include <vector>
#include <memory>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>


namespace AiryEngine {

    class Camera;
    class ShaderProgram;
    class BufferLayout;
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;
    class Texture2D;


    //typedef std::map<std::string, std::shared_ptr<Material>> MaterialsMap;

    struct Material
    {
        std::string name;
        glm::vec3 ambient_color;
        glm::vec3 diffuse_color;
        glm::vec3 specular_color;
        int shininess;
        std::string diffuse_map;
        bool has_duffuse_map = false;
        float alpha_channel = 1.0;
    };


    class Mesh 
    {
    public:
        Mesh(std::shared_ptr<std::vector<float>> vertices, 
                std::shared_ptr<std::vector<unsigned int>> indices, 
                std::shared_ptr<Material> material);

        std::shared_ptr<Material> get_material() const { return this->material; }
        std::shared_ptr<Texture2D> get_texture() const { return this->texture; }
        std::shared_ptr<VertexArray> get_vertex_array() const { return this->vertex_array; }

        bool get_has_texture() const { return this->has_texture; };

        // void get_scale(float (&_scale)[3]) const;
        // void get_rotate(float (&_rotate)[3]) const;
        // void get_translate(float (&_translate)[3]) const;

        float get_ambiant_factor() const { return this->ambiant_factor; }   // Temporary solution
        float get_diffuse_factor() const { return this->diffuse_factor; }   // Temporary solution
        float get_specular_factor() const { return this->specular_factor; }     //Temporary solution
        float get_shininess() const { return this->shininess; }     // Temporary solution

        void set_texture(std::shared_ptr<Texture2D> texture);
        void set_has_texture(bool has_texture);
        void set_material(std::shared_ptr<Material> material);
        void set_diffuse_color(float r, float g, float b);

        void set_translate(glm::vec3& translate);
        void set_translate(float translate_x, float translate_y, float translate_z);
        void set_translate_x(float translate_x);
        void set_translate_y(float translate_y);
        void set_translate_z(float translate_z);

        void set_scale(glm::vec3& scale);
        void set_scale(float scale_x, float scale_y, float scale_z);
        void set_scale_x(float scale_x);
        void set_scale_y(float scale_y);
        void set_scale_z(float scale_z);

        void set_rotate(glm::vec3& rotate);
        void set_rotate(float rotate_x, float rotate_y, float rotate_z);
        void set_rotate_x(float rotate_x);
        void set_rotate_y(float rotate_y);
        void set_rotate_z(float rotate_z);

        void move_mesh(glm::vec3& delta);
        void move_mesh(float delta_move_x, float delta_move_y, float delta_move_z);
        void move_mesh_x(float delta_move_x);
        void move_mesh_y(float delta_move_y);
        void move_mesh_z(float delta_move_z);

        void scale_mesh(glm::vec3& scale);
        void scale_mesh(float scale_x, float scale_y, float scale_z);
        void scale_mesh_x(float scale_x);
        void scale_mesh_y(float scale_y);
        void scale_mesh_z(float scale_z);

        void rotate_mesh(glm::vec3& delta_rotate);
        void rotate_mesh(float delta_angle_x, float delta_angle_y, float delta_angle_z);
        void rotate_mesh_x(float delta_angle_x);
        void rotate_mesh_y(float delta_angle_y);
        void rotate_mesh_z(float delta_angle_z);

        glm::vec3 get_translate() const { return this->translate; }
        glm::vec3 get_scale() const { return this->scale; }
        glm::vec3 get_rotate() const { return this->rotate; }
    
    private:
        std::shared_ptr<std::vector<float>> vertices;
        std::shared_ptr<std::vector<unsigned int>> indices;
        std::shared_ptr<Material> material;
        std::shared_ptr<Texture2D> texture;

        bool has_texture = false;

        std::shared_ptr<VertexArray> vertex_array;
        std::shared_ptr<VertexBuffer> vertex_buffer;
        std::shared_ptr<IndexBuffer> index_buffer;

        // float scale[3] = { 1.0f, 1.0f, 1.0f };
        // float rotate[3] = { 0.0f, 0.0f, 0.0f };
        // float translate[3] = { 0.0f, 0.0f, 0.0f };

        glm::vec3 translate = { 0, 0, 0 };
        glm::vec3 scale = { 1, 1, 1 };
        glm::vec3 rotate = { 0, 0, 0 };

        float ambiant_factor = 0.1f;        // Temporary solution
        float diffuse_factor = 1.0f;        // Temporary solution
        float specular_factor = 0.5f;        // Temporary solution
        float shininess = 32.0f;        // Temporary solution

        void setup_render_data_mesh();
}; 

}