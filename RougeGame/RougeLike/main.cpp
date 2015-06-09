#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "Game.h"
#include "Room.h"
#include "Player.h"
#include "Rouge.h"

#define SIZEX 80
#define SIZEY 60

inline std::string
ProcessKeyboardInput(void)
{
	uint8 LastKeyPressed = NULL;
	// NOTE(jesse): Make sure you don't skip the getchar as it picks up
	// the [enter] after the input normally
	while(((LastKeyPressed=getchar()) != '\n') && LastKeyPressed != EOF);
	Assert(LastKeyPressed);
	if(LastKeyPressed == 'a')
	{
		return "Attacked!";
	}
	// NOTE(jesse): Add more input here
	return "";
}

internal void
UpdateMessageLog(std::string *MessageLog, std::string MessageToHandle)
{
	// NOTE(jesse): Delete oldest message
	MessageLog->erase(0, MessageLog->find("\n") + 1);
	*MessageLog += MessageToHandle;
	*MessageLog += "\n";

	printf("%s", MessageLog->c_str());
}

int 
main()
{
	// HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// SetConsoleCursorPosition(hOut, {0, 0});
	// srand(time(NULL));

	cGame game(SIZEX, SIZEY);

	// cPlayer Player = {};

	std::string MessageLog = "\n\n\n";

	// game.GenerateLevel();
	
	bool32 Running = true;
	while(Running)
	{
		system("cls");

		std::string Message = "";
		Message = ProcessKeyboardInput();

		// NOTE(jesse): Stats and Health Go at the top few rows of
		// the screen
#if 0
		printf("%s the %s:	Level: %d	Health: %d \n"
			   "	EXP: %d/%d	Str:%d	Def:%d	Gold:%d\n", 
			   Player.GetName, "Rouge", Player.GetLevel, 
			   Player.GetHealth, Player.GetEXP, Player.GetMaxEXP, 
			   Player.GetStrength, Player.GetDefence, Player.GetGold);
#endif   
		// NOTE(jesse): Draw the game in the center of the screen

		// NOTE(jesse): Print Action log at the bottom	
		if(Message!="")
		{
			UpdateMessageLog(&MessageLog, Message);
		}
		system("pause");
	}

	return 0;
}

