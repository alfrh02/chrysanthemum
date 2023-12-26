#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    player.setPosition(vec2(ofGetWidth() / 2, ofGetHeight() / 2));
}

//--------------------------------------------------------------
void ofApp::update(){
    player.update(deltaTime);

    deltaTime += ofGetLastFrameTime();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(COLOURS.BACKGROUND);
    player.draw();

    if (debugMode) {
        // ofDrawBitmapStringHighlight(to_string(deltaTime), vec2(0, 0), ofColor(COLOURS.DEBUG_TEXT), ofColor(COLOURS.BACKGROUND));
        ofSetColor(COLOURS.DEBUG_TEXT);
        ofDrawBitmapString(
            to_string(deltaTime),
            vec2(8, 16)
        );

        // mouse coordinates
        ofDrawBitmapStringHighlight(
            to_string(ofGetMouseX()) + ", " + to_string(ofGetMouseY()),
            vec2(ofGetMouseX(), ofGetMouseY()),
            ofColor(COLOURS.DEBUG_TEXT),
            ofColor(COLOURS.BACKGROUND)
        );
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // cout << char(key) << ", " << key << endl;
    player.keyPressed(key);

    if (key == 3680) {
        debugMode = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    // cout << "released " << char(key) << ", " << key << endl;

    player.keyReleased(key);

    if (key == 3680) {
        debugMode = false;
    }
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
