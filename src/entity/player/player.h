#pragma once

#include "entity.h"

class Player : public Entity {

    public:
        Player(vec2 position = vec2(0, 0), vec2 direction = vec2(0, 0), float rotation = 0.0, float size = 20.0, unsigned short health = 100, float speed = 0.0);

        void update(double deltaTime) override;
        void draw() override;
        void keyPressed(int key);
        void keyReleased(int key);

        bool addCargo(int cargo);

        short getCargo();

    private:
        // player input
        // toggled to true on key input, used in vectors for player movement
        bool _w = false;
        bool _a = false;
        bool _s = false;
        bool _d = false;

        const float _MAX_SPEED = 3;
        const float _SPEED_RETURN_RATE = 0.05;

        short _cargo = 0;
        unsigned short _max_cargo = 32;
};