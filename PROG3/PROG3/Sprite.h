#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include "SDL.h"

namespace stain{
	class Sprite
	{
	public:
		~Sprite();
		void setAngle(double angleDegrees);
		double getAngle();
		SDL_Rect getSourceRect();
		int getWidth();
		int getHeight();
		SDL_Texture* getTexture();
		void stopAnimation();
		void startAnimation();
		bool isAnimated();
		std::string getName();
		void setAngleAdjust(double angleDegrees);

		enum class FACING{
			NONE,
			NORTH,
			SOUTH,
			EAST,
			WEST,
			NORTHEAST,
			NORTHWEST,
			SOUTHEAST,
			SOUTHWEST
		};

		void setAngleAdjust(FACING face);
		Sprite(std::string name, SDL_Texture* texture, FACING face = FACING::NONE, int frameSize = 0, int animTime = 0);
	private:
		double angle;
		double angleAdjust;	/* Characters in sprites can face different directions, use this to adjust the angle accordingly */
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