#include "cargoShip.h"

CargoShip::CargoShip(vec2 position, vec2 direction, float rotation, float size, unsigned short health)
: Entity(position, direction, rotation, size, health) {
}

void CargoShip::update(double deltaTime) {
    s = _size + (sin(deltaTime)*3);

    if (int(deltaTime) % 2) {
        _hazardLights = true;
    } else {
        _hazardLights = false;
    }
}

void CargoShip::draw() {
    ofNoFill();
    ofSetColor(COLOURS.BLUE);

    ofPushView();
        ofTranslate(_position);

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
            ofSetColor(COLOURS.ORANGE);

            ofDrawCircle(vec2(-s, s*2), s/10);
            ofDrawCircle(vec2(s, s*2), s/10);
        }
    ofPopView();

}