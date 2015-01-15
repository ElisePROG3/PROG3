#ifndef STAIN_H
#define STAIN_H

#include <string>
#include <vector>
#include "SDL.h"
#include "Entity.h"
#include "EntityHuman.h"
#include "EntityProjectile.h"
#include "MapLevel.h"
#include "Sprite.h"
#include "Portal.h"

/*
	Stain - game engine
*/

namespace stain{
	class Stain{
	public:
		Stain();
		~Stain();
		bool init(std::string title = "Window", int width = 640, int height = 480);
		void setOverlay(std::string handle, int timeToShowMs = -1);
		void setFPS(int fps);
		void addPlayer(EntityHuman* player);
		void addLevel(MapLevel* level);
		void setActiveLevel(std::string levelName);
		void run();

		enum KEYEVENT{
			MOVE_UP,
			MOVE_DOWN,
			MOVE_LEFT,
			MOVE_RIGHT
		};

		void setKey(KEYEVENT event, char letter);

		struct overlayObject{
			SDL_Texture* img;
			int time;
		};
	private:
		SDL_Window* hWnd;
		SDL_Renderer* hRndr;
		std::string WINDOW_TITLE;
		int WINDOW_WIDTH;
		int WINDOW_HEIGHT;

		int fps;
		int lastRenderTime;
		std::vector<overlayObject> displayOverlay;
		std::vector<Entity*> players;	/* It's a list: for future support for multi-player. */
		std::vector<MapLevel*> levels;
		std::vector<EntityProjectile*> projectiles;
		MapLevel* activeLevel;
		SDL_Event event;
		SDL_Point mousePosition;
		SDL_Keycode keyboard[4];

		void render();
		void setPlayerAngleAndMoving(bool up, bool down, bool left, bool right);
		void setPlayerVisualAngle();
	};
}
#endif