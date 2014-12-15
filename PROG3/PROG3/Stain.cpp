#include "Stain.h"
#include "Entity.h"
#include "EntityHuman.h"
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <iostream>

namespace stain{
	Stain::Stain() :hWnd(nullptr), 
					hRndr(nullptr), 
					WINDOW_TITLE("Window"), 
					WINDOW_WIDTH(640), 
					WINDOW_HEIGHT(480), 
					fps(60),
					lastRenderTime(-1),
					displayOverlay(nullptr),
					overlayTime(-1)
	{}

	Stain::~Stain(){

		// Destroy resources.
		for each (Stain_IMG img in images){
			SDL_DestroyTexture(img.hTexture);
		}

		// Destroy mobiles
		for each (Entity* mob in mobiles)
		{
			delete(mob);
		}

		// Close SDL
		SDL_DestroyRenderer(hRndr);
		SDL_DestroyWindow(hWnd);
		SDL_Quit();
	}

	bool Stain::init(std::string newTitle, int newWidth, int newHeight){
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

		SDL_SetRenderDrawColor(hRndr, 0x20, 0xf5, 0xa2, 0xff);

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

	void Stain::setOverlay(std::string handle, int timeToShowMs){
		if (timeToShowMs == -1){
			overlayTime = -1;
		}
		else{
			overlayTime = SDL_GetTicks() + timeToShowMs;
		}

		SDL_Texture* img = getTextureFromHandle(handle);
		if (img != nullptr){
			displayOverlay = img;
		}
		else{
			displayOverlay = nullptr;
		}
	}

	SDL_Texture* Stain::getTextureFromHandle(std::string handle){
		for each (Stain_IMG img in images){
			if (img.handle == handle)
				return img.hTexture;
		}
		return nullptr;
	}

	void Stain::setFPS(int newFPS){
		fps = newFPS;
	}

	bool Stain::addMobile(Entity* entity){
		if (entity != nullptr){
			mobiles.push_back(entity);
			return true;
		}
		return false;
	}

	void Stain::render(){
		int deltaMS = SDL_GetTicks() - lastRenderTime;
		if (fps <= 0 || deltaMS >= 1000 / (float)fps){ // SDL_GetTicks is low resolution, FPS precision suffers.
			if (false) std::cout << "FPS: " << (deltaMS == 0 ? "Through the roof!" : std::to_string(1000 / deltaMS)) << std::endl;	// FPS Debug
			
			// Let's start with clearing the display.
			SDL_RenderClear(hRndr);

			// Let's render mobs
			for each (Entity* mob in mobiles)
			{
				int w, h;
				SDL_Texture* img = mob->getTexture();
				SDL_QueryTexture(img, NULL, NULL, &w, &h);
				SDL_Rect rect = { mob->getX(), mob->getY(), w, h };
				SDL_RenderCopy(hRndr, img, nullptr, &rect);
			}



			// Let's handle any overlays.
			if (displayOverlay != nullptr){
				SDL_RenderCopy(hRndr, displayOverlay, nullptr, nullptr);
			if (overlayTime != -1 && overlayTime - (long int)SDL_GetTicks() <= 0)
					displayOverlay = nullptr;
			}

			// Finally; present!
			SDL_RenderPresent(hRndr);
			lastRenderTime = SDL_GetTicks();
		}
	}
}