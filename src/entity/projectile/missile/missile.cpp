#include "missile.h"

Missile::Missile(vec2 position, vec2 direction, float rotation, double deltaTime)
: Projectile(position, direction, rotation, deltaTime) {
    _speed = 4.0;
    _identity = "Missile";

    _color = COLORS.FOREGROUND;

    _damage = 15.0;
}