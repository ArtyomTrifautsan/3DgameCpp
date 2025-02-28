#include "square_templates_definer.hpp"


SquareTemplateDefender::SquareTemplateDefender()
{
    create_square_templates();
}


void SquareTemplateDefender::create_square_templates()
{
    /*
    n - ничего (пустота)
    c - монетка
    b - барьер
    k - канистра
    */

    this->square_templates = std::make_shared<std::vector<std::string>>();

    // С канистрой 
    this->square_templates->push_back("bkb");
    this->square_templates->push_back("kbb");
    this->square_templates->push_back("bbk");

    // С монетками
    this->square_templates->push_back("bcb");
    this->square_templates->push_back("cbb");
    this->square_templates->push_back("bbc");

    this->square_templates->push_back("bcc");
    this->square_templates->push_back("ccb");

    this->square_templates->push_back("bcn");
    this->square_templates->push_back("ncb");

    this->square_templates->push_back("cbn");
    this->square_templates->push_back("nbc");

    this->square_templates->push_back("ccc");

    // С пустотой
    this->square_templates->push_back("bnb");
    this->square_templates->push_back("nbb");
    this->square_templates->push_back("bbn");

    this->square_templates->push_back("nbn");

    this->square_templates->push_back("nnn");
}


std::string SquareTemplateDefender::get_random_square_template()
{
    return (*this->square_templates)[get_random_number(0, this->square_templates->size() - 1)];
}


int SquareTemplateDefender::get_random_number(int start, int end)
{
    return (rand() % (end - start + 1) + start);
}