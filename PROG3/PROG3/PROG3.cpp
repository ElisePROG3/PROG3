#include <iostream>
#include "Stain.h"
#include "Entity.h"
#include "EntityHuman.h"

int main(int argc, char* argv[])
{
	stain::Stain game = stain::Stain();
	// Init and show loading screen
	game.init("Game!", 800, 600);
	game.loadImage("splash", "data/images/StudioElise.png");
	game.setOverlay("splash", 2000);

	// Load resources
	game.loadImage("mob", "data/images/mob.png");
	game.loadImage("level1", "data/images/grass_bg.png");
	game.loadImage("player", "data/images/player.png", 100, 500);

	// Setup
	stain::MapLevel map1 = stain::MapLevel("meadow", game.getTexture("level1"));

	map1.addMobile(stain::EntityHuman::getInstance(300, 320, 20, game.getSprite("mob")));
	map1.addMobile(stain::EntityHuman::getInstance(280, 190, 20, game.getSprite("mob")));

	game.addLevel(&map1);
	game.setPlayer(stain::EntityHuman::getInstance(250, 250, 20, game.getSprite("player")));

	//game.setFPS(0);

	game.run();

	return 0;
}

