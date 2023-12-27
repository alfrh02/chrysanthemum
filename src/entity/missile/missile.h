#pragma once

#include "entity.h"

class Missile : public Entity {
    public:
        Missile(vec2 position, vec2 direction, float rotation, float size = 8.0);

        void update(double deltaTime) override;
        void draw() override;

        bool isDeadYet();
    private:
        float _speed = 4;
};