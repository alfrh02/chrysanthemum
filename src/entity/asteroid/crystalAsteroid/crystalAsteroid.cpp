#include "crystalAsteroid.h"

CrystalAsteroid::CrystalAsteroid(vec2 position)
: Asteroid(position) {
    _identity = "CrystalAsteroid";

    _colour = COLOURS.MAGENTA;
}