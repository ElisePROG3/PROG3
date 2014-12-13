#ifndef ENTITYLOOT_H
#define ENTITYLOOT_H

#include <string>
#include "Entity.h"

namespace stain{
	class EntityLoot : public Entity {
	public:
		static EntityLoot* getInstance(int x, int y, int size, SDL_Texture* texture);
		void tick();
		~EntityLoot();
	private:
		SDL_Texture* hTexture;
		EntityLoot(int x, int y, int size, SDL_Texture* texture);
		void draw();
	};
}
#endif