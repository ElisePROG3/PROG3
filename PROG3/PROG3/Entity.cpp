#include "Entity.h"

namespace stain{
	Entity::Entity(double x, double y, int size, Sprite* sprite) : 
		x(x), 
		y(y), 
		size(size), 
		lastTick(SDL_GetTicks()),
		dead(false)
	{
		if (sprite != nullptr){
			this->sprite = new Sprite(*sprite);
		}else{
			this->sprite = nullptr;
		}
	}

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
	bool Entity::isDead(){ return dead; }
	void Entity::die(){ dead = true; }

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
		Sprite* sprite = getSprite();

		if (sprite != nullptr){
			SDL_Rect src = sprite->getSourceRect();
			SDL_Rect dst = { (int)(getX() - sprite->getWidth() / 2) - offset.x, (int)(getY() - sprite->getHeight() / 2) - offset.y, sprite->getWidth(), sprite->getHeight() };
			SDL_RenderCopyEx(hRenderer, sprite->getTexture(), &src, &dst, sprite->getAngle(), nullptr, SDL_FLIP_NONE);
		}else{
			// Draw default texture ?
		}
	}
}