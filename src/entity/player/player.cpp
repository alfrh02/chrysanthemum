#include "player.h"

Player::Player(vec2 position, vec2 direction, float rotation, float size, unsigned short health, float speed)
: Entity(position, direction, rotation, size, health, speed) {
    _identity = "Player";
    _type = "Player";
    _rotation_speed = 1.25;
}

void Player::update(double deltaTime) {
    _boundingBox.setPosition(_position.x - _size/2, _position.y - _size/2);

    // calculate directional vector
    _direction = vec2(sin(ofDegToRad(_rotation)), -cos(ofDegToRad(_rotation)));

    // calculate our speed based on if our player is holding W or S, & whether or not we are already at maximum speed
    if ((_w || _s) && (_speed < _MAX_SPEED && _speed > -_MAX_SPEED)) {
        _speed += (_w - _s) * 0.1;
    } else { // if we are not holding W or S we decrement/increment depending on `_speed`'s current value, to make it turn back to 0
        if (_speed > 0) {
            _speed -= _SPEED_RETURN_RATE;
        } else if (_speed < 0) {
            _speed += _SPEED_RETURN_RATE;
        }
    }

    // calculate rotation. the player cannot rotate if they are not moving
    if (round(_speed) != 0) {
        _rotation += (_d - _a) * _rotation_speed;
        if (_rotation <= 0) { // keep rotation within 360 degrees
            _rotation = 359;
        } else if (_rotation >= 360) {
            _rotation = 0;
        }
    }

    _position += _direction * round(_speed);
}

void Player::draw() {
    ofPushView();
        ofTranslate(_position);

        ofSetColor(COLORS.FOREGROUND);

        // draw cargo amount - each letter is 8px wide, 11px tall
        if (_cargo > 0) {
            string s = to_string(_cargo) + "/" + to_string(_max_cargo);
            ofDrawBitmapString(s, vec2(-((int)s.length() * 8) / 2, _size + _size/4));
        }

        ofRotateDeg(_rotation);

        ofSetPolyMode(OF_POLY_WINDING_ODD);
        ofBeginShape();
            ofVertex(-_size / 2, _size / 2);
            ofVertex(0,         -_size / 2);
            ofVertex(_size / 2,  _size / 2);
        ofEndShape();
    ofPopView();
}

void Player::keyPressed(int key) {
    switch(key) {
        case 'w':
            _w = true;
            break;
        case 'a':
            _a = true;
            break;
        case 's':
            _s = true;
            break;
        case 'd':
            _d = true;
            break;
    }
}

void Player::keyReleased(int key) {
    switch(key) {
        case 'w':
            _w = false;
            break;
        case 'a':
            _a = false;
            break;
        case 's':
            _s = false;
            break;
        case 'd':
            _d = false;
            break;
    }
}

bool Player::addCargo(int cargo) {
    _cargo += cargo;
    if (_cargo > _max_cargo) {
        _cargo = _max_cargo;
        return false;
    } else if (_cargo < 0) {
        _cargo = 0;
        return false;
    }
    return true;
}