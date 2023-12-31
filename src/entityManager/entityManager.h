#pragma once

#include "asteroid.h"
#include "crystalAsteroid.h"
#include "richCrystalAsteroid.h"

#include "crystal.h"

#include "cargoShip.h"
#include "missile.h"

class EntityManager {
    public:
        EntityManager();
        ~EntityManager();

        void update(vec2 playerPosition, double deltaTime);
        void draw(vec2 playerPosition);
        void drawBoundingBox(vec2 playerPosition);
        void onDeath(unsigned short index, double deltaTime);

        void addAsteroid(vec2 pos);
        void addMissile(vec2 pos, vec2 dir, float rot, double deltaTime);
        void addCrystal(vec2 pos, vec2 dir, double deltaTime, ofColor color);

    private:
        vector<Entity*> entities;

        const unsigned short _MAX_ASTEROIDS = 512;
        unsigned short _asteroidAmount = 0;
};