#include <iostream>
#include "Game.h"

int main() {
	//init game engine
	Game game;

	//main loop
	while (game.getWindowIsOpen()) {

		//update
		game.update();

		//render
		game.render();
	}
	return 0;
}