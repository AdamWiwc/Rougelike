#include "rouge.h"
#include <conio.h>
#include <stdio.h>
#include <string>

_internal void
UpdateMessageLog(game_state *GameState, std::string MessageToHandle)
{
	// NOTE(jesse): Print Action log at the bottom	
	// NOTE(jesse): Delete oldest message
	GameState->MessageLog.erase(0, GameState->MessageLog.find("\n") + 1);
#if 1
	while (MessageToHandle.size() < 80)
	{
		MessageToHandle += " ";
	}
#endif
	GameState->MessageLog += MessageToHandle;
	GameState->MessageLog += "\n";
}

_internal void
PrintMessageLog(game_state *GameState)
{
	printf("%s", GameState->MessageLog.c_str());
}

_internal void
ProcessKeyboardInput(game_state *GameState)
{
	int32 LastKeyPressed = NULL;

	LastKeyPressed = _getch();
	// NOTE(jesse): Arrow Key Input
	if (LastKeyPressed == 0 || LastKeyPressed == 224)
	{
		switch (_getch())
		{
		case 72:
			// NOTE(jesse): code for arrow up
			UpdateMessageLog(GameState, "Moved North!");
			break;
		case 80:
			// NOTE(jesse): code for arrow down
			UpdateMessageLog(GameState, "Moved South!");
			break;
		case 75:
			// NOTE(jesse): code for arrow right
			UpdateMessageLog(GameState, "Moved West!");
			break;
		case 77:
			// NOTE(jesse): code for arrow left
			UpdateMessageLog(GameState, "Moved East!");
			break;
		}
	}
	else
	{
		// NOTE(jesse): Other input
		if (LastKeyPressed == 'a')
		{
			UpdateMessageLog(GameState, "Attacked the goblin for 20 damage! Critical Hit! KO, the troll has died");
		}
		else if (LastKeyPressed == 'd')
		{
			UpdateMessageLog(GameState, "Blocked");
		}
	}

	// NOTE(jesse): Add more input here
}

_internal void
PrintStats(game_state *GameState)
{
	// NOTE(jesse): Stats and Health Go at the top of the screen
	printf("%s the %s:	Level: %d	Health: %d/%d \n"
		"	EXP: %d/%d	Str:%d	Def:%d	Gold:%d\n",
		GameState->Player->GetName().c_str() , "Rouge", GameState->Player->GetLevel(),
		GameState->Player->getHeath(), GameState->Player->GetMaxHealth(), GameState->Player->GetXP(),
		GameState->Player->GetXpToNext(), 4, 5, GameState->Player->GetGold());
}