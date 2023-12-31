#include "missile.h"

Missile::Missile(vec2 position, vec2 direction, float rotation, double deltaTime)
: Entity(position, direction, rotation, 8.0, 1) {
    _speed = 4.0;
    _rotation_speed = 1.0;
    _identity = "Missile";

    _creationTime = deltaTime;
}

void Missile::update(double deltaTime) {
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

void Missile::draw() {
    ofPushView();
        ofTranslate(_position);
        ofRotateDeg(_rotation);
        ofTranslate(vec2(-_size/2, -_size/2) * _lifetime);

        ofNoFill();
        ofSetColor(COLOURS.FOREGROUND);
        ofDrawRectangle(0, 0, _size * _lifetime, _size * _lifetime);
    ofPopView();
}