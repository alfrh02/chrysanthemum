#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
}

//--------------------------------------------------------------
void ofApp::update(){
    entities.update(deltaTime);

    deltaTime += ofGetLastFrameTime();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(COLORS.BACKGROUND);

    vec2 playerPosition = entities.player.getPosition();
    vec2 cargoshipPosition = entities.cargoship.getPosition();

    // draw dynamic GUI + scene
    ofPushView();
        ofTranslate(ofGetWidth() / 2 - playerPosition.x, ofGetHeight() / 2 - playerPosition.y);

        // DRAW BACKGROUND

        // sun
        ofSetColor(COLORS.ORANGE);
        ofDrawCircle((playerPosition / 1.015) + vec2(200, -200), 50);

        // planet
        ofSetColor(COLORS.BACKGROUND);
        ofFill();

        ofDrawCircle((playerPosition / 1.025) + vec2(-200, 1200), 1500);

        // outline
        ofSetColor(COLORS.GRAY);
        ofNoFill();

        ofDrawCircle((playerPosition / 1.025) + vec2(-200, 1200), 1500);

        if (debugMode) {
            entities.drawBoundingBox();
        }

        entities.draw();
    ofPopView();

    // draw static GUI

    // cargoship pointer
    if (distance(playerPosition, cargoshipPosition) > ofGetHeight() / 2) {
        ofSetColor(COLORS.BLUE);

        vec2 dir = normalize(cargoshipPosition - playerPosition);
        dir += 1;
        dir /= 2;

        vec2 pos = vec2(ofGetWidth() * dir.x + 1, ofGetHeight() * dir.y);

        ofDrawCircle(pos, 10);
    }

    if (debugMode) {
        ofSetColor(COLORS.GREEN);

        // top left
        // framerate + deltatime
        ofDrawBitmapString(
            "            fps | " + to_string(ofGetFrameRate()),
            vec2(8, 16)
        );

        ofDrawBitmapString(
            "   time elapsed | " + to_string(deltaTime),
            vec2(8, 32)
        );

        ofDrawBitmapString(
            "player position | x " + to_string(playerPosition.x) + " y " + to_string(playerPosition.y),
            vec2(8, 48)
        );

        // mouse coordinates
        ofDrawBitmapStringHighlight(
            to_string(ofGetMouseX()) + ", " + to_string(ofGetMouseY()),
            vec2(ofGetMouseX(), ofGetMouseY()),
            ofColor(COLORS.GREEN),
            ofColor(COLORS.BACKGROUND)
        );
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    entities.player.keyPressed(key);

    switch(key) {
        case 32: // space
            entities.addMissile(entities.player.getPosition(), entities.player.getDirection(), entities.player.getRotation(), deltaTime);
            break;
        case 96: // ` tilde
            debugMode = !debugMode;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    entities.player.keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // entities.addAsteroid((vec2(x, y) + playerPosition) - vec2(ofGetWidth() / 2, ofGetHeight() / 2));
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
