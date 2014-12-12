// PROG3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <SDL.h>


int _tmain(int argc, _TCHAR* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
		std::cout << "Ok!";
	}
	else{
		std::cout << "Failed!";
	}

	SDL_Delay(3000);
	SDL_Quit();
	return 0;
}

