

#include "Obstacle.h"
#include "CubeCollider.h"

Obstacle::Obstacle(glm::vec3 pos, Colour col) : GameObject(pos) {
	this->colour = col;
	Obstacle::collider = new CubeCollider(&this->position, 5, 2, 4);
}

Obstacle::~Obstacle() {
	delete Obstacle::collider;
	Obstacle::collider = NULL;
}



unsigned int  Obstacle::setupDrawing(unsigned int listBase) {
	this->base = listBase;
	glNewList(this->base, GL_COMPILE);
	glPushMatrix();
	glColor3f(1, 1, 1);
	glutSolidSphere(2, 40, 100);
	glPopMatrix();

	glEndList();


	return this->base + 1;
}

void Obstacle::start() {
}

void Obstacle::update(int deltaTime) {
}

void Obstacle::collides(Collider* other) {
	if (debugMode) {
		std::cout << "COLLIDED WITH BALL" << std::endl;
	}
	this->active = false;
}