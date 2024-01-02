#include "player.h"

Player::Player(vec2 position, vec2 direction, float rotation, float size, unsigned short health, float speed)
: Ship(position, direction, rotation, size, health, speed) {
    _identity = "Player";
    _rotation_speed = 1.25;

    cout << "Spawned player" << endl;
}

void Player::update(double deltaTime) {
    _boundingBox.setPosition(_position.x - _size/2, _position.y - _size/2);

    // calculate directional vector
    _direction = vec2(sin(ofDegToRad(_rotation)), -cos(ofDegToRad(_rotation)));

    // if the player is holding down W or S, and `_speed` is between -_MAX_SPEED and _MAX_SPEED, we increase `_speed`
    if ((_w || _s) && (_speed < _MAX_SPEED && _speed > -_MAX_SPEED)) {
        _speed += (_w - _s) * 0.1;
    } else { // otherwise we decrement/increment depending on `_speed`'s current value, to make it turn back to 0.
        if (_speed > 0) {
            _speed -= _SPEED_RETURN_RATE;
        } else if (_speed < 0) {
            _speed += _SPEED_RETURN_RATE;
        }
    }

    _position += _direction * round(_speed);

    if (round(_speed) != 0) {
        _rotation += (_d - _a) * _rotation_speed;
        if (_rotation <= 0) {
            _rotation = 359;
        } else if (_rotation >= 360) {
            _rotation = 0;
        }
    }
}

void Player::draw() {
    ofPushView();
        ofTranslate(_position);

        ofSetColor(_color);
        // each letter is 8px wide, 11px tall
        if (_cargo > 0) {
            string s = to_string(_cargo) + "/" + to_string(_max_cargo);
            ofDrawBitmapString(s, vec2(-((int)s.length() * 8) / 2, _size + _size/4));
        }

        ofRotateDeg(_rotation);
        // ofDrawCircle(0, 0, 5);

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