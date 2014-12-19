#ifndef ENTITYLIVING_H
#define ENTITYLIVING_H

#include "Entity.h"
#include "Inventory.h"

namespace stain{
	class EntityLiving : public Entity{
	public:
		virtual ~EntityLiving();

		double getHealth();
		double getHealthMax();
		void setAngle(double angleRadians);
		double getAngle();
		void tick(std::vector<Entity*> interactors);
		bool isMoving();
		void syncVisualAngle(bool synchronize);
		double hurt(double amount);
		double heal(double amount);

		Inventory* inventory;
	protected:
		EntityLiving(double x, double y, int size, Sprite* sprite, double health = 5, double speed = 25, double angle = 6);

		double health, healthMax;
		double angle;
		double speed;
		bool _isMoving;
		bool doSyncAngles;

		virtual void AI(std::vector<Entity*> interactors) = 0;
	};
}
#endif