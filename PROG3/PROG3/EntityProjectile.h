#ifndef ENTITYPROJECTILE_H
#define ENTITYPROJECTILE_H

#include "Entity.h"
#include "InventoryItem.h"

namespace stain{
	class EntityProjectile : public Entity, public InventoryItem{
	public:
		virtual void tick(std::vector<Entity*> interactors);
		void setAngle(double angleRadians);
		bool isMoving();

		virtual ~EntityProjectile();
	protected:
		EntityProjectile(double x, double y, int size, Sprite* sprite, double speed, double angle);
		
		double damage;
		double angle;
		double speed;
		bool _isMoving;

		virtual void AI(std::vector<Entity*> interactors) = 0;
	};
}
#endif