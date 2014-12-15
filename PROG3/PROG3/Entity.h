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
		void setPos(SDL_Point* newPos);
		void move(int deltaX, int deltaY);
		void move(SDL_Point* deltaPoint);
		bool collides(Entity* entity);
		SDL_Texture* getTexture();
		virtual void tick()=0;
		virtual ~Entity();
	protected:
		int x;
		int y;
		int size;
		bool updated;
		SDL_Texture* hTexture;

		Entity(int x, int y, int size, SDL_Texture* texture = nullptr);
		Entity(const Entity&);
		const Entity& operator=(const Entity&);
	};
}
#endif