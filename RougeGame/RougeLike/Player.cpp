#include "Player.h"

//-----------------------------------------------------------
//	Overall entity stuff
//-----------------------------------------------------------

void cEntity::Move(byte dir, class cGame game)
{
	//directions: 1: north, 2: East, 3: South, 4: West
	COORD newCords = m_Cords;

	
	switch (dir)
	{
	case VK_UP:
		newCords.Y--;
		break;
	case VK_RIGHT:
		newCords.X++;
		break;
	case VK_DOWN:
		newCords.Y++;
		break;
	case VK_LEFT:
		newCords.X--;
		break;
	default:
		assert("Player::Move dir unsuported.");
		break;
	}

	if (true) //check with the map to see if those cors are free.
	{
		m_Cords = newCords;
	}
	else
	{
		//maybe add a message system later where we can send a string and it will print it in the event thing
		//send "Something blocks your way."
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
	return m_iHealth;
}
int cPlayer::getDamage()
{
	return m_iDamage;
}
std::string cPlayer::GetName()
{
	return m_name;
}
unsigned int cPlayer::GetXP()
{
	return m_XP;
}
unsigned int cPlayer::GetLevel()
{
	return m_level;
}
unsigned int cPlayer::GetGold()
{
	return m_gold;
}
unsigned int cPlayer::GetXpToNext()
{
	return m_XpToNext;
}
int cPlayer::GetMaxHealth()
{
	return m_maxHealth;
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