#pragma once

#include "asteroid.h"

class CrystalAsteroid : public Asteroid {
    public:
        CrystalAsteroid(vec2 position = vec2(0, 0));

        void update(double deltaTime) override;
        void draw() override;
};