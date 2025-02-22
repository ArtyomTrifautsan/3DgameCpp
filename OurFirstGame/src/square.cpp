#include "square.hpp"


#include <iostream>


Square::Square(std::shared_ptr<AiryEngine::ResourceManager> resource_manager,
                std::shared_ptr<std::vector<std::string>> square_types)
{
    // create_square_types();

    std::vector<std::pair<float, float>> barriers_coords;
    std::vector<std::pair<float, float>> coins_coords;
    std::vector<std::pair<float, float>> fuel_canisters_coords;

    generate_random_coords(square_types, &barriers_coords, &coins_coords, &fuel_canisters_coords);

    create_road(resource_manager);

    create_barriers(resource_manager, barriers_coords);

    create_coins(resource_manager, coins_coords);

    create_fuel_canisters(resource_manager, fuel_canisters_coords);
}

// Square::Square(std::shared_ptr<AiryEngine::ResourceManager> resource_manager,
//                 const std::vector<std::pair<float, float>> barriers_coords, 
//                 const std::vector<std::pair<float, float>> coins_coords)
// {
//     // std::cout << "Square::Square start" << std::endl;

//     create_road(resource_manager);

//     create_barriers(resource_manager, barriers_coords);

//     create_coins(resource_manager, coins_coords);

//     this->has_fuel_canister = false;

//     // std::cout << "Square::Square finish" << std::endl;
// }


Square::Square(std::shared_ptr<AiryEngine::ResourceManager> resource_manager,
            std::shared_ptr<std::vector<std::string>> square_types,
            const std::vector<std::pair<float, float>> barriers_coords, 
            const std::vector<std::pair<float, float>> coins_coords,
            const std::vector<std::pair<float, float>> fuel_canisters_coords)
{
    // std::cout << "Square::Square start" << std::endl;

    create_road(resource_manager);

    create_barriers(resource_manager, barriers_coords);

    create_coins(resource_manager, coins_coords);

    create_fuel_canisters(resource_manager, fuel_canisters_coords);

    // this->has_fuel_canister = true;

    // std::cout << "Square::Square finish" << std::endl;
}


std::string Square::get_random_square_type(std::shared_ptr<std::vector<std::string>> square_types)
{
    return (*square_types)[get_random_number(0, square_types->size() - 1)];
}


int Square::get_random_number(int start, int end)
{
    return (rand() % (end - start + 1) + start);
}


void Square::generate_random_coords(std::shared_ptr<std::vector<std::string>> square_types,
                                std::vector<std::pair<float, float>>* barrier_coords,
                                std::vector<std::pair<float, float>>* coins_coords,
                                std::vector<std::pair<float, float>>* fuel_canisters_coords)
{
    std::string square_type = get_random_square_type(square_types);

    std::pair<float, float> left_pos;
    left_pos.first = 2;
    left_pos.second = 0;
    if ('c' == square_type[0])
        coins_coords->push_back(left_pos);
    else if ('b' == square_type[0])
        barrier_coords->push_back(left_pos);
    else if ('k' == square_type[0])
        fuel_canisters_coords->push_back(left_pos);

    std::pair<float, float> center_pos;
    center_pos.first = 0;
    center_pos.second = 0;
    if ('c' == square_type[1])
        coins_coords->push_back(center_pos);
    else if ('b' == square_type[1])
        barrier_coords->push_back(center_pos);
    else if ('k' == square_type[1])
        fuel_canisters_coords->push_back(center_pos);

    std::pair<float, float> right_pos;
    right_pos.first = -2;
    right_pos.second = 0;
    if ('c' == square_type[2])
        coins_coords->push_back(right_pos);
    else if ('b' == square_type[2])
        barrier_coords->push_back(right_pos);
    else if ('k' == square_type[2])
        fuel_canisters_coords->push_back(right_pos);
}


void Square::create_road(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    this->road = std::make_shared<Road>(
        "RoadModel",
        resource_manager
    );

    // std::cout << "Road has been created" << std::endl;
}


void Square::create_barriers(std::shared_ptr<AiryEngine::ResourceManager> resource_manager,
                        const std::vector<std::pair<float, float>> barriers_coords)
{
    this->barriers = std::make_shared<std::vector<std::shared_ptr<Barrier>>>();
    for (std::pair<float, float> coords : barriers_coords)
    {
        // std::cout << "Barrier coords = (" << coords.first << ", " << coords.second << ")" <<std::endl;

        std::shared_ptr<Barrier> curr_barrier = std::make_shared<Barrier>(
            "BarrierModel",
            resource_manager
        );
        // std::cout << "Barrier 1 has been created" << std::endl;
        curr_barrier->set_position(coords.first, coords.second, 0);
        // std::cout << "Barrier 1 is placed on pos" << std::endl;
        this->barriers->push_back(curr_barrier);
        // std::cout << "Barrier was added to list" << std::endl;
    }

    // std::cout << "Barriers has been created" << std::endl;
}


void Square::create_coins(std::shared_ptr<AiryEngine::ResourceManager> resource_manager,
                    const std::vector<std::pair<float, float>> coins_coords)
{
    this->coins = std::make_shared<std::vector<std::shared_ptr<Coin>>>();
    for (std::pair<float, float> coords : coins_coords)
    {
        // std::cout << "Coin coords = (" << coords.first << ", " << coords.second << ")" <<std::endl;

        std::shared_ptr<Coin> curr_coin = std::make_shared<Coin>(
            "CoinModel",
            resource_manager
        );
        curr_coin->set_position(coords.first, coords.second, 0);

        this->coins->push_back(curr_coin);
    }

    for (int i = 0; i < this->coins->size(); i++)
    {
        glm::vec3 rot = (*this->coins)[i]->get_rotate();
        (*this->coins)[i]->set_rotate(
            rot.x, 
            rot.y + i * 25.0f,  
            rot.z
        );
    }

    // std::cout << "Coins has been created" << std::endl;
}


void Square::create_fuel_canisters(std::shared_ptr<AiryEngine::ResourceManager> resource_manager,
                            const std::vector<std::pair<float, float>> fuel_canisters_coords)
{
    // this->fuel_canister = std::make_shared<FuelCanister>(
    //         "FuelCanisterModel",
    //         resource_manager
    //     );
    // this->fuel_canister->set_position(fuel_canister_coords.first, fuel_canister_coords.second, 0);
    // this->has_fuel_canister = true;

    this->fuel_canisters = std::make_shared<std::vector<std::shared_ptr<FuelCanister>>>();
    for (std::pair<float, float> coords : fuel_canisters_coords)
    {
        // std::cout << "Coin coords = (" << coords.first << ", " << coords.second << ")" <<std::endl;

        std::shared_ptr<FuelCanister> curr_fuel_canister = std::make_shared<FuelCanister>(
            "FuelCanisterModel",
            resource_manager
        );
        // fuel_canister->set_position(fuel_canister_coords.first, fuel_canister_coords.second, 0);

        // std::shared_ptr<Coin> curr_coin = std::make_shared<Coin>(
        //     "CoinModel",
        //     resource_manager
        // );
        curr_fuel_canister->set_position(coords.first, coords.second, 0);

        this->fuel_canisters->push_back(curr_fuel_canister);
    }

    // std::cout << "Fuel canister has been created" << std::endl;
}


void Square::move_along_z_axis(float step, float offset, float number_of_roads)
{
    move_along_z_axis_road(step, offset, number_of_roads);

    move_along_z_axis_barriers(step, offset, number_of_roads);

    move_along_z_axis_coins(step, offset, number_of_roads);

    move_along_z_axis_fuel_canister(step, offset, number_of_roads);
}


void Square::move_along_z_axis_road(float step, float offset, float number_of_roads)
{
    glm::vec3 pos = this->road->get_position();
    this->road->set_position(
        pos.x, 
        pos.y, 
        pos.z - step
    );

    pos = this->road->get_position();
    if (pos.z < -offset)
    {
        this->road->set_position(
            pos.x, 
            pos.y, 
            pos.z + offset * number_of_roads
        );
    }
}


void Square::move_along_z_axis_barriers(float step, float offset, float number_of_roads)
{
    for (int i = 0; i < this->barriers->size(); i++)
    {
        glm::vec3 pos = (*this->barriers)[i]->get_position();
        (*this->barriers)[i]->set_position(
            pos.x, 
            pos.y, 
            pos.z - step
        );

        pos = (*this->barriers)[i]->get_position();
        if (pos.z < -offset)
        {
            (*this->barriers)[i]->set_position(
                pos.x, 
                pos.y, 
                pos.z + offset * number_of_roads
            );
        }
    }
}


void Square::move_along_z_axis_coins(float step, float offset, float number_of_roads)
{
    for (int i = 0; i < this->coins->size(); i++)
    {
        glm::vec3 pos = (*this->coins)[i]->get_position();
        (*this->coins)[i]->set_position(
            pos.x, 
            pos.y, 
            pos.z - step
        );

        pos = (*this->coins)[i]->get_position();
        if (pos.z < -offset)
        {
            (*this->coins)[i]->set_position(
                pos.x, 
                pos.y, 
                pos.z + offset * number_of_roads
            );
        }
    }
}


void Square::move_along_z_axis_fuel_canister(float step, float offset, float number_of_roads)
{
    for (int i = 0; i < this->fuel_canisters->size(); i++)
    {
        glm::vec3 pos = (*this->fuel_canisters)[i]->get_position();
        (*this->fuel_canisters)[i]->set_position(
            pos.x, 
            pos.y, 
            pos.z - step
        );

        pos = (*this->fuel_canisters)[i]->get_position();
        if (pos.z < -offset)
        {
            (*this->fuel_canisters)[i]->set_position(
                pos.x, 
                pos.y, 
                pos.z + offset * number_of_roads
            );
        }
    }
}


void Square::rotate_coins_and_fuel_canister(float rotate_delta_angle)
{
    for (int i = 0; i < this->coins->size(); i++)
    {
        glm::vec3 rotate = (*this->coins)[i]->get_rotate();
        float delta_angle_y = rotate.y + rotate_delta_angle;
        if (delta_angle_y > 360) delta_angle_y -= 360;
        (*this->coins)[i]->set_rotate(
            rotate.x, 
            delta_angle_y,
            rotate.z
        );
    }

    for (int i = 0; i < this->fuel_canisters->size(); i++)
    {
        glm::vec3 fuel_canister_rotate = (*this->fuel_canisters)[i]->get_rotate();
        float delta_angle_y = fuel_canister_rotate.y + rotate_delta_angle;
        if (delta_angle_y > 360) delta_angle_y -= 360;
        (*this->fuel_canisters)[i]->set_rotate(
            fuel_canister_rotate.x, 
            delta_angle_y,
            fuel_canister_rotate.z
        );
    }
}

