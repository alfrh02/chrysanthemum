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
    ofBackground(COLORS.BACKGROUND);

    // draw dynamic GUI + scene
    ofPushView();
        ofTranslate(ofGetWidth() / 2 - player.getPosition().x, ofGetHeight() / 2 - player.getPosition().y);

        // DRAW BACKGROUND

        // sun
        ofSetColor(COLORS.ORANGE);
        ofDrawCircle((player.getPosition() / 1.015) + vec2(200, -200), 50);

        // planet
        ofSetColor(COLORS.BACKGROUND);
        ofFill();

        ofDrawCircle((player.getPosition() / 1.025) + vec2(-200, 1200), 1500);

        // outline
        ofSetColor(COLORS.GRAY);
        ofNoFill();

        ofDrawCircle((player.getPosition() / 1.025) + vec2(-200, 1200), 1500);

        if (debugMode) {
            entities.drawBoundingBox(player.getPosition());
            cargoShip.drawBoundingBox();
            player.drawBoundingBox();
        }

        entities.draw(player.getPosition());
        cargoShip.draw();
        player.draw();
    ofPopView();

    // draw static GUI

    // cargoship pointer
    if (distance(player.getPosition(), cargoShip.getPosition()) > ofGetHeight() / 2) {
        ofSetColor(COLORS.BLUE);

        vec2 dir = normalize(cargoShip.getPosition() - player.getPosition());
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
            "player position | x " + to_string(player.getPosition().x) + " y " + to_string(player.getPosition().y),
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
