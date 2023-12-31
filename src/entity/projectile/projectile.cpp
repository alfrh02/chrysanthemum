#include "missile.h"

Projectile::Projectile(vec2 position, vec2 direction, float rotation, double deltaTime)
: Entity(position, direction, rotation, 8.0, 1) {
    _speed = 4.0;
    _rotation_speed = 1.0;
    _creationTime = deltaTime;

    _identity = "Projectile";
}

void Projectile::update(double deltaTime) {
    _lifetime = 1 - ((deltaTime - _creationTime) / _lifespan);

    _boundingBox.setPosition(_position.x - _size/2 * _lifetime, _position.y - _size/2 * _lifetime);
    _boundingBox.setWidth(_size * _lifetime);
    _boundingBox.setHeight(_size * _lifetime);

    _position += _direction * _speed;
    _rotation += _rotation_speed;

    if (_lifetime < 0) {
        _health = 0;
    }
}