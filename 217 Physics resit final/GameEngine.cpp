#include "GameEngine.h"
#include "MainBall.h"
#include "Obstacle.h"
#include "Walls.h"

MainBall Mainball = MainBall(glm::vec3(5, 4, 3));

bool GameEngine::debugMode;
std::vector<GameObject*> GameEngine::gameobjects; //The definition of static variables needs to be repeated in the cpp file.
GameObject* GameEngine::cameraFollow;
int GameEngine::oldTimeSinceStart;
int GameEngine::newTimeSinceStart;
std::map <int, bool> GameObject::specialKeys;
std::map <char, bool> GameObject::keys;
unsigned int GameEngine::base; // Generate display list base. 


void GameEngine::initEngine(int argc, char **argv, const char* windowTitle, bool debug, int width, int height) {
	GameEngine::debugMode = debug;
	GameObject::debugMode = GameEngine::debugMode;
	//Init glut.
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(windowTitle);

	glewExperimental = GL_TRUE;
	glewInit();


	//Lambda function defined inside the glutDisplayFunc call to call all relevant drawscenes.
	glutDisplayFunc(displayFunc);

	//Lambda function defined inside glutReshapeFunc to do resize logic.
	glutReshapeFunc(reshapeFunc);

	//Lambda functions to link our code to glut's keydown andkeyup. Our function deals with both regular and special keys in one.
	glutKeyboardFunc([](unsigned char key, int x, int y) {
		GameObject::keys[key] = true;
		//if we press escape, exit the game
		if (key == 27) {
			cleanup();
			exit(0);
		}
	});

	glutKeyboardUpFunc([](unsigned char key, int x, int y) {
		GameObject::keys[key] = false;
	});

	glutSpecialFunc([](int key, int x, int y) {
		GameObject::specialKeys[key] = true;
	});

	glutSpecialUpFunc([](int key, int x, int y) {
		GameObject::specialKeys[key] = false;
	});

	glutIdleFunc(updateGame);

}



void GameEngine::displayFunc() {
	//Prepare for drawing all objects.
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST); // Enable depth testing.
	glEnable(GL_LIGHTING);

	// Light property vectors.
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	float lightPos[] = { 0.0, 1.0, 0.0, 0.0 };
	float globAmb[] = { 0.2, 0.2, 0.2, 1.0 };

	// Light properties.
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHT0); // Enable particular light source.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.

													 // Material property vectors.
	float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	float matShine[] = { 50.0 };

	// Material properties.
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

	// Enable color material mode.
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//If we have no object to follow just put the cam in a static position.

	glm::vec3 CameraPosition = Mainball.position;
	glm::vec3 TargetPosition = Mainball.position;
	CameraPosition += Mainball.heading * 10.0f;
	CameraPosition += glm::vec3(0, 10, 0) * 10.0f;
	gluLookAt(CameraPosition.x, CameraPosition.y, CameraPosition.z, TargetPosition.x, TargetPosition.y, TargetPosition.z, 0.0, 1.0, 0.0);




	//Call drawscene for all gameobjects.
	for (std::vector<GameObject*>::size_type i = 0; i != gameobjects.size(); i++) {
		gameobjects[i]->drawScene();
	}
	glutSwapBuffers(); //Finish Draw Scene.
}

void GameEngine::reshapeFunc(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60.0, (float)w / (float)h, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
};

void GameEngine::startEngine() {
	//Explain main interaction with scene.
	std::cout << "Press escape to exit." << std::endl;

	//Start game loop.
	glutMainLoop();
}

//Add a new gameobject to the scene.
void GameEngine::addGameObject(GameObject* gameobject, bool camFollow) {
	gameobjects.push_back(gameobject);
	if (camFollow) {
		cameraFollow = gameobject;
	}

	base = glGenLists(1);
	base = gameobject->setupDrawing(base);
	gameobject->start();
}

//Update the game state.
void GameEngine::updateGame() {



	//Calculate delta time (in mili seconds).
	oldTimeSinceStart = newTimeSinceStart;
	newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = newTimeSinceStart - oldTimeSinceStart;

	//If the last frame was rendered less than 1 ms ago, the detalaTime will be 0 ms. This causes problems in calculations, so sleep for 1ms to adjust.
	if (deltaTime == 0) {
		Sleep(1);
		newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
		deltaTime = newTimeSinceStart - oldTimeSinceStart;
	}

	//Remove any inactive objects first.
	for (std::vector<GameObject*>::size_type i = 0; i != gameobjects.size(); i++) {
		if (!gameobjects[i]->active) {
			delete gameobjects[i];
			gameobjects.erase(gameobjects.begin() + i);
		}
	}

	//Run update for all game objects.
	for (std::vector<GameObject*>::size_type i = 0; i != gameobjects.size(); i++) {
		gameobjects[i]->update(deltaTime);
	}

	
	for (std::vector<GameObject*>::size_type i = 0; i != gameobjects.size(); i++) {
		for (std::vector<GameObject*>::size_type j = i + 1; j != gameobjects.size(); j++) {
			if (gameobjects[i]->collider != NULL) {
				if (gameobjects[i]->collider->collidesWith(gameobjects[j]->collider)) {
					gameobjects[i]->collides(gameobjects[j]->collider);
					gameobjects[j]->collides(gameobjects[i]->collider);
				}
			}
		}
	}

	//Done so indicate that it's time to redraw.
	glutPostRedisplay();
}

//Here we delete pointer objects for when we exit, to prevent memory leaks.
void GameEngine::cleanup() {
	for (auto it = gameobjects.begin(); it != gameobjects.end(); ++it) {
		delete *it;
	}
	gameobjects.clear();
}