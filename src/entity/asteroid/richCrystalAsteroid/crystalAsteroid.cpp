#include "richCrystalAsteroid.h"

RichCrystalAsteroid::RichCrystalAsteroid(vec2 position)
: Asteroid(position) {
    _identity = "RichCrystalAsteroid";

    _color = COLORS.RICH_CRYSTAL;
}