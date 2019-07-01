/////////////////////////////////////////////////////////////////////////////////////////////        

#pragma once


#include "GameObject.h"
#include <vector>

class GameEngine {
private:
	static std::vector<GameObject*> gameobjects;
	static void updateGame();
	static int oldTimeSinceStart;
	static int newTimeSinceStart;
	static GameObject* cameraFollow;
	static bool debugMode;
	static unsigned int base; // Generate display list base. 
public:


	static void initEngine(int argc, char **argv, const char* windowTitle = "New Game", bool debugMode = false, int width = 500, int height = 500);
	static void displayFunc();
	static void reshapeFunc(int w, int h);
	static void addGameObject(GameObject* gameobject, bool camFollow = false);
	static void startEngine();
	static void cleanup();
	//static void Setup();
};

