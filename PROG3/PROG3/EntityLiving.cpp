#include "EntityLiving.h"

namespace stain{
	EntityLiving::EntityLiving(double x, double y, int size, Sprite* sprite, double health, double speed, double angle) :
		Entity(x, y, size, sprite),
		health(health),
		healthMax(health),
		speed(speed),
		angle(angle),
		doSyncAngles(false)
	{}

	EntityLiving::~EntityLiving(){

	}

	double EntityLiving::getHealth(){
		return health;
	}

	double EntityLiving::getHealthMax(){
		return healthMax;
	}

	void EntityLiving::setAngle(double angle){
		this->angle = angle;
		if (doSyncAngles)
			sprite->setAngle(angle * 180 / M_PI - 90); /* Convert radians to degrees */ //TODO: the "-90" is specific to the image because it's looking up/north; handle this!
	}

	bool EntityLiving::isMoving(){
		return _isMoving;
	}

	void EntityLiving::syncVisualAngle(bool synchronize){
		doSyncAngles = synchronize;
		if (synchronize)
			sprite->setAngle(angle * 180 / M_PI - 90);
	}

	void EntityLiving::tick(std::vector<Entity*> interactors){
		/* Execute sub-class AI and do movement. */
		unsigned int deltaTime = SDL_GetTicks() - lastTick;

		AI();

		if (_isMoving){
			double magnitude = (deltaTime / 1000.0) * speed;
			move(SDL_cos(angle) * magnitude, SDL_sin(angle) * magnitude);
		}

		lastTick = SDL_GetTicks();
	}
}