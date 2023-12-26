#pragma once

#include "ofMain.h"

#include "config.h"

using namespace glm;

class Player {
    public:
        Player(vec2 position);
        ~Player();

        void draw();
        void update(double deltaTime);
        void keyPressed(int key);
        void keyReleased(int key);

        void setPosition(vec2 position);

    private:
        bool _w = false;
        bool _a = false;
        bool _s = false;
        bool _d = false;

        vec2 _position;
        unsigned short _rotation = 90;
        unsigned short _size = 20;
};