#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include "SDL.h"

namespace stain{
	class Sprite
	{
	public:
		Sprite(std::string name, SDL_Texture* texture, int frameSize = 0, int animTime = 0);
		~Sprite();
		void setAngle(double angle);
		double getAngle();
		SDL_Rect* getSourceRect();
		int getWidth();
		int getHeight();
		SDL_Texture* getTexture();
		void stopAnimation();
		void startAnimation();
		bool isAnimated();
		std::string getName();
	private:
		double angle;
		int frameSize;
		int frameCount;
		int animTime;
		int startTime;
		std::string name;
		SDL_Texture* hTexture;
		bool isAnimating;
	};
}
#endif