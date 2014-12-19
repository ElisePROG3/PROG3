#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "Sprite.h"
#include "EntityProjectile.h"
#include "InventoryItem.h"

namespace stain{
	class Weapon : public InventoryItem{
	public:
		virtual ~Weapon();
		virtual EntityProjectile* fire(double x, double y, double angle) = 0;
		int getAmmoCount();
		void reload();
	protected:
		Weapon(std::string name, Sprite* sprite);
		double fireRateTime;		/* Delay in millis between discharges */
		int lastFireTime;
		int autoFire;				/* How many rounds to auto-fire, -1 for unending auto-fire */
		int magazineSize;			/* How many rounds a magazine can contain */
		int ammoCount;
		std::string name;
		Sprite* sprite;
	};
}
#endif