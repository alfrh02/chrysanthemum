#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    player.setPosition(vec2(ofGetWidth() / 2, ofGetHeight() / 2));
}

//--------------------------------------------------------------
void ofApp::update(){
    player.update(deltaTime);
    // colonyShip.update(deltaTime);

    deltaTime += ofGetLastFrameTime();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(COLOURS.BACKGROUND);

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

    float s = 50 + (sin(deltaTime)*3);
    ofPushView();
        ofTranslate(vec2(ofGetWidth() / 2, ofGetHeight() / 2));

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

        // ofDrawCircle(vec2(s, s*2), s/4);
        // ofDrawCircle(vec2(0, s/2), s/4);
        // ofDrawCircle(vec2((0 + s) / 1.5, (s*2 + s/2) / 1.5), s/4);
        ofDrawLine(vec2((0 + s) / 2, (s*2 + s/2) / 2), vec2((0 + s) / 1.5, s*2));
        ofDrawLine(vec2((0 - s) / 2, (s*2 + s/2) / 2), vec2((0 - s) / 1.5, s*2));
    ofPopView();
    player.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
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
