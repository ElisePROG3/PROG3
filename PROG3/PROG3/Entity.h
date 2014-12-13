#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>

namespace stain{
	class Entity{
	public:
		int getSize();
		void setSize(int newSize);
		int getX();
		int getY();
		void setX(int newX);
		void setY(int newY);
		SDL_Point getPos();
		void setPos(SDL_Point newPos);
		void move(int deltaX, int deltaY);
		void move(SDL_Point deltaPoint);
		virtual void tick()=0;
		virtual ~Entity();
	protected:
		int x;
		int y;
		int size;
		bool updated;

		Entity(int x, int y, int size);
		Entity(const Entity&);
		const Entity& operator=(const Entity&);

		virtual void draw()=0;
	};
}
#endif