#include "game_round.hpp"


#include <AiryEngineCore/Physics/CollisionDetector.hpp>
#include <AiryEngineCore/Physics/CollidingObjects/CubeCollidingObject.hpp>
#include <AiryEngineCore/Input.hpp>

#include <iostream>


GameRound::GameRound(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    // std::cout << "GameRound::start start" << std::endl;
    this->resource_manager = resource_manager;

    create_car(resource_manager);
    set_car_start_pos();

    this->square_template_defender = std::make_shared<SquareTemplateDefender>();
    create_start_squares(resource_manager);
    place_start_squares();

    // std::cout << "GameRound::start finish" << std::endl;
}


void GameRound::update_game_round()
{
    // std::cout << "GameRound::update_game_round start" << std::endl;

    if (!this->pause)
    {
        for (int i = 0; i < this->squares->size(); i++)
        {
            (*this->squares)[i]->move_along_z_axis(this->game_objects_step, this->road_offset, this->number_of_squares);
            (*this->squares)[i]->rotate_coins_and_fuel_canisters(this->rotate_delta_angle);

            // Если квадрат ушел за пределы видимой области, то удаляем его и 
            // создаём новый квадрат
            if ((*this->squares)[i]->is_out_of_visible_area(this->road_offset))
            {
                // СОЗДАТЬ КВАДРАТ
                (*this->squares)[i] = std::make_shared<Square>(
                    this->resource_manager,
                    this->square_template_defender->get_random_square_template()
                );

                // Размещаем его в самом конце
                (*this->squares)[i]->move_along_z_axis(this->road_offset * 9 * -1, this->road_offset, this->number_of_squares);
            }
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
        if (this->pause) this->pause = false;
        else this->pause = true;
        this->able_to_change_pause = false;
    }
    else 
    {
        this->able_to_change_pause = true;
    }
}




//==================================Create game objects==================================

void GameRound::create_car(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    this->car = std::make_shared<Car>(
        "CarModel",
        resource_manager
    );
}


void GameRound::create_start_squares(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    this->squares = std::make_shared<std::vector<std::shared_ptr<Square>>>();

    for (int i = 0; i < this->number_of_squares; i++)
    {
        std::shared_ptr<Square> curr_square = std::make_shared<Square>(
            resource_manager,
            this->square_template_defender->get_random_square_template()
        );
        this->squares->push_back(curr_square);
    }
}


void GameRound::place_start_squares()
{
    for (int i = 0; i < this->squares->size(); i++)
    {
        (*this->squares)[i]->move_along_z_axis(-this->road_offset * i, this->road_offset, this->number_of_squares);
    }
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
