#include "Weapon.h"

namespace stain{
	Weapon::Weapon(std::string name, Sprite* sprite):
		fireRateTime(0),
		lastFireTime(0),
		autoFire(1),
		magazineSize(1),
		ammoCount(0),
		name(name),
		sprite(sprite)
	{

	}

	Weapon::~Weapon(){

	}

	int Weapon::getAmmoCount(){
		return ammoCount;
	}

	void Weapon::reload(){
		int reloadTime = 400; /* Time in mills to reload the weapon */

		lastFireTime = SDL_GetTicks() + reloadTime;
		ammoCount = magazineSize;
	}
}