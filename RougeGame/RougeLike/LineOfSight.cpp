#include "LineOfSight.h"

#include "Game.h"
cLOS::cLOS(cGame& g) : game(g)
{

}

//can be removed and put into the player class
void cLOS::SetView(COORD pPos)
{
	//creates a line sight 4 in each direction, then a 5th layer used to clean up IsVisible flags on the tiles that are being moved out of range
	for (int i = -5; i < 5; ++i)
	{
		bool flag = true;//used to clean up previous vision
		if (i < 5 && i > -5)
		{
			flag = false;
		}

		int posY = (game.m_iSizeX * pPos.Y);
		int posX = pPos.X + i;
		game.level[posY + posX].IsVisible = flag;
		game.level[posY + posX].IsRevealed = true;
		flag = false;
		for (int j = 5 + i; j > 0; --j)
		{
			
			posY = game.m_iSizeX * (pPos.Y - j);
			game.level[posY + posX].IsVisible = flag;
			game.level[posY + posX].IsRevealed = true;

			posY = game.m_iSizeX * (pPos.Y + j);
			game.level[posY + posX].IsVisible = flag;
			game.level[posY + posX].IsRevealed = true;
			flag = true;
		}
	}
}