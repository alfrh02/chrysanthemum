#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
}

//--------------------------------------------------------------
void ofApp::update(){
    entities.update(player.getPosition(), deltaTime);
    cargoShip.update(deltaTime);
    player.update(deltaTime);

    deltaTime += ofGetLastFrameTime();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(COLOURS.BACKGROUND);

    // draw static GUI
    if (debugMode) {
        ofSetColor(COLOURS.GREEN);

        // top left
        // framerate + deltatime
        ofDrawBitmapString(
            to_string(ofGetFrameRate()),
            vec2(8, 16)
        );

        ofDrawBitmapString(
            to_string(deltaTime),
            vec2(8, 32)
        );

        // mouse coordinates
        ofDrawBitmapStringHighlight(
            to_string(ofGetMouseX()) + ", " + to_string(ofGetMouseY()),
            vec2(ofGetMouseX(), ofGetMouseY()),
            ofColor(COLOURS.GREEN),
            ofColor(COLOURS.BACKGROUND)
        );
    }

    // draw dynamic GUI + scene
    ofTranslate(ofGetWidth() / 2 - player.getPosition().x, ofGetHeight() / 2 - player.getPosition().y);

    if (debugMode) {
        entities.drawBoundingBox(player.getPosition());
        cargoShip.drawBoundingBox();
        player.drawBoundingBox();
    }

    entities.draw(player.getPosition());
    cargoShip.draw();
    player.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    player.keyPressed(key);

    switch(key) {
        case 32: // space
            entities.addMissile(player.getPosition(), player.getDirection(), player.getRotation(), deltaTime);
            break;
        case 96: // ` tilde
            debugMode = !debugMode;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    player.keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    entities.addAsteroid((vec2(x, y) + player.getPosition()) - vec2(ofGetWidth() / 2, ofGetHeight() / 2));
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
