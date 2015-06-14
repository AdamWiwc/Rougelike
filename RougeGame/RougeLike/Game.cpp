#include <stdlib.h>
#include <stdio.h>

#include "Game.h"
#include "Player.h"

#include <assert.h>
int RandomNum(const int min, const int max)
{
	assert(min <= max);
	if (max > min)
		return rand() % (max - min) + min;
	return min;
}

int RandomNum(std::pair<int, int> range)
{
	assert(range.first <= range.second);
	if (range.first != range.second)
		return rand() % (range.second - range.first) + range.first;
	return range.first;
}
cGame::cGame(int sizeX, int sizeY)
	: m_iSizeX(sizeX)
	, m_iSizeY(sizeY)
{
	level = new Tile[m_iSizeX * m_iSizeY];
}


void cGame::PrintLevel(cPlayer& player, HANDLE& hOut)
{
	for (int y = 0; y < m_iSizeY; ++y)
	{
		for (int x = 0; x < m_iSizeX; ++x)
		{
			COORD& pPos = player.GetCords();
			Tile tile = level[(m_iSizeX * y) + x];
			if (pPos.X == x && y == pPos.Y)
			{
				printf("%c", player.getCharRep());
			}
			else if (tile.IsVisible)
			{
				printf("%c", tile.state);
			}
			else if (tile.IsRevealed && tile.state == '#')
			{
				printf("#");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}

void cGame::GenerateLevel(cPlayer& player)
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
	rooms[0].PutPlayerInRoom(player);//puts player in the first room; 
	delete[] rooms;
}


bool cGame::CheckForRoomCollisions(cRoom* room)
{
	for (int i = 0; i < amountOfRooms; ++i)
	{
		cRoom* other = &rooms[i];
		if (room != other)
		{
			if (room->pos.X <= other->pos.X + other->m_iRoomSizeX && room->pos.X + room->m_iRoomSizeX >= other->pos.X 
				&& room->pos.Y <= other->pos.Y + other->m_iRoomSizeY && room->pos.Y + room->m_iRoomSizeY >= other->pos.Y)
			{//collision detected
				return true;
			}
		}
	}
	return false;
}

void cGame::GeneratePaths()
{
	/* Create Paths from room to room
		->Check for rooms in proximity --
			->if one room is right on top of/to the side of another room create a path regardless of distance 
			->have a random chance to generate paths from the longer paths
			->create a spider web effect with the paths for more dynamic gameplay
		->potentially create diagnol paths? if rooms are directly diagnol from one another

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
		cRoom* currentRoom = &rooms[i];
		std::vector<cRoom*> horPathableRooms = FindValidHorRooms(currentRoom);
		std::vector<cRoom*> verPathableRooms = FindValidVerRooms(currentRoom);

		std::pair<int, int> range = { 0, 0 };
		int paths = horPathableRooms.size();
		for (int i = 0; i < paths; ++i)
		{
			cRoom* other = horPathableRooms[i];
			if (GetHorPathableRange(currentRoom, other, range))
			{
				currentRoom->IsConnected = true;
				other->IsConnected = true;
				//generate RandomNumber between the range, then put the path into the room
				int posY = RandomNum(range);
				for (int x = currentRoom->pos.X + currentRoom->m_iRoomSizeX - 1; x < other->pos.X + 1; ++x)
				{
					level[(posY * m_iSizeX) + x].state = ' ';
					level[(posY * m_iSizeX) + x].IsPath = true;


					if (!level[((posY - 1) * m_iSizeX) + x].IsPath)
					{
						level[((posY - 1) * m_iSizeX) + x].state = '1';
					}
					
					if (!level[((posY + 1) * m_iSizeX) + x].IsPath)
					{
						level[((posY + 1) * m_iSizeX) + x].state = '2';
					}
				}
			}
		}

		range = { 0, 0 };
		paths = verPathableRooms.size();
		for (int i = 0; i < paths; ++i)
		{
			cRoom* other = verPathableRooms[i];
			if (GetVerPathableRange(currentRoom, other, range))
			{
				currentRoom->IsConnected = true;
				other->IsConnected = true;
				//generate RandomNumber between the range, then put the path into the room
				int posX = RandomNum(range);
				for (int y = currentRoom->pos.Y + currentRoom->m_iRoomSizeY - 1; y < other->pos.Y + 1; ++y)
				{
					level[(y * m_iSizeX) + posX].state = ' ';
					level[(y * m_iSizeX) + posX].IsPath = true;
				
					if (!level[(y * m_iSizeX) + posX - 1].IsPath)
					{
						level[(y * m_iSizeX) + posX - 1].state = '3';
					}
					
					if (!level[(y * m_iSizeX) + posX + 1].IsPath)
					{
						level[(y * m_iSizeX) + posX + 1].state = '4';
					}
				}
			}
		}
		
	}
}

//returns all the rooms that are below the current room and are within the x range to path to
std::vector<cRoom*> cGame::FindValidVerRooms(cRoom* currentRoom)
{
	std::vector<cRoom*> validRooms;
	for (int i = 0; i < amountOfRooms; ++i)
	{
		cRoom* other = &rooms[i];
		if (currentRoom != other)
		{
			//check if vertical path is possible
			if (currentRoom->pos.X < other->pos.X + other->m_iRoomSizeX - 2 && currentRoom->pos.X + currentRoom->m_iRoomSizeX > other->pos.X + 2)
			{
				if (currentRoom->pos.Y < other->pos.Y)
				{
					validRooms.push_back(other);
				}
			}
		}//currRoom != other
	}//i < amountOfRooms
	return validRooms;
}

//returns all the rooms that are to the right of the current room and are withing the the y range to path to
std::vector<cRoom*> cGame::FindValidHorRooms(cRoom* currentRoom)
{
	std::vector<cRoom*> validRooms;
	for (int i = 0; i < amountOfRooms; ++i)
	{
		cRoom* other = &rooms[i];
		if (currentRoom != other)
		{
			//checks if there is a possible horizontal path
			if (currentRoom->pos.Y < (other->pos.Y + other->m_iRoomSizeY - 2) && (currentRoom->pos.Y + currentRoom->m_iRoomSizeY) > (other->pos.Y + 2))
			{
				//only add it if the room being pathed to is to the right of the current room(prevents multiple paths to the same 2 rooms)
				if (currentRoom->pos.X < other->pos.X)
				{
					//Horizontal path is possible
					validRooms.push_back(other);
				}
			}
		}//currRoom != other
	}//i < amountOfRooms
	return validRooms;
}

//FOR HORIZONTAL
//returns true if there is nothing blocking the path, and sets the range that a path can be made in
bool cGame::GetHorPathableRange(cRoom* currentRoom, cRoom* other, std::pair<int, int>& range)
{	
	range.first = (currentRoom->pos.Y <= other->pos.Y)
		? other->pos.Y + 1 : currentRoom->pos.Y + 1;
	
	range.second = (currentRoom->pos.Y + currentRoom->m_iRoomSizeY <= other->pos.Y + other->m_iRoomSizeY)
		? currentRoom->pos.Y + currentRoom->m_iRoomSizeY - 1 : other->pos.Y + other->m_iRoomSizeY - 1;

	return CheckForHorRoomPathCollisions(currentRoom, other, range);
}

//FOR VERTICAL
//returns true if there is nothing blocking the path, and sets the range that a path can be made in
bool cGame::GetVerPathableRange(cRoom* currentRoom, cRoom* other, std::pair<int, int>& range)
{
	range.first = (currentRoom->pos.X <= other->pos.X)
		? other->pos.X + 1 : currentRoom->pos.X + 1;

	range.second = (currentRoom->pos.X + currentRoom->m_iRoomSizeX <= other->pos.X + other->m_iRoomSizeX)
		? currentRoom->pos.X + currentRoom->m_iRoomSizeX - 1 : other->pos.X + other->m_iRoomSizeX - 1;

	return CheckForVerRoomPathCollisions(currentRoom, other, range);
}


//returns true if there is nothing completely blocking the horizontal path from the first room to the second, and modifies the range accordingly if a room is partially blocking the path
bool cGame::CheckForHorRoomPathCollisions(cRoom* currentRoom, cRoom* other, std::pair<int, int>& range)
{
	for (int i = 0; i < amountOfRooms; ++i)
	{
		cRoom* temp = &rooms[i];
		if (temp != currentRoom && temp != other)
		{
			if (temp->pos.X < other->pos.X && temp->pos.X > currentRoom->pos.X)
			{//this rooms X value is in between the two other rooms X values so it has a potential to block the path
				if (temp->pos.Y <= range.second && temp->pos.Y + temp->m_iRoomSizeY >= range.first)
				{//this room is impeeding on the potential paths
					if (temp->pos.Y <= range.first && temp->pos.Y + temp->m_iRoomSizeY >= range.second)
					{//this room completely blocks the current potential paths
						return false;
					}
					else if (temp->pos.Y <= range.first)
					{//the room is impeeding on the top portion of the possible range
						range.first = temp->pos.Y + temp->m_iRoomSizeY;
					}
					else
					{//the room is impeeding on the bottom portion of the possible range
						range.second = temp->pos.Y;
					}
				}
			}
		}
	}
	return true;
}



//returns true if there is nothing completely blocking the horizontal path from the first room to the second, and modifies the range accordingly if a room is partially blocking the path
bool cGame::CheckForVerRoomPathCollisions(cRoom* currentRoom, cRoom* other, std::pair<int, int>& range)
{
	for (int i = 0; i < amountOfRooms; ++i)
	{
		cRoom* temp = &rooms[i];
		if (temp != currentRoom && temp != other)
		{
			if (temp->pos.Y < other->pos.Y && temp->pos.Y > currentRoom->pos.Y)
			{//this rooms Y value is in between the two other rooms Y values so it has a potential to block the path
				if (temp->pos.X <= range.second && temp->pos.X + temp->m_iRoomSizeX >= range.first)
				{//this room is impeeding on the path
					if (temp->pos.X <= range.first && temp->pos.X + temp->m_iRoomSizeX >= range.second)
					{//this room completely blocks the current path
						return false;
					}
					else if (temp->pos.X <= range.first)
					{//the room is impeeding on the top portion of the possible range
						range.first = temp->pos.X + temp->m_iRoomSizeX + 1;
					}
					else
					{//the room is impeeding on the bottom portion of the possible range
						range.second = temp->pos.X - 1;
					}
				}
			}
		}
	}
	return true;
}