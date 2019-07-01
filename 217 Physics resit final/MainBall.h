
#include "GameObject.h"
#include <cmath>
#include<glm/gtx/rotate_vector.hpp>
#define TURNING_SPEED 90.0 //<turning speed in degrees per second
#define MOVE_SPEED 40.0 //<move speed in coordinate units per second

class MainBall : public GameObject {
private:
	unsigned int base;

	
public:
	//glm::vec3 position;
	glm::vec3 startingHeading = heading;
	float rotationAngle = 0.0; 
	float pitchAngle = 0.0;
	//Collider* collider = NULL;

	MainBall(glm::vec3 pos);
	~MainBall();

	unsigned int setupDrawing(unsigned int listBase); 
	void drawScene(); 
	void start(); 
	void update(int deltaTime);  
	void collides(Collider * other); 
};

