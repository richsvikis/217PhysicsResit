/////////////////////////////////////////////////////////////////////////////////////////////        
/// @class GameObject
/// @brief This class is the base class for all objects in the scene. It is a pure virtual class and you cannot directly instantiate it but you can create classes that extend it and those can all be added to the scene.
///
/// @author Maurice Hendrix
///////////////////////////////////////////////////////////////////////////////////////////// 
#pragma once
/* OPENGL_INCLUDES */
#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif 

#include <map>
#include <iostream>
#include "Collider.h" //gameobjects can have a collider

class GameObject {
protected:
	unsigned int base; 
public:
	static std::map <int, bool> specialKeys;
	static std::map <char, bool> keys;
	static bool debugMode;
	bool active = true;
	Collider* collider = NULL;  
	glm::vec3 position = glm::vec3(0.0, 0.0, 0.0); 
	glm::vec3 heading = glm::vec3(0.0, 0.0, -1.0);  

	GameObject(glm::vec3 pos);
	~GameObject(); 
	
	virtual unsigned int setupDrawing(unsigned int listBase) = 0;
	virtual void drawScene(); 
	virtual void start() = 0; 
	virtual void update(int deltaTime) = 0;
	virtual void collides(Collider* other); 
};

