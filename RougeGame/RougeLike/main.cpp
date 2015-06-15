#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "rouge.h"
#include "rouge.cpp"

#include "Game.h"
#include "Room.h"
#include "Player.h"
#include "LineOfSight.h"

int main()
{
	game_state GameState;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	srand((uint32)time(NULL));

	GameState.IsInitialized = false;
	bool32 Running = true;
	while(Running)
	{	
		if (!GameState.IsInitialized)
		{
			GameState = {};
			GameState.MessageLog = ("\n\n\n");
			GameState.Player = new cPlayer();
			#define SIZEX 80
			#define SIZEY 25
			GameState.CurrentLevel = new cGame(SIZEX, SIZEY);
			GameState.CurrentLevel->GenerateLevel(&GameState);
			GameState.CurrentLineOfSight = new cLOS(*GameState.CurrentLevel);

			GameState.IsInitialized = true;
		}

		//system("cls");
		SetConsoleCursorPosition(hOut, { 0, 0 });
		PrintStats(&GameState);

		GameState.CurrentLineOfSight->SetView(GameState.Player->GetCords());
		// NOTE(jesse): Draw the game in the center of the screen
		printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");

		GameState.CurrentLevel->PrintLevel(&GameState, hOut);

		printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
		
		PrintMessageLog(&GameState);

		ProcessKeyboardInput(&GameState);
	}

	return 0;
}

