#ifndef __TABLE_H_
#define __TABLE_H_

#include "GameObject.h"

class Table : public GameObject {
private:
	glm::vec3 size;
public:

	Table(const glm::vec3& _pos, const glm::vec3& _size);
	unsigned int setupDrawing(unsigned int listBase);
	void drawScene();
	void start();
	void update(int deltaTime);
};
#endif
