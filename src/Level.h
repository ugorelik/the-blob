/***********************************************************************************
 ===================================================================================

*	File name: 		Level.h
					=======

*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes

*	Description
		Basic structure for levels. Creates a level based on the number that was 
		passed into the constructor. Has a parser that reads a text file to create a
		level

====================================================================================		
************************************************************************************/

////PREAMBLE
#pragma once
#ifndef LEVEL_H
#define LEVEL_H
#include "Global.h"
#include <vector>
#include "String"

#include "Sprite.h"
using std::vector;
using std::string;
class Entity;
class GameObject;

// Grass
#define TILE_GRASS			16
#define CHAR_TILE_GRASS		'G'

// Tar
#define TILE_TAR			17
#define CHAR_TILE_TAR		'T'

// Roof
#define TILE_ROOF			18
#define CHAR_TILE_ROOF		'R'

// Gravel
#define TILE_GRAVEL			19
#define CHAR_TILE_GRAVEL	'Q'

// White brick
#define TILE_BRICK_W		20
#define CHAR_TILE_BRICK_W	'W'

//Water tile
#define TILE_WATER			38
#define CHAR_TILE_WATER		'C'

#define TILE_TILE			22
#define CHAR_TILE_TILE		'X'

//Tall Tree
#define TILE_TREE			35
#define CHAR_TILE_TREE   	'Y'

//Short Tree
#define TILE_TREE_2			36
#define CHAR_TILE_TREE_2   	'U'

//Fence
#define TILE_FENCE			34			
#define CHAR_TILE_FENCE   	'F'

//Orange Block
#define TILE_BLOCK			37			
#define CHAR_TILE_BLOCK   	'O'

//UNDERGROUND

//Bottles
#define TILE_BOTTLES		33		
#define CHAR_TILE_BOTTLES   'B'

//Fridge
#define TILE_FRIDGE					32			
#define CHAR_TILE_FRIDGE   			'Z'

//UPPIPE
#define TILE_UPPIPE					27			
#define CHAR_TILE_UPPIPE   			'P'

//UP PIPE TURN 
#define TILE_UPPIPE_TURN			28			
#define CHAR_TILE_UPPIPE_TURN   	'L'

//SIDE PIPE
#define TILE_SIDEPIPE				29			
#define CHAR_TILE_SIDE_PIPE			'S'

//SIDE PIPE END
#define TILE_SIDEPIPE_END			30			
#define CHAR_TILE_SIDEPIPE_END   	'N'

//UPPIPE END
#define TILE_UPPIPE_END				31			
#define CHAR_TILE_UPPIPE_END	   	'D'


//BONUS TILES

//Mike Tile
#define TILE_MIKE			38			
#define CHAR_TILE_MIKE   	'M'

//Eric Tile
#define TILE_ERIC			39			
#define CHAR_TILE_ERIC   	'E'

//Uri Tile
#define TILE_URI			40			
#define CHAR_TILE_URI   	'I'




////CLASS DEFINITION
class Level{
	friend class Game;

	private:
		vector<GameObject *>     * _resetList;
		vector<Entity *>     * _entityList;
		vector<Entity *>     * _enemyList;
		vector<GameObject *> * _staticList;
		vector<GameObject *> * _backgroundList;
		int id;
		static int chipId;
		
		bool isComplete;
		D3DXVECTOR2 _defaultPlayerPos;

		SPRITE grass;
		SPRITE whiteTile, soldierTile;

		void CreateLevel1();
		void CreateLevel2();
		void CreateLevel3();
		void CreateLevel4();
		void CreateLevel5();
		void CreateLevel6();
		void CreateLevel7();
		void CreateLevel8();
		void CreateLevel9();
	private:
		void ParseFile(int levelNumber);
		void ParseFile(int levelNumber, char nom);
		string _levelName;

	public: 
		vector<GameObject *> * GetResetList();
		vector<Entity *> * GetEntityList();
		vector<Entity *> * GetEnemyList();
		vector<GameObject *> * GetBackgroundList();
		vector<GameObject *> * GetStaticList();
		string GetLevelName();
		

		D3DXVECTOR2 GetDefaultPlayerPos();
		void SetDefaultPosition(int x, int y);

	public:
		Level(int i);
		void CreateLevel(int);
		void setComplete(bool);
		bool _isComplete();
		

};

#endif