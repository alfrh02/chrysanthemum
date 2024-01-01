#include "ship.h"

Ship::Ship(vec2 position, vec2 direction, float rotation, float size, unsigned short health, float speed)
: Entity(position, direction, rotation, size, health, speed) {
    _color = COLORS.FOREGROUND;
    _identity = "Ship";
    _type = "Ship";
}

void Ship::draw() {
    ofPushView();
        ofTranslate(_position);
        ofRotateDeg(_rotation);

        ofSetColor(_color);

        ofSetPolyMode(OF_POLY_WINDING_ODD);
        ofBeginShape();
            ofVertex(-_size / 2, _size / 2);
            ofVertex(0,         -_size / 2);
            ofVertex(_size / 2,  _size / 2);
        ofEndShape();
    ofPopView();
}