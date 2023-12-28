#include "missile.h"

Missile::Missile(vec2 position, vec2 direction, float rotation, float size)
: Entity(position, direction, rotation, size, 1) {
}

void Missile::update(double deltaTime) {
    _boundingBox.setPosition(_position.x - _size/2, _position.y - _size/2);
    _position += _direction * _speed;
    _rotation += 1;
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