#ifndef MAP_H
#define MAP_H

#include <windows.h>
class cPlayer;
struct Tile
{
	Tile() 
		: IsVisible(false)
		, IsRevealed(false)
		, state(' ')
	{}
	bool IsVisible;//in current line of sight
	bool IsRevealed;//has been explored
				//Change the default to the walkable floor tile char, or create a flag for walkable and change text color when printing
	char state; //what state the block is in, IE: enemy, wall, player (What gets printed on the screan)
};

class cRoom
{
public:
	cRoom();
	cRoom(int sizeX, int sizeY);
	~cRoom();
	void Init(int sizeX, int sizeY);
	void GenerateRoom();
	void PutPlayerInRoom(cPlayer& player);

	int m_iRoomSizeX;//x and y size of the current room
	int m_iRoomSizeY;

	bool IsConnected;

	COORD pos;
	Tile* m_room;
private:
};



#endif//MAP_H