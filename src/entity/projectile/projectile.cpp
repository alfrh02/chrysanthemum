#include "missile.h"

Projectile::Projectile(vec2 position, vec2 direction, float rotation, double deltaTime)
: Entity(position, direction, rotation, 8.0, 1) {
    _creationTime = deltaTime;
    _color = COLORS.FOREGROUND;

    _identity = "Projectile";
    _type = "Projectile";
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

void Projectile::draw() {
    ofPushView();
        ofTranslate(_position);
        ofRotateDeg(_rotation);
        ofTranslate(vec2(-_size/2, -_size/2) * _lifetime);

        ofSetColor(_color);
        ofDrawRectangle(0, 0, _size * _lifetime, _size * _lifetime);
    ofPopView();
}