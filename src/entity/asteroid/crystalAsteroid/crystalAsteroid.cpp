#include "crystalAsteroid.h"

CrystalAsteroid::CrystalAsteroid(vec2 position)
: Asteroid(position) {
    _identity = "CrystalAsteroid";

    _color = COLORS.CRYSTAL;
}