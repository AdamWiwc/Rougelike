#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "Game.h"
#include "Room.h"
#include "Player.h"
#include "rouge.h"
#include "rouge.cpp"

int 
main()
{
	game_state GameState;
	
	GameState.IsInitialized = false;
	bool32 Running = true;
	while(Running)
	{
		if (!GameState.IsInitialized)
		{
			// HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			// SetConsoleCursorPosition(hOut, {0, 0});
			// srand(time(NULL));
			GameState = {};
			GameState.MessageLog = ("\n\n\n");
			GameState.Player;

			#define SIZEX 80
			#define SIZEY 60
			cGame game(SIZEX, SIZEY);
			// game.GenerateLevel();

			GameState.IsInitialized = true;
		}

		system("cls");

		PrintStats(&GameState);

		// NOTE(jesse): Draw the game in the center of the screen
		printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n\n\n\n\n\n\n\n			GAMESCREEN\n\n\n\n\n\n\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
		
		PrintMessageLog(&GameState);

		ProcessKeyboardInput(&GameState);
	}

	return 0;
}

