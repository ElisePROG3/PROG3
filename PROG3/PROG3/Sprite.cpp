#include "Sprite.h"

namespace stain{
	Sprite::Sprite(std::string name, SDL_Texture* texture, int frameSize, int animTime) :
		name(name),
		hTexture(texture),
		frameSize(frameSize),
		animTime(animTime),
		angle(0.0),
		frameCount(1),
		isAnimating(false),
		startTime(SDL_GetTicks())
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
	}

	Sprite::~Sprite(){

	}

	bool Sprite::isAnimated(){
		return isAnimating;
	}

	void Sprite::setAngle(double inAngle){
		angle = inAngle;
	}

	double Sprite::getAngle(){
		return angle;
	}

	std::string Sprite::getName(){
		return name;
	}

	SDL_Texture* Sprite::getTexture(){
		return hTexture;
	}

	SDL_Rect Sprite::getSourceRect(){
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

	int Sprite::getWidth(){
		/*
		*	Return the frameSize as the width, unless it's zero, then return the texture width;
		*/
		if (frameSize != 0)
			return frameSize;

		int w;
		SDL_QueryTexture(hTexture, nullptr, nullptr, &w, nullptr);

		return w;
	}

	int Sprite::getHeight(){
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