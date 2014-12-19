#ifndef MAPLEVEL_H
#define MAPLEVEL_H

#include <vector>
#include "SDL.h"
#include "Entity.h"
#include "EntityLoot.h"

namespace stain{
	class MapLevel
	{
	public:
		static MapLevel* getInstance(std::string name, SDL_Texture* playfield);
		~MapLevel();
		void focusEntity(Entity* entity, bool center = false);
		void setViewport(int x, int y, int w, int h);
		SDL_Texture* getTexture();
		SDL_Rect* getViewport();
		void addMobile(Entity* mob);
		void removeMobile(Entity* mob);
		void addLoot(EntityLoot* loot);
		void removeLoot(EntityLoot* loot);
		std::vector<Entity*> getMobiles();
		std::vector<EntityLoot*> getLoot();
		std::string getName();
		SDL_Point getMapOffset();
		void purgeDeadEntities();
	private:
		MapLevel(std::string name, SDL_Texture* playfield);
		SDL_Texture* playfield;
		SDL_Rect viewport;
		std::vector<Entity*> mobiles;
		std::vector<EntityLoot*> loots;
		std::string name;
	};
}

#endif