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

void cGame::PrintScreen(HANDLE& hOut)
{
	SetConsoleCursorPosition(hOut, { 0, 0 });
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
	amountOfRooms = 5;
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
			
			isColliding = CheckForRoomCollisions(room);
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
	GeneratePaths();
	delete[] rooms;
}

void cGame::GeneratePaths()
{
	/* Create Paths from room to room
		->Check for rooms in proximity
			->if one room is right on top of/to the side of another room create a path regardless of distance
				->have a random chance to generate paths from the longer paths
					->create a spider web effect with the paths for more dynamic gameplay
			->potentially create diagnol paths? if rooms are directly diagnol form one another
			
			->check the side to create the path from depending on the room that the path is going to (top, bottom, left, right) 
				->open a "door" on one side of the room in any position(unless it is a straight path then ensure that it will still be a straight path) 
				->open a "receiving door" on the room that is being pathed too.
				->create a corner in the paths then create a path to the corner from each room

		->create walls for the paths
	*/

	//collision detection logic:
	/*room->pos.X <= other->pos.X + other->m_iRoomSizeX && room->pos.Y <= other->pos.Y + other->m_iRoomSizeY &&
				room->pos.X + room->m_iRoomSizeX >= other->pos.X && room->pos.Y + room->m_iRoomSizeY >= other->pos.Y )*/
	for (int i = 0; i < amountOfRooms; ++i)
	{
		cRoom& curr = rooms[i];
		for (int z = i + 1; z < amountOfRooms; ++z)
		{
			cRoom& other = rooms[z];

			int pathX;
			int pathY;
			//on top of eachother (straight path qualifies)
			if (curr.pos.X < other.pos.X + other.m_iRoomSizeX - 2 && curr.pos.X + curr.m_iRoomSizeX > other.pos.X)
			{
				if (curr.pos.X >= other.pos.X)
				{
					pathX = RandomNum(curr.pos.X, other.pos.X + other.m_iRoomSizeX);
				}
				else
				{
					pathX = RandomNum(other.pos.X, curr.pos.X + curr.m_iRoomSizeX);
				}

				//current room is below the other room
				if (curr.pos.Y < other.pos.Y)
				{
					for (int y = other.pos.Y + other.m_iRoomSizeY; y < curr.pos.Y; ++y)
					{
						level[(y * m_iSizeX) + pathX - 1].state = '1';
						level[(y * m_iSizeX) + pathX].state = '1';//walkableTile
						level[(y * m_iSizeX) + pathX + 1].state = '1';
					}
				}
				else
				{
					for (int y = other.pos.Y + other.m_iRoomSizeY; y < curr.pos.Y; ++y)
					{
						level[(y * m_iSizeX) + pathX - 1].state = '#';
						level[(y * m_iSizeX) + pathX].state = ' ';//walkableTile 
						level[(y * m_iSizeX) + pathX + 1].state = '#';
					}
				}
			}

			//beside eachother
			if (curr.pos.Y >= other.pos.Y + other.m_iRoomSizeY - 3 || curr.pos.Y + curr.m_iRoomSizeY > other.pos.Y)
			{
				if (curr.pos.Y <= other.pos.Y)
				{
					pathY = RandomNum(curr.pos.Y, other.pos.Y + other.m_iRoomSizeY);
				}
				else
				{
					pathY = RandomNum(other.pos.Y, curr.pos.Y + curr.m_iRoomSizeY);
				}

				//current room is below the other room
				if (curr.pos.X < other.pos.X)
				{
					for (int x = other.pos.X + other.m_iRoomSizeX; x < curr.pos.X; ++x)
					{
						level[(pathY - 1) * m_iSizeX + x].state = '#';
						level[pathY * m_iSizeX + x].state = ' ';//walkableTile
						level[(pathY + 1) * m_iSizeX + x].state = '#';
					}
				}
				else
				{
					for (int x = other.pos.X + other.m_iRoomSizeX; x < curr.pos.X; ++x)
					{
						level[(pathY - 1) * m_iSizeX + x].state = '#';
						level[pathY * m_iSizeX + x].state = ' ';//walkableTile
						level[(pathY + 1) * m_iSizeX + x].state = '#';
					}
				}

			}

		}
	}

	/*cRoom* closestTo = &rooms[0];//dont know what i was thinking
	int roomsNearBy = 0;
	for (int i = 1; i < amountOfRooms; ++i)
	{
		cRoom* curr = &rooms[i];
		if ((curr->pos.X * curr->pos.X) + (curr->pos.Y * curr->pos.Y) < (closestTo->pos.X * closestTo->pos.X) + (closestTo->pos.Y * closestTo->pos.Y))
		{
			closestTo = &rooms[i];
		}
	}*/
}

//returns false if no collisions are detected
bool cGame::CheckForRoomCollisions(cRoom* room)
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





