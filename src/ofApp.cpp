#include "ofApp.h"

//--------------------------------------------------------------
ofApp::~ofApp(){
    for (Entity* e : entities) {
        delete e;
    }
}

//--------------------------------------------------------------
void ofApp::setup(){
}

//--------------------------------------------------------------
void ofApp::update(){
    player.update(deltaTime);
    cargoship.update(deltaTime);

    vec2 playerPosition = player.getPosition();

    for (int i = 0; i < entities.size(); i++) {
        Entity* e = entities[i];
        e->update(deltaTime);

        // collision detection
        // iterate through the rest of the items in the vector (especially so we aren't comparing e to itself)
        for (int y = i + 1; y < entities.size(); y++) {
            Entity* e1 = entities[y];

            string e_identity = e->getType();
            string e1_identity = e1->getType();


            if (e->getIdentity() == "Crystal" || e1->getIdentity() == "Crystal") {
                continue;
            }

            if (e->getType() != "Projectile" && e1->getType() != "Projectile") {
                if (e_identity != e1_identity) {
                    continue;
                }
            }

            // using ofRectangle.instersects() that openFrameworks has kindly gifted us for AABB collision detection
            if (e->getBoundingBox().intersects(e1->getBoundingBox())) {
                e->physicsCollision(e1->getPosition(), e1->getSpeed(), e1->getDamage());
                e1->physicsCollision(e->getPosition(), e->getSpeed(), e->getDamage());
            }
        }

        if (e->getIdentity() == "Crystal" && distance(e->getPosition(), playerPosition) < 128) {
            e->setDirection(normalize(playerPosition - e->getPosition()));

            if (e->getBoundingBox().intersects(player.getBoundingBox())) {
                if (player.addCargo(1)) {
                    e->setHealth(0);
                };
            }
        }

        // set entities who are outside of the simulation distance to dead
        if (distance(e->getPosition(), playerPosition) > SIMULATION_DISTANCE) {
            if (e->getType() == "Asteroid") {
                asteroidAmount--;
            }
            e->setHealth(0);
        }

        // delete dead entities
        if (e->getHealth() <= 0) {
            onDeath(i, deltaTime);
            delete e;
            entities.erase(entities.begin() + i);
            i--;
        }
    }

    if (cargoship.getBoundingBox().intersects(player.getBoundingBox())) {
        if (player.addCargo(-1)) {
            cargoship.addCargo(1);
        }
    }

    while (asteroidAmount < MAX_ASTEROIDS) {
        vec2 pos = vec2(
            ofRandom(SIMULATION_DISTANCE) - SIMULATION_DISTANCE/2,
            ofRandom(SIMULATION_DISTANCE) - SIMULATION_DISTANCE/2
        );

        while (distance(pos + playerPosition, playerPosition) < RENDER_DISTANCE / 2) {
            pos = vec2(
                ofRandom(SIMULATION_DISTANCE) - SIMULATION_DISTANCE/2,
                ofRandom(SIMULATION_DISTANCE) - SIMULATION_DISTANCE/2
            );
        }
        addAsteroid(pos + playerPosition);
    }

    deltaTime += ofGetLastFrameTime();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(COLORS.BACKGROUND);

    vec2 playerPosition = player.getPosition();
    vec2 cargoshipPosition = cargoship.getPosition();

    // draw scene
    ofPushView();
        ofTranslate(ofGetWidth() / 2 - playerPosition.x, ofGetHeight() / 2 - playerPosition.y);
        player.draw();
        cargoship.draw();
        for (Entity* e : entities) {
            if (distance(e->getPosition(), player.getPosition()) < RENDER_DISTANCE) {
                e->draw();
                if (debugMode) {
                    e->drawBoundingBox();
                }
            }
        }
    ofPopView();

    // draw static GUI

    // cargoship pointer
    if (distance(playerPosition, cargoshipPosition) > ofGetHeight() / 2) {
        ofSetColor(COLORS.BLUE);

        vec2 dir = normalize(cargoshipPosition - playerPosition);
        dir += 1;
        dir /= 2;

        vec2 pos = vec2(ofGetWidth() * dir.x, ofGetHeight() * dir.y);

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
    player.keyPressed(key);

    switch(key) {
        case 32: // space
            addMissile(player.getPosition(), player.getDirection(), player.getRotation(), deltaTime);
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
    // entities.addAsteroid((vec2(x, y) + playerPosition) - vec2(ofGetWidth() / 2, ofGetHeight() / 2));
    // entities.addEnemy(vec2(x, y) + entities.player.getPosition() - vec2(ofGetWidth() / 2, ofGetHeight() / 2));
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

//--------------------------------------------------------------
void ofApp::onDeath(unsigned short index, double deltaTime) {
    Entity* e = entities[index];
    ofColor color = COLORS.CRYSTAL;

    if (e->getType() == "Asteroid") {
        unsigned char crystalAmount = 0;
        if (e->getIdentity() == "RichCrystalAsteroid") {
            color = COLORS.RICH_CRYSTAL;
            crystalAmount = 16;
        } else if (e->getIdentity() == "CrystalAsteroid") {
            crystalAmount = 8;
        } else {
            if (ofRandom(1) < 0.25) { // 25% chance of dropping 1-2 crystals
                crystalAmount = ofRandom(1) + 1;
            }
        }

        for (int i = 0; i < crystalAmount; i++) {
            addCrystal(e->getPosition(), vec2(cos(i/2), sin(i/2)), deltaTime, color);
        }
    }
}

//--------------------------------------------------------------
void ofApp::addAsteroid(vec2 pos) {
    Asteroid* a;
    if (ofRandom(1) < CRYSTAL_ASTEROID_SPAWN_CHANCE) {
        if (ofRandom(1) < RICH_CRYSTAL_ASTEROID_SPAWN_CHANCE) {
            a = new RichCrystalAsteroid(pos);
        } else {
            a = new CrystalAsteroid(pos);
        }
    } else {
        a = new Asteroid(pos);
    }
    entities.push_back(a);
    asteroidAmount++;
}

//--------------------------------------------------------------
void ofApp::addMissile(vec2 pos, vec2 dir, float rot, double deltaTime) {
    Missile* m = new Missile(pos, dir, rot, deltaTime);
    entities.push_back(m);
}

//--------------------------------------------------------------
void ofApp::addCrystal(vec2 pos, vec2 dir, double deltaTime, ofColor color) {
    Crystal* c = new Crystal(pos, dir, deltaTime, color);
    entities.push_back(c);
}