#ifndef MAP_H
#define MAP_H


#include <vector>
#include <memory>
#include "action.hpp"

class Map
{
    public:
        

    private:
        std::vector<Location> map;
};


class Location
{
    public:

    private:
        std::vector<std::shared_ptr<Action> > actions;
};

#endif //MAP_H
