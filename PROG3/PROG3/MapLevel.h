#ifndef MAPLEVEL_H
#define MAPLEVEL_H

#include <vector>
#include "SDL.h"
#include "Entity.h"
#include "EntityLoot.h"
#include "Portal.h"

namespace stain{
	class MapLevel
	{
	public:
		static MapLevel* getInstance(std::string name, SDL_Texture* playfield);
		~MapLevel();
		void focusEntity(Entity* entity, bool center = false);
		void setViewport(int x, int y, int w, int h);
		SDL_Texture* getTexture() const;
		SDL_Rect* getViewport();
		void addMobile(Entity* mob);
		void removeMobile(Entity* mob);
		void addLoot(EntityLoot* loot);
		void removeLoot(EntityLoot* loot);
		void addPortal(Portal* portal);
		void removePortal(Portal* portal);
		std::vector<Entity*> getMobiles() const;
		std::vector<EntityLoot*> getLoot() const;
		std::vector<Portal*> getPortals() const;
		std::string getName() const;
		SDL_Point getMapOffset() const;
		void purgeDeadEntities();
	private:
		MapLevel(std::string name, SDL_Texture* playfield);
		SDL_Texture* playfield;
		SDL_Rect viewport;
		std::vector<Entity*> mobiles;
		std::vector<EntityLoot*> loots;
		std::vector<Portal*> portals;
		std::string name;
	};
}

#endif