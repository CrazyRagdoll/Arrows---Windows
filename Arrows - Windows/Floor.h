#pragma once

#include "glm/glm.hpp"

#include <iostream>
#include "GLTexture.h"
#include "TextureLoader.h"
#include "GLSLProgram.h"

class Floor
{
public:
	Floor();
	~Floor();

	void init(float width);

	void draw();

	float _x, _y, _z, _width;

private:

	glm::vec3 _position;

	GLuint _vboID; //vertex buffer object ID
	GLTexture _texture;

	TextureLoader _textureLoader;

	GLSLProgram _colorProgram;	
};