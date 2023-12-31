#include "crystal.h"

Crystal::Crystal(vec2 position, double deltaTime)
: Projectile(position, vec2(0, 0), 0.0, deltaTime) {
    _identity = "Crystal";

    _colour = COLORS.CRYSTAL;
}