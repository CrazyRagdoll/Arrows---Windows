#pragma once

#include "glm/glm.hpp"

#include "GLTexture.h"
#include <string>
#include "TextureLoader.h"
#include "GLSLProgram.h"

using namespace std;

class Crosshair 
{
public:
	Crosshair();
	~Crosshair();

	void init(glm::vec3 pos, glm::vec3 dir, string textures);

	void draw();

private:

	int _vertexSize;

	glm::vec3 _pos, _dir;

	GLuint _vboID; //vertex buffer object ID
	GLTexture _texture;

	TextureLoader _textureLoader;

	GLSLProgram _colorProgram;	
};