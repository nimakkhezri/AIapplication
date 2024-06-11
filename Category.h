#ifndef CATEGORY_H
#define CATEGORY_H

#include <iostream>

class Category {
private:
    std::string name;
    int id;
public:
    Category(std::string name, int id) : name(name), id(id) {}
    Category() {}

    std::string get_name() const;
    int get_id() const;
};

#endif
