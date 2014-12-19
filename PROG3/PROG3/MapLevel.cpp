#include "MapLevel.h"
#include <algorithm> // for remove_if
#include <functional>
namespace stain{
	MapLevel::MapLevel(std::string name, SDL_Texture* playfield) :name(name), playfield(playfield){
	}

	MapLevel::~MapLevel(){
		for each (Entity* mob in mobiles){
			delete(mob);
		}
	}

	MapLevel* MapLevel::getInstance(std::string name, SDL_Texture* playfield){
		return new MapLevel(name, playfield);
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

	void MapLevel::focusEntity(Entity* entity, bool center){
		/*
		*	Pans the map to focus on the location of the entity.
		*	bool center : decides if the viewport should be centered or if a more relaxed padding/leeway (offsetPadding) can be used.
		*/
		int textureWidth, textureHeight;
		int offsetPadding = 150;

		SDL_QueryTexture(playfield, nullptr, nullptr, &textureWidth, &textureHeight);

		if (center){
			viewport.x = (int)entity->getX() - viewport.w / 2;
			viewport.y = (int)entity->getY() - viewport.h / 2;

			viewport.x = viewport.x < 0 ? 0 : viewport.x;
			viewport.y = viewport.y < 0 ? 0 : viewport.y;
			viewport.x = viewport.x > textureWidth - viewport.w ? textureWidth - viewport.w : viewport.x;
			viewport.y = viewport.y > textureHeight - viewport.h ? textureHeight - viewport.h : viewport.y;
		}
		else{
			if (entity->getX() > viewport.x + viewport.w - offsetPadding){
				viewport.x = (int)entity->getX() - viewport.w + offsetPadding;
				viewport.x = viewport.x > textureWidth - viewport.w ? textureWidth - viewport.w : viewport.x;
			}
			if (entity->getX() < viewport.x + offsetPadding){
				viewport.x = (int)entity->getX() - offsetPadding;
				viewport.x = viewport.x < 0 ? 0 : viewport.x;
			}
			if (entity->getY() > viewport.y + viewport.h - offsetPadding){
				viewport.y = (int)entity->getY() - viewport.h + offsetPadding;
				viewport.y = viewport.y > textureHeight - viewport.h ? textureHeight - viewport.h : viewport.y;
			}
			if (entity->getY() < viewport.y + offsetPadding){
				viewport.y = (int)entity->getY() - offsetPadding;
				viewport.y = viewport.y < 0 ? 0 : viewport.y;
			}
		}
	}

	void MapLevel::addMobile(Entity* mob){
		if (mob != nullptr)
			mobiles.push_back(mob);
	}

	void MapLevel::removeMobile(Entity* mob){
		std::vector<Entity*>::iterator itr;
		for (itr = mobiles.begin(); itr != mobiles.end();){
			if (*itr == mob){
				itr = mobiles.erase(itr);
				delete(mob);
				break;
			}
			else
				++itr;
		}
	}

	void MapLevel::addLoot(EntityLoot* loot){
		if (loot != nullptr)
			this->loot.push_back(loot);
	}

	void MapLevel::removeLoot(EntityLoot* loot){
		
	}

	std::vector<Entity*> MapLevel::getMobiles(){
		return mobiles;
	}
	std::vector<EntityLoot*> MapLevel::getLoot(){
		return loot;
	}

	SDL_Point MapLevel::getMapOffset(){
		SDL_Point p = { viewport.x, viewport.y };
		return p;
	}
}