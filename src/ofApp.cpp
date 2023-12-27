#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // cargoShip.setPosition(vec2(ofGetWidth() / 2, ofGetHeight() / 2));
    player.setPosition(vec2(ofGetWidth() / 2, ofGetHeight() / 2));

    CargoShip* c = new CargoShip(vec2(ofGetWidth() / 2, ofGetHeight() / 2));
    entities.push_back(c);

    for (int i = 0; i < 16; i++) {
        Asteroid* a = new Asteroid(vec2(ofRandom(ofGetWidth() / 3) + 100, ofRandom(ofGetHeight())));
        entities.push_back(a);
    }

    for (int i = 0; i < 16; i++) {
        Asteroid* a = new Asteroid(vec2(ofRandom(ofGetWidth() / 3) + (ofGetWidth() / 3) * 2, ofRandom(ofGetHeight())));
        entities.push_back(a);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < entities.size(); i++) {
        entities[i]->update(deltaTime);
        // iteratre thru the rest of the items in the vector (especially so we aren't comparing entities[i] to itself)
        for (int y = i + 1; y < entities.size(); y++) {
            // using ofRectangle.instersects() that openFrameworks has kindly gifted us for AABB collision detection
            if (entities[i]->getBoundingBox().intersects(entities[y]->getBoundingBox())) {
                // we dereference entities[i] to get the derived class name
                string e1 = typeid(*entities[i]).name();
                string e2 = typeid(*entities[y]).name();

                cout << e1 << ", " << e2 << endl;
                if (e1 == "8Asteroid" && e2 == "8Asteroid") {
                    if (entities[i]->getSpeed() < 0.1) {
                        entities[i]->setSpeed(0.25);
                    }
                    entities[i]->setSpeed(entities[i]->getSpeed() / 2);
                    vec2 dir = entities[i]->getPosition() - entities[y]->getPosition();
                    entities[i]->setDirection(dir);

                    entities[y]->setSpeed(entities[i]->getSpeed() / 2);
                    dir = entities[y]->getPosition() - entities[i]->getPosition();
                    entities[y]->setDirection(dir);
                }
            }
        }
    }

    player.update(deltaTime);

    deltaTime += ofGetLastFrameTime();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(COLOURS.BACKGROUND);

    for (int i = 0; i < entities.size(); i++) {
        entities[i]->draw();
    }

    player.draw();

    if (debugMode) {
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

        for (int i = 0; i < entities.size(); i++) {
            entities[i]->drawBoundingBox();
        }
        player.drawBoundingBox();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    player.keyPressed(key);

    switch(key) {
        case 32: // space
            entities.push_back(new Missile(player.getPosition(), player.getDirection(), player.getRotation()));
            break;
        case 96: // ` tilde
            debugMode = !debugMode;
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
    Asteroid* a = new Asteroid(vec2(x, y));
    entities.push_back(a);
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
