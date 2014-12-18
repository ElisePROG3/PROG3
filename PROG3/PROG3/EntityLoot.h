#ifndef ENTITYLOOT_H
#define ENTITYLOOT_H

#include <string>
#include "Entity.h"

namespace stain{
	class EntityLoot : public Entity {
	public:
		static EntityLoot* getInstance(int x, int y, int size, Sprite* sprite);
		void tick();
		~EntityLoot();
	private:
		EntityLoot(int x, int y, int size, Sprite* sprite);
	};
}
#endif