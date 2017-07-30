#include "Terrain.h"

Terrain::Terrain(glm::vec3 pos, float size)
{
	_position = pos;
	_size = size;
}

Terrain::~Terrain()
{

}

void Terrain::init()
{
	Cube::init(_position.x, _position.y, _position.z, _size, "NONE");
}

void Terrain::draw()
{
	Cube::draw();
}