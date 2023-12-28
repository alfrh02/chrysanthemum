#include "crystalAsteroid.h"

CrystalAsteroid::CrystalAsteroid(vec2 position)
: Asteroid(position) {
    _identity = "CrystalAsteroid";
}

void CrystalAsteroid::update(double deltaTime) {
    _boundingBox.setPosition(_position.x - _size/2, _position.y - _size/2);
    _rotation += _rotation_speed;
    _position += _direction * _speed;
}

void CrystalAsteroid::draw() {
    ofSetColor(COLOURS.MAGENTA);

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