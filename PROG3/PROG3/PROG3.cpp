#include <iostream>
#include "Stain.h"
#include "Entity.h"
#include "EntityHuman.h"

int main(int argc, char* argv[])
{
	stain::Stain game = stain::Stain();
	// Init and show loading screen
	game.init("Game!", 800, 600);
	game.loadImage("data/images/StudioElise.png", "splash");
	game.setOverlay("splash", 2000);

	// Load resources
	game.loadImage("data/images/mob.png", "mob");

	stain::EntityHuman* p = stain::EntityHuman::getInstance(100, 100, 20, game.getTextureFromHandle("mob"));
	game.addMobile(p);
	game.addMobile(stain::EntityHuman::getInstance(200, 100, 20, game.getTextureFromHandle("mob")));

	//game.setFPS(0);

	SDL_Event event;
	bool quit = false;
	while (!quit){
		while (SDL_PollEvent(&event) != 0){
			if (event.type == SDL_QUIT){
				quit = true;
			}
		}



		//SDL_Delay(35);

		game.render();
	}

	return 0;
}

