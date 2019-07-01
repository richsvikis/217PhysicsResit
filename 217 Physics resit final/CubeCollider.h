#pragma once
#include "Collider.h"
/* OPENGL_INCLUDES */
#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif 

class CubeCollider : public Collider {
private:
public:
	float length = 0.0, width = 0.0, height = 0.0;


	//////////////////////////////////
	CubeCollider(glm::vec3 * centre, float cubeWidth, float cubeHeight, float cubeLength);
	~CubeCollider(); ///<Default destructor.

	float minX();
	float maxX();
	float minY();
	float maxY();
	float minZ();
	float maxZ();
	bool collidesWith(Collider * other);  ///< Implementation of fuction deciding if this collider collides with the other one.
	void Draw();
};
