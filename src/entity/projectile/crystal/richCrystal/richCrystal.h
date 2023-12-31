#pragma once

#include "crystal.h"

class RichCrystal : public Crystal {
    public:
        RichCrystal(vec2 position = vec2(0, 0), double deltaTime = 0.0);
};