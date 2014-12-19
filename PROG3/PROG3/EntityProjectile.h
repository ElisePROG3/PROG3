#ifndef ENTITYPROJECTILE_H
#define ENTITYPROJECTILE_H

#include "EntityLiving.h"

namespace stain{
	class EntityProjectile : public EntityLiving{
	public:
		void tick(std::vector<Entity*> interactors);
		~EntityProjectile();
	private:
		EntityProjectile(int x, int y, int size, Sprite* sprite, double health, double speed, double angle);
	};
}
#endif