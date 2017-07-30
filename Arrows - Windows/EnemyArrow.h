#pragma once

#include "glm/glm.hpp"
#include "Vertex.h"
#include "GLTexture.h"
#include "TextureLoader.h"
#include "GLSLProgram.h"
#include "Floor.h"
#include "Terrain.h"
#include "Camera.h"

class EnemyArrow
{
public:
	EnemyArrow(glm::vec3 pos, glm::vec3 playerPos, float damage);
	~EnemyArrow();

	void init();

	void draw();

	bool update(float dt);

	void hit(){ _stuck = true; };

	void hitPlayer(){ _active = false; };

	bool getActive(){ return _active; };

	float getDamage() { return _damage; };

	bool checkFloorCollision(Floor& floor);
	bool checkTerrainCollision(Terrain& terrain);
	bool checkPlayerCollision(Camera& camera);

private:
	int _lifeTime;
	float _speed, _width, _length;
	glm::vec3 _direction;
	glm::vec3 _position;
	glm::vec3 _velocity;

	string _skin;

	float _damage;

	bool _stuck, _active;

	float _gravity;

	int _floorTime;

	int _vertexSize;

	GLuint _vboID; //vertex buffer object ID
	GLTexture _texture;

	TextureLoader _textureLoader;

	GLSLProgram _colorProgram;	

};