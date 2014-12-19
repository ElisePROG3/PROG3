#include "EntityLoot.h"
#include "EntityHuman.h"
#include <string>

namespace stain{
	EntityLoot::EntityLoot(int x, int y, int size, Sprite* sprite, int timeToLive) :
		Entity(x, y, size, sprite),
		timeToLive(timeToLive)
	{}

	EntityLoot::~EntityLoot(){
	}

	EntityLoot* EntityLoot::getInstance(int x, int y, int size, Sprite* sprite, int timeToLive){
		return new EntityLoot(x, y, size, sprite, timeToLive);
	}

	void EntityLoot::tick(std::vector<Entity*> interactors){
		for each (EntityHuman* player in interactors){
			if (typeid(*player) == typeid(EntityHuman)){
				if (collides(player)){
					//player.pickup(loot);
					//die() ?
				}
			}
		}
		

		// check ttl - die()
	}
}