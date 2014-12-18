#include "EntityHuman.h"
#include <iostream>
#include <math.h>

namespace stain{
	EntityHuman::EntityHuman(double newX, double newY, int newSize, Sprite* sprite) :Entity(newX, newY, newSize, sprite), speed(40), angle(7.0), isWalking(false){

	}

	EntityHuman::~EntityHuman(){

	}

	EntityHuman* EntityHuman::getInstance(double x, double y, int size, Sprite* sprite){
		return new EntityHuman(x, y, size, sprite);
	}

	void EntityHuman::tick(){
		unsigned int deltaTime = SDL_GetTicks() - lastTick;
		
		AI();

		if (isWalking){
			double magnitude = (deltaTime / 1000.0) * speed;
			move(SDL_cos(angle) * magnitude, SDL_sin(angle) * magnitude);
		}

		lastTick = SDL_GetTicks();
	}

	void EntityHuman::AI(){
		// Basic wandering with semi-randomness caused by system lag.
		if (SDL_GetTicks() % 1000 == 0){
			isWalking = !isWalking;
			if (!isWalking) angle = (rand() % 10000 / 10000.0) * (2 * M_PI);
		}
	}

	void EntityHuman::setAngle(double newAngle){
		angle = newAngle;
	}
}