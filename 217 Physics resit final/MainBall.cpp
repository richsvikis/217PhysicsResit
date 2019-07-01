
#include "MainBall.h"
#include "CubeCollider.h"

MainBall::MainBall(glm::vec3 pos) :GameObject(pos) {
	MainBall::collider = new CubeCollider(&this->position, 5, 2, 4);
}

MainBall::~MainBall() {
	delete MainBall::collider;
	MainBall::collider = NULL;
}

unsigned int MainBall::setupDrawing(unsigned int listBase) {
	this->base = listBase;
	glNewList(this->base, GL_COMPILE);
	glPushMatrix();
	glColor3f(-2, 0, 2);
	glRotatef(-90, 0, 1, 0);
	glutSolidCone(0.5, 0.75, 30, 30);
	glPushMatrix();
	glTranslatef(0, 0, -0.4);
	glColor3f(1, 1, 1);
	glutSolidCube(0.8);
	glPopMatrix();
	glPopMatrix();
	glEndList();
	return this->base + 1;


}

void MainBall::drawScene() {



	glPushMatrix();
	glTranslatef(this->position.x, this->position.y, this->position.z);
	//rotate openGL object
	glRotatef(pitchAngle, 0.0, 0.0, 1.0);
	glRotatef(rotationAngle, 0.0, 1.0, 0.0);
	glCallList(this->base); // Draw Hovercraft.
	glPushMatrix();
	glTranslatef(0.7, 0.2, -0.3);
	glColor3f(1, 1, 1);
	glutSolidSphere(2, 40, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-50, 10, -25);
	glColor3f(0.65, 0.44, 0.13);
	glRotatef(65, 25, 100, 10);
	glutSolidCylinder(1.5, 50, 30, 1);
	glPopMatrix();

	//cue tip
	glPushMatrix();
	glTranslatef(-8.5, 2.4, -5);
	glColor3f(0, 0, 0);
	glRotatef(65, 25, 100, 10);
	glutSolidCylinder(1.5, 7, 30, 1);
	glPopMatrix();
	glPopMatrix();

	//White Ball
	/*
	glPushMatrix();
	glTranslatef(0.7, 0.2, -0.3);
	glColor3f(1, 1, 1);
	glutSolidSphere(2, 40, 100);
	glPopMatrix();
	*/

	/*
	//Cue
	glPushMatrix();
	glTranslatef(-50, 10, -25);
	glColor3f(0.65, 0.44, 0.13);
	glRotatef(65, 25, 100, 10);
	glutSolidCylinder(1.5, 50, 30, 1);
	glPopMatrix();

	//cue tip
	glPushMatrix();
	glTranslatef(-8.5, 2.4, -5);
	glColor3f(0, 0, 0);
	glRotatef(65, 25, 100, 10);
	glutSolidCylinder(1.5, 7, 30, 1);
	glPopMatrix();
	*/

	//	collider->colliderCentre = &position;

		//if we are in debug mode then:
	if (debugMode) {
		//display heading vector
		glPushMatrix();
		glBegin(GL_LINES);
		glColor3f(0, 1, 0);
		glVertex3f(position.x, position.y, position.z);
		glVertex3f(position.x + heading.x, position.y + heading.y, position.z + heading.z);
		glEnd();
		glPopMatrix();
		//display the collider bounding box
		this->collider->Draw();
	}
}

void MainBall::start() {
}

void MainBall::update(int deltaTime) {
	float moveStep = MOVE_SPEED * (deltaTime / 1000.0); //movement speed in units per second * deltaTime in sec = moveStep
	float turningSpeed = TURNING_SPEED * (deltaTime / 1000.0); //turning speed (degrees/sec) * deltaTime in sec = turning speed over delta time

	if (specialKeys[GLUT_KEY_DOWN]) {
		this->position += this->heading * moveStep;
	}
	if (specialKeys[GLUT_KEY_PAGE_UP]) {
		this->pitchAngle += turningSpeed; //in degrees not radians
	}
	if (specialKeys[GLUT_KEY_PAGE_DOWN]) {
		this->pitchAngle -= turningSpeed; //in degrees not radians
	}

	if (specialKeys[GLUT_KEY_LEFT]) {
		this->rotationAngle += turningSpeed; //in degrees not radians
	}
	if (specialKeys[GLUT_KEY_UP]) {
		this->position -= this->heading * moveStep;
	}
	if (specialKeys[GLUT_KEY_RIGHT]) {
		this->rotationAngle -= turningSpeed;
	}


	this->heading = glm::rotate(this->startingHeading, glm::radians(rotationAngle), glm::vec3(0.0, 1.0, 0.0));
	this->heading = glm::rotate(this->heading, glm::radians(pitchAngle), glm::vec3(0.0, 0.0, 1.0));
}

void MainBall::collides(Collider* other) {
	if (debugMode) {
		std::cout << "Collison Happens" << std::endl;
	}
}