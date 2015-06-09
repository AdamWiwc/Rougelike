#ifndef DISPLAY_H
#define DISPLAY_H

#include "Room.h"

class cGame
{
public:
	cGame(unsigned int sizeX, unsigned int sizeY);
	void PrintScreen(HANDLE& hOut);

	void GenerateLevel();
	void GeneratePaths();//delete this!!!

	void GenerateStraightPaths();
	void GenerateCornerPaths();
	
	bool CheckForRoomIntersections(cRoom& rooms, int amountOfRooms);//path going through a room
	bool CheckForRoomCollisions(cRoom* room);
	void SetDifficulty(int maxRooms, int minRooms)
	{
		m_iMaxRooms = maxRooms;
		m_iMinRooms = minRooms;
	}

	Tile& GetTile(const int x, const int y) const
	{
		return level[(y * m_iSizeX) + x];
	}

private:
	void PrintLevel();

	unsigned int m_iSizeX;
	unsigned int m_iSizeY;
	unsigned int amountOfRooms;
	Tile* level; //level
	cRoom* rooms; //array of rooms
	int m_iMaxRooms;
	int m_iMinRooms;
};

#endif //DISPLAY_H