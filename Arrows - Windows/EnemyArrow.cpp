#include "EnemyArrow.h"

EnemyArrow::EnemyArrow(glm::vec3 pos, glm::vec3 playerPos, float damage) :
	_width(1.0f),
	_length(1.0f),
	_skin("NONE"),
	_gravity(-0.002f),
	_floorTime(100),
	_stuck(false),
	_active(true),
	_lifeTime(250),
	_speed(5.0f)
{
	_vboID = 0;

	_position = pos;

	//Figuring out the trajectory.
	float timeTaken = glm::distance(playerPos, pos)/_speed; //time taken for the arrow to reach the player
	//Simple suvat, v = u + at, 0 = u + _gravity * timeTaken
	float upwardsVelocity = 2 * -(_gravity * timeTaken);
	_direction = glm::normalize(playerPos - pos);
	_velocity = glm::vec3(_direction.x, _direction.y + upwardsVelocity, _direction.z) * _speed;
	_damage = damage;
}

EnemyArrow::~EnemyArrow()
{
	//cleaing up the buffers when the sprite is destroyed.
	if(_vboID != 0)
	{
		glDeleteBuffers(1, &_vboID);
	}
}

bool EnemyArrow::checkFloorCollision(Floor& floor)
{
	return(_position.y - _width < floor._y &&
		   _position.x < floor._x + floor._width &&
		   _position.x > floor._x - floor._width &&
		   _position.z < floor._z + floor._width &&
		   _position.z > floor._z - floor._width); 
}

//Checking for collisions with the player
bool EnemyArrow::checkPlayerCollision(Camera& camera)
{
	glm::vec3 tmpP = camera.getPosition();
	float tmpW = camera.getPlayerWidth();
	float tmpH = camera.getPlayerHeight();
	return(_position.x - _width < tmpP.x + tmpW &&
			_position.x + _width > tmpP.x - tmpW &&
			_position.y - _width < tmpP.y + tmpH &&
			_position.y + _width > tmpP.y - tmpH &&
			_position.z - _width < tmpP.z + tmpW &&
			_position.z + _width > tmpP.z - tmpW);
}

//Checking only the TIP of the arrow against stuffs
bool EnemyArrow::checkTerrainCollision(Terrain& terrain)
{
	return(_position.x < terrain._position.x + terrain._size &&
		   _position.x > terrain._position.x - terrain._size &&
		   _position.y < terrain._position.y + terrain._size &&
		   _position.y > terrain._position.y - terrain._size &&
		   _position.z < terrain._position.z + terrain._size &&
		   _position.z > terrain._position.z - terrain._size); 
}

bool EnemyArrow::update(float dt)
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

void EnemyArrow::init()
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
		vertexData[i].setColor(255, 255, 255, 255);
	}
	
	// Binding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	// Uploading the buffer data
	glBufferData(GL_ARRAY_BUFFER, _vertexSize, vertexData, GL_STATIC_DRAW);
	// Unbinding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void EnemyArrow::draw()
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