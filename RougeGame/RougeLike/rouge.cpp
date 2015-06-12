#include "rouge.h"
#include <conio.h>

internal void
UpdateMessageLog(game_state *GameState, std::string MessageToHandle)
{
	// NOTE(jesse): Print Action log at the bottom	
	// NOTE(jesse): Delete oldest message
	GameState->MessageLog.erase(0, GameState->MessageLog.find("\n") + 1);
	GameState->MessageLog += MessageToHandle;
	GameState->MessageLog += "\n";

	printf("%s", GameState->MessageLog.c_str());
}

internal void
ProcessKeyboardInput(game_state *GameState)
{
	uint8 LastKeyPressed = NULL;
	// NOTE(jesse): Make sure you don't skip the getchar as it picks up
	// the [enter] after the input normally
	//while (((LastKeyPressed = getchar()) != '\n') && LastKeyPressed != EOF);
	LastKeyPressed = _getch();
	Assert(LastKeyPressed);
	if (LastKeyPressed == 'a')
	{
		UpdateMessageLog(GameState, "Attacked");
	}
	if (LastKeyPressed == 'd')
	{
		UpdateMessageLog(GameState, "Blocked");
	}
	// NOTE(jesse): Add more input here
}

internal void
PrintStats(game_state *GameState)
{
	// NOTE(jesse): Stats and Health Go at the top of the screen
	printf("%s the %s:	Level: %d	Health: %d/%d \n"
		"	EXP: %d/%d	Str:%d	Def:%d	Gold:%d\n",
		GameState->Player->GetName().c_str() , "Rouge", GameState->Player->GetLevel(),
		GameState->Player->getHeath(), GameState->Player->GetMaxHealth(), GameState->Player->GetXP(),
		GameState->Player->GetXpToNext(), 4, 5, GameState->Player->GetGold());
}