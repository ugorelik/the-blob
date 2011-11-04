/***********************************************************************************
 ===================================================================================

*	File name: 		Chip.h < Entity
					==========
*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes 

*	Description	
		When collided with, the chip pops up a new screen and dissapears
====================================================================================		
************************************************************************************/
#pragma once
#ifndef CHIP_H
#define CHIP_H

#include "Entity.h"
#include <string>

using std::string;

class Player;

class Chip : public Entity
{
private:
	
	string * _message;
	int _id;

public:

	bool CollideAction(Player *);

	Chip(int, int,int);
	~Chip();
};

#endif