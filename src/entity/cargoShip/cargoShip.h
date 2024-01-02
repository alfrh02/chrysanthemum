#pragma once

#include "entity.h"

class CargoShip : public Entity {
    public:
        CargoShip(vec2 position = vec2(0, 0), vec2 direction = vec2(0, 0), float rotation = 0.0, float size = 50.0, unsigned short health = 1000);

        void update(double deltaTime) override;
        void draw() override;

        bool addCargo(int cargo);

    private:
        float s = _size; // used in draw(), modified by deltaTime in update()
        bool _hazardLights = true;

        short _cargo = 0;
        unsigned short _max_cargo = 1024;
};