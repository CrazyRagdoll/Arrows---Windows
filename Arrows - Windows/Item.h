#pragma once

#include "glm/glm.hpp"

#include "GLTexture.h"
#include <string>
#include "TextureLoader.h"
#include "GLSLProgram.h"
#include "Vertex.h"

class Item 
{
public:

	Item(glm::vec3 pos, int value);
	~Item();

	void init();

	void draw();

	bool update(float time);

	glm::vec3 getPosition() { return _position; }

	int getValue() { return _value; }

	void setInactive() { _collected = true; }

	float _width, _height, _depth; //The size of the object

private:

	float _time; //How long the collectables last.

	int _value; //How much the item is worth

	bool _collected; //To set the item to inactive

	int _vertexSize; //holds how many vertices make up the object

	glm::vec3 _position; //center position of the object

	GLuint _vboID; //vertex buffer object ID
	GLTexture _texture;

	TextureLoader _textureLoader;

	GLSLProgram _colorProgram;	

};