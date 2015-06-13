#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "Game.h"
#include "Room.h"
#include "Player.h"
#include "rouge.h"
#include "rouge.cpp"

int main()
{
	game_state GameState;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(NULL));

	cPlayer* player = new cPlayer();

	GameState.IsInitialized = false;
	bool32 Running = true;
	while(Running)
	{	
		if (!GameState.IsInitialized)
		{
			GameState = {};
			GameState.MessageLog = ("\n\n\n");
			GameState.Player;

			#define SIZEX 80
			#define SIZEY 25
			GameState.CurrentLevel = new cGame(SIZEX, SIZEY);
			GameState.CurrentLevel->GenerateLevel(*player);

			GameState.IsInitialized = true;
		}

		//system("cls");
		SetConsoleCursorPosition(hOut, { 0, 0 });
		PrintStats(&GameState);

		// NOTE(jesse): Draw the game in the center of the screen
		printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");

		GameState.CurrentLevel->PrintLevel(*player);

		printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
		
		PrintMessageLog(&GameState);

		ProcessKeyboardInput(&GameState);
	}

	return 0;
}

