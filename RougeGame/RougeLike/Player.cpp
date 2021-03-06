#include "Player.h"
#include <stdlib.h>
#include "rouge.h"
//-----------------------------------------------------------
//	Overall entity stuff
//-----------------------------------------------------------

bool cEntity::Move(byte dir, class cGame *game)
{
	//directions: 1: north, 2: East, 3: South, 4: West
	COORD newCords = m_Cords;

	
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

	if (game->GetTile(newCords.X, newCords.Y).state != '#') //check with the map to see if those cors are free.
	{
		m_Cords = newCords;
		return true;
	}
    else
	{
		//maybe add a message system later where we can send a string and it will print it in the event thing
		//send "Something blocks your way."
		return false;
	}
}
COORD cEntity::GetCords()
{
	return (m_Cords);
}
void cEntity::SetCords(COORD newCords)
{
	m_Cords = newCords;
}

char cEntity::getCharRep()
{
	return m_charRep;
}

//-----------------------------------------------------------
//	Player stuff
//-----------------------------------------------------------

void cPlayer::pickUpGold(int gold)
{
	m_gold += gold;
	//send message to event system "You found X gold, wow shiny"
}
void cPlayer::gainInLevel(int XpGained)
{
	m_XP += XpGained;

	if(m_XP >= m_XpToNext) //player has leveled up
	{
		//Send Message "You feel Stronger now.";
		m_iDamage++;
		m_maxHealth += 10;
		TakeDamage(-50);
	}
}
void cPlayer::TakeDamage(int damage)
{
	m_iHealth -= damage;

	if(m_iHealth > m_maxHealth)
	{
		m_iHealth = m_maxHealth;
	}

	if (m_iHealth <= 0)
	{
		//do the death stuff
	}
	return;
}

int cPlayer::getHeath()
{
	return 0;
	//return m_iHealth;
}
int cPlayer::getDamage()
{
	return m_iDamage;
}
std::string cPlayer::GetName()
{
	return "John";
	//return m_name;
}
unsigned int cPlayer::GetXP()
{
	return 0;
	//return m_XP;
}
unsigned int cPlayer::GetLevel()
{
	return 0;
	//return m_level;
}
unsigned int cPlayer::GetGold()
{
	return 0;
	//return m_gold;
}
unsigned int cPlayer::GetXpToNext()
{
	return 0;
//	return m_XpToNext;
}
int cPlayer::GetMaxHealth()
{
	return 0;
	//return m_maxHealth;
}

//------------------------------------------------------------
// Enemy Stuff
//-----------------------------------------------------------

void cEnemy::TakeDamage(int damage)
{
	m_iHealth -= damage;

	if (m_iHealth <= 0)
	{
		//do the death stuff
	}
	return;
}

unsigned int cEnemy::GetXp()
{
	unsigned int xp = 1 << level;
	return xp;
}
unsigned int cEnemy::GetGold()
{
	unsigned int gold;
	gold = (rand() % 8) * level;
	return gold;

}

void
cEnemy::Path(game_state *GameState)
{
	bool32 Moved = false;

	COORD PlayerPos = GameState->Player->GetCords();
	if(abs(PlayerPos.X - PlayerPos.X) < 10 && abs(PlayerPos.Y - PlayerPos.Y) < 10)
	{
		if(PlayerPos.X - m_Cords.X > 1 || PlayerPos.Y - m_Cords.Y > 1)
		{
			// Attack
			GameState->Player->TakeDamage(3);
		}
		else
		{
			// Move
			uint32 Attempt = 0;
			while(!Moved && Attempt < 4)
			{
				if(m_Cords.Y > PlayerPos.Y)
				{
					Moved = Move(1, GameState->CurrentLevel);
				}
				else if(m_Cords.X > PlayerPos.X)
				{
					Moved = Move(4, GameState->CurrentLevel);
				}
				else if(m_Cords.Y < PlayerPos.Y)
				{
					Moved = Move(3, GameState->CurrentLevel);
				}
				else if(m_Cords.X < PlayerPos.X)
				{
					Moved = Move(2, GameState->CurrentLevel);
				}
				++Attempt;
			}
		}
	}
}