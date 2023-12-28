#include "entityManager.h"

EntityManager::EntityManager(unsigned short startingAsteroids) {
    cout << "Initialised EntityManager with " << startingAsteroids << " starting asteroids" << endl;

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

EntityManager::~EntityManager() {
    for (Entity* e : entities) {
        delete e;
    }
}

void EntityManager::update(double deltaTime) {
    for (int i = 0; i < entities.size(); i++) {
        entities[i]->update(deltaTime);
        // collision detection !
        // iterate thru the rest of the items in the vector (especially so we aren't comparing entities[i] to itself)
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
                } else if (e1 == "7Missile") {
                    entities[y]->setSpeed(0.1);
                    vec2 dir = entities[y]->getPosition() - entities[i]->getPosition();
                    entities[y]->setDirection(dir);

                    entities[y]->takeDamage(entities[i]->getDamage());

                    entities[i]->setHealth(0);
                } else if (e2 == "7Missile") {
                    entities[i]->setSpeed(0.05);
                    vec2 dir = entities[i]->getPosition() - entities[y]->getPosition();
                    entities[i]->setDirection(dir);

                    entities[i]->takeDamage(entities[y]->getDamage());

                    entities[y]->setHealth(0);
                }
            }
        }

        if (entities[i]->getHealth() == 0) {
            // cout << entities[i] << endl;
            delete entities[i];
            i -= 1;
            // entities.erase(entities.begin() + i);
        }
    }

    // for (Entity* e : entities) {
    //     if (e->getHealth() == 0) {
    //         delete e;
    //     }
    // }
}

void EntityManager::draw() {
    for (Entity* e : entities) {
        e->draw();
    }
}

void EntityManager::drawBoundingBox() {
    for (Entity* e : entities) {
        e->drawBoundingBox();
    }
}

void EntityManager::addAsteroid(vec2 pos) {
    Asteroid* a = new Asteroid(pos);
    entities.push_back(a);
}

void EntityManager::addMissile(vec2 pos, vec2 dir, float rot) {
    Missile* m = new Missile(pos, dir, rot);
    entities.push_back(m);
}