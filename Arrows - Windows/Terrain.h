#pragma once

#include "glm/glm.hpp"

#include "Cube.h"

class Terrain : public Cube
{
public:
	Terrain(glm::vec3 pos, float size);
	~Terrain();

	void init();

	void draw();

	glm::vec3 _position;
	float _size;

private:

};