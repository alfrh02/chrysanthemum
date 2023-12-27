#pragma once

#include "entity.h"

class Asteroid : public Entity {
    public:
        Asteroid(vec2 position = vec2(0, 0), vec2 direction = vec2(0, 0), float rotation = ofRandom(360), float size = ofRandom(15) + 10, unsigned short health = 100, float speed = ofRandom(8), float seed = ofRandom(32767), float xAmp = ofRandom(2) + 0.5, float yAmp = ofRandom(2) + 0.5);

        void update(double deltaTime);
        void draw();

    private:
        float _seed;
        float _xAmp;
        float _yAmp;
        float _rotation_speed;
};