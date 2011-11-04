/***********************************************************************************
 ===================================================================================

*	File name: 		TutorialChip.h < Entity
					==========
*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes 

*	Description
		Specific type of chip
====================================================================================		
************************************************************************************/

#pragma once
#ifndef TUTORIAL_CHIP_H
#define TUTORIAL_CHIP_H

#include "Entity.h"
#include <string>

using std::string;

class Player;

class TutorialChip : public Entity
{
private:
	
	string * _message;
	int _id;

public:

	bool CollideAction(Player *);

	TutorialChip(int, int,int);
	~TutorialChip();
};

#endif