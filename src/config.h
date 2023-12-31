#pragma once


// this file contains variables that are needed globally
// or are relevant enough to be put here
// consider this the "settings"

const struct {
    unsigned int RENDER_DISTANCE = 1920;              // distance for which something should be calling draw()
    unsigned int SIMULATION_DISTANCE = 8192;          // distance for which something should be considered alive - everything farther than this distance is deleted (other than the cargoship)
    float CRYSTAL_ASTEROID_SPAWN_CHANCE = 0.05;       // chance for a normal asteroid to become a crystal asteroid
    float RICH_CRYSTAL_ASTEROID_SPAWN_CHANCE = 0.05;  // chance for a crystal asteroid to become a rich crystal asteroid
} SETTINGS;

const struct {
    ofColor FOREGROUND = ofColor(224);
    ofColor BACKGROUND = ofColor(5);
    ofColor GRAY = ofColor(64);

    ofColor RED = ofColor(255, 32, 32);
    ofColor GREEN = ofColor(0, 255, 0);
    ofColor BLUE = ofColor(0, 120, 255);
    ofColor ORANGE = ofColor(245, 179, 66);
    ofColor MAGENTA = ofColor(255, 0, 255);
    ofColor GOLD = ofColor(255, 160, 64);

    ofColor CRYSTAL = GOLD;
    ofColor RICH_CRYSTAL = MAGENTA;
} COLOURS;