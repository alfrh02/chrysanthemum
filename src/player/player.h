#pragma once

#include <vector>
#include "ofMain.h"
#include "entity.h"

#include "config.h"
#include "missile.h"

using namespace glm;

class Player : public Entity {
    public:
        Player(vec2 position, vec2 direction);
        ~Player();

        void update(double deltaTime);
        void draw();
        void keyPressed(int key);
        void keyReleased(int key);
		void mousePressed(int x, int y, int button);

        void setPosition(vec2 position);

        vector<Missile*> missiles;

    private:
        // player input
        bool _w = false;
        bool _a = false;
        bool _s = false;
        bool _d = false;

        vec2 _position;
        vec2 _direction;

        float _speed = 0;
        const float _MAX_SPEED = 3;
        const float _SPEED_RETURN_RATE = 0.05;

        float _rotation = 90;
        const float _ROTATION_SPEED = 1.25;

        unsigned short _size = 20;
};