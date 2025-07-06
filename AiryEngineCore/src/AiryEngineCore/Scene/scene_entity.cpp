#include "scene_entity.hpp"

#include <AiryEngineCore/Rendering/OpenGL/Model3D.hpp>
#include <AiryEngineCore/Rendering/OpenGL/LightSource.hpp>
#include <AiryEngineCore/Physics/SolidObjects/CubeSolid.hpp>


namespace AiryEngine {

    SceneEntity::SceneEntity()
    {
        this->models = std::make_shared<std::vector<std::shared_ptr<Model3D>>>();
        this->solid_cubes = std::make_shared<std::vector<std::shared_ptr<SolidCube>>>();
        this->light_sources = std::make_shared<std::vector<std::shared_ptr<LightSource>>>();

        SceneEntity::number_of_scene_entities += 1;

        // ПОТЕНЦИАЛЬНО НЕ УНИКАЛЬНОЕ ИМЯ
        this->name = "scene_entity_" + static_cast<char>(SceneEntity::number_of_scene_entities);
    }


    SceneEntity::SceneEntity(std::shared_ptr<std::vector<std::shared_ptr<Model3D>>> models,
                            std::shared_ptr<std::vector<std::shared_ptr<SolidCube>>> solid_cubes,
                            std::shared_ptr<std::vector<std::shared_ptr<LightSource>>> light_sources)
    {
        this->models = models;
        this->solid_cubes = solid_cubes;
        this->light_sources = light_sources;

        SceneEntity::number_of_scene_entities += 1;

        // ПОТЕНЦИАЛЬНО НЕ УНИКАЛЬНОЕ ИМЯ
        this->name = "scene_entity_" + static_cast<char>(SceneEntity::number_of_scene_entities);
    }


    SceneEntity::~SceneEntity()
    {
        // Вот что тут должно происходить ???

        SceneEntity::number_of_scene_entities -= 1;
    }


    bool change_name(std::string new_name)
    {
        // Имя каждой сущности должно быть уникальным!!! Как это обеспечит?
        // Нужно завести статическую переменную, хранящую множетсво всех имен 
        // у сущностей. При создании нового имени проверяем, есть ли оно в 
        // множестве. Если его нет, то успешно меняем имя, добавляем его в 
        // множество и возвращаем true, это значит что имя успешно поменялось.
        // Если имя уже существует, то возвращаем false и ничего не меняем.
    }


    void SceneEntity::add_model(std::shared_ptr<Model3D> model)
    {
        this->models->push_back(model);
    }


    void SceneEntity::add_solid_cube(std::shared_ptr<SolidCube> solid_cube)
    {
        this->solid_cubes->push_back(solid_cube);
    }


    void SceneEntity::add_light_source(std::shared_ptr<LightSource> light_source)
    {
        this->light_sources->push_back(light_source);
    }


    void SceneEntity::remove_model(std::shared_ptr<Model3D> model)
    {
        for (std::vector<std::shared_ptr<Model3D>>::iterator curr_model_ptr = this->models->begin(); 
            curr_model_ptr != this->models->end();)
        {
            if (*curr_model_ptr == model)
                curr_model_ptr = this->models->erase(curr_model_ptr);
            else
                ++curr_model_ptr;
        }
    }


    void SceneEntity::remove_solid_cube(std::shared_ptr<SolidCube> solid_cube)
    {
        for (std::vector<std::shared_ptr<SolidCube>>::iterator curr_solid_cube_ptr = this->solid_cubes->begin(); 
            curr_solid_cube_ptr != this->solid_cubes->end();)
        {
            if (*curr_solid_cube_ptr == solid_cube)
                curr_solid_cube_ptr = this->solid_cubes->erase(curr_solid_cube_ptr);
            else
                ++curr_solid_cube_ptr;
        }
    }


    void SceneEntity::remove_light_source(std::shared_ptr<LightSource> light_source)
    {
        for (std::vector<std::shared_ptr<LightSource>>::iterator curr_light_source_ptr = this->light_sources->begin(); 
            curr_light_source_ptr != this->light_sources->end();)
        {
            if (*curr_light_source_ptr == light_source)
                curr_light_source_ptr = this->light_sources->erase(curr_light_source_ptr);
            else
                ++curr_light_source_ptr;
        }
    }


    void SceneEntity::set_is_visible(bool is_visible)
    {
        this->is_visible = is_visible;
    }


    void SceneEntity::set_is_solid(bool is_solid)
    {
        this->is_solid = is_solid;
    }


    //====================SET TRANSLATE====================
    void SceneEntity::set_translate(const glm::vec3 translate)
    {
        this->translate.x = translate.x;
        this->translate.y = translate.y;
        this->translate.z = translate.z;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->set_translate(translate);
        
        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->set_translate(translate);
        
        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->set_translate(translate);
    }


    void SceneEntity::set_translate(float translate_x, float translate_y, float translate_z)
    {
        this->translate.x = translate_x;
        this->translate.y = translate_y;
        this->translate.z = translate_z;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->set_translate(translate_x, translate_y, translate_z);
        
        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->set_translate(translate_x, translate_y, translate_z);
        
        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->set_translate(translate_x, translate_y, translate_z);
    }


    void SceneEntity::set_translate_x(float translate_x)
    {
        this->translate.x = translate_x;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->set_translate_x(translate_x);
        
        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->set_translate_x(translate_x);
        
        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->set_translate_x(translate_x);
    }


    void SceneEntity::set_translate_y(float translate_y)
    {
        this->translate.y = translate_y;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->set_translate_y(translate_y);
        
        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->set_translate_y(translate_y);

        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->set_translate_y(translate_y);
    }


    void SceneEntity::set_translate_z(float translate_z)
    {
        this->translate.z = translate_z;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->set_translate_z(translate_z);
        
        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->set_translate_z(translate_z);

        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->set_translate_z(translate_z);
    }


    //====================SET SCALE====================
    void SceneEntity::set_scale(const glm::vec3 scale)
    {
        this->scale.x = scale.x;
        this->scale.y = scale.y;
        this->scale.z = scale.z;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->set_scale(scale);
        
        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->set_scale(scale);
        
        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->set_scale(scale);
    }


    void SceneEntity::set_scale(float scale_x, float scale_y, float scale_z)
    {
        this->scale.x = scale_x;
        this->scale.y = scale_y;
        this->scale.z = scale_z;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->set_scale(scale_x, scale_y, scale_z);
        
        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->set_scale(scale_x, scale_y, scale_z);
        
        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->set_scale(scale_x, scale_y, scale_z);
    }


    void SceneEntity::set_scale_x(float scale_x)
    {
        this->scale.x = scale_x;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->set_scale_x(scale_x);
        
        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->set_scale_x(scale_x);
        
        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->set_scale_x(scale_x);
    }


    void SceneEntity::set_scale_y(float scale_y)
    {
        this->scale.y = scale_y;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->set_scale_y(scale_y);
        
        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->set_scale_y(scale_y);

        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->set_scale_y(scale_y);
    }


    void SceneEntity::set_scale_z(float scale_z)
    {
        this->scale.z = scale_z;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->set_scale_z(scale_z);
        
        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->set_scale_z(scale_z);

        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->set_scale_z(scale_z);
    }


    //====================SET ROTATE====================
    void SceneEntity::set_rotate(const glm::vec3 rotate)
    {
        this->rotate.x = rotate.x;
        this->rotate.y = rotate.y;
        this->rotate.z = rotate.z;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->set_rotate(rotate);
        
        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->set_rotate(rotate);
        
        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->set_rotate(rotate);
    }


    void SceneEntity::set_rotate(float rotate_x, float rotate_y, float rotate_z)
    {
        this->rotate.x = rotate_x;
        this->rotate.y = rotate_y;
        this->rotate.z = rotate_z;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->set_rotate(rotate_x, rotate_y, rotate_z);

        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->set_rotate(rotate_x, rotate_y, rotate_z);

        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->set_rotate(rotate_x, rotate_y, rotate_z);
    }


    void SceneEntity::set_rotate_x(float rotate_x)
    {
        this->rotate.x = rotate_x;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->set_rotate_x(rotate_x);
        
        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->set_rotate_x(rotate_x);
        
        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->set_rotate_x(rotate_x);
    }


    void SceneEntity::set_rotate_y(float rotate_y)
    {
        this->rotate.y = rotate_y;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->set_rotate_y(rotate_y);
        
        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->set_rotate_y(rotate_y);
        
        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->set_rotate_y(rotate_y);
    }


    void SceneEntity::set_rotate_z(float rotate_z)
    {
        this->rotate.z = rotate_z;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->set_rotate_z(rotate_z);
        
        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->set_rotate_z(rotate_z);
        
        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->set_rotate_z(rotate_z);
    }    


    //====================MOVE====================
    void SceneEntity::move_scene_entity(const glm::vec3 delta)
    {
        this->translate.x = this->translate.x + delta.x;
        this->translate.y = this->translate.y + delta.y;
        this->translate.z = this->translate.z + delta.z;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->move_model(delta);

        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->move_cube_solid(delta);

        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->move_light_source(delta);
    }


    void SceneEntity::move_scene_entity(float delta_move_x, float delta_move_y, float delta_move_z)
    {
        this->translate.x = this->translate.x + delta_move_x;
        this->translate.y = this->translate.y + delta_move_y;
        this->translate.z = this->translate.z + delta_move_z;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->move_model(delta_move_x, delta_move_y, delta_move_z);

        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->move_cube_solid(delta_move_x, delta_move_y, delta_move_z);

        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->move_light_source(delta_move_x, delta_move_y, delta_move_z);
    }


    void SceneEntity::move_scene_entity_x(float delta_move_x)
    {
        this->translate.x = this->translate.x + delta_move_x;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->move_model_x(delta_move_x);

        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->move_cube_solid_x(delta_move_x);

        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->move_light_source_x(delta_move_x);
    }


    void SceneEntity::move_scene_entity_y(float delta_move_y)
    {
        this->translate.y = this->translate.y + delta_move_y;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->move_model_y(delta_move_y);

        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->move_cube_solid_y(delta_move_y);

        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->move_light_source_y(delta_move_y);
    }


    void SceneEntity::move_scene_entity_z(float delta_move_z)
    {
        this->translate.z = this->translate.z + delta_move_z;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->move_model_y(delta_move_z);

        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->move_cube_solid_y(delta_move_z);

        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->move_light_source_y(delta_move_z);
    }


    //====================SCALE====================
    void SceneEntity::scale_scene_entity(const glm::vec3 scale)
    {
        this->scale.x = this->scale.x * scale.x;
        this->scale.y = this->scale.y * scale.y;
        this->scale.z = this->scale.z * scale.z;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->scale_model(scale);

        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->scale_cube_solid(scale);

        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->scale_light_source(scale);
    }


    void SceneEntity::scale_scene_entity(float scale_x, float scale_y, float scale_z)
    {
        this->scale.x = this->scale.x * scale_x;
        this->scale.y = this->scale.y * scale_y;
        this->scale.z = this->scale.z * scale_z;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->scale_model(scale_x, scale_y, scale_z);

        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->scale_cube_solid(scale_x, scale_y, scale_z);

        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->scale_light_source(scale_x, scale_y, scale_z);
    }


    void SceneEntity::scale_scene_entity_x(float scale_x)
    {
        this->scale.x = this->scale.x * scale_x;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->scale_model_x(scale_x);

        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->scale_cube_solid_x(scale_x);

        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->scale_light_source_x(scale_x);
    }


    void SceneEntity::scale_scene_entity_y(float scale_y)
    {
        this->scale.y = this->scale.y * scale_y;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->scale_model_y(scale_y);

        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->scale_cube_solid_y(scale_y);

        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->scale_light_source_y(scale_y);
    }


    void SceneEntity::scale_scene_entity_z(float scale_z)
    {
        this->scale.z = this->scale.z * scale_z;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->scale_model_z(scale_z);

        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->scale_cube_solid_z(scale_z);

        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->scale_light_source_z(scale_z);
    }


    //====================ROTATE====================
    void SceneEntity::rotate_scene_entity(const glm::vec3 delta_rotate)
    {
        this->rotate.x = this->rotate.x + delta_rotate.x;
        this->rotate.y = this->rotate.y + delta_rotate.y;
        this->rotate.z = this->rotate.z + delta_rotate.z;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->rotate_model(delta_rotate);

        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->rotate_cube_solid(delta_rotate);

        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->rotate_light_source(delta_rotate);
    }


    void SceneEntity::rotate_scene_entity(float delta_angle_x, float delta_angle_y, float delta_angle_z)
    {
        this->rotate.x = this->rotate.x + delta_angle_x;
        this->rotate.y = this->rotate.y + delta_angle_y;
        this->rotate.z = this->rotate.z + delta_angle_z;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->rotate_model(delta_angle_x, delta_angle_y, delta_angle_z);

        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->rotate_cube_solid(delta_angle_x, delta_angle_y, delta_angle_z);

        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->rotate_light_source(delta_angle_x, delta_angle_y, delta_angle_z);
    }


    void SceneEntity::rotate_scene_entity_x(float delta_angle_x)
    {
        this->rotate.x = this->rotate.x + delta_angle_x;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->rotate_model_x(delta_angle_x);

        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->rotate_cube_solid_x(delta_angle_x);

        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->rotate_light_source_x(delta_angle_x);
    }


    void SceneEntity::rotate_scene_entity_y(float delta_angle_y)
    {
        this->rotate.y = this->rotate.y + delta_angle_y;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->rotate_model_y(delta_angle_y);

        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->rotate_cube_solid_y(delta_angle_y);

        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->rotate_light_source_y(delta_angle_y);
    }


    void SceneEntity::rotate_scene_entity_z(float delta_angle_z)
    {
        this->rotate.z = this->rotate.z + delta_angle_z;

        for (std::shared_ptr<Model3D> current_model : *this->models)
            current_model->rotate_model_z(delta_angle_z);

        for (std::shared_ptr<SolidCube> current_solid_cube : *this->solid_cubes) 
            current_solid_cube->rotate_cube_solid_z(delta_angle_z);

        for (std::shared_ptr<LightSource> current_light_source : *this->light_sources)
            current_light_source->rotate_light_source_z(delta_angle_z);
    }

}