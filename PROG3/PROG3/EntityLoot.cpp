#include "EntityLoot.h"
#include <string>

namespace stain{
	EntityLoot::EntityLoot(int newX, int newY, int newSize, Sprite* newSprite) :Entity(newX, newY, newSize, newSprite){
	}

	EntityLoot::~EntityLoot(){
	}

	EntityLoot* EntityLoot::getInstance(int x, int y, int size, Sprite* sprite){
		return new EntityLoot(x, y, size, sprite);
	}

	void EntityLoot::tick(){

	}
}