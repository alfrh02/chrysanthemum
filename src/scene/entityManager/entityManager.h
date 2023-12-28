#pragma once

#include "asteroid.h"
#include "cargoShip.h"
#include "missile.h"

class EntityManager {
    public:
        EntityManager(unsigned short startingAsteroids = 16);
        ~EntityManager();

        void update(vec2 playerPosition, double deltaTime);
        void draw();

        void drawBoundingBox(vec2 playerPosition);
        void addAsteroid(vec2 pos);
        void addMissile(vec2 pos, vec2 dir, float rot);

    private:
        vector<Entity*> entities;
        vector<Entity*> deadEntities;

        const unsigned short _DELETION_DISTANCE = 1000;
};