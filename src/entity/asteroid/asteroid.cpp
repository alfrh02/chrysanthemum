#include "asteroid.h"

Asteroid::Asteroid(vec2 position, vec2 direction, float rotation, float size, unsigned short health, float speed, float seed, float xAmp, float yAmp)
: Entity(position, direction, rotation, size, health, speed) {
    _identity = "Asteroid";

    _seed = seed;
    _xAmp = xAmp;
    _yAmp = yAmp;

    _speed = ofRandom(1) * 0.05;
    _rotation_speed = (ofRandom(2) + 0.2) * 0.1; // set rotation speed to something random + slow

    if (ofRandom(1) > 0.5) { // rotation speed has a 50% chance of inverting
        _rotation_speed = -_rotation_speed;
    }

    // make their bounding box 10% smaller to account for their irregular shape
    _boundingBox = ofRectangle(_position - _size/2, _size - (_size/10), _size - (_size/10));

    _color = COLORS.FOREGROUND;
}

void Asteroid::update(double deltaTime) {
    _boundingBox.setPosition(_position.x - _size/2, _position.y - _size/2);
    _rotation += _rotation_speed;
    _position += _direction * _speed;
}

void Asteroid::draw() {
    ofSetColor(_color);

    ofPushView();
        ofTranslate(_position);
        ofRotateDeg(_rotation);
        ofTranslate(vec2(-_size/4, -_size/4));

        ofBeginShape();
            for (float i = 0; i < 6; i += 0.5) {
                ofVertex(
                    (cos(i) + ofNoise(_seed/i)) * (_size/2 * _xAmp),
                    (sin(i) + ofNoise(_seed/i)) * (_size/2 * _yAmp)
                );
            }
            ofVertex(
                (cos(0.5) + ofNoise(_seed/0.5)) * (_size/2 * _xAmp),
                (sin(0.5) + ofNoise(_seed/0.5)) * (_size/2 * _yAmp)
            );
        ofEndShape();
    ofPopView();
}