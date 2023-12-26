#include "player.h"

Player::Player(vec2 position) {
    cout << "Creating Player" << endl;

    _position = position;
}

Player::~Player() {
    cout << "Destroying Player" << endl;
}

void Player::draw() {
    // drawing the actual player "sprite"
    ofPushView();
        ofTranslate(_position);
        ofRotateDeg(_rotation);

        short size = _size;

        ofSetColor(COLOURS.FOREGROUND);
        ofDrawTriangle(
            vec2(-size, size),
            vec2(0,     -size - 5),
            vec2(size,  size)
        );

        size -= 1;

        ofSetColor(COLOURS.BACKGROUND);
        ofDrawTriangle(
            vec2(-size, size),
            vec2(0,      -size - 5),
            vec2(size,  size)
        );
    ofPopView();
}

void Player::update(double deltaTime) {
    vec2 dir = vec2(sin(ofDegToRad(_rotation)), -cos(ofDegToRad(_rotation)));
    _position += dir * (_w - _s);

    _rotation += (_d - _a);
    if (_rotation <= 0) {
        _rotation = 359;
    } else if (_rotation >= 360) {
        _rotation = 0;
    }
}

void Player::keyPressed(int key) {
    switch(key) {
        case 119:
            _w = true;
            break;
        case 97:
            _a = true;
            break;
        case 115:
            _s = true;
            break;
        case 100:
            _d = true;
            break;
    }
}

void Player::keyReleased(int key) {
    switch(key) {
        case 119:
            _w = false;
            break;
        case 97:
            _a = false;
            break;
        case 115:
            _s = false;
            break;
        case 100:
            _d = false;
            break;
    }
}

void Player::setPosition(vec2 position) {
    _position = position;
}