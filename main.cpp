#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"
#include<time.h>


int main()
{
	
	srand(time(NULL));
	game Game;
	Game.run();

	return 0;
}