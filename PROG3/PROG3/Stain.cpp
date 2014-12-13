#include "Stain.h"
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <iostream>

namespace stain{
	Stain::Stain() : hWnd(nullptr), hRndr(nullptr), WINDOW_TITLE("Window"), WINDOW_WIDTH(640), WINDOW_HEIGHT(480){

	}

	Stain::~Stain(){
		for each (Stain_IMG img in images){
			SDL_DestroyTexture(img.hTexture);
		}
		SDL_DestroyRenderer(hRndr);
		SDL_DestroyWindow(hWnd);
		SDL_Quit();
	}

	bool Stain::init(std::string newTitle = "Window", int newWidth = 640, int newHeight = 480){
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
			std::cout << "[SEVERE] Failed to initialize SDL. " << SDL_GetError();
			return false;
		}

		WINDOW_TITLE = newTitle;
		WINDOW_WIDTH = newWidth;
		WINDOW_HEIGHT = newHeight;

		hWnd = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		if (hWnd == nullptr) {
			std::cout << "[SEVERE] Failed to create window. " << SDL_GetError();
			return false;
		}

		hRndr = SDL_CreateRenderer(hWnd, 0, SDL_RENDERER_ACCELERATED);
		if (hRndr == nullptr){
			std::cout << "[SEVERE] Failed to create accelerated renderer. " << SDL_GetError();
			return false;
		}

		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
			std::cout << "[SEVERE] Failed to initialize PNG image loading. " << IMG_GetError();
			return false;
		}
		return true;
	}

	bool Stain::loadImage(std::string filePath, std::string handleName){
		SDL_Texture* newTexture = nullptr;
		SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());
		if (loadedSurface == nullptr){
			std::cout << "[WARNING] Cannot load image (" << filePath << "). " << IMG_GetError();
			return false;
		}
		else{
			newTexture = SDL_CreateTextureFromSurface(hRndr, loadedSurface);
			if (newTexture == nullptr) {
				std::cout << "[WARNING] Unable to create texture from image (" << filePath << "). " << SDL_GetError();
				return false;
			}
			SDL_FreeSurface(loadedSurface);

			Stain_IMG imgObj = { newTexture, handleName };
			images.push_back(imgObj);

			return true;
		}
	}

	void Stain::showOverlay(std::string handle){
		SDL_Texture* img = getTextureFromHandle(handle);
		if (img != nullptr){
			SDL_RenderCopy(hRndr, img, nullptr, nullptr);
			SDL_RenderPresent(hRndr);
		}
	}

	SDL_Texture* Stain::getTextureFromHandle(std::string handle){
		for each (Stain_IMG img in images){
			if (img.handle == handle)
				return img.hTexture;
		}
		return nullptr;
	}
}