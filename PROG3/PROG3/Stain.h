#ifndef STAIN_H
#define STAIN_H

#include <string>
#include <vector>
#include "SDL.h"
#include "Entity.h"
#include "EntityHuman.h"
#include "MapLevel.h"
#include "Sprite.h"

/*
	Stain - game engine
*/

namespace stain{
	class Stain{
	public:
		Stain();
		~Stain();
		bool init(std::string title = "Window", int width = 640, int height = 480);
		bool loadImage(std::string handleName, std::string filePath, int frameSize = 0, int animTime = 0);
		void setOverlay(std::string handle, int timeToShowMs = -1);
		SDL_Texture* getTexture(std::string handle);
		Sprite* getSprite(std::string handle);
		void setFPS(int fps);
		void addPlayer(EntityHuman* player);
		void addLevel(MapLevel* level);
		void setActiveLevel(std::string levelName);
		void run();
	private:
		SDL_Window* hWnd;
		SDL_Renderer* hRndr;
		std::string WINDOW_TITLE;
		int WINDOW_WIDTH;
		int WINDOW_HEIGHT;

		int fps;
		int lastRenderTime;
		int overlayTime;
		SDL_Texture* displayOverlay;
		std::vector<Entity*> players;	/* It's a list: for future support for multi-player. */
		std::vector<MapLevel*> levels;
		MapLevel* activeLevel;
		SDL_Event event;
		SDL_Point mousePosition;
		std::vector<Sprite*> images;

		void render();
		void setPlayerAngleAndMoving(bool up, bool down, bool left, bool right);
		void setPlayerVisualAngle();
	};
}
#endif