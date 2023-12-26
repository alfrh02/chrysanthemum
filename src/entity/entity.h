#pragma once

#include "ofMain.h"
#include "config.h"

using namespace glm;

class Entity {
    public:
        Entity(vec2 position = vec2(0, 0), vec2 direction = vec2(0, 0), float rotation = 0.0);

        void setPosition(vec2 position);
    protected:
        vec2 _position = vec2(0, 0);
        vec2 _direction = vec2(0, 0);
        float _rotation = 0;
};