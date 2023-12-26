#pragma once

#include "entity.h"
#include "missile.h"
#include <vector>

class Player : public Entity {

    public:
        void update(double deltaTime);
        void draw();
        void keyPressed(int key);
        void keyReleased(int key);

        vector<Missile*> missiles;

    private:
        // player input
        bool _w = false;
        bool _a = false;
        bool _s = false;
        bool _d = false;

        float _speed = 0;
        const float _MAX_SPEED = 3;
        const float _SPEED_RETURN_RATE = 0.05;

        const float _ROTATION_SPEED = 1.25;

        unsigned short _size = 20;
};