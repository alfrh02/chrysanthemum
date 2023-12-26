#include "missile.h"

Missile::Missile(vec2 position, vec2 direction, float rotation) {
    _position = position;
    _direction = direction;
    _rotation = rotation;
}


void Missile::update(double deltaTime) {
    _lifetime += ofGetLastFrameTime() * 2;
    _position += _direction * _speed;
}

void Missile::draw() {
    unsigned short size = _size;

    ofSetColor(COLOURS.FOREGROUND);

    ofPushView();
        ofTranslate(_position);
        ofRotateDeg(_rotation);
        if ((int)_lifetime % 2) {
            ofTranslate(vec2(size/2, -size/4));
            ofRotateDeg(45);
        }

        ofSetColor(COLOURS.FOREGROUND);
        ofDrawRectangle(vec2(0, 0), size, size);

        size -= 1;
        ofSetColor(COLOURS.BACKGROUND);

        ofDrawRectangle(vec2(0.5, 0.5), size, size);
    ofPopView();
}

bool Missile::isDeadYet() {
    return _lifetime > _lifespan;
}