#ifndef ENTITYLOOT_H
#define ENTITYLOOT_H

#include "Entity.h"

namespace stain{
	class EntityHuman : public Entity
	{
	public:
		static EntityHuman* getInstance(int x, int y, int size, SDL_Texture* texture);
		void tick();
		~EntityHuman();
	private:
		EntityHuman(int x, int y, int size, SDL_Texture* texture);
		SDL_Texture* hTexture;
		void draw();
	};
}
#endif