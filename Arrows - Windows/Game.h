#ifndef GAME_H_
#define GAME_H_

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>

#include "GLSLProgram.h"
#include "Window.h"
#include "Camera.h"
#include "InputManager.h"
#include "Timing.h"
#include "Arrow.h"
#include "EnemyArrow.h"
#include "AgentMelee.h"
#include "AgentRanged.h"
#include "Cube.h"
#include "Crosshair.h"
#include "Floor.h"
#include "Terrain.h"
#include "PlayerStatus.h"
#include "Item.h"

enum class GameState {PLAY, PAUSE, MAIN_MENU, EXIT};

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void processPauseInput();
	void drawGame();
	void drawObjects();

	//Object processing functions to keep the code more readable
	void processState();
	void nextWave(int wave);
	void processWave();
	void processArrows(float dt);
	void processEnemyArrows(float dt);
	void processMeleeAgents(float dt);
	void processRangedAgents(float dt);
	void processCollectables(float ct);

	//A simple functions to build a map
	void generateMap();
	void generateTerrain(int blocks, int terrainLevel, float size, float floor);

	Window _window;
	int _screenWidth;
	int _screenHeight;

	PlayerStatus _player;

	Cube _cube;		

	Floor _floor;

	GameState _gameState;	

	GLSLProgram _colorProgram;

	Camera _camera;

	InputManager _inputManager;

	FpsLimiter _fpsLimiter;

	std::vector<Arrow> _arrows;

	std::vector<EnemyArrow> _enemyArrows;

	std::vector<Terrain> _terrain;

	std::vector<AgentMelee> _meleeAgents;

	std::vector<AgentRanged> _rangedAgents;

	std::vector<Item> _arrowItems;

	float _maxFPS;
	float _fps;
	float _shotTimer, _SHOTSPEED, _shotPower;
	float _floorSize;

	int _spawnBuffer, _spawnTimer;  //Used to give the player an amout of time before the next wave spawns.
	int _wave; //What wave the player is on

	bool _paused;

	//To bebug!!
	bool _debug;
};

#endif