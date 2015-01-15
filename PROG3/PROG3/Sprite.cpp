#include "Sprite.h"

namespace stain{
	Sprite::Sprite(std::string name, SDL_Texture* texture, FACING face, int frameSize, int animTime) :
		name(name),
		hTexture(texture),
		frameSize(frameSize),
		animTime(animTime),
		angle(0.0),
		frameCount(1),
		isAnimating(false),
		startTime(SDL_GetTicks()),
		angleAdjust(0.0)
	{
		/*
		*	Animated frames are assumed to be square, frameSize is both width and height of the frame.
		*	If the image is not animated it doesn't need to be square.
		*	A frameSize value of zero decides that it's not animated.
		*	(frameSize is an optional argument of the constructor but it must be given, together with animTime, for animation to be relevant)
		*/
		int width;
		SDL_QueryTexture(texture, nullptr, nullptr, &width, nullptr);
		if (frameSize == 0){
			frameCount = 1;
		}else{
			frameCount = width / frameSize;
			if (frameCount < 1) frameCount = 1;
		}
		if (frameCount > 1) isAnimating = true;

		setAngleAdjust(face);
	}

	Sprite::~Sprite(){

	}

	bool Sprite::isAnimated() const {
		return isAnimating;
	}

	void Sprite::setAngle(double angleDegrees){
		angle = angleDegrees + angleAdjust;
	}

	double Sprite::getAngle() const {
		return angle;
	}

	void Sprite::setAngleAdjust(double angleDegrees){
		angleAdjust = angleDegrees;
	}

	void Sprite::setAngleAdjust(FACING face){
		switch (face){
		case FACING::EAST:
			angleAdjust = 180;
			break;
		case FACING::NORTH:
			angleAdjust = 90;
			break;
		case FACING::NORTHEAST:
			angleAdjust = 135;
			break;
		case FACING::NORTHWEST:
			angleAdjust = 45;
			break;
		case FACING::SOUTH:
			angleAdjust = 270;
			break;
		case FACING::SOUTHEAST:
			angleAdjust = 225;
			break;
		case FACING::SOUTHWEST:
			angleAdjust = 315;
			break;
		case FACING::WEST:
			angleAdjust = 0;
			break;
		default:
			angleAdjust = 0;
			break;
		}
	}

	std::string Sprite::getName() const {
		return name;
	}

	SDL_Texture* Sprite::getTexture() const {
		return hTexture;
	}

	SDL_Rect Sprite::getSourceRect() const {
		/*
		*	Returns an SDL_Rect with dimensions to the frame that should be currently displayed.
		*	If frameSize is zero then we're not animating and we should just return the dimensions to the texture.
		*/
		SDL_Rect retval;

		if (frameSize == 0){
			int w, h;
			SDL_QueryTexture(hTexture, nullptr, nullptr, &w, &h);
			
			retval.x = 0;
			retval.y = 0;
			retval.w = w;
			retval.h = h;
		}else{
			int frameNumber = ((SDL_GetTicks() - startTime) / animTime) % frameCount;
			retval.x = (isAnimating) ? frameSize * (frameNumber ) : 0;
			retval.y = 0;
			retval.w = frameSize;
			retval.h = frameSize;
		}

		return retval;
	}

	int Sprite::getWidth() const {
		/*
		*	Return the frameSize as the width, unless it's zero, then return the texture width;
		*/
		if (frameSize != 0)
			return frameSize;

		int w;
		SDL_QueryTexture(hTexture, nullptr, nullptr, &w, nullptr);

		return w;
	}

	int Sprite::getHeight() const {
		/*
		*	Return the frameSize as the height, unless it's zero, then return the texture height;
		*/
		if (frameSize != 0)
			return frameSize;

		int h;
		SDL_QueryTexture(hTexture, nullptr, nullptr, nullptr, &h);

		return h;
	}

	void Sprite::stopAnimation(){
		isAnimating = false;
	}

	void Sprite::startAnimation(){
		startTime = SDL_GetTicks();
		isAnimating = true;
	}
}