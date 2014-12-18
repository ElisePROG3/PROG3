#include "MapLevel.h"

namespace stain{
	MapLevel::MapLevel(std::string newName, SDL_Texture* newPlayfield) :name(newName), playfield(newPlayfield){
	}

	MapLevel::~MapLevel(){
	}

	void MapLevel::setViewport(int x, int y, int w, int h){
		viewport.x = x;
		viewport.y = y;
		viewport.w = w;
		viewport.h = h;
	}

	SDL_Rect* MapLevel::getViewport(){
		return &viewport;
	}

	SDL_Texture* MapLevel::getTexture(){
		return playfield;
	}

	std::string MapLevel::getName(){
		return name;
	}

	void MapLevel::focusEntity(Entity* entity){
		viewport.x = entity->getX() - viewport.w / 2;
		viewport.y = entity->getY() - viewport.h / 2;

		//
	}

	void MapLevel::addMobile(Entity* mob){
		if (mob != nullptr)
			mobiles.push_back(mob);
	}

	std::vector<Entity*> MapLevel::getMobiles(){
		return mobiles;
	}
}