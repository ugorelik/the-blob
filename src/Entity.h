/***********************************************************************************
 ===================================================================================

*	File name: 		Enity.h
					==========

*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes

*	Description
		Enitity < GameObject
		Entity is an implementation of game object. It mainly holds all of the
		common methods between a Solider, Scientist and Zombie. Entities are further
		specialized to create enemies (not a type). An entity that is not specialized
		will be a tree or a fence. Basically a collidable, stationary object.

*	TODO
		Make an enemy specialization. It does not make sense for a tree to have a lot
		of unused methods.

====================================================================================		
************************************************************************************/
#pragma once

#ifndef ENTITY
#define	ENTITY

#include "GameObject.h"

#define TILE_BLOB 9
#define TILE_BLOB_POSSESS 10
#define TILE_BLOB_POSSESS_READY 41
#define TILE_BLOB_MOVE_10
#define TILE_SOLDIER 0
#define TILE_SCIENTIST 3
#define TILE_ZOMBIE 7
#define TILE_DEAD_SOLDIER 12
#define TILE_DEAD_SCIENTIST 13
#define TILE_DEAD_ZOMBIE 14


#define TYPE_SOLDIER 0
#define TYPE_SCIENTIST 1
#define TYPE_ZOMBIE 2
#define TYPE_CHIP 3

#define STEP_SOLDIER	25
#define STEP_SCIENTIST  35


#define DIRECTION_UP -1
#define DIRECTION_DOWN 1
#define DIRECTION_LEFT -2
#define DIRECTION_RIGHT 2



class Player;

//beginning of class Entity
class	Entity : public GameObject	
{
public:
	Entity();
	Entity(int, int);
	Entity(int, int, int);
	Entity(int, int, int, float);
	Entity(int , int, float , int , int , int );
	virtual void Update(long time);		//The move function

	void ApproximateBlock();	// Get to the nearest tile
	virtual bool CollideAction(Player *);

	int GetType();
	int GetStepAdd();
	int GetDeathFrame();

	void Chase(int time);
	void Flee(int time);
	void Patrol(int time);
	void Search(int time);

	bool CheckDirectionInvalid(int);


protected:
	bool CheckLOS(int x, int y, int direction,int sight); //DIRECTION: 0 = up, 1 = right, 2 = down, 3 = left
	bool CheckLineOfSight(int, int);
	void BlockMove(long);
	void BlockMove(int);

	int _type;
	int _stepAdd;
	int _deathFrame;
	int _moveAmountX;
	int _moveAmountY;
	int aiState;
	int _lastMove;		//time this entity last moved
	int _patDirection;
	int _patLength;
	int _moveDelay;		//time this waits in between actions
	int _stepsMoved;	//number of steps moved in current direction
	D3DXVECTOR3 defaultPos;
}; //End of class Entity	

#endif