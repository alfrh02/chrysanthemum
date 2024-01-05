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
    deltaTime += ofGetLastFrameTime();

    // update player & cargoship
    player.update(deltaTime);
    cargoship.update(deltaTime);

    vec2 playerPosition = player.getPosition();

    if (cargoship.getBoundingBox().intersects(player.getBoundingBox())) {
        if (player.addCargo(-1)) { // if we can subtract 1 from the players cargo, we will add it to the cargoship's cargo
            cargoship.addCargo(1);
        }
    }

    while (asteroidAmount < MAX_ASTEROIDS) {
        vec2 pos = vec2(0, 0);
        while (distance(pos + playerPosition, playerPosition) < RENDER_DISTANCE / 2) { // guarantee asteroid is outside of render distance but within simulation distance
            pos = vec2(
                ofRandom(SIMULATION_DISTANCE) - SIMULATION_DISTANCE/2,
                ofRandom(SIMULATION_DISTANCE) - SIMULATION_DISTANCE/2
            );
        }
        addAsteroid(pos + playerPosition);
    }

    // update all entities
    for (int i = 0; i < entities.size(); i++) {
        Entity* e = entities[i];
        e->update(deltaTime);

        // make crystals move towards the player when the player is in range
        // & player-crystal collision detection
        if (e->getIdentity() == "Crystal" && distance(e->getPosition(), playerPosition) < 128) {
            e->setDirection(normalize(playerPosition - e->getPosition()));
            if (e->getBoundingBox().intersects(player.getBoundingBox())) {
                if (player.addCargo(1)) {
                    e->setHealth(0);
                };
            }
        }

        for (int y = i + 1; y < entities.size(); y++) {
            Entity* e1 = entities[y];

            // exclude crystals from collision detection w/ asteroids and missiles
            if (e->getIdentity() == "Crystal" || e1->getIdentity() == "Crystal") {
                continue;
            }

            // using ofRectangle.instersects() that openFrameworks has kindly gifted us for AABB collision detection
            if (e->getBoundingBox().intersects(e1->getBoundingBox())) {
                e->physicsCollision(e1->getPosition(), e1->getSpeed(), e1->getDamage());
                e1->physicsCollision(e->getPosition(), e->getSpeed(), e->getDamage());
            }
        }

        // set entities who are outside of the simulation distance to dead
        if (distance(e->getPosition(), playerPosition) > SIMULATION_DISTANCE) {
            e->setHealth(0);
        }

        // delete dead entities
        if (e->getHealth() <= 0) {

            // calculate asteroid drops
            if (e->getType() == "Asteroid") {
                asteroidAmount--;

                ofColor color = COLORS.CRYSTAL;
                unsigned char crystalAmount = 0;
                if (e->getIdentity() == "RichCrystalAsteroid") {
                    color = COLORS.RICH_CRYSTAL;
                    crystalAmount = 8;
                } else if (e->getIdentity() == "CrystalAsteroid") {
                    crystalAmount = 4;
                } else {
                    if (ofRandom(1) < 0.25) { // 25% chance of dropping 1-2 crystals
                        crystalAmount = ofRandom(1) + 1;
                    }
                }

                for (int i = 0; i < crystalAmount; i++) {
                    addCrystal(e->getPosition(), vec2(cos(i/2), sin(i/2)), color);
                }
            }

            delete e;
            entities.erase(entities.begin() + i);
            i--;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(COLORS.BACKGROUND);

    vec2 playerPosition = player.getPosition();
    vec2 cargoshipPosition = cargoship.getPosition();

    // --- DRAW SCENE ---
    ofPushView();
        ofTranslate(ofGetWidth() / 2 - playerPosition.x, ofGetHeight() / 2 - playerPosition.y);

        ofNoFill();

        player.draw();
        cargoship.draw();
        if (debugMode) {
            player.drawBoundingBox();
            cargoship.drawBoundingBox();
        }

        for (Entity* e : entities) {
            if (distance(e->getPosition(), player.getPosition()) < RENDER_DISTANCE) {
                e->draw();
                if (debugMode) {
                    e->drawBoundingBox();
                }
            }
        }
    ofPopView();

    // --- DRAW GUI ---
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

        ofDrawBitmapString("            fps | " + to_string(ofGetFrameRate()), vec2(8, 16));
        ofDrawBitmapString("   time elapsed | " + to_string(deltaTime), vec2(8, 32));
        ofDrawBitmapString("player position | x " + to_string(playerPosition.x) + " y " + to_string(playerPosition.y), vec2(8, 48));
        ofDrawBitmapString("asteroid amount | " + to_string(asteroidAmount), vec2(8, 64));

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
    switch(key) {
        case ' ':
            addMissile(player.getPosition(), player.getDirection(), player.getRotation());
            break;
        case '`':
            debugMode = !debugMode;
            break;
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
    if (debugMode) {
        addAsteroid((vec2(x, y) + player.getPosition()) - vec2(ofGetWidth() / 2, ofGetHeight() / 2));
    }
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
void ofApp::addMissile(vec2 pos, vec2 dir, float rot) {
    Missile* m = new Missile(pos, dir, rot, deltaTime);
    entities.push_back(m);
}

//--------------------------------------------------------------
void ofApp::addCrystal(vec2 pos, vec2 dir, ofColor color) {
    Crystal* c = new Crystal(pos, dir, deltaTime, color);
    entities.push_back(c);
}