#ifndef WEAPONGUN_H
#define WEAPONGUN_H

#include "Weapon.h"

namespace stain{
	class WeaponGun : public Weapon{
	public:
		static WeaponGun* getInstance(std::string name, Sprite* sprite);
		~WeaponGun();
		EntityProjectile* fire(double x, double y, double angle);
	private:
		WeaponGun(std::string name, Sprite* sprite);
	};
}
#endif