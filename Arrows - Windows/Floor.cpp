#include "Floor.h"
#include "Vertex.h"

#include <iostream>
#include <cstddef>


Floor::Floor() 
{
	_vboID = 0;
	_x = _y = _z = 0;
}

Floor::~Floor()
{
	if(_vboID != 0)
	{
		glDeleteBuffers(1, &_vboID);
	}
}

void Floor::init(float width)
{
	_width = width;

	//../src/Textures/NeHe.bmp
	_texture.id = _textureLoader.loadGLTexture("Textures/Tile2.png");

	// If the vertex buffer is 0, use OpenGL to set it.
	if( _vboID == 0 )
	{
		glGenBuffers(1, &_vboID);
	}

	Vertex vertexData[6];

    //  X     Y     Z       U     V
    // floor
    vertexData[0].setPosUV(_x + -_width, _y, _z + -_width, 0.0f, 0.0f);
    vertexData[1].setPosUV(_x +  _width, _y, _z + -_width, 1.0f, 0.0f);
    vertexData[2].setPosUV(_x + -_width, _y, _z +  _width, 0.0f, 1.0f);
    vertexData[3].setPosUV(_x +  _width, _y, _z + -_width, 1.0f, 0.0f);
    vertexData[4].setPosUV(_x +  _width, _y, _z +  _width, 1.0f, 1.0f);
    vertexData[5].setPosUV(_x + -_width, _y, _z +  _width, 0.0f, 1.0f);

    for (int i = 0; i < 6; i++) {
		vertexData[i].setColor(1.0f, 1.0f, 0.0f, 1.0f);
	}

	// Binding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	// Uploading the buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	// Unbinding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Floor::draw()
{
		//bind the buffer object
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	//Activating and binding the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture.id);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	//tell opengl that we want to use the first arrribute array.
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//This is the position attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	//This is the color attribute pointer	
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	//this is the UV attribute pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	
	//Draw the 6 verticies to the screen
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//disable the vertex attrib array. Not optional
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	//unbind the  texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//unbind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}