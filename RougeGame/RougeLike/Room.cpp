#include "Room.h"
#include "Player.h"
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
	/*
		Random Decorative objects
			Shrines
			Wells
			boxes
			chairs
			tables
			furniture

			Example:

			##############################
			\
			\		c c c c
					=======
					c c c c
			\
			\


		Traps that damage you
		Treasure chests
		Secret walls (With treasures inside)
		Secret Peter Chan ascii shrine
	*/
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

//puts player in the designated room
void cRoom::PutPlayerInRoom(cPlayer& player)
{
	player.SetCords({rand() % (m_iRoomSizeX - 2) + pos.X, rand() % (m_iRoomSizeY - 2) + 1 + pos.Y});
}
