#ifndef ENTITYHUMAN_H
#define ENTITYHUMAN_H

#include "Entity.h"
#include "Sprite.h"

namespace stain{
	class EntityHuman : public Entity
	{
	public:
		static EntityHuman* getInstance(double x, double y, int size, Sprite* sprite);
		void tick();
		~EntityHuman();
		void setAngle(double angle);
	private:
		EntityHuman(double x, double y, int size, Sprite* sprite);
		int speed;
		double angle;
		bool isWalking;

		void AI();
	};
}
#endif