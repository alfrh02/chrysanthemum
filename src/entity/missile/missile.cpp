#include "missile.h"

Missile::Missile(vec2 position, vec2 direction, float rotation) {
    _position = position;
    _direction = direction;
    _rotation = rotation;
}


void Missile::update(double deltaTime) {
    _lifetime += ofGetLastFrameTime();
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
        // ofSetPolyMode(OF_POLY_WINDING_NONZERO);
        // ofBeginShape();
        //     ofVertex(0, 0);
        //     ofVertex(_size, 0);
        //     ofVertex(_size, _size);
        //     ofVertex(0, _size);
        // ofEndShape();
    ofPopView();
}

bool Missile::isDeadYet() {
    return _lifetime > _lifespan;
}