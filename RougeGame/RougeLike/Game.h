#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include "Room.h"

class cPlayer;
class cGame
{
public:
	cGame(int sizeX, int sizeY);
	void PrintLevel(cPlayer& player);

	void GenerateLevel(cPlayer& player);
	void GeneratePaths();

	std::vector<cRoom*> FindValidHorRooms(cRoom* currentRoom);
	std::vector<cRoom*> FindValidVerRooms(cRoom* currentRoom);

	bool GetHorPathableRange(cRoom* currentRoom, cRoom* other, std::pair<int, int>& range);
	bool GetVerPathableRange(cRoom* currentRoom, cRoom* other, std::pair<int, int>& range);

	bool CheckForHorRoomPathCollisions(cRoom* currentRoom, cRoom* other, std::pair<int, int>& range);
	bool CheckForVerRoomPathCollisions(cRoom* currentRoom, cRoom* other, std::pair<int, int>& range);

	//bool CheckForRoomIntersections(cRoom& rooms, int amountOfRooms);//path going through a room
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

	Tile& GetTile(const int xy) const
	{
		return level[xy];
	}
private:

	int m_iSizeX;
	int m_iSizeY;
	int amountOfRooms;
	Tile* level; //level
	cRoom* rooms; //array of rooms
	int m_iMaxRooms;
	int m_iMinRooms;
};

#endif //DISPLAY_H