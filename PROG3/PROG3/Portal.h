#ifndef PORTAL_H
#define PORTAL_H

#include "Entity.h"

namespace stain{
	class Portal : public Entity{
	public:
		static Portal* getInstance(double x, double y, int size, Sprite* sprite, std::string destination);
		void tick(std::vector<Entity*> interactors);
		void tick(std::vector<Entity*> interactors, std::string &warp);
		~Portal();
	private:
		Portal(double x, double y, int size, Sprite* sprite, std::string destination);
		std::string destination;
	};
}
#endif