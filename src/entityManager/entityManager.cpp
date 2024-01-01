#include "entityManager.h"

EntityManager::EntityManager() {
    cout << "Initialised EntityManager with a max asteroid count of " << _MAX_ASTEROIDS << endl;
}

EntityManager::~EntityManager() {
    for (Entity* e : entities) {
        delete e;
    }
}

void EntityManager::update(double deltaTime) {
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

            if (e->getIdentity() == "Crystal" || e1->getIdentity() == "Crystal") {
                continue;
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
        if (distance(e->getPosition(), playerPosition) > SETTINGS.SIMULATION_DISTANCE) {
            if (e->getType() == "Asteroid") {
                _asteroidAmount--;
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

void EntityManager::draw() {
    player.draw();
    cargoship.draw();

    for (Entity* e : entities) {
        if (distance(e->getPosition(), player.getPosition()) < SETTINGS.RENDER_DISTANCE) {
            e->draw();
        }
    }
}

void EntityManager::drawBoundingBox() {
    player.drawBoundingBox();
    cargoship.drawBoundingBox();

    for (Entity* e : entities) {
        if (distance(e->getPosition(), player.getPosition()) < SETTINGS.RENDER_DISTANCE) {
            e->drawBoundingBox();
        }
    }
}

void EntityManager::onDeath(unsigned short index, double deltaTime) {
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

void EntityManager::addCrystal(vec2 pos, vec2 dir, double deltaTime, ofColor color) {
    Crystal* c = new Crystal(pos, dir, deltaTime, color);
    entities.push_back(c);
}