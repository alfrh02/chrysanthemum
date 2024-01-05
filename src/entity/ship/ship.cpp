#include "ship.h"

Ship::Ship(vec2 position, vec2 direction, float rotation, float size, unsigned short health, float speed)
: Entity(position, direction, rotation, size, health, speed) {
    _color = COLORS.FOREGROUND;
    _identity = "Ship";
    _type = "Ship";
}