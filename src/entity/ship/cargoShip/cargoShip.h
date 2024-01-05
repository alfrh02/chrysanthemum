#pragma once

#include "ship.h"

class CargoShip : public Ship {
    public:
        CargoShip(vec2 position = vec2(0, 0), vec2 direction = vec2(0, 0), float rotation = 0.0, float size = 50.0, unsigned short health = 1000);

        void update(double deltaTime) override;
        void draw() override;

    private:
        float s = _size; // we are modifying `s` (using sin()) so that we don't have to modify `_size`
        bool _hazardLights = true;
};