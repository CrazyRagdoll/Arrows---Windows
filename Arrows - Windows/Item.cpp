#include "Item.h"

Item::Item(glm::vec3 pos, int value) :
	_width(0.5f),
	_depth(0.5f),
	_height(4.0f),
	_time(10000.0f),
	_collected(false)
{
	_position = pos;
	_value = value;

	_vboID = 0;
}

Item::~Item()
{
	//cleaing up the buffers when the sprite is destroyed.
	if(_vboID != 0)
	{
		glDeleteBuffers(1, &_vboID);
	}
}

bool Item::update(float time)
{
	_time --;
	
	//Making the arrows all floaty like
	_position.y += sin(time/500)/4;

	if(_time <= 0 || _collected) { return true; }
	return false;
}

void Item::init()
{
	// If the vertex buffer is 0, use OpenGL to set it.
	if( _vboID == 0 )
	{
		glGenBuffers(1, &_vboID);
	}

    // Make a cube out of triangles (two triangles per side)
	Vertex vertexData[36];
    //  X     Y     Z       U     V
    // bottom
    vertexData[0].setPosUV(_position.x - _width, _position.y - _height, _position.z - _depth,   0.0f, 0.0f);
    vertexData[1].setPosUV(_position.x + _width, _position.y - _height, _position.z - _depth,   1.0f, 0.0f);
    vertexData[2].setPosUV(_position.x - _width, _position.y - _height, _position.z + _depth,   0.0f, 1.0f);
    vertexData[3].setPosUV(_position.x + _width, _position.y - _height, _position.z - _depth,   1.0f, 0.0f);
    vertexData[4].setPosUV(_position.x + _width, _position.y - _height, _position.z + _depth,   1.0f, 1.0f);
    vertexData[5].setPosUV(_position.x - _width, _position.y - _height, _position.z + _depth,   0.0f, 1.0f);

    // top
    vertexData[6].setPosUV(_position.x - _width, _position.y + _height, _position.z - _depth,   0.0f, 0.0f);
    vertexData[7].setPosUV(_position.x - _width, _position.y + _height, _position.z + _depth,   0.0f, 1.0f);
    vertexData[8].setPosUV(_position.x + _width, _position.y + _height, _position.z - _depth,   1.0f, 0.0f);
    vertexData[9].setPosUV(_position.x + _width, _position.y + _height, _position.z - _depth,   1.0f, 0.0f);
    vertexData[10].setPosUV(_position.x - _width, _position.y + _height, _position.z + _depth,   0.0f, 1.0f);
    vertexData[11].setPosUV(_position.x + _width, _position.y + _height, _position.z + _depth,   1.0f, 1.0f);

    // right
    vertexData[12].setPosUV(_position.x + _width, _position.y - _height, _position.z + _depth,   1.0f, 0.0f); 
    vertexData[13].setPosUV(_position.x + _width, _position.y - _height, _position.z - _depth,   0.0f, 0.0f); 
    vertexData[14].setPosUV(_position.x + _width, _position.y + _height, _position.z - _depth,   0.0f, 1.0f); 
    vertexData[15].setPosUV(_position.x + _width, _position.y - _height, _position.z + _depth,   1.0f, 0.0f); 
    vertexData[16].setPosUV(_position.x + _width, _position.y + _height, _position.z - _depth,   0.0f, 1.0f); 
    vertexData[17].setPosUV(_position.x + _width, _position.y + _height, _position.z + _depth,   1.0f, 1.0f); 

	// left
    vertexData[18].setPosUV(_position.x - _width, _position.y - _height, _position.z + _depth,   0.0f, 0.0f);
    vertexData[19].setPosUV(_position.x - _width, _position.y + _height, _position.z - _depth,   1.0f, 1.0f);
    vertexData[20].setPosUV(_position.x - _width, _position.y - _height, _position.z - _depth,   1.0f, 0.0f);
    vertexData[21].setPosUV(_position.x - _width, _position.y - _height, _position.z + _depth,   0.0f, 0.0f);
    vertexData[22].setPosUV(_position.x - _width, _position.y + _height, _position.z + _depth,   0.0f, 1.0f);
    vertexData[23].setPosUV(_position.x - _width, _position.y + _height, _position.z - _depth,   1.0f, 1.0f);

    // front
    vertexData[24].setPosUV(_position.x - _width, _position.y - _height, _position.z + _depth,   1.0f, 0.0f);
    vertexData[25].setPosUV(_position.x + _width, _position.y - _height, _position.z + _depth,   0.0f, 0.0f);
    vertexData[26].setPosUV(_position.x - _width, _position.y + _height, _position.z + _depth,   1.0f, 1.0f);
    vertexData[27].setPosUV(_position.x + _width, _position.y - _height, _position.z + _depth,   0.0f, 0.0f);
    vertexData[28].setPosUV(_position.x + _width, _position.y + _height, _position.z + _depth,   0.0f, 1.0f);
    vertexData[29].setPosUV(_position.x - _width, _position.y + _height, _position.z + _depth,   1.0f, 1.0f);

    // back
    vertexData[30].setPosUV(_position.x - _width, _position.y - _height, _position.z - _depth,   0.0f, 0.0f);
    vertexData[31].setPosUV(_position.x - _width, _position.y + _height, _position.z - _depth,   0.0f, 1.0f);
    vertexData[32].setPosUV(_position.x + _width, _position.y - _height, _position.z - _depth,   1.0f, 0.0f);
    vertexData[33].setPosUV(_position.x + _width, _position.y - _height, _position.z - _depth,   1.0f, 0.0f);
    vertexData[34].setPosUV(_position.x - _width, _position.y + _height, _position.z - _depth,   0.0f, 1.0f);
    vertexData[35].setPosUV(_position.x + _width, _position.y + _height, _position.z - _depth,   1.0f, 1.0f);

	for (int i = 0; i < 36; i++) {
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

void Item::draw()
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