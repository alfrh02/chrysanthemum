#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cargoShip.setPosition(vec2(ofGetWidth() / 2, ofGetHeight() / 2));
    player.setPosition(vec2(ofGetWidth() / 2, ofGetHeight() / 2));

    for (int i = 0; i < 4; i++) {
        asteroids.push_back(new Asteroid(vec2(ofGetWidth() / (i + 1), ofGetHeight() / 2)));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < asteroids.size(); i++) {
        asteroids[i]->update(deltaTime);
    }
    cargoShip.update(deltaTime);
    player.update(deltaTime);

    deltaTime += ofGetLastFrameTime();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(COLOURS.BACKGROUND);

    for (int i = 0; i < asteroids.size(); i++) {
        asteroids[i]->draw();
    }

    cargoShip.draw();
    player.draw();

    if (debugMode) {
        // ofDrawBitmapStringHighlight(to_string(deltaTime), vec2(0, 0), ofColor(COLOURS.DEBUG_TEXT), ofColor(COLOURS.BACKGROUND));
        ofSetColor(COLOURS.GREEN);
        ofDrawBitmapString(
            to_string(deltaTime),
            vec2(8, 16)
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
    if (char(key) == '`') {
        debugMode = !debugMode;
    }
    player.keyPressed(key);
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
