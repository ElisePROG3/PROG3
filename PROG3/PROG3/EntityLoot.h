#ifndef ENTITYLOOT_H
#define ENTITYLOOT_H

#include "Entity.h"

namespace stain{
	class EntityLoot : public Entity {
	public:
		static EntityLoot* getInstance(int x, int y, int size, Sprite* sprite, int timeToLive = 20000);
		void tick(std::vector<Entity*> interactors);
		~EntityLoot();
	private:
		EntityLoot(int x, int y, int size, Sprite* sprite, int timeToLive);
		int timeToLive;
	};
}
#endif