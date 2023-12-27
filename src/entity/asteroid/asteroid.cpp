#include "asteroid.h"

Asteroid::Asteroid(vec2 position, vec2 direction, float rotation, float size, unsigned short health, float speed, float seed, float xAmp, float yAmp)
: Entity(position, direction, rotation, size, health, speed) {
    _seed = seed;
    _xAmp = xAmp;
    _yAmp = yAmp;

    _rotation_speed = (ofRandom(1) - 2) * 0.1;
}

void Asteroid::update(double deltaTime) {
    _rotation += _rotation_speed;
}

void Asteroid::draw() {
    ofSetColor(COLOURS.RED);

    ofPushView();
        ofTranslate(_position);
        ofRotateDeg(_rotation);

        ofBeginShape();
            for (float i = 0; i < 6; i += 0.5) {
                ofVertex(
                    (cos(i) + ofNoise(_seed/i)) * (_size * _xAmp),
                    (sin(i) + ofNoise(_seed/i)) * (_size * _yAmp)
                );
            }
        ofEndShape();
    ofPopView();
}