#ifndef ENTITYHUMAN_H
#define ENTITYHUMAN_H

#include "EntityLiving.h"
#include "Sprite.h"

namespace stain{
	class EntityHuman : public EntityLiving{
	public:
		static EntityHuman* getInstance(double x, double y, int size, Sprite* sprite, double health = 80, double speed = 250, double angle = 3);
		~EntityHuman();
		void tick(std::vector<Entity*> interactors);
		void startMoving();
		void stopMoving();
		
		enum class CONNECTION{
			LOCAL,
			REMOTE
		};

		CONNECTION getNetworkConnectStatus();
	private:
		EntityHuman(double x, double y, int size, Sprite* sprite, double health, double speed, double angle);

		CONNECTION connectType;

		void AI(std::vector<Entity*> interactors);
	};
}
#endif