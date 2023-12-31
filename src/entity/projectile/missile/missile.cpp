#include "missile.h"

Missile::Missile(vec2 position, vec2 direction, float rotation, double deltaTime)
: Projectile(position, direction, rotation, deltaTime) {
    _identity = "Missile";
}

void Missile::draw() {
    ofPushView();
        ofTranslate(_position);
        ofRotateDeg(_rotation);
        ofTranslate(vec2(-_size/2, -_size/2) * _lifetime);

        ofNoFill();
        ofSetColor(COLOURS.FOREGROUND);
        ofDrawRectangle(0, 0, _size * _lifetime, _size * _lifetime);
    ofPopView();
}