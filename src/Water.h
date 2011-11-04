/***********************************************************************************
 ===================================================================================

*	File name: 		Water.h < Entity
					==========
*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes 

*	Description
		Alters the player's move speed
====================================================================================		
************************************************************************************/
#pragma once
#ifndef WATER_H
#define WATER_H

#include "Entity.h"
#include <string>

using std::string;

class Player;

class Water : public Entity
{
private:
	
	string * _message;
	int _id;

public:

	bool CollideAction(Player *);

	Water(int, int,int);
	~Water();
};

#endif