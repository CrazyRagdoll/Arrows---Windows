#include "PlayerStatus.h"

PlayerStatus::PlayerStatus() :
	_score(0.0f)
{

}

PlayerStatus::~PlayerStatus()
{

}

void PlayerStatus::init()
{
	_life = 1000.0f;
	_time = 0.0f;
	_totalTime = 0.0f;
	_ammo = 10;
	_wave = 1;
	_score = 0.0f;
	std::cout << "Your life: " << _life << std::endl;
	std::cout << "Your ammo: " << _ammo << std::endl;
	std::cout << "Wave     : " << _wave << std::endl;
}

void PlayerStatus::reset()
{
	_life = 1000.0f;
	_time = 0.0f;
	_totalTime = 0.0f;
	_ammo = 10;
	_wave = 1;
	_highScore = _score;
	_score = 0.0f;
	std::cout << "Your life: " << _life << std::endl;
	std::cout << "Your ammo: " << _ammo << std::endl;
	std::cout << "Wave     : " << _wave << std::endl;
}

void PlayerStatus::damage(float damage)
{
	_life -= damage;
	std::cout << "Your life: " << _life << std::endl;
}