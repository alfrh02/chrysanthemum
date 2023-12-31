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
                entities[i]->physicsCollision(entities[y]->getPosition(), entities[y]->getSpeed(), entities[y]->getDamage());
                entities[y]->physicsCollision(entities[i]->getPosition(), entities[i]->getSpeed(), entities[i]->getDamage());
            }
        }

        if (distance(entities[i]->getPosition(), playerPosition) > SETTINGS.SIMULATION_DISTANCE) {
            if (entities[i]->getIdentity() == "Asteroid") {
                _asteroidAmount--;
            }
            entities[i]->setHealth(0);
        }

        if (entities[i]->getHealth() <= 0) {
            delete entities[i];
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