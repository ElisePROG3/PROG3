#include "Assets.h"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

namespace stain{
	std::vector<Sprite*> Assets::images;
	SDL_Renderer* Assets::hRndr = nullptr;

	void Assets::deleteAssets(){
		/* Destroy resources. */
		for each (Sprite* sprite in images){
			SDL_DestroyTexture(sprite->getTexture());
			delete (sprite);
		}
	}

	void Assets::setRenderer(SDL_Renderer* renderer){
		hRndr = renderer;
	}

	bool Assets::loadImage(std::string handleName, std::string filePath, Sprite::FACING face, int frameSize, int animTime){
		/*
		*	Load an image from file, toss it into a Sprite class together with some meta-data and put the lot in a list.
		*/
		if (hRndr == nullptr){
			std::cout << "[SEVERE] Renderer is not set up, cannot create textures!";
			return false;
		}

		SDL_Texture* newTexture = nullptr;
		SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());
		if (loadedSurface == nullptr){
			std::cout << "[WARNING] Cannot load image (" << filePath << "). " << IMG_GetError();
			return false;
		}else{
			newTexture = SDL_CreateTextureFromSurface(hRndr, loadedSurface);
			if (newTexture == nullptr) {
				std::cout << "[WARNING] Unable to create texture from image (" << filePath << "). " << SDL_GetError();
				return false;
			}
			SDL_FreeSurface(loadedSurface);

			Sprite* sprite = new Sprite(handleName, newTexture, face, frameSize, animTime);
			images.push_back(sprite);

			return true;
		}
	}

	SDL_Texture* Assets::getTexture(std::string handle){
		/*
		*	Iterates through the list of sprites and mathches handle to sprite name.
		*	The texture of the sprite is returned when a match is found.
		*/
		for each (Sprite* sprite in images){
			if (sprite->getName() == handle)
				return sprite->getTexture();
		}
		return nullptr;
	}

	Sprite* Assets::getSprite(std::string handle){
		/*
		*	Iterates through the list of sprites, matching handle to sprite name.
		*	The sprite is returned when a match is found.
		*/
		for each (Sprite* sprite in images){
			if (sprite->getName() == handle)
				return sprite;
		}
		return nullptr;
	}
}