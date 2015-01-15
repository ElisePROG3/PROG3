#include "EntityLiving.h"

namespace stain{
	EntityLiving::EntityLiving(double x, double y, int size, Sprite* sprite, double health, double speed, double angle) :
		Entity(x, y, size, sprite),
		health(health),
		healthMax(health),
		speed(speed),
		angle(angle),
		doSyncAngles(false),
		_isMoving(false),
		inventory(Inventory::getInstance())
	{}

	EntityLiving::~EntityLiving(){
		delete(inventory);
	}

	double EntityLiving::getHealth() const {
		return health;
	}

	double EntityLiving::getHealthMax() const {
		return healthMax;
	}

	void EntityLiving::setAngle(double angle){
		this->angle = angle;
		if (doSyncAngles)
			sprite->setAngle(angle * 180 / M_PI); /* Convert radians to degrees */
	}

	double EntityLiving::getAngle() const {
		return angle;
	}

	bool EntityLiving::isMoving() const {
		return _isMoving;
	}

	void EntityLiving::syncVisualAngle(bool synchronize){
		/*
		*	Makes it so that the angle of the sprite (visual angle) matches the angle the entity is facing.
		*/
		doSyncAngles = synchronize;
		if (synchronize)
			sprite->setAngle(angle * 180 / M_PI);
	}

	void EntityLiving::tick(std::vector<Entity*> interactors){
		if (dead) return;
		/* Execute sub-class AI and do movement. */
		unsigned int deltaTime = SDL_GetTicks() - lastTick;

		AI(interactors);

		if (_isMoving){
			double magnitude = (deltaTime / 1000.0) * speed;
			move(SDL_cos(angle) * magnitude, SDL_sin(angle) * magnitude);
		}

		lastTick = SDL_GetTicks();
	}

	double EntityLiving::hurt(double amount){
		health -= amount;
		if (health < 0) health = 0;
		if (health > healthMax) health = healthMax;

		if (health == 0){
			die();
			// effect? sound?
		}else{
			// effect? sound?
		}

		return health;
	}

	double EntityLiving::heal(double amount){
		health += amount;
		if (health < 0) health = 0;
		if (health > healthMax) health = healthMax;

		// do stuff? sound?

		return health;
	}
}