#include "EntityBug.h"
#include <math.h>

namespace stain{
	EntityBug::EntityBug(double x, double y, int size, Sprite* sprite, double health, double speed, double angle) :
		EntityLiving(x, y, size, sprite, health, speed, angle)
	{
		syncVisualAngle(true);
	}

	EntityBug::~EntityBug(){

	}

	EntityBug* EntityBug::getInstance(double x, double y, int size, Sprite* sprite, double health, double speed, double angle){
		return new EntityBug(x, y, size, sprite, health, speed, angle);
	}

	void EntityBug::tick(std::vector<Entity*> interactors){
		EntityLiving::tick(interactors);

	}

	void EntityBug::AI(){
		// Basic wandering with semi-randomness caused by system lag.
		if (SDL_GetTicks() % 1000 == 0){
			_isMoving = !_isMoving;
			if (_isMoving) setAngle((rand() % 10000 / 10000.0) * (2 * M_PI));
		}
	}
}