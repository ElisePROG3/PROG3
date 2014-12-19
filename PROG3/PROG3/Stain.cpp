#include "Stain.h"
#include "Entity.h"
#include "EntityHuman.h"
#include "Weapon.h"
#include "WeaponGun.h"
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
		activeLevel(nullptr)
	{}

	Stain::~Stain(){

		/* Destroy resources. */
		for each (Sprite* sprite in images){
			SDL_DestroyTexture(sprite->getTexture());
			delete (sprite);
		}

		/* Destroy maps */
		for each (MapLevel* level in levels){
			delete(level);
		}

		/* Destroy projectiles */
		for each (EntityProjectile* projectile in projectiles){
			delete(projectile);
		}

		/* Delete players */
		for each (EntityLiving* player in players){
			for each (InventoryItem* item in player->inventory->getItems()){
				delete(item);
			}
			delete(player);
		}

		/* Close SDL */
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

		//TODO: figure out if WINDOW_WIDTH/HEIGHT are inner- or outer dimensions.
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

		SDL_SetRenderDrawColor(hRndr, 0x20, 0xf5, 0xa2, 0xff); // 'Tis just something random so I can see it.

		return true;
	}

	bool Stain::loadImage(std::string handleName, std::string filePath, Sprite::FACING face, int frameSize, int animTime){
		/*
		*	Load an image from file, toss it into a Sprite class together with some meta-data and put the lot in a list.
		*/
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

			Sprite* sprite = new Sprite(handleName, newTexture, face, frameSize, animTime);
			images.push_back(sprite);

			return true;
		}
	}

	void Stain::setOverlay(std::string handle, int timeToShowMs){
		/*
		*	Display an overlay (an image; e.g. "splash screen", pause image, message board, etc.) over the screen.
		*	timeToShowMs : how long, in milliseconds, to show the overlay. -1 is forever (untill manually closed).
		*	To close/remove the overlay use a handle value that is not a valid handle e.g. nullptr.
		*/
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

	Sprite* Stain::getSprite(std::string handle){
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

	void Stain::setFPS(int newFPS){
		fps = newFPS;
	}

	void Stain::addLevel(MapLevel* level){
		if (level != nullptr){
			/* Initialize the maps viewport to match the window dimensions */
			level->setViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			levels.push_back(level);
			/* If we haven't chosen an active map let's do it now */
			if (activeLevel == nullptr)
				activeLevel = level;
		}
	}

	void Stain::render(){
		/*
		*	Does all the rendering.
		*/
		int deltaMS = SDL_GetTicks() - lastRenderTime;
		if (fps <= 0 || deltaMS >= 1000 / (float)fps){ // SDL_GetTicks is low resolution, FPS precision suffers.
			if (false) std::cout << "FPS: " << (deltaMS == 0 ? "Through the roof!" : std::to_string(1000 / deltaMS)) << std::endl;	// FPS Debug

			/* Let's start with clearing the display. */
			SDL_RenderClear(hRndr);

			/* Let's render the map background of the current map */
			if (activeLevel->getTexture() != nullptr)
				SDL_RenderCopy(hRndr, activeLevel->getTexture(), activeLevel->getViewport(), nullptr);

			/* Let's render all the mobs in the current map */
			for each (Entity* mob in activeLevel->getMobiles()){
				mob->draw(hRndr, activeLevel->getMapOffset());
			}

			/* Let's render loot items in the current map */
			for each (EntityLoot* loot in activeLevel->getLoot()){
				loot->draw(hRndr, activeLevel->getMapOffset());
			}

			/* Let's render obstackles in the current map. */


			/* Let's render the players */
			for each (Entity* player in players){
				player->draw(hRndr, activeLevel->getMapOffset());
			}

			/* Let's draw the GUI */


			/* Let's handle the overlay. This should be rendered last so that it covers everything */
			if (displayOverlay != nullptr){
				SDL_RenderCopy(hRndr, displayOverlay, nullptr, nullptr);
				if (overlayTime != -1 && overlayTime - (long int)SDL_GetTicks() <= 0)
					displayOverlay = nullptr;
			}

			/* Finally; present! */
			SDL_RenderPresent(hRndr);
			lastRenderTime = SDL_GetTicks();
		}
	}

	void Stain::addPlayer(EntityHuman* newPlayer){
		players.push_back(newPlayer);
		activeLevel->focusEntity(newPlayer, true);
	}

	void Stain::setActiveLevel(std::string levelName){
		/*
		*	Picks the level/map from the list by matching levelName and makes it the active level/map.
		*/
		for each (MapLevel* level in levels){
			if (level->getName() == levelName){
				activeLevel = level;
				break;
			}
		}
	}

	void Stain::run(){
		/*
		*	Main loop
		*/
		bool quit = false;
		bool keyLeft = false, keyRight = false, keyUp = false, keyDown = false;

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
						if (!keyUp){
							keyUp = true;
							setPlayerAngleAndMoving(keyUp, keyDown, keyLeft, keyRight);
						}
						break;
					case SDLK_s:
					case SDLK_DOWN:
						if (!keyDown){
							keyDown = true;
							setPlayerAngleAndMoving(keyUp, keyDown, keyLeft, keyRight);
						}
						break;
					case SDLK_a:
					case SDLK_LEFT:
						if (!keyLeft){
							keyLeft = true;
							setPlayerAngleAndMoving(keyUp, keyDown, keyLeft, keyRight);
						}
						break;
					case SDLK_d:
					case SDLK_RIGHT:
						if (!keyRight){
							keyRight = true;
							setPlayerAngleAndMoving(keyUp, keyDown, keyLeft, keyRight);
						}
						break;
					}
					break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym){
					case SDLK_w:
					case SDLK_UP:
						if (keyUp){
							keyUp = false;
							setPlayerAngleAndMoving(keyUp, keyDown, keyLeft, keyRight);
						}
						break;
					case SDLK_s:
					case SDLK_DOWN:
						if (keyDown){
							keyDown = false;
							setPlayerAngleAndMoving(keyUp, keyDown, keyLeft, keyRight);
						}
						break;
					case SDLK_a:
					case SDLK_LEFT:
						if (keyLeft){
							keyLeft = false;
							setPlayerAngleAndMoving(keyUp, keyDown, keyLeft, keyRight);
						}
						break;
					case SDLK_d:
					case SDLK_RIGHT:
						if (keyRight){
							keyRight = false;
							setPlayerAngleAndMoving(keyUp, keyDown, keyLeft, keyRight);
						}
					}
					break;
				case SDL_MOUSEMOTION:
					/* Set the player's visual angle to point at the mouse cursor*/
					mousePosition.x = event.motion.x;
					mousePosition.y = event.motion.y;
					setPlayerVisualAngle();
					break;
				case SDL_MOUSEBUTTONDOWN:
					
					// Test stuff
					/*
					for each (Entity* mob in activeLevel->getMobiles())
					{
						mob->die();
						break;
					}
					*/
					EntityLiving* player = nullptr;
					for each (EntityLiving* p in players){
						player = p;
						break;
					}

					Weapon* armedItem = (Weapon*)player->inventory->getSelectedItem();
					
					if (armedItem != nullptr){
						EntityProjectile* projectile = armedItem->fire(player->getX(), player->getY(), player->getAngle() * 180 / M_PI);
						if (projectile != nullptr){
							projectiles.push_back(projectile);
							std::cout << "Shoot!\n";
						}
						else{
							std::cout << "null projectile\n";
						}
					}
					else{
						std::cout << "null gun\n";
					}
					
					
					break;
				}
			}




			//SDL_Delay(100);


			/* Remove dead entities */
			activeLevel->purgeDeadEntities();

			/* Loot heartbeat */
			for each (EntityLoot* loot in activeLevel->getLoot()){
				loot->tick(players);
			}

			/* Mobiles heartbeat */
			for each (Entity* mob in activeLevel->getMobiles()){
				mob->tick(players);
			}

			/* Player heartbeat */
			for each (EntityHuman* player in players){
				player->tick(activeLevel->getMobiles());
				if (player->isMoving()){
					setPlayerVisualAngle();
					activeLevel->focusEntity(player);
				}
			}

			/* Render screen */
			render();
		}
	}

	void Stain::setPlayerAngleAndMoving(bool keyUp, bool keyDown, bool keyLeft, bool keyRight){
		/*
		*	Helper function:
		*	Set the player (movement) angle depending on which keys (up, down, left, right) are pressed down
		*	then start or stop moving.
		*/

		/* Let's get our local player */
		EntityHuman* localPlayer = nullptr;
		for each (EntityHuman* player in players){
			if (player->getNetworkConnectStatus() == EntityHuman::CONNECTION::LOCAL){
				localPlayer = player;
				break;
			}
		}

		if (localPlayer != nullptr){
			if ((keyUp && !keyDown) || (keyDown && !keyUp) || (keyLeft && !keyRight) || (keyRight && !keyLeft)){
				double ang = 0;

				ang = keyUp ? ((M_PI * 1.5) + (M_PI / 4) * ((keyLeft && !keyRight) ? -1 : ((keyRight && !keyLeft) ? 1 : 0))) : (keyDown ? ((M_PI * 0.5) + (M_PI / 4) * ((keyLeft && !keyRight) ? 1 : ((keyRight && !keyLeft) ? -1 : 0))) : 0);
				if (ang == 0){
					ang = keyLeft ? (M_PI) : 0;
				}
				localPlayer->setAngle(ang);
				if (!localPlayer->isMoving()) localPlayer->startMoving();
			}
			else{
				localPlayer->stopMoving();
			}
		}
	}

	void Stain::setPlayerVisualAngle(){
		/*
		*	Helper function:
		*	Set the visual angle of the player (sprite) so that it's aiming at the mouse cursor.
		*/

		/* Let's get our local player */
		EntityHuman* localPlayer = nullptr;
		for each (EntityHuman* player in players){
			if (player->getNetworkConnectStatus() == EntityHuman::CONNECTION::LOCAL){
				localPlayer = player;
				break;
			}
		}
		if (localPlayer != nullptr){
			localPlayer->getSprite()->setAngle(SDL_atan2(localPlayer->getY() - activeLevel->getMapOffset().y - mousePosition.y, localPlayer->getX() - activeLevel->getMapOffset().x - mousePosition.x) * 180 / M_PI);
		}
	}



}