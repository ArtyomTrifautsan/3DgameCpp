#include "game_round.hpp"


#include <AiryEngineCore/Physics/CollisionDetector.hpp>
#include <AiryEngineCore/Physics/CollidingObjects/CubeCollidingObject.hpp>
#include <AiryEngineCore/Input.hpp>

#include <iostream>


GameRound::GameRound(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    // std::cout << "GameRound::start start" << std::endl;

    create_car(resource_manager);

    create_squares(resource_manager);
    set_squares_start_pos();

    // create_roads(resource_manager);
    
    // create_barriers(resource_manager);

    // create_coins(resource_manager);

    // create_fuel_canister(resource_manager);

    // std::cout << "GameRound::start finish" << std::endl;
}


void GameRound::update_game_round()
{
    // std::cout << "GameRound::update_game_round start" << std::endl;

    if (!this->pause)
    {
        // move_back_game_objects();
        // rotate_coins_and_fuel_canister();

        // this->square->move_along_z_axis(this->game_objects_step, this->road_offset, this->number_of_squares);
        // this->square->rotate_coins_and_fuel_canister(this->rotate_delta_angle);

        for (std::shared_ptr<Square> curr_square : *this->squares)
        {
            curr_square->move_along_z_axis(this->game_objects_step, this->road_offset, this->number_of_squares);
            curr_square->rotate_coins_and_fuel_canister(this->rotate_delta_angle);
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
        // std::cout << "KEY_C pressed" << std::endl; 
        // // if (AiryEngine::Timer::get_current_time() - this->last_pause_change_time <= 0.08f)
        //     // return;

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
        // "Mashina12.obj",
        // "FunnyRider/SportCar",
        resource_manager
    );
}

void GameRound::create_squares(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    // std::cout << "GameRound::create_squares start" << std::endl;

    this->squares = std::make_shared<std::vector<std::shared_ptr<Square>>>();

    for (int i = 0; i < 5; i++)
    {
        this->squares->push_back(create_square_1_kind(resource_manager));
        this->squares->push_back(create_square_2_kind(resource_manager));
        // this->squares->push_back(create_square_3_kind(resource_manager));
    }

    // std::cout << "GameRound::create_squares finish" << std::endl;
}


void GameRound::set_squares_start_pos()
{
    for (int i = 0; i < this->squares->size(); i++)
    {
        // (*this->squares)[i]->set_position(0, 0, this->road_offset * i);
        (*this->squares)[i]->move_along_z_axis(this->road_offset * i * -1, this->road_offset, this->number_of_squares);
    }

    // for (int i = 0; i < this->squares->size(); i++)
    // {
    //     if ((*this->squares)[i]->get_has_fuel_canister())
    //         std::cout << "yes Fuel canister" << std::endl;
    //     else
    //         std::cout << "no Fuel canister" << std::endl;
    // }
}


std::shared_ptr<Square> GameRound::create_square_1_kind(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    std::vector<std::pair<float, float>> barrier_coords;

    std::vector<std::pair<float, float>> coin_coords;

    std::shared_ptr<Square> curr_square = std::make_shared<Square>(
        resource_manager,
        barrier_coords,
        coin_coords
    );

    // if (curr_square->get_has_fuel_canister())
    //     std::cout << "yes Fuel canister" << std::endl;
    // else
    //     std::cout << "no Fuel canister" << std::endl;

    this->number_of_squares += 1;

    return curr_square;
}


std::shared_ptr<Square> GameRound::create_square_2_kind(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    std::vector<std::pair<float, float>> barrier_coords;
    std::vector<std::pair<float, float>> coin_coords;
    int random_number;

    std::pair<float, float> left_pos;
    left_pos.first = 2;
    left_pos.second = 0;
    random_number = get_random_number(1, 100);
    if (random_number < 10)
    {
        
    }
    else if (random_number < 40)
    {
        barrier_coords.push_back(left_pos);
    }
    else
    {
        coin_coords.push_back(left_pos);
    }

    std::pair<float, float> center_pos;
    center_pos.first = 0;
    center_pos.second = 0;
    random_number = get_random_number(1, 100);
    if (random_number < 10)
    {
        
    }
    else if (random_number < 40)
    {
        barrier_coords.push_back(center_pos);
    }
    else
    {
        coin_coords.push_back(center_pos);
    }
    
    std::pair<float, float> right_pos;
    right_pos.first = -2;
    right_pos.second = 0;
    random_number = get_random_number(1, 100);
    if (random_number < 10)
    {
        
    }
    else if (random_number < 40)
    {
        barrier_coords.push_back(right_pos);
    }
    else
    {
        coin_coords.push_back(right_pos);
    }

    

    std::shared_ptr<Square> curr_square = std::make_shared<Square>(
        resource_manager,
        barrier_coords,
        coin_coords
    );

    // if (curr_square->get_has_fuel_canister())
    //     std::cout << "yes Fuel canister" << std::endl;
    // else
    //     std::cout << "no Fuel canister" << std::endl;

    this->number_of_squares += 1;

    return curr_square;
}


std::shared_ptr<Square> GameRound::create_square_3_kind(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    std::vector<std::pair<float, float>> barrier_coords;
    std::pair<float, float> aux_pair;

    // barrier_coords.push_back(std::pair<float, float>(0, 0));
    aux_pair.first = 0;
    aux_pair.second = 0;
    barrier_coords.push_back(aux_pair);

    aux_pair.first = 2;
    aux_pair.second = 0;
    barrier_coords.push_back(aux_pair);

    std::vector<std::pair<float, float>> coin_coords;
    // coin_coords.push_back(std::pair<float, float>(-2, 0));
    aux_pair.first = -2;
    aux_pair.second = 0;
    coin_coords.push_back(aux_pair);

    std::shared_ptr<Square> curr_square = std::make_shared<Square>(
        resource_manager,
        barrier_coords,
        coin_coords
    );

    // if (curr_square->get_has_fuel_canister())
    //     std::cout << "yes Fuel canister" << std::endl;
    // else
    //     std::cout << "no Fuel canister" << std::endl;

    this->number_of_squares += 1;

    return curr_square;
}


std::shared_ptr<Square> GameRound::create_square_8_kind(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    std::vector<std::pair<float, float>> barrier_coords;
    std::pair<float, float> aux_pair;

    // barrier_coords.push_back(std::pair<float, float>(0, 0));
    aux_pair.first = 0;
    aux_pair.second = 0;
    barrier_coords.push_back(aux_pair);

    std::vector<std::pair<float, float>> coin_coords;
    // coin_coords.push_back(std::pair<float, float>(-2, 0));
    aux_pair.first = -2;
    aux_pair.second = 0;
    coin_coords.push_back(aux_pair);

    std::pair<float, float> fuel_canister_coords;
    // fuel_canister_coords = std::pair<float, float>(2, 0);
    fuel_canister_coords.first = 2;
    fuel_canister_coords.second = 0;

    std::shared_ptr<Square> curr_square = std::make_shared<Square>(
        resource_manager,
        barrier_coords,
        coin_coords,
        fuel_canister_coords
    );

    // if (curr_square->get_has_fuel_canister())
    //     std::cout << "yes Fuel canister" << std::endl;
    // else
    //     std::cout << "no Fuel canister" << std::endl;

    this->number_of_squares += 1;

    return curr_square;
}


/*
void GameRound::create_roads(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    // this->road = std::make_shared<Road>(
    //     "RoadModel",
    //     "WayOne.obj",
    //     "FunnyRider/Road",
    //     resource_manager
    // );

    this->roads = std::make_shared<std::vector<std::shared_ptr<Road>>>();
    std::string model_name = "RoadModel";
    for (int i = 0; i < this->number_of_roads; i++)
    {
        // std::cout << "create road " << i << std::endl;
        // model_name += "1";
        std::shared_ptr<Road> curr_road = std::make_shared<Road>(
            model_name,
            // "WayOne.obj",
            // "FunnyRider/Road",
            resource_manager
        );
        // std::cout << "created road " << i << std::endl;
        this->roads->push_back(curr_road);
    }
}


void GameRound::create_barriers(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    // this->barrier = std::make_shared<Barrier>(
    //     "BarrierModel",
    //     "Pregrados.obj",
    //     "FunnyRider/Pregrados",
    //     resource_manager
    // );

    this->barriers = std::make_shared<std::vector<std::shared_ptr<Barrier>>>();
    std::string model_name = "BarrierModel";
    for (int i = 0; i < this->number_of_barriers; i++)
    {
        // std::cout << "create road " << i << std::endl;
        // model_name += "1";
        std::shared_ptr<Barrier> curr_barrier = std::make_shared<Barrier>(
            model_name,
            // "Pregrados.obj",
            // "FunnyRider/Pregrados",
            resource_manager
        );
        // std::cout << "created road " << i << std::endl;
        this->barriers->push_back(curr_barrier);
    }
}


void GameRound::create_coins(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    // this->coin = std::make_shared<Coin>(
    //     "CoinModel",
    //     "Monetka12.obj",
    //     "FunnyRider/Coin",
    //     resource_manager
    // );

    this->coins = std::make_shared<std::vector<std::shared_ptr<Coin>>>();
    std::string model_name = "CoinModel";
    for (int i = 0; i < this->number_of_coins; i++)
    {
        // std::cout << "create road " << i << std::endl;
        // model_name += "1";
        std::shared_ptr<Coin> curr_coin = std::make_shared<Coin>(
            model_name,
            // "Monetka12.obj",
            // "FunnyRider/Coin",
            resource_manager
        );
        // std::cout << "created road " << i << std::endl;
        this->coins->push_back(curr_coin);
    }
}


void GameRound::create_fuel_canister(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    this->fuel_canister = std::make_shared<FuelCanister>(
        "FuelCanisterModel",
        // "Kanistra.obj",
        // "FunnyRider/Canister",
        resource_manager
    );
}
*/


void GameRound::set_start_pos()
{
    set_car_start_pos();

    // set_roads_start_pos();

    // set_barriers_start_pos();

    // set_coins_start_pos();

    // set_fuel_canister_pos();
}


void GameRound::set_car_start_pos()
{
    this->car->set_position(0.277f, 0, -1.8f);
}


/*
void GameRound::set_roads_start_pos()
{
    // float road_offset = 4.317f * 2 - 0.1f;
    for (int i = 0; i < this->roads->size(); i++)
    {
        (*this->roads)[i]->set_position(0, 0, this->road_offset * i);
    }
}


void GameRound::set_barriers_start_pos()
{
    // float road_offset = 4.317f * 2 - 0.1f;
    for (int i = 0; i < this->barriers->size(); i++)
    {
        (*this->barriers)[i]->set_position(0, 0, this->road_offset * i + 1.0f);
    }
}


void GameRound::set_coins_start_pos()
{
    // float road_offset = 4.317f * 2 - 0.1f;
    for (int i = 0; i < this->coins->size(); i++)
    {
        (*this->coins)[i]->set_position(-2.0f, 0, this->road_offset * i + 1.0f);

        glm::vec3 rot = (*this->coins)[i]->get_rotate();
        (*this->coins)[i]->set_rotate(
            rot.x, 
            rot.y + i * 25.0f,  
            rot.z
        );
    }
}

void GameRound::set_fuel_canister_pos()
{
    this->fuel_canister->set_position(2.0f, 0, this->road_offset);
}
*/


/*
void GameRound::move_back_game_objects()
{
    move_back_roads();

    move_back_barriers();

    move_back_coins();

    move_back_fuel_canister();
}




void GameRound::move_back_roads()
{
    for (int i = 0; i < this->roads->size(); i++)
    {
        glm::vec3 pos = (*this->roads)[i]->get_position();
        (*this->roads)[i]->set_position(
            pos.x, 
            pos.y, 
            pos.z - this->game_objects_step
        );

        pos = (*this->roads)[i]->get_position();
        if (pos.z < -this->road_offset)
        {
            (*this->roads)[i]->set_position(
                pos.x, 
                pos.y, 
                pos.z + this->road_offset * this->number_of_roads
            );
        }
    }
}


void GameRound::move_back_barriers()
{
    for (int i = 0; i < this->barriers->size(); i++)
    {
        glm::vec3 pos = (*this->barriers)[i]->get_position();
        (*this->barriers)[i]->set_position(
            pos.x, 
            pos.y, 
            pos.z - this->game_objects_step
        );

        pos = (*this->barriers)[i]->get_position();
        if (pos.z < -this->road_offset)
        {
            (*this->barriers)[i]->set_position(
                pos.x, 
                pos.y, 
                pos.z + this->road_offset * this->number_of_roads
            );
        }
    }
}


void GameRound::move_back_coins()
{
    for (int i = 0; i < this->coins->size(); i++)
    {
        glm::vec3 pos = (*this->coins)[i]->get_position();
        (*this->coins)[i]->set_position(
            pos.x, 
            pos.y, 
            pos.z - this->game_objects_step
        );

        pos = (*this->coins)[i]->get_position();
        if (pos.z < -this->road_offset)
        {
            (*this->coins)[i]->set_position(
                pos.x, 
                pos.y, 
                pos.z + this->road_offset * this->number_of_roads
            );
        }
    }
}


void GameRound::move_back_fuel_canister()
{
    glm::vec3 pos = this->fuel_canister->get_position();
    this->fuel_canister->set_position(
        pos.x, 
        pos.y, 
        pos.z - this->game_objects_step
    );

    pos = this->fuel_canister->get_position();
    if (pos.z < -this->road_offset)
    {
        this->fuel_canister->set_position(
            pos.x, 
            pos.y, 
            pos.z + this->road_offset * this->number_of_roads
        );
    }
}
*/


/*
void GameRound::rotate_coins_and_fuel_canister()
{
    for (int i = 0; i < this->coins->size(); i++)
    {
        glm::vec3 rotate = (*this->coins)[i]->get_rotate();
        float delta_angle_y = rotate.y + this->rotate_delta_angle;
        if (delta_angle_y > 360) delta_angle_y -= 360;
        (*this->coins)[i]->set_rotate(
            rotate.x, 
            delta_angle_y,
            rotate.z
        );
    }

    glm::vec3 fuel_canister_rotate = this->fuel_canister->get_rotate();
    float delta_angle_y = fuel_canister_rotate.y + this->rotate_delta_angle;
    if (delta_angle_y > 360) delta_angle_y -= 360;
    this->fuel_canister->set_rotate(
        fuel_canister_rotate.x, 
        delta_angle_y,
        fuel_canister_rotate.z
    );
}
*/


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

    // for (std::shared_ptr<Barrier> barrier : *this->barriers)
    // for (std::shared_ptr<Barrier> barrier : *(this->square->get_barriers()))
    // {
    //     std::shared_ptr<AiryEngine::CubeCollidingObject> barrier_coll_cube = barrier->get_colliding_cube();
    //     barrier_coll_cube->set_is_collided(false);

    //     if (AiryEngine::CollisionDetector::cube_cube_collision(*car_coll_cube, *barrier_coll_cube))
    //     {
    //         car_coll_cube->set_is_collided(true);
    //         barrier_coll_cube->set_is_collided(true);
    //     }
    // }
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

    // for (std::shared_ptr<Coin> coin : *(this->square->get_coins()))
    // {
    //     std::shared_ptr<AiryEngine::CubeCollidingObject> coin_coll_cube = coin->get_colliding_cube();
    //     coin_coll_cube->set_is_collided(false);

    //     if (AiryEngine::CollisionDetector::cube_cube_collision(*car_coll_cube, *coin_coll_cube))
    //     {
    //         car_coll_cube->set_is_collided(true);
    //         coin_coll_cube->set_is_collided(true);
    //     }
    // }
}


void GameRound::check_fuel_canister_collision()
{
    std::shared_ptr<AiryEngine::CubeCollidingObject> car_coll_cube = this->car->get_colliding_cube();

    // for (int i = 0; i < this->squares->size(); i++)
    // {
    //     if ((*this->squares)[i]->get_has_fuel_canister())
    //         std::cout << "yes Fuel canister" << std::endl;
    //     else
    //         std::cout << "no Fuel canister" << std::endl;
    // }

    for (std::shared_ptr<Square> curr_square : *this->squares)
    {
        // if (!curr_square->get_has_fuel_canister())
        // {
        //     // std::cout << "no Fuel canister" << std::endl;
        //     return;
        // }

        // std::cout << "yes Fuel canister" << std::endl;

        if (curr_square->get_has_fuel_canister())
        {
            std::shared_ptr<AiryEngine::CubeCollidingObject> fuel_canister_coll_cube = curr_square->get_fuel_canister()->get_colliding_cube();
            fuel_canister_coll_cube->set_is_collided(false);

            if (AiryEngine::CollisionDetector::cube_cube_collision(*car_coll_cube, *fuel_canister_coll_cube))
            {
                car_coll_cube->set_is_collided(true);
                fuel_canister_coll_cube->set_is_collided(true);
            }
        }
    }

    // if (!this->square->get_has_fuel_canister())
    //     return;

    // std::shared_ptr<AiryEngine::CubeCollidingObject> car_coll_cube = this->car->get_colliding_cube();

    // std::shared_ptr<AiryEngine::CubeCollidingObject> fuel_canister_coll_cube = this->square->get_fuel_canister()->get_colliding_cube();
    // fuel_canister_coll_cube->set_is_collided(false);

    // if (AiryEngine::CollisionDetector::cube_cube_collision(*car_coll_cube, *fuel_canister_coll_cube))
    // {
    //     car_coll_cube->set_is_collided(true);
    //     fuel_canister_coll_cube->set_is_collided(true);
    // }
}


int GameRound::get_random_number(int start, int end)
{
    return (rand() % (end - start + 1) + start);
}