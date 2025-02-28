#pragma once

// Системные библиотеки
#include <memory>
#include <string>
#include <vector>


class SquareTemplateDefender {
public:
    SquareTemplateDefender();

    std::shared_ptr<std::vector<std::string>> get_square_templates() const { return this->square_templates; }

    std::string get_random_square_template();

private:
    void create_square_templates();
    int get_random_number(int start, int end);

    std::shared_ptr<std::vector<std::string>> square_templates;
};