#pragma once

#include "ofMain.h"

#include "config.h"

using namespace glm;

class Missile {
    public:
        Missile(vec2 position, vec2 direction, float rotation);
        ~Missile();

        void update(double deltaTime);
        void draw();

        bool isDeadYet();
    private:
        float _speed = 4;
        short _size = 16;

        vec2 _position;
        vec2 _direction;
        float _rotation;

        double _lifetime = 0;
        unsigned short _lifespan = 16;
};