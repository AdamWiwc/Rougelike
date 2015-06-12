#ifndef PLAYER_H
#define PLAYER_H

#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <string>

#include "Game.h"

class cEntity
{
public:
	cEntity()
	{
	}
	~cEntity(){}
	void Move(byte dir, class cGame game); //takes a direction and checks if it can move there, if it can, updates plyrCords.
	bool TakeDamage(int damage); //if this returns false, thing is dead. 
	void Attack(byte dir);
	COORD GetCords();
	void SetCords(COORD newCords);
	char getCharRep();
	
protected:
	int m_iHealth;
	int m_iDamage;
	COORD m_Cords;
	char m_charRep;
};

class cPlayer : public cEntity
{
public:
	cPlayer() : m_XP(0), m_level(1), m_gold(0), m_XpToNext(15)
	{
		 m_iHealth = m_maxHealth;
		 m_charRep = '@';
	}
	~cPlayer()
	{}

	void pickUpGold(int gold);
	void gainInLevel(int XpGained);
	void TakeDamage(int damage);

	int getHeath();
	int getDamage();
	std::string GetName();
	unsigned int GetXP();
	unsigned int GetLevel();
	unsigned int GetGold();
	unsigned int GetXpToNext();
	int GetMaxHealth();

private:
	std::string m_name;
	unsigned int m_XP;
	unsigned int m_level;
	unsigned int m_gold;
	unsigned int m_XpToNext;
	int m_maxHealth;
};

class cEnemy : public cEntity
{
public:

	cEnemy(int a = 1) : level(a)
	{
		m_charRep = 'G';
	}
	~cEnemy()
	{}

	void Path(class cGame game);
	void TakeDamage(int damage);
	unsigned int GetXp();
	unsigned int GetGold();


private:
	unsigned int level;
	
	
	

};



#endif //PLAYER_H