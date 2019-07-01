#pragma once
#include "GameObject.h"
#include "Obstacle.h"

class Walls : public GameObject
{
public:

	Walls(glm::vec3 pos, Colour col = { 0,0,2 });
	~Walls();///<Default destructor.

	Colour colour;
	/* Overridden from the GameObject class.*/
	unsigned int setupDrawing(unsigned int listBase);///<Overridden setup drawing method.
	void start();  ///Overridden start method.
	void update(int deltaTime);  ///<Overridden update method.
	void collides(Collider * other);///<Overridden collides method.
};