#pragma once

#include "entity.h"

class Ship : public Entity {
    public:
        Ship(vec2 position = vec2(0, 0), vec2 direction = vec2(0, 0), float rotation = 0.0, float size = 20.0, unsigned short health = 100, float speed = 0.0);

        bool addCargo(int cargo);

    protected:
        short _cargo = 0;
        unsigned short _max_cargo = 1024;
};