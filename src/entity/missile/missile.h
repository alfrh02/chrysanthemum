#pragma once

#include "entity.h"

class Missile : public Entity {
    public:
        Missile(vec2 position, vec2 direction, float rotation);

        void update(double deltaTime);
        void draw();

        bool isDeadYet();
    private:
        float _speed = 4;
        short _size = 16;

        double _lifetime = 0;
        unsigned short _lifespan = 16;
};