#ifndef MAP_H
#define MAP_H

#include <windows.h>
class cPlayer;
struct game_state;
struct Tile
{
	Tile() 
		: IsVisible(false)
		, IsRevealed(false)
		, IsPath(false)
		, state(' ')
	{}
	bool IsVisible;//in current line of sight
	bool IsRevealed;//has been explored
	bool IsPath;
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
	void PutPlayerInRoom(game_state *GameState);

	int m_iRoomSizeX;//x and y size of the current room
	int m_iRoomSizeY;

	bool IsConnected;

	COORD pos;
	Tile* m_room;
private:
};



#endif//MAP_H