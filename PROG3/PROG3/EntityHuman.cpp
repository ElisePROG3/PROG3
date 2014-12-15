#include "EntityHuman.h"

namespace stain{
	EntityHuman::EntityHuman(int newX, int newY, int newSize, SDL_Texture* newTexture) :Entity(newX, newY, newSize, newTexture){

	}

	EntityHuman::~EntityHuman(){

	}

	EntityHuman* EntityHuman::getInstance(int x, int y, int size, SDL_Texture* texture){
		return new EntityHuman(x, y, size, texture);
	}

	void EntityHuman::tick(){

	}
}