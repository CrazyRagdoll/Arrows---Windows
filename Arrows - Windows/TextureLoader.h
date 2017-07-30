#pragma once

#include <SOIL/SOIL.h>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>

using namespace std;

class TextureLoader
{
public:
	TextureLoader();
	~TextureLoader();

	int loadGLTexture(string imagePath);

private:

	GLuint _texture[1];
};