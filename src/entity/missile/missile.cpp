#include "missile.h"

Missile::Missile(vec2 position, vec2 direction, float rotation, float size) {
    _position = position;
    _direction = direction;
    _rotation = rotation;

    _size = size;
}


void Missile::update(double deltaTime) {
    _position += _direction * _speed;
    _rotation += 1;
}

void Missile::draw() {
    ofPushView();
        ofTranslate(_position);
        ofTranslate(vec2(-_size/2, -_size/2));
        ofRotateDeg(_rotation);

        ofNoFill();
        ofSetColor(COLOURS.FOREGROUND);
        ofDrawRectangle(0, 0, _size, _size);
    ofPopView();
}

bool Missile::isDeadYet() {
    // return _lifetime > _lifespan;
    return false;
}