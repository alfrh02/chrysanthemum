#pragma once

// this file contains variables that are needed globally
// or are relevant enough to be put here
// consider this the "settings"

// the undefined are defined in ofApp::setup()
struct {
    unsigned int renderDistance;     // distance for which something should be calling draw()
    unsigned int simulationDistance; // distance for which something should be considered alive - everything farther than this distance is deleted (other than the cargoship)
} settings;

// --- colours ---
const struct {
    ofColor FOREGROUND = ofColor(224);
    ofColor BACKGROUND = ofColor(5);
    ofColor GRAY = ofColor(64);

    ofColor RED = ofColor(255, 32, 32);
    ofColor GREEN = ofColor(0, 255, 0);
    ofColor BLUE = ofColor(0, 120, 255);
    ofColor ORANGE = ofColor(245, 179, 66);
    ofColor MAGENTA = ofColor(255, 0, 255);
} COLOURS;