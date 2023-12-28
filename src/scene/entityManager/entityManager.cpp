#include "entityManager.h"

EntityManager::EntityManager() {
    cout << "Initialised EntityManager with a max asteroid count of " << _MAX_ASTEROIDS << endl;
}

EntityManager::~EntityManager() {
    for (Entity* e : entities) {
        delete e;
    }
}

void EntityManager::update(vec2 playerPosition,double deltaTime) {
    for (int i = 0; i < entities.size(); i++) {
        entities[i]->update(deltaTime);
        // collision detection !
        // iterate thru the rest of the items in the vector (especially so we aren't comparing entities[i] to itself)
        for (int y = i + 1; y < entities.size(); y++) {
            // using ofRectangle.instersects() that openFrameworks has kindly gifted us for AABB collision detection
            if (entities[i]->getBoundingBox().intersects(entities[y]->getBoundingBox())) {
                string e1 = entities[i]->getIdentity();
                string e2 = entities[y]->getIdentity();

                if (e1 == "Missile") {
                    entities[y]->physicsCollision(entities[i]->getPosition(), entities[i]->getSpeed());
                    entities[y]->takeDamage(entities[i]->getDamage());

                    entities[i]->setHealth(0);
                } else if (e2 == "Missile") {
                    entities[i]->physicsCollision(entities[y]->getPosition(), entities[y]->getSpeed());
                    entities[i]->takeDamage(entities[y]->getDamage());

                    entities[y]->setHealth(0);
                } else {
                    entities[i]->physicsCollision(entities[y]->getPosition(), entities[i]->getSpeed());
                    entities[y]->physicsCollision(entities[i]->getPosition(), entities[i]->getSpeed());
                }
            }
        }

        if (distance(entities[i]->getPosition(), playerPosition) > _DELETION_DISTANCE) {
            if (entities[i]->getIdentity() == "Asteroid") {
                _asteroidAmount--;
            }
            entities[i]->setHealth(0);
        }

        if (entities[i]->getHealth() == 0) {
            delete entities[i];
            entities.erase(entities.begin() + i);
            i--;
        }
    }

    while (_asteroidAmount < _MAX_ASTEROIDS) {
        vec2 pos = vec2(
            ofRandom(_DELETION_DISTANCE) - _DELETION_DISTANCE/2,
            ofRandom(_DELETION_DISTANCE) - _DELETION_DISTANCE/2
        );

        while (distance(pos + playerPosition, playerPosition) < _RENDER_DISTANCE / 2) {
            pos = vec2(
                ofRandom(_DELETION_DISTANCE) - _DELETION_DISTANCE/2,
                ofRandom(_DELETION_DISTANCE) - _DELETION_DISTANCE/2
            );
        }
        addAsteroid(pos + playerPosition);
    }
}

void EntityManager::draw(vec2 playerPosition) {
    for (Entity* e : entities) {
        if (distance(e->getPosition(), playerPosition) < _RENDER_DISTANCE) {
            e->draw();
        }
    }
}

void EntityManager::drawBoundingBox(vec2 playerPosition) {
    for (Entity* e : entities) {
        if (distance(e->getPosition(), playerPosition) < _RENDER_DISTANCE) {
            e->drawBoundingBox();
        }
    }
}

void EntityManager::addAsteroid(vec2 pos) {
    if (ofRandom(1) > 0.5) {
        CrystalAsteroid* a = new CrystalAsteroid(pos)
    } else {
        Asteroid* a = new Asteroid(pos);
    }
    entities.push_back(a);
    _asteroidAmount++;
}

void EntityManager::addMissile(vec2 pos, vec2 dir, float rot, double deltaTime) {
    Missile* m = new Missile(pos, dir, rot, deltaTime);
    entities.push_back(m);
}