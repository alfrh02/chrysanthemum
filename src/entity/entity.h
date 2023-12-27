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
        void takeDamage(int damage);

        // setters
        void setPosition(vec2 position);
        void setDirection(vec2 direction);
        void setSize(float size);
        void setSpeed(float speed);

        // getters
        vec2 getPosition();
        vec2 getDirection();
        float getRotation();
        float getSpeed();
        ofRectangle getBoundingBox();

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