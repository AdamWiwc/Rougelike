#include <windows.h>

class Enemy
{
public:

	Enemy(int a = 10, int b = 2) :health(a), damage(b)
	{}
	~Enemy(){}

	void randMove();
	void TakeDamage();
	COORD GetCords();
	void setCords();


private:

	int health;
	int damage;


};