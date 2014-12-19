#ifndef ENTITYPROJECTILEBULLET_H
#define ENTITYPROJECTILEBULLET_H

#include "EntityProjectile.h"

namespace stain{
	class EntityProjectileBullet : public EntityProjectile{
	public:
		static EntityProjectileBullet* getInstance(double x, double y, double angle);
		~EntityProjectileBullet();

		void tick(std::vector<Entity*> interactors);
	private:
		EntityProjectileBullet(double x, double y, double angle);

		void AI(std::vector<Entity*> interactors);
	};
}
#endif