#include "Entity.h"

namespace stain{
	Entity::Entity(int startX, int startY, int startSize, SDL_Texture* newTexture) : x(startX), y(startY), size(startSize), updated(true), hTexture(newTexture){

	}

	Entity::~Entity(){

	}

	// Getters & Setters
	int Entity::getSize(){ return size; }
	void Entity::setSize(int newSize){ size = newSize; updated = true; }
	int Entity::getX(){ return x; }
	int Entity::getY(){ return y; }
	void Entity::setX(int newX){ x = newX; updated = true; }
	void Entity::setY(int newY){ y = newY; updated = true; }
	SDL_Point Entity::getPos(){ return SDL_Point{x, y}; }
	void Entity::setPos(SDL_Point* newPos){ x = newPos->x; y = newPos->y; updated = true; }
	void Entity::move(int deltaX, int deltaY){ x += deltaX; y += deltaY; updated = true; }
	void Entity::move(SDL_Point* deltaPoint){ x += deltaPoint->x; y += deltaPoint->y; updated = true; }
	SDL_Texture* Entity::getTexture(){ return hTexture; }

	// Basic functionality
	bool Entity::collides(Entity* entity){
		int a = entity->getX() - x;
		int b = entity->getY() - y;

		double distance = SDL_sqrt(a*a + b*b);

		if (distance < (entity->getSize() + size)){
			return true;
		}

		return false;
	}
}