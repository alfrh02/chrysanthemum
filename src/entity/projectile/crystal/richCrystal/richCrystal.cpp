#include "richCrystal.h"

RichCrystal::RichCrystal(vec2 position, double deltaTime)
: Crystal(position, deltaTime) {
    _identity = "RichCrystal";

    _colour = COLORS.RICH_CRYSTAL;
}