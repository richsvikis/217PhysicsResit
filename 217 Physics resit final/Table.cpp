#include "Table.h"

Table::Table(const glm::vec3 & _pos, const glm::vec3 & _size) : GameObject(_pos) {
	size = _size;
}

unsigned int Table::setupDrawing(unsigned int listBase) {
	this->base = listBase;
	glNewList(this->base, GL_COMPILE);
	glPushMatrix();
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
	glVertex3f(50, -1, 100);
	glVertex3f(85, -1, 30);
	glVertex3f(-25, -1, -25);
	glVertex3f(-60, -1, 50);
	glEnd();
	glPopMatrix();
	glEndList();
	return this->base + 1;
}

void Table::drawScene() {
	glPushMatrix();
	glCallList(this->base); // Draw grass.
	glPopMatrix(); // End draw grass.

	glPushMatrix();
	glColor3f(0.15, 0.21, 1.00);
	glBegin(GL_QUADS);
	glVertex3f(500, -10, 1000);
	glVertex3f(850, -10, 300);
	glVertex3f(-250, -10, -250);
	glVertex3f(-600, -10, 500);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.00, 0.50, 0.06);
	glBegin(GL_QUADS);
	glVertex3f(600, -5, 5);
	glVertex3f(300, -5, 10);
	glVertex3f(-250, -5, -10);
	glVertex3f(-600, -5, 20);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(700, -5, 10);
	glVertex3f(700, -5, 20);
	glVertex3f(400, -5, -30);
	glVertex3f(100, -5, 40);
	glEnd();
	glPopMatrix();

	//left


	//right 
	glPushMatrix();
	glTranslatef(-59, 1.2, 50);
	glColor3f(0.23, 0.16, 0.05);
	glRotatef(65, 35, 10000, 10);
	glutSolidCylinder(4, 120, 20, 1);
	glPopMatrix();

	//UP 
	glPushMatrix();
	glTranslatef(50, 1.2, 104);
	glColor3f(0.23, 0.16, 0.05);
	glRotatef(155, 40, 100, 10);
	glutSolidCylinder(4, 86, 20, 1);
	glPopMatrix();

	//Down
	glPushMatrix();
	glTranslatef(-55, 1.2, 51);
	glColor3f(0.23, 0.16, 0.05);
	glRotatef(155, 40, 200, 10);
	glutSolidCylinder(4, 84, 20, 1);
	glPopMatrix();

}

void Table::start() {
}

void Table::update(int deltaTime) {
}
