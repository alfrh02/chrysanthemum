#include "cargoShip.h"

CargoShip::CargoShip(vec2 position, vec2 direction, float rotation, float size, unsigned short health)
: Ship(position, direction, rotation, size, health) {
    _identity = "CargoShip";
    _type = "CargoShip";
}

void CargoShip::update(double deltaTime) {
    _boundingBox.setPosition(_position.x - s, _position.y - s*2);
    _boundingBox.setWidth(s*2);
    _boundingBox.setHeight(s*6);

    // hazard lights are on every other second
    _hazardLights = int(deltaTime) % 2;

    s = _size + (sin(deltaTime)*3);
}

void CargoShip::draw() {
    ofPushView();
        ofTranslate(_position);

        ofSetColor(COLORS.FOREGROUND);

        // draw cargo amount - each letter is 8px wide, 11px tall
        if (_cargo > 0) {
            string str = to_string(_cargo) + "/" + to_string(_max_cargo);
            ofDrawBitmapString(str, vec2(-((int)str.length() * 8) / 2, s*5));
        }

        ofSetColor(COLORS.BLUE);

        ofDrawRectangle(vec2(-s/2, -s/2), s, s);
        ofDrawLine(vec2(-s/2, -s/2), vec2(s/2, s/2));
        ofDrawLine(vec2(s/2, -s/2), vec2(-s/2, s/2));

        ofTranslate(vec2(0, -s)); // jump up one (top box)

        ofDrawRectangle(vec2(-s/2, -s/2), s, s);
        ofDrawLine(vec2(-s/2, -s/2), vec2(s/2, s/2));
        ofDrawLine(vec2(s/2, -s/2), vec2(-s/2, s/2));

        ofTranslate(vec2(0, s*2)); // jump down two (last full box)

        ofDrawRectangle(vec2(-s/2, -s/2), s, s);
        ofDrawLine(vec2(-s/2, -s/2), vec2(s/2, s/2));
        ofDrawLine(vec2(s/2, -s/2), vec2(-s/2, s/2));

        ofTranslate(vec2(0, s)); // jump down one more (bottom box)
        ofDrawLine(vec2(-s/2, -s/2), vec2(-s/2, s/2 * 0.33));
        ofDrawLine(vec2(s/2, -s/2), vec2(s/2, s/2 * 0.33));

        ofDrawLine(vec2(0, -s/2 * 0.33), vec2(-s, s/2));
        ofDrawLine(vec2(0, -s/2 * 0.33), vec2(s, s/2));

        ofDrawLine(vec2(-s, s/2), vec2(-s, s*2));
        ofDrawLine(vec2(s, s/2), vec2(s, s*2));

        ofDrawLine(vec2(-s, s*2), vec2(0, s/2));
        ofDrawLine(vec2(s, s*2), vec2(0, s/2));

        ofDrawLine(vec2((0 + s) / 2, (s*2 + s/2) / 2), vec2((0 + s) / 1.5, s*2));
        ofDrawLine(vec2((0 - s) / 2, (s*2 + s/2) / 2), vec2((0 - s) / 1.5, s*2));

        if (_hazardLights) {
            ofSetColor(COLORS.ORANGE);

            ofDrawCircle(vec2(-s, s*2), s/10);
            ofDrawCircle(vec2(s, s*2), s/10);
        }
    ofPopView();
}