#ifndef DISPLAY_H
#define DISPLAY_H

#include "Room.h"

class cGame
{
public:
	cGame(unsigned int sizeX, unsigned int sizeY);
	void PrintScreen();

	void GenerateLevel();
	bool CheckForRoomCollisions(cRoom* room, int amountOfRooms);
	void SetDifficulty(int maxRooms, int minRooms)
	{
		m_iMaxRooms = maxRooms;
		m_iMinRooms = minRooms;
	}
	Tile* GetLevel()
	{
		return level;
	}

private:
	void PrintLevel();

	unsigned int m_iSizeX;
	unsigned int m_iSizeY;

	Tile* level; //level
	cRoom* rooms; //array of rooms
	int m_iMaxRooms;
	int m_iMinRooms;
};



#endif //DISPLAY_H