#pragma once

#include "asteroid.h"
#include "cargoShip.h"
#include "missile.h"

class EntityManager {
    public:
        EntityManager(unsigned short startingAsteroids = 16);
        ~EntityManager();

        void update(double deltaTime);
        void draw();

        void drawBoundingBox();
        void addAsteroid(vec2 pos);
        void addMissile(vec2 pos, vec2 dir, float rot);

    private:
        vector<Entity*> entities;
};