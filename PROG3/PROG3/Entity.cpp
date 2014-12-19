#include "Entity.h"

namespace stain{
	Entity::Entity(double x, double y, int size, Sprite* sprite) : 
		x(x), 
		y(y), 
		size(size), 
		sprite(new Sprite(*sprite)),
		lastTick(SDL_GetTicks())
	{}

	Entity::~Entity(){
		delete (sprite);
	}

	/* Getters & Setters */
	int Entity::getSize(){ return size; }
	void Entity::setSize(int newSize){ size = newSize; }
	double Entity::getX(){ return x; }
	double Entity::getY(){ return y; }
	void Entity::setX(double newX){ x = newX; }
	void Entity::setY(double newY){ y = newY; }
	void Entity::move(double deltaX, double deltaY){ x += deltaX; y += deltaY; }
	Sprite* Entity::getSprite(){ return sprite; }

	/* Basic functionality */
	bool Entity::collides(Entity* entity){
		/*
		*	Checks if this collides with entity.
		*/
		double a = entity->getX() - x;
		double b = entity->getY() - y;

		double distance = SDL_sqrt(a*a + b*b);

		if (distance < (entity->getSize() + size)){
			return true;
		}

		return false;
	}

	void Entity::draw(SDL_Renderer* hRenderer, SDL_Point offset){
		SDL_Rect src = getSprite()->getSourceRect();
		SDL_Rect dst = { (int)(getX() - getSprite()->getWidth() / 2) - offset.x, (int)(getY() - getSprite()->getHeight() / 2) - offset.y, getSprite()->getWidth(), getSprite()->getHeight() };
		SDL_RenderCopyEx(hRenderer, getSprite()->getTexture(), &src, &dst, getSprite()->getAngle(), nullptr, SDL_FLIP_NONE);
	}
}