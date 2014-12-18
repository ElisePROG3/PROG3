#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include "Sprite.h"

namespace stain{
	class Entity{
	public:
		int getSize();
		void setSize(int newSize);
		double getX();
		double getY();
		void setX(double newX);
		void setY(double newY);
		void move(double deltaX, double deltaY);
		bool collides(Entity* entity);
		Sprite* getSprite();
		virtual void tick()=0;
		virtual ~Entity();
	protected:
		double x;
		double y;
		int size;
		unsigned int lastTick;
		Sprite* sprite;

		Entity(double x, double y, int size, Sprite* sprite = nullptr);
		Entity(const Entity&);
		const Entity& operator=(const Entity&);
	};
}
#endif