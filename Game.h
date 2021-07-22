#pragma once

#include <iostream>
#include <conio.h>
#include <time.h>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#ifndef GAME_H
#define GAME_H

/*
	Class that acts as the game engine
	wrapper class
*/

class Game
{
private:
	//SF Variables
	sf::RenderWindow* window;
	sf::Event event;
	sf::VideoMode videoMode;

	//Game logic
	int points;
	int tiles;
	float ballPositionX;
	float ballPositionY;
	std::vector<sf::RectangleShape> tileArray;

	//Game objects
	sf::RectangleShape platform;
	sf::CircleShape ball;

	//Private functions
	void initVariables();
	void initWindow();
	void initPlatform();
	void initCircle();
	void initTiles();

public:
	//Constructors / Destructos
	Game();
	virtual ~Game();

	//Accesors
	const bool getWindowIsOpen() const;

	//Functions
	void poolEvents();
	void update();
	void renderTiles();
	void render();

	//game functions
	void movePlatformRigth();
	void movePlatformLeft();
	void jumpingBall();
	void checkCollisionPlatformWithBall();
	void checkCollisionBallWithTile();
	void checkWinStatus();
};

#endif

