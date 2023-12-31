#pragma once

#include "projectile.h"

class Crystal : public Projectile {
    public:
        Crystal(vec2 position = vec2(0, 0), vec2 direction = vec2(0, 0), double deltaTime = 0.0, ofColor color = COLORS.RICH_CRYSTAL);

        void draw() override;
};