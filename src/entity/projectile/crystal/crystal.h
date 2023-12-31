#pragma once

#include "projectile.h"

class Crystal : public Projectile {
    public:
        Crystal(vec2 position = vec2(0, 0), double deltaTime = 0.0);

    protected:
        ofColor _colour;
};