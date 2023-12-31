#include "richCrystalAsteroid.h"

RichCrystalAsteroid::RichCrystalAsteroid(vec2 position)
: Asteroid(position) {
    _identity = "richCrystalAsteroid";

    _color = COLORS.RICH_CRYSTAL;
}