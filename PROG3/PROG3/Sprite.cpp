#include "Sprite.h"
#include <iostream>//debug
namespace stain{
	Sprite::Sprite(std::string newName, SDL_Texture* newTexture, int newFrameSize, int newAnimTime) :
		name(newName),
		hTexture(newTexture),
		frameSize(newFrameSize),
		animTime(newAnimTime),
		angle(0.0),
		frameCount(1),
		isAnimating(false)
	{
		startTime = SDL_GetTicks();
		int width;
		SDL_QueryTexture(newTexture, nullptr, nullptr, &width, nullptr);
		if (newFrameSize == 0){
			frameCount = 1;
		}else{
			frameCount = width / newFrameSize;
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

	SDL_Rect* Sprite::getSourceRect(){
		SDL_Rect* retval = new SDL_Rect();

		if (frameSize == 0){
			int w, h;
			SDL_QueryTexture(hTexture, nullptr, nullptr, &w, &h);
			
			retval->x = 0;
			retval->y = 0;
			retval->w = w;
			retval->h = h;
		}else{
			int frameNumber = (SDL_GetTicks() % animTime) % frameCount;
		std::cout << SDL_GetTicks() % animTime << std::endl;
			retval->x = (isAnimating) ? frameSize * (frameNumber ) : 0;
			retval->y = 0;
			retval->w = frameSize;
			retval->h = frameSize;
		}

		return retval;
	}

	int Sprite::getWidth(){
		if (frameSize != 0)
			return frameSize;

		int w;
		SDL_QueryTexture(hTexture, nullptr, nullptr, &w, nullptr);

		return w;
	}

	int Sprite::getHeight(){
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