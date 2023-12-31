#pragma once

#include "entity.h"

class Ship : public Entity {
    public:
        Ship(vec2 position = vec2(0, 0), vec2 direction = vec2(0, 0), float rotation = 0.0, float size = 20.0, unsigned short health = 100, float speed = 0.0);

        void draw() override;

    protected:
        const float _MAX_SPEED = 3;
        const float _SPEED_RETURN_RATE = 0.05;

        ofColor _color;
};