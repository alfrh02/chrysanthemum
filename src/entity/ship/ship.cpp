#include "ship.h"

Ship::Ship(vec2 position, vec2 direction, float rotation, float size, unsigned short health, float speed)
: Entity(position, direction, rotation, size, health, speed) {
    _identity = "Ship";
    _type = "Ship";
}

bool Ship::addCargo(int cargo) {
    _cargo += cargo;
    if (_cargo > _max_cargo) {
        _cargo = _max_cargo;
        return false;
    } else if (_cargo < 0) {
        _cargo = 0;
        return false;
    }
    return true;
}