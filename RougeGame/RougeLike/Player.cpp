#include "Player.h"


void Player::Move(byte dir, class cGame game)
{
	//directions: 1: north, 2: East, 3: South, 4: West
	COORD newCords = plyrCords;

	
	switch (dir)
	{
	case 1:
		newCords.Y--;
		break;
	case 2:
		newCords.X++;
		break;
	case 3:
		newCords.Y++;
		break;
	case 4:
		newCords.X--;
		break;
	default:
		assert("Player::Move dir unsuported.");
		break;
	}

	if (true) //check with the map to see if those cors are free.
	{
		plyrCords = newCords;
	}
	else
	{
		//maybe add a message system later where we can send a string and it will print it in the event thing
		//send "Something blocks your way."
	}
}

bool Player::TakeDamage(int damage)
{
	health -= damage;

	if (health <= 0)
	{
		//player has died. do whatever we are going to do.
		return false;
	}
	else if (damage >= 0)
	{
		//Print to event log: "Ouch!"
	}
	else
	{
		//print to event log: "You feel rejuvenated."
		if (health > MAXHEALTH)
			health = MAXHEALTH;
	}
	return true;
}

COORD Player::GetCords()
{
	return (plyrCords);
}

void Player::SetCords(COORD newCords)
{
	plyrCords = newCords;
}
