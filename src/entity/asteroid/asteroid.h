#pragma once

#include "entity.h"

class Asteroid : public Entity {
    public:
        Asteroid(vec2 position = vec2(0, 0), vec2 direction = vec2(ofRandom(2) - 1, ofRandom(2) - 1), float rotation = ofRandom(360), float size = ofRandom(25) + 10, unsigned short health = 100, float speed = ofRandom(8), float seed = ofRandom(32767), float xAmp = ofRandom(0.5) + 0.5, float yAmp = ofRandom(0.5) + 0.5);

        void update(double deltaTime) override;
        void draw() override;

    protected:
        float _seed;
        float _xAmp;
        float _yAmp;

        ofColor _color;
};