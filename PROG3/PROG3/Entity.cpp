#include "Entity.h"

namespace stain{
	Entity::Entity(double startX, double startY, int startSize, Sprite* newSprite) : x(startX), y(startY), size(startSize), sprite(newSprite){
		lastTick = SDL_GetTicks();
	}

	Entity::~Entity(){

	}

	// Getters & Setters
	int Entity::getSize(){ return size; }
	void Entity::setSize(int newSize){ size = newSize; }
	double Entity::getX(){ return x; }
	double Entity::getY(){ return y; }
	void Entity::setX(double newX){ x = newX; }
	void Entity::setY(double newY){ y = newY; }
	void Entity::move(double deltaX, double deltaY){ x += deltaX; y += deltaY; }
	Sprite* Entity::getSprite(){
		return sprite;
	}

	// Basic functionality
	bool Entity::collides(Entity* entity){
		double a = entity->getX() - x;
		double b = entity->getY() - y;

		double distance = SDL_sqrt(a*a + b*b);

		if (distance < (entity->getSize() + size)){
			return true;
		}

		return false;
	}
}