#include "Arrow.h"

double TO_RAD = 3.14159265358979323846/180;

Arrow::Arrow(glm::vec3 pos, glm::vec3 dir, float speed, float width, float length, int lifeTime, string texture) :
	_gravity(-0.002f),
	_floorTime(100),
	_stuck(false),
	_active(true)
{
	_vboID = 0;
	
	_lifeTime = lifeTime;
	_position = pos;
	_direction = dir;
	_speed = speed;
	_width = width;
	_length = length;
	_velocity = dir * speed;
	_skin = texture;
}

Arrow::~Arrow()
{
	//cleaing up the buffers when the sprite is destroyed.
	if(_vboID != 0)
	{
		glDeleteBuffers(1, &_vboID);
	}
}

bool Arrow::update(float dt)
{	
	//checking to see if the arrow is still in flight or not, then updating its position and deleting after a certain time
	if(_stuck){
		_floorTime--;
	} else {
		//SUVAT to figure out the effects of gravity on the velocity v = u + at
		_velocity.y += (dt * _gravity);
		_position += _velocity;
		_lifeTime--;
	}

	if(!_active || _lifeTime == 0 || _floorTime == 0) { return true; }
	return false;
}

void Arrow::clean()
{

}

bool Arrow::checkFloorCollision(Floor& floor)
{
	return(_position.y - _width < floor._y &&
		   _position.x < floor._x + floor._width &&
		   _position.x > floor._x - floor._width &&
		   _position.z < floor._z + floor._width &&
		   _position.z > floor._z - floor._width); 
}

//Checking for collisions with agents
bool Arrow::checkAgentCollision(Agent& agent)
{
	return(_position.x - _width < agent._position.x + agent._width &&
			_position.x + _width > agent._position.x - agent._width &&
			_position.y - _width < agent._position.y + agent._height &&
			_position.y + _width > agent._position.y - agent._height &&
			_position.z - _width < agent._position.z + agent._width &&
			_position.z + _width > agent._position.z - agent._width);
}

//Checking only the TIP of the arrow against stuffs
bool Arrow::checkTerrainCollision(Terrain& terrain)
{
	return(_position.x < terrain._position.x + terrain._size &&
		   _position.x > terrain._position.x - terrain._size &&
		   _position.y < terrain._position.y + terrain._size &&
		   _position.y > terrain._position.y - terrain._size &&
		   _position.z < terrain._position.z + terrain._size &&
		   _position.z > terrain._position.z - terrain._size); 
}

//Checking collisions with cubes
bool Arrow::checkCollision(Cube& cube)
{
	return(_position.x + _width > cube._x - cube._width &&
		_position.x - _width < cube._x + cube._width &&
		_position.y + _width > cube._y - cube._width &&
		_position.y - _width < cube._y + cube._width &&
		_position.z + _width > cube._z - cube._width &&
		_position.z - _width < cube._z + cube._width); 
}

//Rotation function created using 3D rotation matrix math.
glm::vec3 Arrow::rotate(float deg, glm::vec3 axis, glm::vec3 pos)
{
	//If not a single axis has been specified return false.
	if(!(axis.x == 0.0f && axis.y == 0.0f && axis.z == 1.0f) && 
		!(axis.x == 0.0f && axis.y == 1.0f && axis.z == 0.0f) && 
		!(axis.x == 1.0f && axis.y == 0.0f && axis.z == 0.0f)) { return pos; }

	glm::vec3 temp = glm::vec3(0.0f, 0.0f, 0.0f);
	deg *= TO_RAD;

	//For rotations along the x
	if(axis.x == 1.0f && axis.y == 0.0f && axis.z == 0.0f)
	{
		std::cout << "Rotating around the X axis." << std::endl;
		temp.x = pos.x;
		temp.y = (pos.y * cos(deg) - pos.z * sin(deg));
		temp.z = (pos.y * sin(deg) + pos.z * cos(deg));
		return temp; 
	}

	//For rotations along the y.
	if(axis.x == 0.0f && axis.y == 1.0f && axis.z == 0.0f)
	{
		std::cout << "Rotating around the Y axis." << std::endl;
		temp.x = (pos.x * cos(deg) + pos.z * sin(deg));
		temp.y = pos.y;
		temp.z = (pos.x *-sin(deg) + pos.z * cos(deg));
		return temp;
	}

	//For rotations along the z.
	if(axis.x == 0.0f && axis.y == 0.0f && axis.z == 1.0f)
	{
		std::cout << "Rotating around the Z axis." << std::endl;
		temp.x = (pos.x * cos(deg) - pos.y * sin(deg));
		temp.y = (pos.x * sin(deg) + pos.y * cos(deg));
		temp.z = pos.z;
		return temp;
	}
}	

void Arrow::init()
{

	if (_skin != "NONE")
	{
		_texture.id = _textureLoader.loadGLTexture(_skin);	
	}

	// If the vertex buffer is 0, use OpenGL to set it.
	if( _vboID == 0 )
	{
		glGenBuffers(1, &_vboID);
	}

	//Making the code a bit more readable. 
	float posX = _width + _position.x; float negX = -_width + _position.x;
	float posY = _width + _position.y; float negY = -_width + _position.y;
	float posZ = _width + _position.z; float negZ = -_width + _position.z;


	/*	~~~~~~~~Experimental CODE~~~~~~~~~~~~
	std::vector<glm::vec3> p;

	p.emplace_back(glm::vec3(negX, negY, negZ));
	p.emplace_back(glm::vec3(posX, negY, negZ));
	p.emplace_back(glm::vec3(negX, negY, posZ));
	p.emplace_back(glm::vec3(posX, negY, negZ));
	p.emplace_back(glm::vec3(posX, negY, posZ));
	p.emplace_back(glm::vec3(negX, negY, posZ));

	p.emplace_back(glm::vec3(negX, posY, negZ));
	p.emplace_back(glm::vec3(negX, posY, posZ));
	p.emplace_back(glm::vec3(posX, posY, negZ));
	p.emplace_back(glm::vec3(posX, posY, negZ));
	p.emplace_back(glm::vec3(negX, posY, posZ));
	p.emplace_back(glm::vec3(posX, posY, posZ));

	p.emplace_back(glm::vec3(posX, negY, posZ));
	p.emplace_back(glm::vec3(posX, negY, negZ));
	p.emplace_back(glm::vec3(posX, posY, negZ));
	p.emplace_back(glm::vec3(posX, negY, posZ));
	p.emplace_back(glm::vec3(posX, posY, negZ));
	p.emplace_back(glm::vec3(posX, posY, posZ));

	p.emplace_back(glm::vec3(negX, negY, posZ));
	p.emplace_back(glm::vec3(negX, posY, negZ));
	p.emplace_back(glm::vec3(negX, negY, negZ));
	p.emplace_back(glm::vec3(negX, negY, posZ));
	p.emplace_back(glm::vec3(negX, posY, posZ));
	p.emplace_back(glm::vec3(negX, posY, negZ));

	p.emplace_back(glm::vec3(negX, negY, posZ));
	p.emplace_back(glm::vec3(posX, negY, posZ));
	p.emplace_back(glm::vec3(negX, posY, posZ));
	p.emplace_back(glm::vec3(posX, negY, posZ));
	p.emplace_back(glm::vec3(posX, posY, posZ));
	p.emplace_back(glm::vec3(negX, posY, posZ));

	p.emplace_back(glm::vec3(negX, negY, negZ));
	p.emplace_back(glm::vec3(negX, posY, negZ));
	p.emplace_back(glm::vec3(posX, negY, negZ));
	p.emplace_back(glm::vec3(posX, negY, negZ));
	p.emplace_back(glm::vec3(negX, posY, negZ));
	p.emplace_back(glm::vec3(posX, posY, negZ));

	for(int i = 0; i < p.size(); i++)
	{
		p[i] = rotate(45.0f, glm::vec3(0.0f, 1.0f, 0.0f), p[i]);
		vertexData[i].setPosUV(p[i].x, p[i].y, p[i].z, 0.0, 0.0);
	}*/

    // Make a cube out of triangles (two triangles per side)
	Vertex vertexData[36];

    //  X     Y     Z       U     V
    // bottom
    vertexData[0].setPosUV(negX, negY, negZ,   0.0f, 0.0f);
    vertexData[1].setPosUV(posX, negY, negZ,   1.0f, 0.0f);
    vertexData[2].setPosUV(negX, negY, posZ,   0.0f, 1.0f);
    vertexData[3].setPosUV(posX, negY, negZ,   1.0f, 0.0f);
    vertexData[4].setPosUV(posX, negY, posZ,   1.0f, 1.0f);
    vertexData[5].setPosUV(negX, negY, posZ,   0.0f, 1.0f);

    // top
    vertexData[6].setPosUV(negX, posY, negZ,   0.0f, 0.0f);
    vertexData[7].setPosUV(negX, posY, posZ,   0.0f, 1.0f);
    vertexData[8].setPosUV(posX, posY, negZ,   1.0f, 0.0f);
    vertexData[9].setPosUV(posX, posY, negZ,   1.0f, 0.0f);
    vertexData[10].setPosUV(negX, posY, posZ,   0.0f, 1.0f);
    vertexData[11].setPosUV(posX, posY, posZ,   1.0f, 1.0f);

    // right
    vertexData[12].setPosUV(posX, negY, posZ,   1.0f, 0.0f); 
    vertexData[13].setPosUV(posX, negY, negZ,   0.0f, 0.0f); 
    vertexData[14].setPosUV(posX, posY, negZ,   0.0f, 1.0f); 
    vertexData[15].setPosUV(posX, negY, posZ,   1.0f, 0.0f); 
    vertexData[16].setPosUV(posX, posY, negZ,   0.0f, 1.0f); 
    vertexData[17].setPosUV(posX, posY, posZ,   1.0f, 1.0f); 

	// left
    vertexData[18].setPosUV(negX, negY, posZ,   0.0f, 0.0f);
    vertexData[19].setPosUV(negX, posY, negZ,   1.0f, 1.0f);
    vertexData[20].setPosUV(negX, negY, negZ,   1.0f, 0.0f);
    vertexData[21].setPosUV(negX, negY, posZ,   0.0f, 0.0f);
    vertexData[22].setPosUV(negX, posY, posZ,   0.0f, 1.0f);
    vertexData[23].setPosUV(negX, posY, negZ,   1.0f, 1.0f);

    // front
    vertexData[24].setPosUV(negX, negY, posZ,   1.0f, 0.0f);
    vertexData[25].setPosUV(posX, negY, posZ,   0.0f, 0.0f);
    vertexData[26].setPosUV(negX, posY, posZ,   1.0f, 1.0f);
    vertexData[27].setPosUV(posX, negY, posZ,   0.0f, 0.0f);
    vertexData[28].setPosUV(posX, posY, posZ,   0.0f, 1.0f);
    vertexData[29].setPosUV(negX, posY, posZ,   1.0f, 1.0f);

    // back
    vertexData[30].setPosUV(negX, negY, negZ,   0.0f, 0.0f);
    vertexData[31].setPosUV(negX, posY, negZ,   0.0f, 1.0f);
    vertexData[32].setPosUV(posX, negY, negZ,   1.0f, 0.0f);
    vertexData[33].setPosUV(posX, negY, negZ,   1.0f, 0.0f);
    vertexData[34].setPosUV(negX, posY, negZ,   0.0f, 1.0f);
    vertexData[35].setPosUV(posX, posY, negZ,   1.0f, 1.0f);

    _vertexSize = sizeof(vertexData);

	for (int i = 0; i < 36; i++) {
		vertexData[i].setColor(1.0f, 0.0f, 0.0f, 1.0f);
	}
	
	// Binding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	// Uploading the buffer data
	glBufferData(GL_ARRAY_BUFFER, _vertexSize, vertexData, GL_STATIC_DRAW);
	// Unbinding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Arrow::draw()
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