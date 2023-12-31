#pragma once

#include "entity.h"

class Projectile : public Entity {
    public:
        Projectile(vec2 position = vec2(0, 0), vec2 direction = vec2(0, 0), float rotation = 0.0, double deltaTime = 0.0);

        void update(double deltaTime) override;
        void draw() override;

    protected:
        double _creationTime;

        unsigned char _lifespan = 2;
        float _lifetime = 0;

        ofColor _color;
};