#include "square.hpp"


#include <iostream>


Square::Square(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    // std::cout << "Square::Square started (void)" << std::endl;

    std::vector<std::pair<float, float>> barriers_coords;
    std::vector<std::pair<float, float>> coins_coords;
    std::vector<std::pair<float, float>> fuel_canisters_coords;

    create_road(resource_manager);

    create_barriers(resource_manager, barriers_coords);

    create_coins(resource_manager, coins_coords);

    create_fuel_canisters(resource_manager, fuel_canisters_coords);

    // std::cout << "Square::Square finished (void)" << std::endl;
}


Square::Square(std::shared_ptr<AiryEngine::ResourceManager> resource_manager, std::string square_template)
{
    // std::cout << "Square::Square started (template)" << std::endl;

    std::vector<std::pair<float, float>> barriers_coords;
    std::vector<std::pair<float, float>> coins_coords;
    std::vector<std::pair<float, float>> fuel_canisters_coords;

    generate_coords_by_template(square_template, &barriers_coords, &coins_coords, &fuel_canisters_coords);

    create_road(resource_manager);

    create_barriers(resource_manager, barriers_coords);

    create_coins(resource_manager, coins_coords);

    create_fuel_canisters(resource_manager, fuel_canisters_coords);

    // std::cout << "Square::Square finished (template)" << std::endl;
}


void Square::generate_coords_by_template(std::string square_template,
                                        std::vector<std::pair<float, float>>* barrier_coords,
                                        std::vector<std::pair<float, float>>* coins_coords,
                                        std::vector<std::pair<float, float>>* fuel_canisters_coords)
{
    std::pair<float, float> left_pos;
    left_pos.first = 2;
    left_pos.second = 0;
    if ('c' == square_template[0])
        coins_coords->push_back(left_pos);
    else if ('b' == square_template[0])
        barrier_coords->push_back(left_pos);
    else if ('k' == square_template[0])
        fuel_canisters_coords->push_back(left_pos);

    std::pair<float, float> center_pos;
    center_pos.first = 0;
    center_pos.second = 0;
    if ('c' == square_template[1])
        coins_coords->push_back(center_pos);
    else if ('b' == square_template[1])
        barrier_coords->push_back(center_pos);
    else if ('k' == square_template[1])
        fuel_canisters_coords->push_back(center_pos);

    std::pair<float, float> right_pos;
    right_pos.first = -2;
    right_pos.second = 0;
    if ('c' == square_template[2])
        coins_coords->push_back(right_pos);
    else if ('b' == square_template[2])
        barrier_coords->push_back(right_pos);
    else if ('k' == square_template[2])
        fuel_canisters_coords->push_back(right_pos);
}


void Square::create_road(std::shared_ptr<AiryEngine::ResourceManager> resource_manager)
{
    this->road = std::make_shared<Road>(
        "RoadModel",
        resource_manager
    );
}


void Square::create_barriers(std::shared_ptr<AiryEngine::ResourceManager> resource_manager,
                        const std::vector<std::pair<float, float>>& barriers_coords)
{
    this->barriers = std::make_shared<std::vector<std::shared_ptr<Barrier>>>();
    for (std::pair<float, float> coords : barriers_coords)
    {
        std::shared_ptr<Barrier> curr_barrier = std::make_shared<Barrier>(
            "BarrierModel",
            resource_manager
        );
        curr_barrier->set_position(coords.first, coords.second, 0);
        this->barriers->push_back(curr_barrier);
    }
}


void Square::create_coins(std::shared_ptr<AiryEngine::ResourceManager> resource_manager,
                    const std::vector<std::pair<float, float>>& coins_coords)
{
    this->coins = std::make_shared<std::vector<std::shared_ptr<Coin>>>();
    for (std::pair<float, float> coords : coins_coords)
    {
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
}


void Square::create_fuel_canisters(std::shared_ptr<AiryEngine::ResourceManager> resource_manager,
                            const std::vector<std::pair<float, float>>& fuel_canisters_coords)
{
    this->fuel_canisters = std::make_shared<std::vector<std::shared_ptr<FuelCanister>>>();
    for (std::pair<float, float> coords : fuel_canisters_coords)
    {
        std::shared_ptr<FuelCanister> curr_fuel_canister = std::make_shared<FuelCanister>(
            "FuelCanisterModel",
            resource_manager
        );
        curr_fuel_canister->set_position(coords.first, coords.second, 0);

        this->fuel_canisters->push_back(curr_fuel_canister);
    }
}


void Square::move_along_z_axis(float step, float offset, float number_of_roads)
{
    this->z_position -= step;

    move_along_z_axis_road(step, offset, number_of_roads);

    move_along_z_axis_barriers(step, offset, number_of_roads);

    move_along_z_axis_coins(step, offset, number_of_roads);

    move_along_z_axis_fuel_canisters(step, offset, number_of_roads);
}


void Square::move_along_z_axis_road(float step, float offset, float number_of_roads)
{
    glm::vec3 pos = this->road->get_position();
    this->road->set_position(
        pos.x, 
        pos.y, 
        pos.z - step
    );
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
    }
}


void Square::move_along_z_axis_fuel_canisters(float step, float offset, float number_of_roads)
{
    for (int i = 0; i < this->fuel_canisters->size(); i++)
    {
        glm::vec3 pos = (*this->fuel_canisters)[i]->get_position();
        (*this->fuel_canisters)[i]->set_position(
            pos.x, 
            pos.y, 
            pos.z - step
        );
    }
}


void Square::rotate_coins_and_fuel_canisters(float rotate_delta_angle)
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


bool Square::is_out_of_visible_area(float road_offset)
{
    // if (this->z_position < -road_offset)
    //     return true;

    // return false;

    return this->z_position < -road_offset;
}