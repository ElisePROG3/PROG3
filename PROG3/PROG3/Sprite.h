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
		double getAngle() const;
		SDL_Rect getSourceRect() const;
		int getWidth() const;
		int getHeight() const;
		SDL_Texture* getTexture() const;
		void stopAnimation();
		void startAnimation();
		bool isAnimated() const;
		std::string getName() const;
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