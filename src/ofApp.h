#pragma once

#include <typeinfo>

#include "ofMain.h"

#include "config.h"

#include "player.h"
#include "cargoShip.h"
#include "entityManager.h"

using namespace glm;

class ofApp : public ofBaseApp{

	public:
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

		double deltaTime = 0;

		bool debugMode = false;

		Player player;
		CargoShip cargoShip;

		EntityManager entities;
		// vector<Entity*> entities;
};