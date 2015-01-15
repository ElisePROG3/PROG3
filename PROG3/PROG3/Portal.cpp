#include "Portal.h"

namespace stain{
	Portal::Portal(double x, double y, int size, Sprite* sprite, std::string destination) :
		Entity(x, y, size, sprite), destination(destination)
	{}

	Portal::~Portal(){}

	Portal* Portal::getInstance(double x, double y, int size, Sprite* sprite, std::string destination){
		return new Portal(x, y, size, sprite, destination);
	}

	void Portal::tick(std::vector<Entity*> interactors){
		
	}

	void Portal::tick(std::vector<Entity*> interactors, std::string &warp){
		if (collides(interactors.front())){
			warp = destination;
		}
	}
}