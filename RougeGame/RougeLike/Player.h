#ifndef PLAYER_H
#define PLAYER_H

#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include "Game.h"

#define MAXHEALTH 100

class Player
{
public:
	Player() : health(MAXHEALTH)
	{
	}
	~Player(){}
	void Move(byte dir, class cGame game); //takes a direction and checks if it can move there, if it can, updates plyrCords.
	bool TakeDamage(int damage); //if this returns false, player is dead. 
	void Attack(byte dir);
	COORD GetCords();
	void SetCords(COORD newCords);

private:
	int health;
	unsigned int damage;
	COORD plyrCords;
	

};


#endif //PLAYER_H