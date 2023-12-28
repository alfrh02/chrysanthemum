#include "missile.h"

Missile::Missile(vec2 position, vec2 direction, float rotation, double deltaTime)
: Entity(position, direction, rotation, 8.0, 1) {
    _speed = 4.0;
    _rotation_speed = 1.0;
    _identity = "Missile";

    _creationTime = deltaTime;
}

void Missile::update(double deltaTime) {
    _boundingBox.setPosition(_position.x - _size/2, _position.y - _size/2);
    _position += _direction * _speed;
    _rotation += _rotation_speed;

    if (deltaTime - _creationTime > 2) {
        _health = 0;
    }
}

void Missile::draw() {
    ofPushView();
        ofTranslate(_position);
        ofRotateDeg(_rotation);
        ofTranslate(vec2(-_size/2, -_size/2));

        ofNoFill();
        ofSetColor(COLOURS.FOREGROUND);
        ofDrawRectangle(0, 0, _size, _size);
    ofPopView();
}

bool Missile::isDeadYet() {
    // return _lifetime > _lifespan;
    return false;
}