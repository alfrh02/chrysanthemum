#include "crystal.h"

Crystal::Crystal(vec2 position, vec2 direction, double deltaTime, ofColor color)
: Projectile(position, direction, 0.0, deltaTime) {
    _speed = 0.25;
    _identity = "Crystal";
    _lifespan = 4;

    _color = color;
}

void Crystal::draw() {
    ofPushView();
        ofTranslate(_position);
        ofRotateDeg(_rotation);
        ofTranslate(vec2(-_size/2, -_size/2) * _lifetime);

        ofFill();
        ofSetColor(_color);
        ofDrawRectangle(0, 0, _size * _lifetime, _size * _lifetime);
    ofPopView();
}