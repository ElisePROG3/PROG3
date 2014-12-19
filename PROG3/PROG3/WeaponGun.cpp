#include "WeaponGun.h"
#include "EntityProjectileBullet.h"

namespace stain{
	WeaponGun::WeaponGun(std::string name, Sprite* sprite):
		Weapon(name, sprite)
	{
		fireRateTime = 100;
		magazineSize = 6;
		autoFire = 1;
		ammoCount = 999;	// temp for testing
	}

	WeaponGun::~WeaponGun()
	{

	}

	WeaponGun* WeaponGun::getInstance(std::string name, Sprite* sprite){
		return new WeaponGun(name, sprite);
	}

	EntityProjectile* WeaponGun::fire(double x, double y, double angle){
		/* Check if fire rate and ammo is ok. */
		if (ammoCount <= 0 || SDL_GetTicks() - lastFireTime < fireRateTime)
			return nullptr;

		EntityProjectile* newProjectile = EntityProjectileBullet::getInstance(x, y, angle);

		ammoCount--;
		lastFireTime = SDL_GetTicks();

		return newProjectile;
	}
}