#ifndef MAPLEVEL_H
#define MAPLEVEL_H

#include <vector>
#include "SDL.h"
#include "Entity.h"

namespace stain{
	class MapLevel
	{
	public:
		MapLevel(std::string name, SDL_Texture* playfield);
		~MapLevel();
		void focusEntity(Entity* entity);
		void setViewport(int x, int y, int w, int h);
		SDL_Texture* getTexture();
		SDL_Rect* getViewport();
		void addMobile(Entity* mob);
		std::vector<Entity*> getMobiles();
		std::string getName();
	private:
		SDL_Texture* playfield;
		SDL_Rect viewport;
		std::vector<Entity*> mobiles;
		std::string name;
	};
}

#endif