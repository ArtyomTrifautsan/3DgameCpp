#include "AiryEngineCore/Rendering/OpenGL/Model3D.hpp"

#include "AiryEngineCore/Rendering/OpenGL/Mesh.hpp"
#include "AiryEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "AiryEngineCore/Rendering/OpenGL/VertexBuffer.hpp"


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

    // void Model3D::draw(std::shared_ptr<ShaderProgram> shader_program, Camera& camera, const glm::vec3& light_source_position, const glm::vec3& light_source_color)
    // {
    //     for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
    //         current_mesh->draw(shader_program, camera, light_source_position, light_source_color);
    // }

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

    void Model3D::set_scale(float scale_x, float scale_y, float scale_z)
    {
        if (scale_x > 0) this->scale[0] = scale_x;
        if (scale_y > 0) this->scale[1] = scale_y;
        if (scale_z > 0) this->scale[2] = scale_z;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_scale(scale_x, scale_y, scale_z);
    }

    void Model3D::set_rotate(float angle_x, float angle_y, float angle_z)
    {
        this->rotate[0] = angle_x;
        this->rotate[1] = angle_y;
        this->rotate[2] = angle_z;
        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_rotate(angle_x, angle_y, angle_z);
    }

    void Model3D::set_translate(float translate_x, float translate_y, float translate_z)
    {
        this->translate[0] = translate_x;
        this->translate[1] = translate_y;
        this->translate[2] = translate_z;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_translate(translate_x, translate_y, translate_z);
    }

    void Model3D::set_translate_x(float value)
    {
        this->translate[0] = value;
        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_translate_x(value);
    }

    void Model3D::set_translate_y(float value)
    {
        this->translate[1] = value;
        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_translate_y(value);
    }

    void Model3D::set_translate_z(float value)
    {
        this->translate[2] = value;
        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_translate_z(value);
    }

    void Model3D::move_model(float delta_move_x, float delta_move_y, float delta_move_z)
    {
        this->translate[0] = this->translate[0] + delta_move_x;
        this->translate[1] = this->translate[1] + delta_move_y;
        this->translate[2] = this->translate[2] + delta_move_z;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_translate(this->translate[0], this->translate[1], this->translate[2]);
    }

    // void Model3D::move_model_x(float delta_move_x);
    // void Model3D::move_model_y(float delta_move_y);
    // void Model3D::move_model_z(float delta_move_z);

    void Model3D::rotate_model(float delta_angle_x, float delta_angle_y, float delta_angle_z)
    {
        this->rotate[0] = this->rotate[0] + delta_angle_x;
        this->rotate[1] = this->rotate[1] + delta_angle_y;
        this->rotate[2] = this->rotate[2] + delta_angle_z;

        for (std::shared_ptr<Mesh> current_mesh : this->meshes) 
            current_mesh->set_rotate(this->rotate[0], this->rotate[1], this->rotate[2]);
    }

    // void Model3D::rotate_x(float delta_angle_x);
    // void Model3D::rotate_y(float delta_angle_y);
    // void Model3D::rotate_z(float delta_angle_z);


    std::vector<float> __temp1 = {
        //    position                  index

        // FRONT
         1.0f,  1.0f,  1.0f,              // 0        Правая верхняя
         1.0f, -1.0f,  1.0f,              // 1        Правая нижняя
        -1.0f,  1.0f,  1.0f,              // 2        Левая верхняя
        -1.0f, -1.0f,  1.0f,              // 3        Левая нижняя

        // BACK                                  
         1.0f,  1.0f, -1.0f,              // 4        Правая верхняя
         1.0f, -1.0f, -1.0f,              // 5        Правая нижняя
        -1.0f,  1.0f, -1.0f,              // 6        Левая верхняя
        -1.0f, -1.0f, -1.0f              // 7        Левая нижняя
    };
    std::shared_ptr<std::vector<float>> studing_cube_vertices = std::make_shared<std::vector<float>>(std::move(__temp1));

    std::vector<unsigned int> __temp2 = {
        0, 1, 2, 2, 3, 1, // front
        4, 5, 6, 6, 7, 5, // back
        1, 0, 4, 4, 5, 1, // right
        3, 2, 6, 6, 7, 3, // left
        0, 2, 6, 6, 4, 0, // top
        1, 3, 7, 7, 5, 1  // bottom
    };
    std::shared_ptr<std::vector<unsigned int>> studing_cube_indices = std::make_shared<std::vector<unsigned int>>(std::move(__temp2));

    std::shared_ptr<CubeMesh> create_cube_mesh_from_points()
    {
        BufferLayout bufferLayout_vec3
        {
            ShaderDataType::Float3
        };

        std::shared_ptr<Material> material = std::make_shared<Material>();

        // std::shared_ptr<CubeMesh> mesh = std::make_shared<CubeMesh>(
        return std::make_shared<CubeMesh>(
            studing_cube_vertices,
            studing_cube_indices,
            bufferLayout_vec3,
            material
        );

        // std::vector<std::shared_ptr<CubeMesh>> _meshes = { mesh };

        // return std::make_shared<Model3D>(_meshes);
    }



    struct MeshData {
        std::shared_ptr<std::vector<float>> vertices;  // [x0,y0,z0, x1,y1,z1, ...]
        std::shared_ptr<std::vector<unsigned int>> indices;  // Пары индексов для GL_LINES
    };

    MeshData generateCubeWireframe(const int subdivisions = 4)
    {
        const int squaresPerEdge = subdivisions;
        const int vertsPerEdge = subdivisions + 1;
        MeshData mesh;
        mesh.vertices = std::make_shared<std::vector<float>>();
        mesh.indices = std::make_shared<std::vector<unsigned int>>();

        const int verticesPerEdge = squaresPerEdge + 1;
        const float step = 2.0f / squaresPerEdge; // Куб размером 2x2x2, центрирован в (0,0,0)

        // Обработка 6 граней куба
        for (int face = 0; face < 6; ++face) {
            const size_t baseIndex = mesh.vertices->size() / 3; // Базовый индекс текущей грани (в вершинах)

            // Генерация вершин для текущей грани
            for (int i = 0; i < verticesPerEdge; ++i) {
                float v = -1.0f + i * step;  // Координата вдоль оси V
                for (int j = 0; j < verticesPerEdge; ++j) {
                    float u = -1.0f + j * step;  // Координата вдоль оси U

                    float x, y, z;
                    switch (face) {
                        case 0: // Правая грань (+X), снаружи смотрим в -X
                            x =  1.0f;
                            y =  u;
                            z =  v;
                            break;
                        case 1: // Левая грань (-X), снаружи смотрим в +X
                            x = -1.0f;
                            y = -u;  // Инверсия для сохранения CCW
                            z =  v;
                            break;
                        case 2: // Верхняя грань (+Y), снаружи смотрим в -Y
                            x =  u;
                            y =  1.0f;
                            z = -v;  // Инверсия для сохранения CCW
                            break;
                        case 3: // Нижняя грань (-Y), снаружи смотрим в +Y
                            x =  u;
                            y = -1.0f;
                            z =  v;
                            break;
                        case 4: // Передняя грань (+Z), снаружи смотрим в -Z
                            x =  u;
                            y =  v;
                            z =  1.0f;
                            break;
                        case 5: // Задняя грань (-Z), снаружи смотрим в +Z
                            x = -u;  // Инверсия для сохранения CCW
                            y =  v;
                            z = -1.0f;
                            break;
                        default:
                            continue;
                    }
                    // Добавляем вершину как три отдельных float
                    mesh.vertices->push_back(x);
                    mesh.vertices->push_back(y);
                    mesh.vertices->push_back(z);
                }
            }

            // Генерация индексов для текущей грани
            for (int i = 0; i < squaresPerEdge; ++i) {
                for (int j = 0; j < squaresPerEdge; ++j) {
                    unsigned int v0 = static_cast<unsigned int>(baseIndex + i * verticesPerEdge + j);
                    unsigned int v1 = static_cast<unsigned int>(baseIndex + i * verticesPerEdge + (j + 1));
                    unsigned int v2 = static_cast<unsigned int>(baseIndex + (i + 1) * verticesPerEdge + (j + 1));
                    unsigned int v3 = static_cast<unsigned int>(baseIndex + (i + 1) * verticesPerEdge + j);

                    // Два треугольника на квадрат (обход против часовой стрелки)
                    if (face < 6)
                    {
                        mesh.indices->push_back(v0);
                        mesh.indices->push_back(v1);
                        mesh.indices->push_back(v2);

                        mesh.indices->push_back(v0);
                        mesh.indices->push_back(v2);
                        mesh.indices->push_back(v3);
                    }
                    else
                    {
                        mesh.indices->push_back(v2);
                        mesh.indices->push_back(v1);
                        mesh.indices->push_back(v0);

                        mesh.indices->push_back(v3);
                        mesh.indices->push_back(v2);
                        mesh.indices->push_back(v0);
                    }
                }
            }
        }

        // std::cout << 

        return mesh;
    }

    std::shared_ptr<CubeMesh> create_cube_mesh_from_points_2()
    {
        BufferLayout bufferLayout_vec3
        {
            ShaderDataType::Float3
        };

        MeshData mesh = generateCubeWireframe(4);

        std::shared_ptr<Material> material = std::make_shared<Material>();

        // std::shared_ptr<CubeMesh> mesh = std::make_shared<CubeMesh>(
        return std::make_shared<CubeMesh>(
            mesh.vertices,
            mesh.indices,
            bufferLayout_vec3,
            material
        );

        // std::vector<std::shared_ptr<CubeMesh>> _meshes = { mesh };

        // return std::make_shared<Model3D>(_meshes);
    }

    
    /*

    MeshData generateCubeWireframe(const int subdivisions = 4)
    {
        const int squaresPerEdge = subdivisions;
        const int vertsPerEdge = subdivisions + 1;
        MeshData mesh;
        mesh.vertices = std::make_shared<std::vector<float>>();
        mesh.indices = std::make_shared<std::vector<unsigned int>>();

        const int verticesPerEdge = squaresPerEdge + 1;
        const float step = 2.0f / squaresPerEdge; // Куб размером 2x2x2, центрирован в (0,0,0)

        // Обработка 6 граней куба
        for (int face = 0; face < 6; ++face) {
            const size_t baseIndex = mesh.vertices->size() / 6; // Базовый индекс текущей грани (в вершинах)

            // Нормаль для текущей грани куба
            float faceNx, faceNy, faceNz;
            switch (face) {
                case 0: faceNx =  1.0f; faceNy =  0.0f; faceNz =  0.0f; break; // +X
                case 1: faceNx = -1.0f; faceNy =  0.0f; faceNz =  0.0f; break; // -X
                case 2: faceNx =  0.0f; faceNy =  1.0f; faceNz =  0.0f; break; // +Y
                case 3: faceNx =  0.0f; faceNy = -1.0f; faceNz =  0.0f; break; // -Y
                case 4: faceNx =  0.0f; faceNy =  0.0f; faceNz =  1.0f; break; // +Z
                case 5: faceNx =  0.0f; faceNy =  0.0f; faceNz = -1.0f; break; // -Z
                default: faceNx = 0.0f; faceNy = 0.0f; faceNz = 0.0f; break;
            }

            // Генерация вершин для текущей грани
            for (int i = 0; i < verticesPerEdge; ++i) {
                float v = -1.0f + i * step;  // Координата вдоль оси V
                for (int j = 0; j < verticesPerEdge; ++j) {
                    float u = -1.0f + j * step;  // Координата вдоль оси U

                    float x, y, z;
                    switch (face) {
                        case 0: // Правая грань (+X), снаружи смотрим в -X
                            x =  1.0f;
                            y =  u;
                            z =  v;
                            break;
                        case 1: // Левая грань (-X), снаружи смотрим в +X
                            x = -1.0f;
                            y = -u;  // Инверсия для сохранения CCW
                            z =  v;
                            break;
                        case 2: // Верхняя грань (+Y), снаружи смотрим в -Y
                            x =  u;
                            y =  1.0f;
                            z = -v;  // Инверсия для сохранения CCW
                            break;
                        case 3: // Нижняя грань (-Y), снаружи смотрим в +Y
                            x =  u;
                            y = -1.0f;
                            z =  v;
                            break;
                        case 4: // Передняя грань (+Z), снаружи смотрим в -Z
                            x =  u;
                            y =  v;
                            z =  1.0f;
                            break;
                        case 5: // Задняя грань (-Z), снаружи смотрим в +Z
                            x = -u;  // Инверсия для сохранения CCW
                            y =  v;
                            z = -1.0f;
                            break;
                        default:
                            continue;
                    }
                    // Добавляем вершину как три отдельных float
                    mesh.vertices->push_back(x);
                    mesh.vertices->push_back(y);
                    mesh.vertices->push_back(z);

                    // Нормаль вершины (пока — нормаль грани)
                    mesh.vertices->push_back(faceNx);
                    mesh.vertices->push_back(faceNy);
                    mesh.vertices->push_back(faceNz);
                }
            }

            // Генерация индексов для текущей грани
            for (int i = 0; i < squaresPerEdge; ++i) {
                for (int j = 0; j < squaresPerEdge; ++j) {
                    unsigned int v0 = static_cast<unsigned int>(baseIndex + i * verticesPerEdge + j);
                    unsigned int v1 = static_cast<unsigned int>(baseIndex + i * verticesPerEdge + (j + 1));
                    unsigned int v2 = static_cast<unsigned int>(baseIndex + (i + 1) * verticesPerEdge + (j + 1));
                    unsigned int v3 = static_cast<unsigned int>(baseIndex + (i + 1) * verticesPerEdge + j);

                    // Два треугольника на квадрат (обход против часовой стрелки)
                    if (face < 6)
                    {
                        mesh.indices->push_back(v0);
                        mesh.indices->push_back(v1);
                        mesh.indices->push_back(v2);

                        mesh.indices->push_back(v0);
                        mesh.indices->push_back(v2);
                        mesh.indices->push_back(v3);
                    }
                    else
                    {
                        mesh.indices->push_back(v2);
                        mesh.indices->push_back(v1);
                        mesh.indices->push_back(v0);

                        mesh.indices->push_back(v3);
                        mesh.indices->push_back(v2);
                        mesh.indices->push_back(v0);
                    }
                }
            }
        }

        // std::cout << 

        return mesh;
    }

    std::shared_ptr<CubeMesh> create_cube_mesh_from_points_2()
    {
        BufferLayout bufferLayout_vec3
        {
            ShaderDataType::Float3,
            ShaderDataType::Float3
        };

        MeshData mesh = generateCubeWireframe(4);

        std::shared_ptr<Material> material = std::make_shared<Material>();

        // std::shared_ptr<CubeMesh> mesh = std::make_shared<CubeMesh>(
        return std::make_shared<CubeMesh>(
            mesh.vertices,
            mesh.indices,
            bufferLayout_vec3,
            material
        );

        // std::vector<std::shared_ptr<CubeMesh>> _meshes = { mesh };

        // return std::make_shared<Model3D>(_meshes);
    }

    */
}