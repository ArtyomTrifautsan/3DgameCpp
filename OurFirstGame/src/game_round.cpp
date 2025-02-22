#include "game_round.hpp"


#include <AiryEngineCore/Physics/CollisionDetector.hpp>
#include <AiryEngineCore/Physics/CollidingObjects/CubeCollidingObject.hpp>
#include <AiryEngineCore/Input.hpp>

#include <iostream>


GameRound::GameRound(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    // std::cout << "GameRound::start start" << std::endl;

    create_square_types();
    // std::cout << "GameRound::start square_types created" << std::endl;

    create_car(resource_manager);
    // std::cout << "GameRound::start car created" << std::endl;

    create_squares(resource_manager);
    // std::cout << "GameRound::start squares created" << std::endl;
    set_squares_start_pos();
    // std::cout << "GameRound::start start pos of squares defined" << std::endl;

    // std::cout << "GameRound::start finish" << std::endl;
}


void GameRound::update_game_round()
{
    // std::cout << "GameRound::update_game_round start" << std::endl;

    if (!this->pause)
    {
        // std::cout << "GameRound::update_game_round before cycle" << std::endl;
        for (std::shared_ptr<Square> curr_square : *this->squares)
        {
            curr_square->move_along_z_axis(this->game_objects_step, this->road_offset, this->number_of_squares);
            // std::cout << "GameRound::update_game_round move_along_z_axis" << std::endl;
            curr_square->rotate_coins_and_fuel_canister(this->rotate_delta_angle);
            // std::cout << "GameRound::update_game_round rotate_coins_and_fuel_canister" << std::endl;
        }
    }

    drive_car();

    check_collisions();

    // std::cout << "GameRound::update_game_round finish" << std::endl;
}


void GameRound::handle_events()
{
    if (AiryEngine::Input::IsKeyPressed(AiryEngine::KeyCode::KEY_C))
    {
        // std::cout << "Pause changed" << std::endl; 
        if (this->pause) this->pause = false;
        else this->pause = true;
        this->able_to_change_pause = false;
    }
    else 
    {
        this->able_to_change_pause = true;
    }
}


void GameRound::create_car(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    this->car = std::make_shared<Car>(
        "CarModel",
        resource_manager
    );
}


void GameRound::create_squares(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    // std::cout << "GameRound::create_squares start" << std::endl;

    this->squares = std::make_shared<std::vector<std::shared_ptr<Square>>>();

    for (int i = 0; i < 5; i++)
    {
        this->squares->push_back(create_void_square(resource_manager));
        this->squares->push_back(create_random_square(resource_manager));
    }

    // std::cout << "GameRound::create_squares finish" << std::endl;
}


void GameRound::set_squares_start_pos()
{
    for (int i = 0; i < this->squares->size(); i++)
    {
        (*this->squares)[i]->move_along_z_axis(this->road_offset * i * -1, this->road_offset, this->number_of_squares);
    }
}


std::shared_ptr<Square> GameRound::create_void_square(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    std::vector<std::pair<float, float>> barrier_coords;

    std::vector<std::pair<float, float>> coin_coords;

    std::vector<std::pair<float, float>> fuel_canister_coords;

    std::shared_ptr<Square> curr_square = std::make_shared<Square>(
        resource_manager,
        this->square_types,
        barrier_coords,
        coin_coords,
        fuel_canister_coords
    );

    this->number_of_squares += 1;

    return curr_square;
}


std::shared_ptr<Square> GameRound::create_random_square(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    std::shared_ptr<Square> curr_square = std::make_shared<Square>(
        resource_manager,
        this->square_types
    );

    this->number_of_squares += 1;

    return curr_square;
}


void GameRound::set_start_pos()
{
    set_car_start_pos();
}


void GameRound::set_car_start_pos()
{
    this->car->set_position(0.277f, 0, -1.8f);
}


void GameRound::drive_car()
{
    this->car->update_moving_state();
}


void GameRound::create_square_types()
{
    /*
    n - ничего (пустота)
    c - монетка
    b - барьер
    k - канистра
    */

    this->square_types = std::make_shared<std::vector<std::string>>();

    // С канистрой 
    this->square_types->push_back("bkb");
    this->square_types->push_back("kbb");
    this->square_types->push_back("bbk");

    // С монетками
    this->square_types->push_back("bcb");
    this->square_types->push_back("cbb");
    this->square_types->push_back("bbc");

    this->square_types->push_back("bcc");
    this->square_types->push_back("ccb");

    this->square_types->push_back("bcn");
    this->square_types->push_back("ncb");

    this->square_types->push_back("cbn");
    this->square_types->push_back("nbc");

    this->square_types->push_back("ccc");

    // С пустотой
    this->square_types->push_back("bnb");
    this->square_types->push_back("nbb");
    this->square_types->push_back("bbn");

    this->square_types->push_back("nbn");

    this->square_types->push_back("nnn");
}


void GameRound::check_collisions()
{
    std::shared_ptr<AiryEngine::CubeCollidingObject> car_coll_cube = this->car->get_colliding_cube();
    car_coll_cube->set_is_collided(false);

    check_barrier_collision();
    check_coins_collision();
    check_fuel_canister_collision();
}


void GameRound::check_barrier_collision()
{
    std::shared_ptr<AiryEngine::CubeCollidingObject> car_coll_cube = this->car->get_colliding_cube();

    for (std::shared_ptr<Square> curr_square : *this->squares)
    {
        for (std::shared_ptr<Barrier> barrier : *(curr_square->get_barriers()))
        {
            std::shared_ptr<AiryEngine::CubeCollidingObject> barrier_coll_cube = barrier->get_colliding_cube();
            barrier_coll_cube->set_is_collided(false);

            if (AiryEngine::CollisionDetector::cube_cube_collision(*car_coll_cube, *barrier_coll_cube))
            {
                car_coll_cube->set_is_collided(true);
                barrier_coll_cube->set_is_collided(true);
            }
        }
    }
}


void GameRound::check_coins_collision()
{
    std::shared_ptr<AiryEngine::CubeCollidingObject> car_coll_cube = this->car->get_colliding_cube();

    for (std::shared_ptr<Square> curr_square : *this->squares)
    {
        for (std::shared_ptr<Coin> coin : *(curr_square->get_coins()))
        {
            std::shared_ptr<AiryEngine::CubeCollidingObject> coin_coll_cube = coin->get_colliding_cube();
            coin_coll_cube->set_is_collided(false);

            if (AiryEngine::CollisionDetector::cube_cube_collision(*car_coll_cube, *coin_coll_cube))
            {
                car_coll_cube->set_is_collided(true);
                coin_coll_cube->set_is_collided(true);
            }
        }
    }
}


void GameRound::check_fuel_canister_collision()
{
    std::shared_ptr<AiryEngine::CubeCollidingObject> car_coll_cube = this->car->get_colliding_cube();

    for (std::shared_ptr<Square> curr_square : *this->squares)
    {
        for (std::shared_ptr<FuelCanister> fuel_canister : *(curr_square->get_fuel_canisters()))
        {
            std::shared_ptr<AiryEngine::CubeCollidingObject> fuel_canister_coll_cube = fuel_canister->get_colliding_cube();
            fuel_canister_coll_cube->set_is_collided(false);

            if (AiryEngine::CollisionDetector::cube_cube_collision(*car_coll_cube, *fuel_canister_coll_cube))
            {
                car_coll_cube->set_is_collided(true);
                fuel_canister_coll_cube->set_is_collided(true);
            }
        }
    }
}
