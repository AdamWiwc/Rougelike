#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <Windows.h>

#include "Game.h"
#include "Room.h"
#include "Player.h"

#define SIZEX 80
#define SIZEY 60

using namespace std;

int main()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, {0, 0});
	srand(time(NULL));

	cGame game(SIZEX, SIZEY);

	game.GenerateLevel();

	game.PrintScreen();

	return 0;
}

