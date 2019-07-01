#include "GameEngine.h"
#include "Table.h"
#include "MainBall.h"
#include "Obstacle.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include "Walls.h"

//Obstacle obstacle = Obstacle(glm::vec3(0, 0, 4));

//Hovercraft hovercraft = Hovercraft(glm::vec3(5, 4, 3));


//
//std::vector<GameObject*> gameobjects;
//Hovercraft hovercraft = Hovercraft(glm::vec3(5, 4, 3));



int main(int argc, char **argv) {



	//Initialise the engine.
	GameEngine::initEngine(argc, argv, "Pool", true);

	//Adding grass field.
	GameEngine::addGameObject(new Table(glm::vec3(0, 0, 0), glm::vec3(5, 0, 5)));

	//Adding an Obstacle.
	GameEngine::addGameObject(new Obstacle(glm::vec3(38, 0.0, 40), { 0.55f, 0.27f, 0.07f }));

	//Adding an Obstacle with different colour.
	GameEngine::addGameObject(new Obstacle(glm::vec3(50, 0.0, 30)) );

	//Add a movable hovercraft.
	GameEngine::addGameObject(new MainBall(glm::vec3(-2, 0, 50)), false);

	GameEngine::addGameObject(new Walls(glm::vec3(5, 0, -30), { 0.55f, 0.27f, 0.07f }));

	//GameEngine::addGameObject(new (glm::vec3(2, 0.0, -2.0), { 0.55f, 0.27f, 0.07f }));
	//Start the game engine.
	GameEngine::startEngine();




	//setup();

	return 0;

}