#include "EntityLoot.h"
#include <string>

namespace stain{
	EntityLoot::EntityLoot(int newX, int newY, int newSize, SDL_Texture* newTexture) :Entity(newX, newY, newSize), hTexture(newTexture){
	}

	EntityLoot::~EntityLoot(){
	}

	EntityLoot* EntityLoot::getInstance(int x, int y, int size, SDL_Texture* texture){
		return new EntityLoot(x, y, size, texture);
	}

	void EntityLoot::tick(){

	}
	void EntityLoot::draw(){

	}
}