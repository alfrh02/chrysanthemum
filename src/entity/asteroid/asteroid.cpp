#include "asteroid.h"

Asteroid::Asteroid(vec2 position, vec2 direction, float rotation, float size, unsigned short health, float speed, float seed, float xAmp, float yAmp)
: Entity(position, direction, rotation, size, health, speed) {
    _seed = seed;
    _xAmp = xAmp;
    _yAmp = yAmp;

    _rotation_speed = (ofRandom(2) + 0.2) * 0.1;
}

void Asteroid::update(double deltaTime) {
    _boundingBox.setPosition(_position.x - _size/2, _position.y - _size/2);
    _rotation += _rotation_speed;
    _position += _direction * round(_speed);

    _speed *= 0.98;
}

void Asteroid::draw() {
    ofSetColor(COLOURS.FOREGROUND);

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