/*

Класс GameRound занимается игровой логикой:
1) Взаимодейтсвие игровых объектов;
2) Поведение отдельных объектов;

Класс GameRound НЕ занимается:
1) Отрисовкой игровых объектов


*/


#pragma once

// Файлы движка
#include <AiryEngineCore/Physics/CollisionDetector.hpp>

#include <AiryEngineCore/Rendering/OpenGL/Model3D.hpp>

#include <AiryEngineCore/ResourceManager.hpp>
#include <AiryEngineCore/Renderer.hpp>
#include <AiryEngineCore/Camera.hpp>
#include <AiryEngineCore/timer.hpp>


// Файлы игры
#include "game_objects/car.hpp"
#include "game_objects/road.hpp"
#include "game_objects/barrier.hpp"
#include "game_objects/coin.hpp"
#include "game_objects/fuel_canister.hpp"
#include "square.hpp"


// Системные библиотеки
#include <memory>
#include <string>
#include <vector>

// Нужны для таймера
#include <chrono>
#include <thread>


class GameRound {
public:
    GameRound(std::shared_ptr<AiryEngine::ResourceManager> resource_manager);

    void set_start_pos();

    void update_game_round();

    void handle_events();

    std::shared_ptr<Car> get_car() const { return this->car; }

    std::shared_ptr<std::vector<std::shared_ptr<Square>>> get_squares() const { return this->squares; }

private:
    void create_car(std::shared_ptr<AiryEngine::ResourceManager> resource_manager);
    void create_squares(std::shared_ptr<AiryEngine::ResourceManager> resource_manager);

    std::shared_ptr<Square> create_void_square(std::shared_ptr<AiryEngine::ResourceManager> resource_manager);
    std::shared_ptr<Square> create_random_square(std::shared_ptr<AiryEngine::ResourceManager> resource_manager);

    void set_car_start_pos();
    void set_squares_start_pos();

    void move_back_squares();

    void drive_car();

    void check_collisions();
    void check_barrier_collision();
    void check_coins_collision();
    void check_fuel_canister_collision();

    void create_square_types();
    // bool square_types = false;


    std::shared_ptr<Car> car;

    std::shared_ptr<std::vector<std::shared_ptr<Square>>> squares;
    int number_of_squares = 0;

    bool pause = false;
    bool able_to_change_pause = true;

    float road_offset = 4.317f * 2 - 0.1f;
    float game_objects_step = 0.17f;

    float rotate_delta_angle = 1.0f;

    std::shared_ptr<std::vector<std::string>> square_types;
};