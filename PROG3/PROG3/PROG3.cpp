#include <iostream>
#include "Stain.h"
#include "Assets.h"
#include "EntityHuman.h"
#include "EntityBug.h"
#include "WeaponGun.h"
#include "Portal.h"

using namespace stain;

int main(int argc, char* argv[])
{
	Stain game = Stain();
	// Init and show loading screen
	game.init("Game!", 800, 600);
	Assets::loadImage("splash", "data/images/StudioElise.png");
	Assets::loadImage("instructions", "data/images/instructions.png");
	game.setOverlay("splash", 3000);
	game.setOverlay("instructions");

	// Load resources
	Assets::loadImage("mob", "data/images/mob.png", Sprite::FACING::SOUTH);
	Assets::loadImage("mob32", "data/images/mob32.png", Sprite::FACING::SOUTH);
	Assets::loadImage("level1", "data/images/grass_bg.png");
	Assets::loadImage("level2", "data/images/room.png");
	Assets::loadImage("victory", "data/images/theend.png");
	Assets::loadImage("player", "data/images/player.png", Sprite::FACING::EAST, 100, 89);
	Assets::loadImage("loot_gun", "data/images/loot_handgun.png");
	Assets::loadImage("bullet", "data/images/bullet2.png");
	Assets::loadImage("portal", "data/images/portal.png", Sprite::FACING::NONE, 75, 100);

	// Set custom keys
	game.setKey(Stain::KEYEVENT::MOVE_UP, 'i');
	game.setKey(Stain::KEYEVENT::MOVE_DOWN, 'k');
	game.setKey(Stain::KEYEVENT::MOVE_LEFT, 'j');
	game.setKey(Stain::KEYEVENT::MOVE_RIGHT, 'l');

	// Setup
	MapLevel* map1 = MapLevel::getInstance("meadow", Assets::getTexture("level1"));
	MapLevel* map2 = MapLevel::getInstance("dungeon", Assets::getTexture("level2"));

	map1->addMobile(EntityBug::getInstance(300, 320, 8, Assets::getSprite("mob")));
	map1->addMobile(EntityBug::getInstance(280, 190, 8, Assets::getSprite("mob")));
	map1->addMobile(EntityBug::getInstance(500, 500, 8, Assets::getSprite("mob")));
	map1->addMobile(EntityBug::getInstance(480, 560, 8, Assets::getSprite("mob")));
	map1->addMobile(EntityBug::getInstance(400, 540, 8, Assets::getSprite("mob")));
	map1->addMobile(EntityBug::getInstance(390, 380, 8, Assets::getSprite("mob")));
	map1->addMobile(EntityBug::getInstance(450, 480, 8, Assets::getSprite("mob")));
	map1->addMobile(EntityBug::getInstance(480, 590, 8, Assets::getSprite("mob")));
	map1->addMobile(EntityBug::getInstance(540, 400, 8, Assets::getSprite("mob")));
	map1->addMobile(EntityBug::getInstance(590, 530, 8, Assets::getSprite("mob")));
	map1->addMobile(EntityBug::getInstance(570, 420, 8, Assets::getSprite("mob")));
	map1->addMobile(EntityBug::getInstance(420, 410, 8, Assets::getSprite("mob")));
	map1->addMobile(EntityBug::getInstance(380, 550, 8, Assets::getSprite("mob")));
	map1->addMobile(EntityBug::getInstance(560, 520, 8, Assets::getSprite("mob")));
	map1->addMobile(EntityBug::getInstance(530, 390, 8, Assets::getSprite("mob")));

	map2->addMobile(EntityBug::getInstance(360, 320, 8, Assets::getSprite("mob32"), 120));
	map2->addMobile(EntityBug::getInstance(390, 270, 8, Assets::getSprite("mob32"), 120));
	map2->addMobile(EntityBug::getInstance(420, 290, 8, Assets::getSprite("mob32"), 120));
	map2->addMobile(EntityBug::getInstance(430, 340, 8, Assets::getSprite("mob32"), 120));
	map2->addMobile(EntityBug::getInstance(400, 310, 8, Assets::getSprite("mob32"), 120));

	map1->addLoot(EntityLoot::getInstance(60, 420, 8, Assets::getSprite("loot_gun"), 360000, WeaponGun::getInstance("Hand gun", Assets::getSprite("loot_gun"))));

	map1->addPortal(Portal::getInstance(900, 400, 35, Assets::getSprite("portal"), "dungeon"));
	map2->addPortal(Portal::getInstance(40, 300, 35, Assets::getSprite("portal"), "meadow"));

	game.addLevel(map1);	// First level added will be the starting level unless another level is set as active.
	game.addLevel(map2);

	game.addPlayer(EntityHuman::getInstance(200, 200, 25, Assets::getSprite("player")));

	//game.setFPS(0);

	game.run();

	return 0;
}

