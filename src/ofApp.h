#pragma once

#include "ofMain.h"

#include "crystalAsteroid.h"
#include "richCrystalAsteroid.h"
#include "asteroid.h"

#include "cargoShip.h"

#include "crystal.h"
#include "missile.h"

#include "player.h"

using namespace glm;

class ofApp : public ofBaseApp{

	public:
		~ofApp();

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        void addAsteroid(vec2 pos);
        void addMissile(vec2 pos, vec2 dir, float rot);
        void addCrystal(vec2 pos, vec2 dir, ofColor color);

		double deltaTime = 0;
		bool debugMode = false;
		bool helpText = true;

        Player player;
		CargoShip cargoship;

		vector<Entity*> entities;

		const unsigned short MAX_ASTEROIDS = 512;
        unsigned short asteroidAmount = 0;				   // used to ensure there is a consistent amount of asteroids in the scene at any time

		const unsigned int RENDER_DISTANCE = ofGetWidth(); // distance for which something should be calling draw()
		const unsigned int SIMULATION_DISTANCE = 4096;     // distance for which something should be considered alive - everything farther than this distance is deleted (other than the cargoship)

		float CRYSTAL_ASTEROID_SPAWN_CHANCE = 0.05;        // chance for a normal asteroid to become a crystal asteroid
		float RICH_CRYSTAL_ASTEROID_SPAWN_CHANCE = 0.05;   // chance for a crystal asteroid to become a rich crystal asteroid
};