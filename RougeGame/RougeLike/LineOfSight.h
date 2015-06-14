#ifndef LINEOFSIGHT_H
#define LINEOFSIGHT_H

#include <windows.h>
class cGame;
class cLOS
{
public:
	cLOS(cGame& l);
	void SetView(COORD pPos);
private:
	cGame& game;
};


#endif //LINEOFSIGHT_H