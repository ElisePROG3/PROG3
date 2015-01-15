#include "Stain.h"
#include "Entity.h"
#include "EntityHuman.h"
#include "Weapon.h"
#include "WeaponGun.h"
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <iostream>
#include "Assets.h"
#include <algorithm> // for remove_if

namespace stain{
	Stain::Stain() :
		hWnd(nullptr),					/* Handle to the SDL window */
		hRndr(nullptr),					/* Handle to the SDL renderer */
		WINDOW_TITLE("Window"),			/* Window name */
		WINDOW_WIDTH(640),				/* Window width */
		WINDOW_HEIGHT(480),				/* Window height */
		fps(60),						/* How often the playfield should be rendered */
		lastRenderTime(-1),				/* Holds the time in ticks since the playfield was rendered last time. Used for rate (FPS) limiting */
		activeLevel(nullptr)			/* A pointer to the current level */
	{
		/* Set defualt keys */
		keyboard[KEYEVENT::MOVE_UP] = SDLK_w;
		keyboard[KEYEVENT::MOVE_DOWN] = SDLK_s;
		keyboard[KEYEVENT::MOVE_LEFT] = SDLK_a;
		keyboard[KEYEVENT::MOVE_RIGHT] = SDLK_d;
	}

	Stain::~Stain(){

		/* Destroy resources. */
		Assets::deleteAssets();

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
		/*
		*	Initiation.
		*	Init SDL, the window and the renderer.
		*	Prepare SDL_IMG to load PNG image format.
		*	Give renderer to Assets and set some default values.
		*/
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

		Assets::setRenderer(hRndr);
		SDL_SetRenderDrawColor(hRndr, 0x20, 0xf5, 0xa2, 0xff); // 'Tis just something random so I can see it.

		return true;
	}

	void Stain::setOverlay(std::string handle, int timeToShowMs){
		/*
		*	Display an overlay (an image; e.g. "splash screen", pause image, message board, etc.) over the screen.
		*	timeToShowMs : how long, in milliseconds, to show the overlay. -1 is forever (untill manually closed).
		*	To close/remove the overlay use a handle value that is not a valid handle e.g. nullptr.
		*/

		int oTime;

		if (timeToShowMs < 0){
			oTime = -1;
		}else{
			oTime = SDL_GetTicks() + timeToShowMs;
		}

		SDL_Texture* img = Assets::getTexture(handle);
		if (img != nullptr){
			displayOverlay.push_back({ img, oTime });
		}
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
		if (fps <= 0 || deltaMS >= 1000 / (float)fps){ // Note: SDL_GetTicks is low resolution, FPS precision suffers.
			if (false) std::cout << "FPS: " << (deltaMS == 0 ? "Through the roof!" : std::to_string(1000 / deltaMS)) << std::endl;	// FPS Debug

			/* Let's start with clearing the display. */
			SDL_RenderClear(hRndr);

			/* Let's draw the map background of the current map */
			if (activeLevel->getTexture() != nullptr)
				SDL_RenderCopy(hRndr, activeLevel->getTexture(), activeLevel->getViewport(), nullptr);

			/* Let's draw projectiles */
			for each (EntityProjectile* projectile in projectiles){
				projectile->draw(hRndr, activeLevel->getMapOffset());
			}

			/* Let's render all the mobs in the current map */
			for each (Entity* mob in activeLevel->getMobiles()){
				mob->draw(hRndr, activeLevel->getMapOffset());
			}

			/* Let's draw loot items in the current map */
			for each (EntityLoot* loot in activeLevel->getLoot()){
				loot->draw(hRndr, activeLevel->getMapOffset());
			}

			/* Let's draw obstacles in the current map. */


			/* Let's draw portals in the current map */
			for each (Portal* portal in activeLevel->getPortals()){
				portal->draw(hRndr, activeLevel->getMapOffset());
			}

			/* Let's draw the players */
			for each (Entity* player in players){
				player->draw(hRndr, activeLevel->getMapOffset());
			}

			/* Let's draw the GUI */


			/* Let's handle the overlay(s). This should be rendered last so that it covers everything */
			if (!displayOverlay.empty()){
				SDL_RenderCopy(hRndr, displayOverlay.front().img, nullptr, nullptr);
				if (displayOverlay.front().time != -1 && displayOverlay.front().time - (long int)SDL_GetTicks() <= 0)
					displayOverlay.erase(displayOverlay.begin());
			}

			/* Finally; present! */
			SDL_RenderPresent(hRndr);
			lastRenderTime = SDL_GetTicks();
		}
	}

	void Stain::addPlayer(EntityHuman* newPlayer){
		if (newPlayer){
			players.push_back(newPlayer);
			activeLevel->focusEntity(newPlayer, true);
		}
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

	void Stain::setKey(KEYEVENT event, char letter){
		/*
		*	Set custom keys for actions.
		*/
		keyboard[event] = SDL_GetKeyFromName(&letter);
	}

	void Stain::run(){
		/*
		*	Main loop
		*/
		bool quit = false, gameOver = false;
		bool keyLeft = false, keyRight = false, keyUp = false, keyDown = false;

		while (!quit){
			while (SDL_PollEvent(&event) != 0){
				switch (event.type){
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == keyboard[KEYEVENT::MOVE_UP]){
						if (!keyUp){
							keyUp = true;
							setPlayerAngleAndMoving(keyUp, keyDown, keyLeft, keyRight);
						}
					}
					if (event.key.keysym.sym == keyboard[KEYEVENT::MOVE_DOWN]){
						if (!keyDown){
							keyDown = true;
							setPlayerAngleAndMoving(keyUp, keyDown, keyLeft, keyRight);
						}
					}
					if (event.key.keysym.sym == keyboard[KEYEVENT::MOVE_LEFT]){
						if (!keyLeft){
							keyLeft = true;
							setPlayerAngleAndMoving(keyUp, keyDown, keyLeft, keyRight);
						}
					}
					if (event.key.keysym.sym == keyboard[KEYEVENT::MOVE_RIGHT]){
						if (!keyRight){
							keyRight = true;
							setPlayerAngleAndMoving(keyUp, keyDown, keyLeft, keyRight);
						}
					}
					
					break;
				case SDL_KEYUP:
					if (event.key.keysym.sym == keyboard[KEYEVENT::MOVE_UP]){
						if (keyUp){
							keyUp = false;
							setPlayerAngleAndMoving(keyUp, keyDown, keyLeft, keyRight);
						}
					}

					if (event.key.keysym.sym == keyboard[KEYEVENT::MOVE_DOWN]){
						if (keyDown){
							keyDown = false;
							setPlayerAngleAndMoving(keyUp, keyDown, keyLeft, keyRight);
						}
					}
					if (event.key.keysym.sym == keyboard[KEYEVENT::MOVE_LEFT]){
						if (keyLeft){
							keyLeft = false;
							setPlayerAngleAndMoving(keyUp, keyDown, keyLeft, keyRight);
						}
					}
					if (event.key.keysym.sym == keyboard[KEYEVENT::MOVE_RIGHT]){
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
					
					/* Handle overlays that need clicking */
					if (!displayOverlay.empty() && !gameOver){
						if (displayOverlay.front().time == -1)
							displayOverlay.erase(displayOverlay.begin());
					}

					/* Handle user clicks, fire weapons etc */
					/* Let's get our local player */
					EntityHuman* localPlayer = nullptr;
					for each (EntityHuman* player in players){
						if (player->getNetworkConnectStatus() == EntityHuman::CONNECTION::LOCAL){
							localPlayer = player;
							break;
						}
					}

					Weapon* armedItem = (Weapon*)localPlayer->inventory->getSelectedItem();
					
					if (armedItem != nullptr){
						EntityProjectile* projectile = armedItem->fire(localPlayer->getX(), localPlayer->getY(), localPlayer->getSprite()->getAngle() * M_PI / 180);
						if (projectile != nullptr){
							projectiles.push_back(projectile);
							std::cout << "Shoot! (p: " << projectiles.size() << " | e: " << activeLevel->getMobiles().size() << ")\n";
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

			/* Tick() only if no overlay is displayed */
			if (displayOverlay.size() == 0){
				/* Remove dead entities */
				projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](EntityProjectile* projectile){ return projectile->isDead(); }), projectiles.end());
				activeLevel->purgeDeadEntities();

				/* Projectiles heartbeat */
				for each (EntityProjectile* projectile in projectiles){
					projectile->tick(activeLevel->getMobiles());
				}

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

				/* Portal heartbeat */
				for each (Portal* portal in activeLevel->getPortals()){
					std::string doWarp = "";
					portal->tick(players, doWarp);
					if (!doWarp.empty()){
						setActiveLevel(doWarp);
						players.front()->setX(700);		// Ran out of time - quick fix.
						players.front()->setY(300);
						break;
					}
				}

				/* Check win condition */
				int mobCount = 0;
				for each (MapLevel* level in levels){
					mobCount += level->getMobiles().size();
				}
				if (mobCount == 0 && !gameOver){
					std::cout << "You win!\n";
					setOverlay("victory");
					gameOver = true;
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