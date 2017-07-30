#pragma once

#include "glm/glm.hpp"

#include <vector>
#include "Floor.h"
#include "Terrain.h"
#include "Agent.h"

class Arrow 
{
public:
	Arrow(glm::vec3 pos, glm::vec3 dir, float speed, float width, float length, int lifeTime, string texture);
	~Arrow();

	void init();

	void draw();

	bool update(float dt);

	void hit(){ _stuck = true; };

	void hitAgent(){ _active = false; };

	void clean();

	glm::vec3 rotate(float deg, glm::vec3 axis, glm::vec3 pos);

	bool getActive(){ return _active; };

	bool checkFloorCollision(Floor& floor);
	bool checkTerrainCollision(Terrain& terrain);
	bool checkAgentCollision(Agent& agent);
	bool checkCollision(Cube& cube);

private:
	int _lifeTime;
	float _speed, _width, _length;
	glm::vec3 _direction;
	glm::vec3 _position;
	glm::vec3 _velocity;

	string _skin;

	bool _stuck, _active;

	float _gravity;

	int _floorTime;

	int _vertexSize;

	GLuint _vboID; //vertex buffer object ID
	GLTexture _texture;

	TextureLoader _textureLoader;

	GLSLProgram _colorProgram;	
};