#include "entityManager.h"

EntityManager::EntityManager() {
    cout << "Initialised EntityManager with a max asteroid count of " << _MAX_ASTEROIDS << endl;
}

EntityManager::~EntityManager() {
    for (Entity* e : entities) {
        delete e;
    }
}

void EntityManager::update(vec2 playerPosition, double deltaTime) {
    for (int i = 0; i < entities.size(); i++) {
        Entity* e = entities[i];
        e->update(deltaTime);

        // collision detection
        // iterate thru the rest of the items in the vector (especially so we aren't comparing e to itself)
        for (int y = i + 1; y < entities.size(); y++) {
            Entity* e1 = entities[y];
            // using ofRectangle.instersects() that openFrameworks has kindly gifted us for AABB collision detection
            if (e->getBoundingBox().intersects(e1->getBoundingBox())) {
                e->physicsCollision(e1->getPosition(), e1->getSpeed(), e1->getDamage());
                e1->physicsCollision(e->getPosition(), e->getSpeed(), e->getDamage());
            }
        }

        // set entities who are outside of the simulation distance to dead
        if (distance(e->getPosition(), playerPosition) > SETTINGS.SIMULATION_DISTANCE) {
            if (e->getIdentity() == "Asteroid" || e->getIdentity() == "CrystalAsteroid" || e->getIdentity() == "RichCrystalAsteroid") {
                _asteroidAmount--;
            }
            e->setHealth(0);
        }

        // delete dead entities
        if (e->getHealth() <= 0) {
            delete e;
            entities.erase(entities.begin() + i);
            i--;
        }
    }

    while (_asteroidAmount < _MAX_ASTEROIDS) {
        vec2 pos = vec2(
            ofRandom(SETTINGS.SIMULATION_DISTANCE) - SETTINGS.SIMULATION_DISTANCE/2,
            ofRandom(SETTINGS.SIMULATION_DISTANCE) - SETTINGS.SIMULATION_DISTANCE/2
        );

        while (distance(pos + playerPosition, playerPosition) < SETTINGS.RENDER_DISTANCE / 2) {
            pos = vec2(
                ofRandom(SETTINGS.SIMULATION_DISTANCE) - SETTINGS.SIMULATION_DISTANCE/2,
                ofRandom(SETTINGS.SIMULATION_DISTANCE) - SETTINGS.SIMULATION_DISTANCE/2
            );
        }
        addAsteroid(pos + playerPosition);
    }
}

void EntityManager::draw(vec2 playerPosition) {
    for (Entity* e : entities) {
        if (distance(e->getPosition(), playerPosition) < SETTINGS.RENDER_DISTANCE) {
            e->draw();
        }
    }
}

void EntityManager::drawBoundingBox(vec2 playerPosition) {
    for (Entity* e : entities) {
        if (distance(e->getPosition(), playerPosition) < SETTINGS.RENDER_DISTANCE) {
            e->drawBoundingBox();
        }
    }
}

void EntityManager::addAsteroid(vec2 pos) {
    Asteroid* a;
    if (ofRandom(1) < SETTINGS.CRYSTAL_ASTEROID_SPAWN_CHANCE) {
        if (ofRandom(1) < SETTINGS.RICH_CRYSTAL_ASTEROID_SPAWN_CHANCE) {
            a = new RichCrystalAsteroid(pos);
        } else {
            a = new CrystalAsteroid(pos);
        }
    } else {
        a = new Asteroid(pos);
    }
    entities.push_back(a);
    _asteroidAmount++;
}

void EntityManager::addMissile(vec2 pos, vec2 dir, float rot, double deltaTime) {
    Missile* m = new Missile(pos, dir, rot, deltaTime);
    entities.push_back(m);
}