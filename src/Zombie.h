/***********************************************************************************
 ===================================================================================

*	File name: 		Zombie.cpp < Entity
					==========
*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes 

*	Description
		Zombie code that details its AI and movement characteristics as well as
		collision event.
====================================================================================		
************************************************************************************/
#pragma once
#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Entity.h"

class Zombie : public Entity {
	private:
		void RunAI(int);
		int _scentRadius;
	public:
		Zombie();
		Zombie(int x, int y, float heading, int moveDelay = 5000, int patDirection = 0 , int patLength = 0);
		void Update(long time);
		bool CollideAction(Player *);
		bool ZombieLOS();
};

#endif

