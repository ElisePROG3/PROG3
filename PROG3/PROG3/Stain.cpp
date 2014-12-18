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
					overlayTime(-1),
					player(nullptr),
					activeLevel(nullptr)
	{}

	Stain::~Stain(){

		// Destroy resources.
		for each (Sprite* sprite in images){
			SDL_DestroyTexture(sprite->getTexture());
			delete (sprite);
		}

		// Destroy maps and their mobiles
		for each (MapLevel* level in levels){
			for each (Entity* mob in level->getMobiles()){
				delete(mob);
			}
			delete(level);
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

	bool Stain::loadImage(std::string handleName, std::string filePath, int frameSize, int animTime){
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

			Sprite* sprite = new Sprite(handleName, newTexture, frameSize, animTime);
			images.push_back(sprite);

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

		SDL_Texture* img = getTexture(handle);
		if (img != nullptr){
			displayOverlay = img;
		}
		else{
			displayOverlay = nullptr;
		}
	}

	SDL_Texture* Stain::getTexture(std::string handle){
		for each (Sprite* sprite in images){
			if (sprite->getName() == handle)
				return sprite->getTexture();
		}
		return nullptr;
	}

	Sprite* Stain::getSprite(std::string handle){
		for each (Sprite* sprite in images){
			if (sprite->getName() == handle)
				return sprite;
		}
		return nullptr;
	}

	void Stain::setFPS(int newFPS){
		fps = newFPS;
	}

	void Stain::addLevel(MapLevel* level){
		if (level != nullptr){
			level->setViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			levels.push_back(level);
			if (activeLevel == nullptr)
				activeLevel = level;
		}
	}

	void Stain::render(){
		int deltaMS = SDL_GetTicks() - lastRenderTime;
		if (fps <= 0 || deltaMS >= 1000 / (float)fps){ // SDL_GetTicks is low resolution, FPS precision suffers.
			if (false) std::cout << "FPS: " << (deltaMS == 0 ? "Through the roof!" : std::to_string(1000 / deltaMS)) << std::endl;	// FPS Debug
			
			// Let's start with clearing the display.
			SDL_RenderClear(hRndr);

			// Let's render the map background of the current map
			if (activeLevel->getTexture() != nullptr)
				SDL_RenderCopy(hRndr, activeLevel->getTexture(), activeLevel->getViewport(), nullptr);

			// Let's render mobs in current map

			for each (Entity* mob in activeLevel->getMobiles()){
				SDL_Rect* src = mob->getSprite()->getSourceRect();
				SDL_Rect dst = { mob->getX(), mob->getY(), mob->getSprite()->getWidth(), mob->getSprite()->getHeight() };
				SDL_RenderCopyEx(hRndr, mob->getSprite()->getTexture(), src, &dst, mob->getSprite()->getAngle(), nullptr, SDL_FLIP_NONE);
				delete (src);
			}

			// Let's render the player
			if (player != nullptr){
				SDL_Rect* src = player->getSprite()->getSourceRect();
				SDL_Rect dst = { player->getX(), player->getY(), player->getSprite()->getWidth(), player->getSprite()->getHeight() };
				SDL_RenderCopyEx(hRndr, player->getSprite()->getTexture(), src, &dst, player->getSprite()->getAngle(), nullptr, SDL_FLIP_NONE);
				delete (src);
			}

			// Let's render obstackles in current map.



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

	void Stain::setPlayer(Entity* newPlayer){
		player = newPlayer;
	}

	void Stain::setActiveLevel(std::string levelName){
		for each (MapLevel* level in levels){
			if (level->getName() == levelName){
				activeLevel = level;
				break;
			}
		}
	}

	void Stain::run(){
		bool quit = false;
		while (!quit){
			while (SDL_PollEvent(&event) != 0){
				switch (event.type){
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym){
					case SDLK_w:
					case SDLK_UP:

						break;
					case SDLK_s:
					case SDLK_DOWN:

						break;
					case SDLK_a:
					case SDLK_LEFT:

						break;
					case SDLK_d:
					case SDLK_RIGHT:

						break;
					}

				}
			}

			//SDL_Delay(100);

			// Mobiles heartbeat
			for each (Entity* mob in activeLevel->getMobiles()){
				mob->tick();
			}

			// Render screen
			render();
		}
	}





}