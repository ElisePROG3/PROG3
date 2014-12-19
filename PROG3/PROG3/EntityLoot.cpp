#include "EntityLoot.h"
#include "EntityHuman.h"
#include <string>

namespace stain{
	EntityLoot::EntityLoot(int x, int y, int size, Sprite* sprite, int timeToLive, InventoryItem* lootItem) :
		Entity(x, y, size, sprite),
		timeToLive(timeToLive),
		startTime(SDL_GetTicks())
	{
		if (lootItem != nullptr)
			loot.push_back(lootItem);
	}

	EntityLoot::~EntityLoot(){
	}

	EntityLoot* EntityLoot::getInstance(int x, int y, int size, Sprite* sprite, int timeToLive, InventoryItem* lootItem){
		return new EntityLoot(x, y, size, sprite, timeToLive, lootItem);
	}

	void EntityLoot::tick(std::vector<Entity*> interactors){
		if (dead) return;
		if (SDL_GetTicks() > startTime + timeToLive){
			die();
			return;
		}

		for each (EntityHuman* player in interactors){
			if (typeid(*player) == typeid(EntityHuman)){
				if (collides(player)){
					for each (InventoryItem* item in loot){
						player->inventory->addItem(item);
					}
					die();
					break;
				}
			}
		}
	}

	void EntityLoot::addLootItem(InventoryItem* item){
		if (item != nullptr)
			loot.push_back(item);
	}

	std::vector<InventoryItem*> EntityLoot::getLootItems(){
		return loot;
	}
}