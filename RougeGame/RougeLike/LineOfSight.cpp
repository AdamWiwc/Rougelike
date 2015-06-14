#include "LineOfSight.h"

#include "Game.h"
cLOS::cLOS(cGame& g) : game(g)
{

}

void cLOS::SetView()
{
	for (int i = -4; i < 4; ++i)
	{
		int posY = (game.m_iSizeX * pPos.Y);
		int posX = pPos.X + i;
		game.level[posY + posX].IsVisible = true;
		game.level[posY + posX].IsRevealed = true;
		for (int j = 4 + i; j > 0; --j)
		{
			posY = game.m_iSizeX * (pPos.Y - j);
			game.level[posY + posX].IsVisible = true;
			game.level[posY + posX].IsRevealed = true;

			posY = game.m_iSizeX * (pPos.Y + j);
			game.level[posY + posX].IsVisible = true;
			game.level[posY + posX].IsRevealed = true;
		}
	}
}