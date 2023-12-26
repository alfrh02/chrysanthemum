#include "entity.h"

using namespace glm;

Entity::Entity(vec2 position, vec2 direction, float rotation) {
    _position = position;
    _direction = direction;
    _rotation = rotation;
}

void Entity::setPosition(vec2 position) {
    _position = position;
}