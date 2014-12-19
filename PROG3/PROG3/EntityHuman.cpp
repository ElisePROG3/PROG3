#include "EntityHuman.h"

namespace stain{
	EntityHuman::EntityHuman(double x, double y, int size, Sprite* sprite, double health, double speed, double angle) :
		EntityLiving(x, y, size, sprite, health, speed, angle),
		connectType(CONNECTION::LOCAL) /* For future use for multi-player */
	{
		this->sprite->stopAnimation();
	}

	EntityHuman::~EntityHuman(){

	}

	EntityHuman* EntityHuman::getInstance(double x, double y, int size, Sprite* sprite, double health, double speed, double angle){
		return new EntityHuman(x, y, size, sprite, health, speed, angle);
	}

	void EntityHuman::tick(std::vector<Entity*> interactors){
		if (dead) return;
		EntityLiving::tick(interactors);

	}

	void EntityHuman::AI(std::vector<Entity*> interactors){
		/* This could be used for debuffs like panic or confusion. */
	}

	void EntityHuman::startMoving(){
		_isMoving = true;
		sprite->startAnimation();
	}

	void EntityHuman::stopMoving(){
		_isMoving = false;
		sprite->stopAnimation();
	}

	EntityHuman::CONNECTION EntityHuman::getNetworkConnectStatus(){
		return connectType;
	}
}