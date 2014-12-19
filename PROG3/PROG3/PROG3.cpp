#include <iostream>
#include "Stain.h"
#include "EntityHuman.h"
#include "EntityBug.h"
#include "WeaponGun.h"

using namespace stain;

int main(int argc, char* argv[])
{
	Stain game = Stain();
	// Init and show loading screen
	game.init("Game!", 800, 600);
	game.loadImage("splash", "data/images/StudioElise.png");
	game.setOverlay("splash", 1000);

	// Load resources
	game.loadImage("mob", "data/images/mob.png", Sprite::FACING::SOUTH);
	game.loadImage("mob32", "data/images/mob32.png", Sprite::FACING::SOUTH);
	game.loadImage("level1", "data/images/grass_bg.png");
	game.loadImage("player", "data/images/player.png", Sprite::FACING::EAST, 100, 89);
	game.loadImage("loot_gun", "data/images/loot_handgun.png");
	game.loadImage("bullet", "data/images/bullet.png", Sprite::FACING::EAST);

	// Setup
	MapLevel* map1 = MapLevel::getInstance("meadow", game.getTexture("level1"));

	map1->addMobile(EntityBug::getInstance(300, 320, 8, game.getSprite("mob")));
	map1->addMobile(EntityBug::getInstance(280, 190, 8, game.getSprite("mob32")));

	map1->addLoot(EntityLoot::getInstance(260, 420, 8, game.getSprite("loot_gun"), 5000, WeaponGun::getInstance("Hand gun", game.getSprite("loot_gun"))));

	game.addLevel(map1);
	game.addPlayer(EntityHuman::getInstance(550, 500, 25, game.getSprite("player")));

	//game.setFPS(0);

	game.run();

	return 0;
}

