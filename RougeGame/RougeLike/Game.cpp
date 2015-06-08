#include <stdlib.h>
#include <stdio.h>

#include "Game.h"

int RandomNum(const int min, const int max)
{
	return rand() % (max - min) + min;
}

cGame::cGame(unsigned int sizeX, unsigned int sizeY)
	: m_iSizeX(sizeX)
	, m_iSizeY(sizeY)
{
	level = new Tile[m_iSizeX * m_iSizeY];
	printf("");
}

void cGame::PrintScreen()
{
	//Print Hud stuff
	printf("Hud Stuffs like HP and what not\n");

	PrintLevel();//print level

	//print other hud stuff
	printf("Other Hud Stuffs like action print outs??? maybe...\n");
}



void cGame::PrintLevel()
{
	for (int y = 0; y < m_iSizeY; ++y)
	{
		for (int x = 0; x < m_iSizeX; ++x)
		{
			Tile tile = level[(m_iSizeX * y) + x];
			//if (tile.IsVisible)
			{
				//tile.IsRevealed = true;
				printf("%c", tile.state);
			}
		}
		printf("\n");
	}
}

void cGame::GenerateLevel()
{
	int amountOfRooms = 5;
	int sizeX;
	int sizeY;

	rooms = new cRoom[amountOfRooms];

	for (int i = 0; i < amountOfRooms; ++i)
	{
		//x and y size have to be greater than 25
		sizeX = RandomNum(7, m_iSizeX / 4 + 2);
		sizeY = RandomNum(7, m_iSizeY / 4 + 2);
		rooms[i].Init(sizeX, sizeY);
		rooms[i].GenerateRoom();
	}

	rooms[0].PutPlayerInRoom();//puts player in the first room; 

	//TODO:
		//Put the player in one of the rooms <<<
		//place all rooms in the level <<<
		//Give each room a coordinate <<<
		//check for collisions and replace <<<
		//Create Paths from each Room 
		//Fix all of the memory leaks, cuz c++ :(

	for (int i = 0; i < amountOfRooms; ++i)//places all the rooms in the level
	{
		cRoom* room = &rooms[i];
	
		bool isColliding = false;
		do
		{
			room->pos = { RandomNum(0, m_iSizeX - room->m_iRoomSizeX), RandomNum(0, m_iSizeY - room->m_iRoomSizeY) };
			
			isColliding = CheckForRoomCollisions(room, amountOfRooms);
			if (!isColliding)
			{
				/*for (int z = 0; z < room->m_iRoomSizeY; ++z)//better more complicated way, that isnt working... fix later
				{
					//copies each tile in the room over the old tile (May or May not be working, idk. ill debug it later)
					memcpy(&level[room->pos.X * z], &room[room->m_iRoomSizeX * z], sizeof(Tile) * room->m_iRoomSizeX);
				}*/
				for (int y = room->pos.Y; y < room->pos.Y + room->m_iRoomSizeY; ++y)
				{
					for (int x = room->pos.X; x < room->pos.X + room->m_iRoomSizeX; ++x)
					{
						level[(y * m_iSizeX) + x] = room->m_room[(y - room->pos.Y) * (room->m_iRoomSizeX) + (x - room->pos.X)];
					}
				}
			}
		} while (isColliding);//while the room was not placed in the room
	}
	delete[] rooms;
}

//returns false if no collisions are detected
bool cGame::CheckForRoomCollisions(cRoom* room, int amountOfRooms)
{
	for (int i = 0; i < amountOfRooms; ++i)
	{
		cRoom* other = &rooms[i];
		if (room  != other)
			if (room->pos.X <= other->pos.X + other->m_iRoomSizeX && room->pos.Y <= other->pos.Y + other->m_iRoomSizeY &&
				room->pos.X + room->m_iRoomSizeX >= other->pos.X && room->pos.Y + room->m_iRoomSizeY >= other->pos.Y )
			{
				return true;
			}
	}
	
	return false;
}
