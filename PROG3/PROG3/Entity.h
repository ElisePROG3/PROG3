#ifndef ENTITY_H
#define ENTITY_H

#include "SDL.h"
#include "Sprite.h"
#include <vector>

namespace stain{
	class Entity{
	public:
		int getSize() const;
		void setSize(int newSize);
		double getX() const;
		double getY() const;
		void setX(double newX);
		void setY(double newY);
		void move(double deltaX, double deltaY);
		Sprite* getSprite() const;
		bool isDead() const;
		void die();

		bool collides(Entity* entity);
		void draw(SDL_Renderer* hRenderer, SDL_Point offset);
		virtual void tick(std::vector<Entity*> interactors) = 0;
		virtual ~Entity();
	protected:
		double x;
		double y;
		int size;
		unsigned int lastTick;
		Sprite* sprite;
		bool dead;

		Entity(double x, double y, int size, Sprite* sprite = nullptr);
		//Entity(const Entity&);
		//const Entity& operator=(const Entity&);
	};
}
#endif