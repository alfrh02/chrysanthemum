#pragma once

#include "entity.h"

class Missile : public Entity {
    public:
        Missile(vec2 position, vec2 direction, float rotation, double deltaTime = 0.0);

        void update(double deltaTime) override;
        void draw() override;

    private:
        double _creationTime;

        unsigned char _lifespan = 2;
        float _lifetime = 0;
};