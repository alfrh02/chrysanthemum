#include "player.h"

void Player::update(double deltaTime) {
    // calculate directional vector
    _direction = vec2(sin(ofDegToRad(_rotation)), -cos(ofDegToRad(_rotation)));

    // if the player is holding down W or S, and `_speed` is between -_MAX_SPEED and _MAX_SPEED, we increase `_speed`
    if ((_w || _s) && (_speed < _MAX_SPEED && _speed > -_MAX_SPEED)) {
        _speed += 0.1 * (_w - _s);
    } else { // otherwise we decrement/increment depending on `_speed`'s current value, to make it turn back to 0.
        if (_speed > 0) {
            _speed -= _SPEED_RETURN_RATE;
        } else if (_speed < 0) {
            _speed += _SPEED_RETURN_RATE;
        }
    }

    _position += _direction * round(_speed);

    if (round(_speed) != 0) {
        _rotation += (_d - _a) * _ROTATION_SPEED;
        if (_rotation <= 0) {
            _rotation = 359;
        } else if (_rotation >= 360) {
            _rotation = 0;
        }
    }

    // handle player going off-screen
    if (_position.x > ofGetWidth() + _size) {
        _position.x = 0 - _size;
    } else if (_position.x < 0 - _size) {
        _position.x = ofGetWidth() + _size;
    }
    if (_position.y > ofGetHeight() + _size) {
        _position.y = 0 - _size;
    } else if (_position.y < 0 - _size) {
        _position.y = ofGetHeight() + _size;
    }

    for (int i = 0; i < missiles.size(); i++) {
        missiles[i]->update(deltaTime);
    }
}

void Player::draw() {
    // drawing the actual player "sprite"
    ofPushView();
        ofTranslate(_position);
        ofRotateDeg(_rotation);

        ofNoFill();
        ofSetColor(COLOURS.FOREGROUND);

        ofSetPolyMode(OF_POLY_WINDING_ODD);
        ofBeginShape();
            ofVertex(-_size, _size);
            ofVertex(0,      -_size);
            ofVertex(_size,  _size);
        ofEndShape();
    ofPopView();

    for (int i = 0; i < missiles.size(); i++) {
        missiles[i]->draw();
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
        case 32:
            missiles.push_back(new Missile(_position, _direction, _rotation));
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