#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    player.setPosition(vec2(ofGetWidth() / 2, ofGetHeight() / 2));
}

//--------------------------------------------------------------
void ofApp::update(){
    entities.update(deltaTime);
    player.update(deltaTime);

    deltaTime += ofGetLastFrameTime();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(COLOURS.BACKGROUND);

    entities.draw();
    player.draw();

    if (debugMode) {
        entities.drawBoundingBox();
        player.drawBoundingBox();

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
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    player.keyPressed(key);

    switch(key) {
        case 32: // space
            entities.addMissile(player.getPosition(), player.getDirection(), player.getRotation());
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
    entities.addAsteroid(vec2(x, y));
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
