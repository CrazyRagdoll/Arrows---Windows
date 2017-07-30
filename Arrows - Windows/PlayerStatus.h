#pragma once

#include <iostream>

class PlayerStatus 
{
public:

	PlayerStatus();
	~PlayerStatus();

	void init();

	void reset();

	void damage(float damage);

	//Some simple setters
	void setLife(float life) { _life = life; }
	void setTime(float time) { _time = time; }
	void setTotalTime(float time) { _totalTime = time; }
	void setAmmo(int   ammo) { _ammo = ammo; }
	void setWave(int   wave) { _wave = wave; }

	//Some simple getters.
	float getLife() { return _life; }
	float getTime() { return _time; }
	float getScore() { return _score; }
	float getHighScore() { return _highScore; }
	float getTotalTime() { return _totalTime; }
	int   getAmmo() { return _ammo; }
	int   getWave() { return _wave; }

	//incrementers
	void incTime(float time) { _time += time; }
	void incScore(float score) { _score += score; }
	void incTotalTime(float time) { _totalTime += time; }
	void incAmmo(int   ammo) { _ammo += ammo; std::cout << "Your ammo: " << _ammo << std::endl; }
	void incWave(int   wave) { _wave += wave; std::cout << "Starting Wave: " << _wave << "." << std::endl;}

private:

	float _life;
	float _time;
	float _totalTime;
	float _score;
	float _highScore;
	int _ammo;
	int _wave;

};