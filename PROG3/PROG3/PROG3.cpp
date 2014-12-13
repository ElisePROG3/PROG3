#include <iostream>
#include "Stain.h"

int main(int argc, char* argv[])
{
	stain::Stain game = stain::Stain();
	// Init and show loading screen
	game.init("Game!", 800, 600);
	game.loadImage("data/images/StudioElise.png", "splash");
	game.showOverlay("splash");

	// Load resources
	game.loadImage("data/images/mob.png", "mob");

	SDL_Event event;
	bool quit = false;
	while (!quit){
		while (SDL_PollEvent(&event) != 0){
			if (event.type == SDL_QUIT){
				quit = true;
			}
		}
	}

	return 0;
}

