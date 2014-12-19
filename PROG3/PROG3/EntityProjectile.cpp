#include "EntityProjectile.h"

namespace stain{
	EntityProjectile::EntityProjectile(int x, int y, int size, Sprite* sprite, double health, double speed, double angle):
		EntityLiving(x, y, size, sprite, health, speed, angle)
	{

	}

	EntityProjectile::~EntityProjectile(){

	}

	void EntityProjectile::tick(std::vector<Entity*> interactors){
		//damage mobs
	}
}