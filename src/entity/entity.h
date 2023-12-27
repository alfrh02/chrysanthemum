#pragma once

#include "ofMain.h"
#include "config.h"

using namespace glm;

class Entity {
    public:
        Entity(vec2 position = vec2(0, 0), vec2 direction = vec2(0, 0), float rotation = 0.0, float size = 20.0, unsigned short health = 100, float speed = 0.0);

        virtual void update(double deltaTime);
        virtual void draw();

        void drawBoundingBox();

        void setPosition(vec2 position);
        void setSize(float size);

        vec2 getPosition();
        vec2 getDirection();
        float getRotation();
    protected:
        vec2 _position;
        vec2 _direction;
        float _rotation;

        float _size;
        float _speed;
        unsigned short _health;
        unsigned short _maxHealth;

        ofRectangle _boundingBox;
};