#include "enemy.h"

Enemy::Enemy(vec2 position, vec2 direction, float rotation, float size, unsigned short health, float speed)
: Ship(position, direction, rotation, size, health, speed) {
    _identity = "Enemy";
    _rotation_speed = 1.25;
    _color = COLORS.RED;

    cout << "Spawned enemy" << endl;
}

void Enemy::update(double deltaTime) {
    _boundingBox.setPosition(_position.x - _size/2, _position.y - _size/2);
    // _direction = vec2(sin(ofDegToRad(_rotation)), -cos(ofDegToRad(_rotation)));
    _position += _direction * round(_speed);
}

void Enemy::draw() {
    ofPushView();
        ofTranslate(_position);
        ofRotateDeg(_rotation);

        ofSetColor(_color);
        ofDrawCircle(0, 0, 5);

        ofSetPolyMode(OF_POLY_WINDING_ODD);
        ofBeginShape();
            ofVertex(-_size / 2, _size / 2);
            ofVertex(0,         -_size / 2);
            ofVertex(_size / 2,  _size / 2);
        ofEndShape();
    ofPopView();
}