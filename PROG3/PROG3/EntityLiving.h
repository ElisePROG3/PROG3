#ifndef ENTITYLIVING_H
#define ENTITYLIVING_H

#include "Entity.h"

namespace stain{
	class EntityLiving : public Entity{
	public:
		virtual ~EntityLiving();
		double getHealth();
		double getHealthMax();
		void setAngle(double angleRadians);
		void tick(std::vector<Entity*> interactors);
		bool isMoving();
		void syncVisualAngle(bool synchronize);
	protected:
		EntityLiving(double x, double y, int size, Sprite* sprite, double health = 5, double speed = 25, double angle = 6);

		double health, healthMax;
		double angle;
		double speed;
		bool _isMoving;
		bool doSyncAngles;

		virtual void AI() = 0;
	};
}
#endif