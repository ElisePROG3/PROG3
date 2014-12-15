#ifndef STAIN_H
#define STAIN_H

#include <string>
#include <vector>
#include "SDL.h"
#include "Entity.h"

/*
	Stain - game engine
*/

namespace stain{
	class Stain{
	public:
		Stain();
		~Stain();
		bool init(std::string title = "Window", int width = 640, int height = 480);
		bool loadImage(std::string filePath, std::string handleName);
		void setOverlay(std::string handle, int timeToShowMs = -1);
		SDL_Texture* getTextureFromHandle(std::string handle);
		void setFPS(int fps);
		void render();
		bool addMobile(Entity* entity);
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
		std::vector<Entity*> mobiles;

		struct Stain_IMG{
			SDL_Texture* hTexture;
			std::string handle;
		};
		std::vector<Stain_IMG> images;
	};
}
#endif