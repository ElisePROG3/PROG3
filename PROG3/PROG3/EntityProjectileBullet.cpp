#include "EntityProjectileBullet.h"
#include "EntityLiving.h"

namespace stain{
	EntityProjectileBullet::EntityProjectileBullet(double x, double y, double angle) :
		EntityProjectile(x, y, 4, sprite, 400, angle)
	{
		//sprite = Stain.getSpprite("bullet");	// fix this. maybe add static ResourceLoader ?
		damage = 10;
	}

	EntityProjectileBullet::~EntityProjectileBullet(){

	}

	EntityProjectileBullet* EntityProjectileBullet::getInstance(double x, double y, double angle){
		return new EntityProjectileBullet(x, y, angle);
	}

	void EntityProjectileBullet::tick(std::vector<Entity*> interactors){
		if (dead) return;
		EntityProjectile::tick(interactors);

		for each (EntityLiving* interactor in interactors){
			if (collides(interactor)){
				interactor->hurt(damage);
				die();
				break;
			}
		}
	}

	void EntityProjectileBullet::AI(std::vector<Entity*> interactors){
		/* This could be used for heat seeking missiles etc. */
	}
}