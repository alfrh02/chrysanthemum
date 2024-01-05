#pragma once

#include "ship.h"

class Enemy : public Ship {

    public:
        Enemy(vec2 position = vec2(0, 0), vec2 direction = vec2(0, 0), float rotation = 0.0, float size = 20.0, unsigned short health = 100, float speed = 0.0);

        void update(double deltaTime) override;
        void draw() override;
};