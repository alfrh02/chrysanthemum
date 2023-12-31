#pragma once

#include "projectile.h"

class Missile : public Projectile {
    public:
        Missile(vec2 position, vec2 direction, float rotation, double deltaTime = 0.0);
};