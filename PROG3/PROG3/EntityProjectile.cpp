#include "EntityProjectile.h"

namespace stain{
	EntityProjectile::EntityProjectile(double x, double y, int size, Sprite* sprite, double speed, double angle) :
		Entity(x, y, size, sprite),
		damage(1),
		speed(speed),
		angle(angle)
	{
		_isMoving = true;
	}

	EntityProjectile::~EntityProjectile(){

	}

	void EntityProjectile::setAngle(double angle){
		this->angle = angle;
		sprite->setAngle(angle * 180 / M_PI); /* Convert radians to degrees */
	}

	bool EntityProjectile::isMoving(){
		return _isMoving;
	}

	void EntityProjectile::tick(std::vector<Entity*> interactors){
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
}