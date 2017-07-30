#include "Agent.h"


Agent::Agent() 
{
	_vboID = 0;
}

Agent::~Agent()
{
	//cleaing up the buffers when the sprite is destroyed.
	if(_vboID != 0)
	{
		glDeleteBuffers(1, &_vboID);
	}
}

bool Agent::lookForPlayer(glm::vec3 playerPos)
{
	//Along with the current position of the agent these two values form a triangle of view
	//by using the cross product of the direction the agent is facing and which way is up I can find points to the left and right.
	glm::vec3 _fieldOfViewLeft, _fieldOfViewRight;
	_fieldOfViewLeft  =  glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), _direction * _viewRange) + _direction * _viewDist + _position;
	_fieldOfViewRight = -glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), _direction * _viewRange) + _direction * _viewDist + _position;

	//Barycentric coordinate system collision detection
	glm::vec3 p2 = _fieldOfViewLeft; glm::vec3 p3 = _fieldOfViewRight; glm::vec3 p1 = _position;
	float alpha = ((p2.z - p3.z)*(playerPos.x - p3.x) + (p3.x - p2.x)*(playerPos.z - p3.z)) /
					((p2.z - p3.z)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.z - p3.z));
	float beta  = ((p3.z - p1.z)*(playerPos.x - p3.x) + (p1.x - p3.x)*(playerPos.z - p3.z)) / 
					((p2.z - p3.z)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.z - p3.z));
	float gamma = 1.0f - alpha - beta;

	//If all of the values are above 0 the player is inside the LoS triangle.
	if(alpha > 0 && beta > 0 && gamma > 0) {
		return true;
	} 
	return false;
}

void Agent::init(string texture, int r, int g, int b, int a)
{
	_r = r; _g = g; _b = b; _a = a;
	if (texture != "NONE")
	{
		_texture.id = _textureLoader.loadGLTexture(texture);	
	}

	// If the vertex buffer is 0, use OpenGL to set it.
	if( _vboID == 0 )
	{
		glGenBuffers(1, &_vboID);
	}

    // Make a cube out of triangles (two triangles per side)
	Vertex vertexData[36];
    //  X     Y     Z       U     V
    // bottom
    vertexData[0].setPosUV(-_width + _position.x,-_height + _position.y,-_width + _position.z,   0.0f, 0.0f);
    vertexData[1].setPosUV( _width + _position.x,-_height + _position.y,-_width + _position.z,   1.0f, 0.0f);
    vertexData[2].setPosUV(-_width + _position.x,-_height + _position.y, _width + _position.z,   0.0f, 1.0f);
    vertexData[3].setPosUV( _width + _position.x,-_height + _position.y,-_width + _position.z,   1.0f, 0.0f);
    vertexData[4].setPosUV( _width + _position.x,-_height + _position.y, _width + _position.z,   1.0f, 1.0f);
    vertexData[5].setPosUV(-_width + _position.x,-_height + _position.y, _width + _position.z,   0.0f, 1.0f);

    // top
    vertexData[6].setPosUV(-_width + _position.x, _height + _position.y,-_width + _position.z,   0.0f, 0.0f);
    vertexData[7].setPosUV(-_width + _position.x, _height + _position.y, _width + _position.z,   0.0f, 1.0f);
    vertexData[8].setPosUV( _width + _position.x, _height + _position.y,-_width + _position.z,   1.0f, 0.0f);
    vertexData[9].setPosUV( _width + _position.x, _height + _position.y,-_width + _position.z,   1.0f, 0.0f);
    vertexData[10].setPosUV(-_width + _position.x, _height + _position.y, _width + _position.z,   0.0f, 1.0f);
    vertexData[11].setPosUV( _width + _position.x, _height + _position.y, _width + _position.z,   1.0f, 1.0f);

    // right
    vertexData[12].setPosUV( _width + _position.x,-_height + _position.y, _width + _position.z,   1.0f, 0.0f); 
    vertexData[13].setPosUV( _width + _position.x,-_height + _position.y,-_width + _position.z,   0.0f, 0.0f); 
    vertexData[14].setPosUV( _width + _position.x, _height + _position.y,-_width + _position.z,   0.0f, 1.0f); 
    vertexData[15].setPosUV( _width + _position.x,-_height + _position.y, _width + _position.z,   1.0f, 0.0f); 
    vertexData[16].setPosUV( _width + _position.x, _height + _position.y,-_width + _position.z,   0.0f, 1.0f); 
    vertexData[17].setPosUV( _width + _position.x, _height + _position.y, _width + _position.z,   1.0f, 1.0f); 

	// left
    vertexData[18].setPosUV(-_width + _position.x,-_height + _position.y, _width + _position.z,   0.0f, 0.0f);
    vertexData[19].setPosUV(-_width + _position.x, _height + _position.y,-_width + _position.z,   1.0f, 1.0f);
    vertexData[20].setPosUV(-_width + _position.x,-_height + _position.y,-_width + _position.z,   1.0f, 0.0f);
    vertexData[21].setPosUV(-_width + _position.x,-_height + _position.y, _width + _position.z,   0.0f, 0.0f);
    vertexData[22].setPosUV(-_width + _position.x, _height + _position.y, _width + _position.z,   0.0f, 1.0f);
    vertexData[23].setPosUV(-_width + _position.x, _height + _position.y,-_width + _position.z,   1.0f, 1.0f);

    // front
    vertexData[24].setPosUV(-_width + _position.x,-_height + _position.y, _width + _position.z,   1.0f, 0.0f);
    vertexData[25].setPosUV( _width + _position.x,-_height + _position.y, _width + _position.z,   0.0f, 0.0f);
    vertexData[26].setPosUV(-_width + _position.x, _height + _position.y, _width + _position.z,   1.0f, 1.0f);
    vertexData[27].setPosUV( _width + _position.x,-_height + _position.y, _width + _position.z,   0.0f, 0.0f);
    vertexData[28].setPosUV( _width + _position.x, _height + _position.y, _width + _position.z,   0.0f, 1.0f);
    vertexData[29].setPosUV(-_width + _position.x, _height + _position.y, _width + _position.z,   1.0f, 1.0f);

    // back
    vertexData[30].setPosUV(-_width + _position.x,-_height + _position.y,-_width + _position.z,   0.0f, 0.0f);
    vertexData[31].setPosUV(-_width + _position.x, _height + _position.y,-_width + _position.z,   0.0f, 1.0f);
    vertexData[32].setPosUV( _width + _position.x,-_height + _position.y,-_width + _position.z,   1.0f, 0.0f);
    vertexData[33].setPosUV( _width + _position.x,-_height + _position.y,-_width + _position.z,   1.0f, 0.0f);
    vertexData[34].setPosUV(-_width + _position.x, _height + _position.y,-_width + _position.z,   0.0f, 1.0f);
    vertexData[35].setPosUV( _width + _position.x, _height + _position.y,-_width + _position.z,   1.0f, 1.0f);

	for (int i = 0; i < 36; i++) {
		vertexData[i].setColor(_r, _g, _b, _a);
	}
	
	// Binding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	// Uploading the buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	// Unbinding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Agent::draw()
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
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	
	//Draw the 6 verticies to the screen
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//disable the vertex attrib array. Not optional
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	//unbind the  texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//unbind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}