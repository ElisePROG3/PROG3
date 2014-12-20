#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "SDL.h"

namespace stain{
	class Obstacle
	{
	public:
		~Obstacle();

		SDL_Rect* getBoundary();
	private:
		Obstacle();

		SDL_Rect* boundary;
	};
}
#endif