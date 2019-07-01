
#pragma once
#include "GameObject.h"


struct Colour {
	float r, g, b;
};

class Obstacle : public GameObject
{
public:

	Obstacle(glm::vec3 pos, Colour col = { 0,0,1 });
	~Obstacle();///<Default destructor.

	Colour colour;///<Current colour of the object.

	/* Overridden from the GameObject class.*/
	unsigned int setupDrawing(unsigned int listBase);
	void start();  
	void update(int deltaTime);  
	void collides(Collider * other);
};

