#include "entity.h"

using namespace glm;

Entity::Entity(vec2 position, vec2 direction, float rotation, float size, unsigned short health, float speed) {
    _position = position;
    _direction = direction;
    _rotation = rotation;

    _size = size;
    _speed = speed;
    _health = health;
    _maxHealth = health;
}

void Entity::setPosition(vec2 position) {
    _position = position;
}