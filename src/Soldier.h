/***********************************************************************************
 ===================================================================================

*	File name: 		Soldier.h < Entity
					==========
*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes 

*	Description
		All that distinguishes the soldier from the zombies and the scientist
====================================================================================		
************************************************************************************/
#pragma once
#ifndef SOLDIER_H
#define SOLDIER_H

#include "Entity.h"

class Soldier : public Entity {
private:
	void RunAI(int);
	bool _moved;
	

public:
	Soldier();
	//Soldier(int, int, float);
	Soldier(int x, int y, float heading, int moveDelay = 5000, int patDirection = 0 , int patLength = 0);
	void Update(long time);
	bool CollideAction(Player *);
};

#endif