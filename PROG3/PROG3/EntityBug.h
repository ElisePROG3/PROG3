#ifndef ENTITYBUG_H
#define ENTITYBUG_H

#include "EntityLiving.h"
#include "Sprite.h"

namespace stain{
	class EntityBug : public EntityLiving{
	public:
		static EntityBug* getInstance(double x, double y, int size, Sprite* sprite, double health = 50, double speed = 50, double angle = 5);
		void tick(std::vector<Entity*> interactors);
		~EntityBug();
	private:
		EntityBug(double x, double y, int size, Sprite* sprite, double health, double speed, double angle);

		void AI(std::vector<Entity*> interactors);
	};
}
#endif