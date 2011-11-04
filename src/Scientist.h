/***********************************************************************************
 ===================================================================================

*	File name: 		Scientist.h < Entity
					==========
*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes 

*	Description
		The Scientist class contains scientist specific movement characteristics.
		All that makes the scientist different from soldiers and zombies.
====================================================================================		
************************************************************************************/
#pragma once
#ifndef SCIENTIST_H
#define SCIENTIST_H

#include "Entity.h"

class Scientist : public Entity{
private:
	void RunAI(int time);
public:
	Scientist();
	Scientist(int x, int y, float heading, int moveDelay = 8000, int patDirection = 0 , int patLength = 0);
	//void Update();
	void Update(long time);
	bool CollideAction(Player *);
};




#endif