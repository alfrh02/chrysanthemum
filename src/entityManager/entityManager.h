#pragma once

#include "asteroid.h"
#include "crystalAsteroid.h"
#include "richCrystalAsteroid.h"

#include "crystal.h"

#include "cargoShip.h"

#include "player.h"
#include "enemy.h"

#include "missile.h"

class EntityManager {
    public:
        EntityManager();
        ~EntityManager();

        void update(double deltaTime);
        void draw();
        void drawBoundingBox();
        void onDeath(unsigned short index, double deltaTime);

        void addAsteroid(vec2 pos);
        void addMissile(vec2 pos, vec2 dir, float rot, double deltaTime);
        void addCrystal(vec2 pos, vec2 dir, double deltaTime, ofColor color);
        void addEnemy(vec2 pos);

        Player player;
		CargoShip cargoship;

    private:
        vector<Entity*> entities;

        const unsigned short _MAX_ASTEROIDS = 512;
        unsigned short _asteroidAmount = 0;
};