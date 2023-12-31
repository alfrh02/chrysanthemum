#pragma once

#include "asteroid.h"
#include "crystalAsteroid.h"
#include "richCrystalAsteroid.h"
#include "cargoShip.h"
#include "missile.h"

class EntityManager {
    public:
        EntityManager();
        ~EntityManager();

        void update(vec2 playerPosition, double deltaTime);
        void draw(vec2 playerPosition);
        void drawBoundingBox(vec2 playerPosition);

        void addAsteroid(vec2 pos);
        void addMissile(vec2 pos, vec2 dir, float rot, double deltaTime);

    private:
        vector<Entity*> entities;

        const unsigned short _MAX_ASTEROIDS = 1024;
        unsigned short _asteroidAmount = 0;
};