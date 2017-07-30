#include "AgentMelee.h"

AgentMelee::AgentMelee(glm::vec3 pos, glm::vec3 dir, float width, float height, float life): 
	_agentState(AgentState::PATROL)
{
	_position = pos; _patPos = pos;
	_direction = dir; _patDir = dir;
	_width = width;
	_height = height;
	_life = life;

	//Randomizing the patrol direction! -- everyones gota be different!
	int rando = rand() % 4;
	if(rando == 0){ _direction = _patDir = glm::vec3(0.0f, 0.0f, 1.0f);	} 
	else if(rando == 1) { _direction = _patDir = glm::vec3(0.0f, 0.0f, -1.0f); } 
	else if(rando == 2) { _direction = _patDir = glm::vec3(1.0f, 0.0f, 0.0f); } 
	else { _direction = _patDir = glm::vec3(-1.0f, 0.0f, 0.0f); }

	//Melee units variables
	_patrolTimer = 0.0f;
	_patrolLimit = 150.0f;
	_speed = 0.04f;
	_attackSpeed = 100.0f;
	_asCount = _attackSpeed;
	_damage = 200.0f;
	_hitPlayer = false;
	_currentSpeed = _speed;
	_range = 15.0f;
	_viewDist = 150.0f;
	_viewRange = 75.0f;
}

AgentMelee::~AgentMelee()
{

}

void AgentMelee::init()
{
	Agent::init("NONE", 255, 0, 0, 255);
}

void AgentMelee::draw()
{
	Agent::draw();
}

bool AgentMelee::inAttackRange(const Camera &camera)
{
	Camera cam = camera;
	glm::vec3 playerPos = cam.getPosition();
	float width = cam.getPlayerWidth();
	float height = cam.getPlayerHeight();
	return(playerPos.x - width < _position.x + _width + _range &&
			playerPos.x + width > _position.x - _width - _range &&
			playerPos.y - height < _position.y + _height + _range &&
			playerPos.y + height > _position.y - _height - _range &&
			playerPos.z - width < _position.z + _width + _range &&
			playerPos.z + width > _position.z - _width - _range);
}

bool AgentMelee::collideWithTerrain(Terrain terrain, glm::vec3 newPos)
{
	return(terrain._position.x - terrain._size < newPos.x + _width &&
		terrain._position.x + terrain._size > newPos.x - _width &&
		terrain._position.y - terrain._size < newPos.y + _height &&
		terrain._position.y + terrain._size > newPos.y - _height &&
		terrain._position.z - terrain._size < newPos.z + _width &&
		terrain._position.z + terrain._size > newPos.z - _width);
}

bool AgentMelee::collideWithPlayer(const Camera &camera, glm::vec3 newPos)
{
	Camera cam = camera;
	glm::vec3 playerPos = cam.getPosition();
	float width = cam.getPlayerWidth();
	float height = cam.getPlayerHeight();
	return(playerPos.x - width < newPos.x + _width &&
		playerPos.x + width > newPos.x - _width &&
		playerPos.y - height < newPos.y + _height &&
		playerPos.y + height > newPos.y - _height &&
		playerPos.z - width < newPos.z + _width &&
		playerPos.z + width > newPos.z - _width);
}

void AgentMelee::move(float dt, const Camera &camera)
{
	glm::vec3 newPos = _position + _direction * (_currentSpeed * dt);
	//if the next movement doesnt move the agent ontop of the player
	if(!collideWithPlayer(camera, newPos))
	{
		_position.x = newPos.x;
		_position.z = newPos.z;
	}
}

void AgentMelee::patrol(float dt, const Camera &camera)
{
	//Some simple patrolling math to make the agent move back and forth
	if(_patrolTimer == _patrolLimit) { _patrolLimit *= -1; _direction *= -1; } 
	if(_patrolLimit > 0) { _patrolTimer++; } else { _patrolTimer--; }
	move(dt, camera);
	Camera cam = camera;
	//If the agent finds the player Chase that mofo!
	if(Agent::lookForPlayer(cam.getPosition())) { _agentState = AgentState::CHASE; } 
}

void AgentMelee::chase(float dt, const Camera &camera)
{
	//If the agent gets in attack range of the player attack!
	if(inAttackRange(camera)){ _agentState = AgentState::ATTACK; } 
	//Getting the direction to the player.
	Camera cam = camera;
	_direction = glm::normalize(cam.getPosition() - _position);
	//Move towards the player
	move(dt, camera);
}

void AgentMelee::attack(float dt, const Camera &camera, PlayerStatus player)
{
	//Getting the direction to the player.
	Camera cam = camera;
	_direction = glm::normalize(cam.getPosition() - _position);
	//Move towards the player
	move(dt, camera);

	//if the agent has stopped his attack "animation"
	if(_asCount == 0) 
	{ 
		if (inAttackRange(camera)) {
			_hitPlayer = true;
		}
		_agentState = AgentState::CHASE; 
		_asCount = _attackSpeed;
	} else { 
		_asCount--; 
	}
}

bool AgentMelee::update(float dt, PlayerStatus player, const Camera &camera)
{	
	if(_agentState == AgentState::PATROL)
	{
		_currentSpeed = _speed;
		patrol(dt, camera);
		
	} else if(_agentState == AgentState::CHASE) {
		_currentSpeed = _speed * 1.5;
		chase(dt, camera);
		
	} else if(_agentState == AgentState::ATTACK)
	{
		_currentSpeed = _speed/2;
		attack(dt, camera, player);
	}
	
	if(_life <= 0) { return true; }
	return false;
}