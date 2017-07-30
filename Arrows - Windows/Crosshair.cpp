#include "Crosshair.h"
#include "Vertex.h"

#include <iostream>
#include <cstddef>

Crosshair::Crosshair()
{
	_vboID = 0;
}

Crosshair::~Crosshair()
{
	//cleaing up the buffers when the sprite is destroyed.
	if(_vboID != 0)
	{
		glDeleteBuffers(1, &_vboID);
	}
}

void Crosshair::init(glm::vec3 pos, glm::vec3 dir, string texture)
{
	_pos = pos;
	_dir = glm::normalize(dir);

	if (texture != "NONE")
	{
		_texture.id = _textureLoader.loadGLTexture(texture);	
	}

	// If the vertex buffer is 0, use OpenGL to set it.
	if( _vboID == 0 )
	{
		glGenBuffers(1, &_vboID);
	}

    // making the crosshair out of 4 triangles
	Vertex vertexData[12];
    //  X     Y     Z       U     V
    // vertical rectangle
	vertexData[0].setPosUV( _pos.x + 0.2f + _dir.x, _pos.y + 1.0f + _dir.y, _pos.z + _dir.z, 0.0f, 0.0f);
	vertexData[1].setPosUV( _pos.x - 0.2f + _dir.x, _pos.y + 1.0f + _dir.y, _pos.z + _dir.z, 0.0f, 0.0f);
	vertexData[2].setPosUV( _pos.x - 0.2f + _dir.x, _pos.y - 1.0f + _dir.y, _pos.z + _dir.z, 0.0f, 0.0f);

	vertexData[3].setPosUV( _pos.x - 0.2f + _dir.x, _pos.y - 1.0f + _dir.y, _pos.z + _dir.z, 0.0f, 0.0f);
	vertexData[4].setPosUV( _pos.x + 0.2f + _dir.x, _pos.y - 1.0f + _dir.y, _pos.z + _dir.z, 0.0f, 0.0f);
	vertexData[5].setPosUV( _pos.x + 0.2f + _dir.x, _pos.y + 1.0f + _dir.y, _pos.z + _dir.z, 0.0f, 0.0f);

	vertexData[6].setPosUV( _pos.x - 1.0f + _dir.x, _pos.y + 0.2f + _dir.y, _pos.z + _dir.z, 0.0f, 0.0f);
	vertexData[7].setPosUV( _pos.x - 1.0f + _dir.x, _pos.y - 0.2f + _dir.y, _pos.z + _dir.z, 0.0f, 0.0f);
	vertexData[8].setPosUV( _pos.x + 1.0f + _dir.x, _pos.y - 0.2f + _dir.y, _pos.z + _dir.z, 0.0f, 0.0f);

	vertexData[9].setPosUV( _pos.x + 1.0f + _dir.x, _pos.y - 0.2f + _dir.y, _pos.z + _dir.z, 0.0f, 0.0f);
	vertexData[10].setPosUV( _pos.x+ 1.0f + _dir.x, _pos.y + 0.2f + _dir.y, _pos.z + _dir.z, 0.0f, 0.0f);
	vertexData[11].setPosUV( _pos.x- 1.0f + _dir.x, _pos.y + 0.2f + _dir.y, _pos.z + _dir.z, 0.0f, 0.0f);

	for (int i = 0; i < 12; i++) {
		vertexData[i].setColor(255, 255, 255, 255);
	}

	_vertexSize = sizeof(vertexData);
	
	// Binding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	// Uploading the buffer data
	glBufferData(GL_ARRAY_BUFFER, _vertexSize, vertexData, GL_STATIC_DRAW);
	// Unbinding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Crosshair::draw()
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
	glDrawArrays(GL_TRIANGLES, 0, _vertexSize);

	//disable the vertex attrib array. Not optional
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	//unbind the  texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//unbind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}