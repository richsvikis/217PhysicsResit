/////////////////////////////////////////////////////////////////////////////////////////////        
/// @class Collider
/// @brief This is the base class for colliders.
///
/// @author Maurice Hendrix
///////////////////////////////////////////////////////////////////////////////////////////// 
#pragma once
#include <glm/vec3.hpp>

class Collider {
protected:
	glm::vec3* colliderCentre = NULL; ///<Centre point for the collider @note Usually the same as the gameobject it is a collider for.
public:
	virtual bool collidesWith(Collider* other) = 0; ///<pure virtual function. very collider must implement collidesWith, which calculates whethwer this collider collides with other.

	/* Every collider must implement the following pure virtual function or otherwise cause a compile error.*/
	virtual float minX() = 0; ///<Lowest x value for the collider. Must override in inherited classes.
	virtual float maxX() = 0; ///<Highest x value for the collider. Must override in inherited classes.
	virtual float minY() = 0; ///<Lowest y value for the collider. Must override in inherited classes.
	virtual float maxY() = 0; ///<Highest y value for the collider. Must override in inherited classes.
	virtual float minZ() = 0; ///<Lowest z value for the collider. Must override in inherited classes.
	virtual float maxZ() = 0; ///<Highest z value for the collider. Must override in inherited classes.
	virtual void Draw() = 0; ///<Draw method for debug mode. Must override in inherited classes.
};

