
#include "Walls.h"
#include "CubeCollider.h"


Walls::Walls(glm::vec3 pos, Colour col) : GameObject(pos) {
	this->colour = col;
	Walls::collider = new CubeCollider(&this->position, 20, 10, 60);
}

Walls::~Walls() {
	delete Walls::collider;
	Walls::collider = NULL;
}

unsigned int  Walls::setupDrawing(unsigned int listBase) {
	this->base = listBase;
	glNewList(this->base, GL_COMPILE);
	glPushMatrix();
	glTranslatef(-25, 1.2, 10);
	glColor3f(0.23, 0.16, 0.05);
	glRotatef(63, 5, 400, 10);
	glutSolidCylinder(4, 120, 20, 1);
	glPopMatrix();

	glEndList();


	return this->base + 1;
}

void Walls::start() {
}

void Walls::update(int deltaTime) {
}

void Walls::collides(Collider* other) {
	if (debugMode) {
		std::cout << "COLLIDED WITH WALL" << std::endl;
	}
	this->active = false;
}