#include "AgentRanged.h"

AgentRanged::AgentRanged(glm::vec3 pos, glm::vec3 dir, float width, float height, float life) :
	_agentState(AgentState::SCOUT)
{
	_position = pos; _patPos = pos;
	_direction = dir; _patDir = dir;
	_width = width;
	_height = height;
	_life = life;

	//Melee units variables
	_patrolTimer = 0.0f;
	_patrolLimit = 200.0f;
	_scoutTimer = 0.0f;
	_scoutLimit = 200.0f;
	_speed = 0.04f;
	_attackSpeed = 25.0f;
	_asCount = _attackSpeed;
	_attackCooldown = 150.0f;
	_attackTimer = _attackCooldown;
	_damage = 100.0f;
	_hitPlayer = false;
	_currentSpeed = _speed;
	_range = 150.0f;
	_viewDist = 300.0f;
	_viewRange = 150.0f;
}

AgentRanged::~AgentRanged()
{

}

void AgentRanged::init()
{
	Agent::init("NONE", 0, 255, 0, 255);
}

void AgentRanged::draw()
{
	Agent::draw();
}

bool AgentRanged::inAttackRange(const Camera &camera)
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

bool AgentRanged::collideWithTerrain(Terrain terrain, glm::vec3 newPos)
{
	return(terrain._position.x - terrain._size < _position.x + _width &&
		terrain._position.x + terrain._size > _position.x - _width &&
		terrain._position.y - terrain._size < _position.y + _height &&
		terrain._position.y + terrain._size > _position.y - _height &&
		terrain._position.z - terrain._size < _position.z + _width &&
		terrain._position.z + terrain._size > _position.z - _width);
}

bool AgentRanged::collideWithPlayer(const Camera &camera, glm::vec3 newPos)
{
	Camera cam = camera;
	glm::vec3 playerPos = cam.getPosition();
	float width = cam.getPlayerWidth();
	float height = cam.getPlayerHeight();
	return(playerPos.x - width < _position.x + _width &&
		playerPos.x + width > _position.x - _width &&
		playerPos.y - height < _position.y + _height &&
		playerPos.y + height > _position.y - _height &&
		playerPos.z - width < _position.z + _width &&
		playerPos.z + width > _position.z - _width);
}

void AgentRanged::move(float dt, const Camera &camera)
{
	glm::vec3 newPos = _position + _direction * (_currentSpeed * dt);
	if(!collideWithPlayer(camera, newPos))
	{
		_position.x = newPos.x;
		_position.z = newPos.z;
	}
}

void AgentRanged::scout(float dt, const Camera &camera)
{
	//The melee agent will patrol, this agent will stand around looking out for the agent
	//by randomly looking in different directions.
	_scoutTimer++;
	if(_scoutTimer == _scoutLimit)
	{
		//Getting the agent to look north, south, east & west randomly
		int rando = rand() % 4;
		if(rando == 1){
			//std::cout << "looking north" << std::endl;
			_direction = glm::vec3(0.0f, 0.0f, 1.0f);	
		} else if(rando == 2) {
			//std::cout << "looking south" << std::endl;
			_direction = glm::vec3(0.0f, 0.0f, -1.0f);
		} else if(rando == 3) {
			//std::cout << "looking west" << std::endl;
			_direction = glm::vec3(1.0f, 0.0f, 0.0f);
		} else {
			//std::cout << "looking east" << std::endl;
			_direction = glm::vec3(-1.0f, 0.0f, 0.0f);
		}
		_scoutTimer = 0;
	}
	Camera cam = camera;
	if(Agent::lookForPlayer(cam.getPosition())) { _agentState = AgentState::CHASE; }
}

void AgentRanged::patrol(float dt, const Camera &camera)
{
	//Some simple patrolling math to make the agent move back and forth
	if(_patrolTimer == _patrolLimit) { _patrolLimit *= -1; _direction *= -1; } 
	if(_patrolLimit > 0) { _patrolTimer++; } else { _patrolTimer--; }
	move(dt, camera);
	//If the agent finds the player Chase that mofo!
	Camera cam = camera;
	if(Agent::lookForPlayer(cam.getPosition())) { _agentState = AgentState::CHASE; }
}

void AgentRanged::chase(float dt, const Camera &camera)
{
	_attackTimer--;
	//If the agent gets in attack range of the player and his attack is off cooldown
	if(inAttackRange(camera))
	{ 
		if(_attackTimer <= 0)
		{
			_agentState = AgentState::ATTACK;
		} 
	} else {
		//Getting the direction to the player.
		Camera cam = camera;
		_direction = glm::normalize(cam.getPosition() - _position);
		//Move towards the player
		move(dt, camera);
	}
}

void AgentRanged::attack(float dt, const Camera &camera, PlayerStatus player)
{
	//Getting the direction to the player.
	Camera cam = camera;
	_direction = glm::normalize(cam.getPosition() - _position);

	//if the agent has stopped his attack "animation"
	if(_asCount == 0) 
	{ 
		if (inAttackRange(camera)) {
			_attackTimer = _attackCooldown;
			_hitPlayer = true;
		}
		_agentState = AgentState::CHASE; 
		_asCount = _attackSpeed;
	} else { 
		_asCount--; 
	}
}

bool AgentRanged::update(float dt, PlayerStatus player, const Camera &camera)
{	
	if(_agentState == AgentState::SCOUT)
	{
		_currentSpeed = 0;
		scout(dt, camera);
	} else if(_agentState == AgentState::PATROL)
	{
		_currentSpeed = _speed;
		patrol(dt, camera);
		
	} else if(_agentState == AgentState::CHASE) 
	{
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