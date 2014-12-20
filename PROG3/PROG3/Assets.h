#ifndef ASSETS_H
#define ASSETS_H

#include <string>
#include <vector>
#include "SDL.h"
#include "Sprite.h"

namespace stain{
	class Assets
	{
	public:
		~Assets();

		static bool loadImage(std::string handleName, std::string filePath, Sprite::FACING face = Sprite::FACING::NONE, int frameSize = 0, int animTime = 0);
		static SDL_Texture* getTexture(std::string handle);
		static Sprite* getSprite(std::string handle);
		static void setRenderer(SDL_Renderer* renderer);
		static void deleteAssets();
	private:
		Assets();

		static std::vector<Sprite*> images;
		static SDL_Renderer* hRndr;
	};
}
#endif