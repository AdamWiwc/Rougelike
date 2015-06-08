#include "Room.h"

#include <stdio.h>
cRoom::cRoom()
{

}

cRoom::cRoom(int sizeX, int sizeY)
	: m_iRoomSizeX(sizeX)
	, m_iRoomSizeY(sizeY)
{
	m_room = new Tile[m_iRoomSizeX * m_iRoomSizeY];
}

cRoom::~cRoom()
{
	if (m_room)
		delete[] m_room;
}
void cRoom::Init(int sizeX, int sizeY)
{
	m_iRoomSizeX = sizeX;
	m_iRoomSizeY = sizeY;
	m_room = new Tile[m_iRoomSizeX * m_iRoomSizeY];
}

void cRoom::GenerateRoom()
{
	//create walls
	//and opens a 'door' for a path 
	//Will Place Random Objects in the room for the game (what ever you guys decide you want, keys, chests or other things)
	
	for (int i = 0; i < m_iRoomSizeX; ++i)
	{
		m_room[i].state = '#';// Horizontal walls (TOP and BOTTOMW)
		m_room[((m_iRoomSizeY - 1) * (m_iRoomSizeX)) + i].state = '#';
	}

	for (int i = 0; i < m_iRoomSizeY; ++i)
	{
		m_room[m_iRoomSizeX * i].state = '#';// Verticle walls
		m_room[m_iRoomSizeX * i + m_iRoomSizeX - 1].state = '#';
	}
}

void cRoom::PutPlayerInRoom()
{
	int pos = m_iRoomSizeX + 3;
	if (m_room[pos].state == ' ')//checks the position to make sure there is nothing else in it
	{
		m_room[pos].state = 'P';//puts the player in a random position in the room;
	}
}
