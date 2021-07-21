#include "Game.h"

//functions private
void Game::initVariables() {
	this->window = nullptr;

	this->points = 0;
	this->tiles = 4;
	this->ballPositionX = 5;
	this->ballPositionY = 2;

	srand(time(NULL));
}

void Game::initWindow() {
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
	
	//fps, limit 60, to smooth
	this->window->setFramerateLimit(60);
}

//init platform, otherwise player
void Game::initPlatform() {
	this->platform.setPosition(300.f, 550.f);
	this->platform.setSize(sf::Vector2f(200.f, 10.f));
	this->platform.setFillColor(sf::Color::White);
}

void Game::initCircle() {
	this->ball.setRadius(50);
	this->ball.setPosition(0.f, 80.f);
}

void Game::initTiles() {
	int positionX = 0;

	for (int i = 0; i < this->tiles; i++) {
		sf::RectangleShape tile;
		tile.setSize(sf::Vector2f(195.f, 25.f));
		tile.setFillColor(sf::Color::Green);
		tile.setOutlineThickness(5.f);
		tile.setOutlineColor(sf::Color::Black);
		tile.setPosition(positionX, 0);

		this->tileArray.push_back(tile);
		positionX += 200.f;
	}
}

//Construcots / Destructors
//init all game resources
Game::Game() {
	this->initVariables();
	this->initWindow();
	this->initPlatform();
	this->initCircle();
	this->initTiles();
}


Game::~Game() {
	//cleaning memory
	delete this->window;
}

//Accesors
const bool Game::getWindowIsOpen() const {
	return this -> window -> isOpen();
}

//control plaftorm functions and also public functions
void Game::movePlatformLeft() {
	if (this->platform.getPosition().x > 0.f) {
		this->platform.move(-25, 0);
	}
}

void Game::movePlatformRigth() {
	if (this->platform.getPosition().x < 600.f) {
		this->platform.move(25, 0);
	}
}

void Game::jumpingBall()
{
	//OX parametrs
	if (this->ball.getPosition().x > 700.f)
		this->ballPositionX = -5;
	else if (this->ball.getPosition().x < 0.f)
		this->ballPositionX = 5;

	//OY parametrs
	if (this->ball.getPosition().y > 500.f) {
		this->window->close();
		std::cout << "You lose :(\n";
	}
	else if (this->ball.getPosition().y < 0.f)
		this->ballPositionY = rand() % 5 + 1;
		

	//rendering ball
	this->ball.move(ballPositionX, ballPositionY);
}

void Game::checkCollisionPlatformWithBall() {
	if (this->ball.getGlobalBounds().intersects(this->platform.getGlobalBounds())) {
		this->ballPositionY = (rand() % 5 + 1) - 5;
	}
}

//checking collision ball with tiles
//Bug here :((
//have to repair this shit function

void Game::checkCollisionBallWithTile() {
	for (int i = 0; i < this->tileArray.size(); i++) {
		if (this->ball.getGlobalBounds().intersects(this->tileArray[i].getGlobalBounds()))
			printf("%d position", i + 1);
			//this->tileArray.erase(std::remove(this->tileArray.begin(), this->tileArray.end(), this->tileArray[i]));
	}
}

//functions public
void Game::poolEvents()
{
	//event pooling
	while (this -> window ->pollEvent(this->event)) {
		switch (this->event.type) {
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (this->event.key.code == sf::Keyboard::Escape)
					this->window->close();
				else if (this->event.key.code == sf::Keyboard::A)
					this->movePlatformLeft();
				else if (this->event.key.code == sf::Keyboard::D)
					this->movePlatformRigth();
				break;
		}
	}
}

//updating all important functions and objects
void Game::update()
{
	this->poolEvents();
	this->jumpingBall();
	this->checkCollisionPlatformWithBall();
	this->checkCollisionBallWithTile();
}

void Game::renderTiles() {
	/*
		@return void

		returning all the tiles on the top bar
	*/

	for (int i = 0; i < this->tileArray.size(); i++) {
		this->window->draw(tileArray[i]);
	}
}

void Game::render()
{
	/*
	* @return void
	* 
	*	- clearing old frame
	*	- rendering objects
	*	- display new frame
	*/

	this->window->clear();

	//drawing game
	this->window->draw(this->platform);
	this->window->draw(this->ball);
	this->renderTiles();

	this->window->display();
}
