#ifndef STAIN_H
#define STAIN_H

#include <string>
#include <vector>
#include "SDL.h"

/*
	Stain - game engine
*/

namespace stain{
	class Stain
	{
	public:
		Stain();
		~Stain();
		bool init(std::string title, int width, int height);
		bool loadImage(std::string filePath, std::string handleName);
		void showOverlay(std::string handle);
		SDL_Texture* getTextureFromHandle(std::string handle);
	private:
		SDL_Window* hWnd;
		SDL_Renderer* hRndr;
		std::string WINDOW_TITLE;
		int WINDOW_WIDTH;
		int WINDOW_HEIGHT;
		struct Stain_IMG{
			SDL_Texture* hTexture;
			std::string handle;
		};
		std::vector<Stain_IMG> images;
	};
}
#endif