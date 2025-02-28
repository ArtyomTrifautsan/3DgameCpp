/*

Объект класса Square - это квадрат дороги со всеми игровыми объектами на ней.

Square содержит:
-Вектор барьеров
-Вектор монеток
-ОДНУ канистру (не всекда)

что должен уметь объект класса Square:
+Генерация игровых объектов. На вход подается строка, в которой указаны координаты 
 монет, препятствий и канистры (если есть). Метод парсит эту строку и генерирует
 объекты в тех координатах
+Двигаться в направлении экрана (move back)
+Удаляться после того, как уедет за пределы экрана


*/


#pragma once

// Файлы движка
#include <AiryEngineCore/ResourceManager.hpp>


// Файлы игры
#include "game_objects/road.hpp"
#include "game_objects/barrier.hpp"
#include "game_objects/coin.hpp"
#include "game_objects/fuel_canister.hpp"


// Системные библиотеки
#include <memory>
#include <string>
#include <vector>
#include <utility>


class Square {
public:
    // Квадрат без объектов
    Square(std::shared_ptr<AiryEngine::ResourceManager> resource_manager);      

    // Квадрат определенного типа
    Square(std::shared_ptr<AiryEngine::ResourceManager> resource_manager, std::string square_template);

    std::shared_ptr<Road> get_road() const { return this->road; }
    std::shared_ptr<std::vector<std::shared_ptr<Barrier>>> get_barriers() const { return this->barriers; }
    std::shared_ptr<std::vector<std::shared_ptr<Coin>>> get_coins() const { return this->coins; }
    std::shared_ptr<std::vector<std::shared_ptr<FuelCanister>>> get_fuel_canisters() const { return this->fuel_canisters; }

    int get_number_of_barriers() const { return this->number_of_barriers; }
    int get_number_of_coins() const { return this->number_of_coins; }
    int get_number_of_fuel_canisters() const { return this->number_of_fuel_canisters; }

    void move_along_z_axis(float step, float offset, float number_of_roads);

    void rotate_coins_and_fuel_canisters(float rotate_delta_angle);

    bool get_visible() const { return this->visible; }

    bool is_out_of_visible_area(float road_offset);

private:
    void generate_coords_by_template(std::string square_template,
                                    std::vector<std::pair<float, float>>* barrier_coords,
                                    std::vector<std::pair<float, float>>* coins_coords,
                                    std::vector<std::pair<float, float>>* fuel_canisters_coords);

    void create_road(std::shared_ptr<AiryEngine::ResourceManager> resource_manager);
    void create_barriers(std::shared_ptr<AiryEngine::ResourceManager> resource_manager,
                            const std::vector<std::pair<float, float>>& barriers_coords);
    void create_coins(std::shared_ptr<AiryEngine::ResourceManager> resource_manager,
                        const std::vector<std::pair<float, float>>& coins_coords);
    void create_fuel_canisters(std::shared_ptr<AiryEngine::ResourceManager> resource_manager,
                                const std::vector<std::pair<float, float>>& fuel_canisters_coords);

    void move_along_z_axis_road(float step, float offset, float number_of_roads);
    void move_along_z_axis_barriers(float step, float offset, float number_of_roads);
    void move_along_z_axis_coins(float step, float offset, float number_of_roads);
    void move_along_z_axis_fuel_canisters(float step, float offset, float number_of_roads);


    float z_position = 0;

    std::shared_ptr<Road> road;

    std::shared_ptr<std::vector<std::shared_ptr<Barrier>>> barriers;
    int number_of_barriers = 0;

    std::shared_ptr<std::vector<std::shared_ptr<Coin>>> coins;
    int number_of_coins = 0;

    std::shared_ptr<std::vector<std::shared_ptr<FuelCanister>>> fuel_canisters;
    int number_of_fuel_canisters = 0;

    bool visible = true;
};