#pragma once

#include "ofMain.h"
#include "config.h"

using namespace glm;

class Entity {
    public:
        Entity(vec2 position = vec2(0, 0), vec2 direction = vec2(0, 0), float rotation = 0.0, float size = 20.0, unsigned short health = 100, float speed = 0.0, unsigned short damage = 5);

        virtual void update(double deltaTime);
        virtual void draw();

        void drawBoundingBox();

        void physicsCollision(vec2 colliderPosition, float colliderSpeed, unsigned short damage);

        // setters
        void setPosition(vec2 position);
        void setDirection(vec2 direction);
        void setSize(float size);
        void setSpeed(float speed);
        void setHealth(unsigned short health);

        // getters
        vec2 getPosition();
        vec2 getDirection();
        float getRotation();
        float getSpeed();
        short getHealth();
        unsigned short getDamage();
        ofRectangle getBoundingBox();
        string getIdentity();

    protected:
        vec2 _position;
        vec2 _direction;
        float _rotation;

        float _size;

        float _speed;
        float _rotation_speed;

        short _health;
        short _maxHealth;
        unsigned short _damage;

        ofRectangle _boundingBox;

        string _identity;
};