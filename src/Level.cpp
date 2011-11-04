#include "Level.h"

#include "Entity.h"
#include "GameObject.h"
#include "Soldier.h"
#include "Zombie.h"
#include "Scientist.h"
#include "Chip.h"
#include "Water.h"
#include "TutorialChip.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int Level::chipId = 1;

Level::Level(int i){
	
	// Convert to string

	_resetList = new vector<GameObject *>();
	_enemyList = new vector<Entity *>();
	_entityList = new vector<Entity *>();
	_backgroundList = new vector<GameObject *>();

	// Create the level
	ParseFile(i);
	ParseFile(i, 'c');

	isComplete = false;
	CreateLevel(i);

}

void Level::CreateLevel(int i)
{
	if(i==1){
		//_defaultPlayerPos = D3DXVECTOR2(14, 1);
		_levelName = "Courtyard";
		CreateLevel1();
	}
	else if (i == 2) {
		_defaultPlayerPos = D3DXVECTOR2(2,3);
		_levelName = "Laboratory";
		CreateLevel2();
	}
	else if (i==3) {
		//_defaultPlayerPos = D3DXVECTOR2(2,2);
		_levelName = "Forest";
		CreateLevel3(); 
	}
	else if (i== 4){
		//_defaultPlayerPos = D3DXVECTOR2(15, 1);
		_levelName = "Orchard";
		CreateLevel4();
	}
	else if (i== 5){
		//_defaultPlayerPos = D3DXVECTOR2(1, 16);
		_levelName = "Garden";
		CreateLevel5();
	}
	else if (i== 6){
		//_defaultPlayerPos = D3DXVECTOR2(15, 22);
		_levelName = "Testing Grounds";
		CreateLevel6();
	}
	else if (i== 7){
		//_defaultPlayerPos = D3DXVECTOR2(1, 10);
		_levelName = "River";
		CreateLevel7();
	}
	else if (i== 8){
		//_defaultPlayerPos = D3DXVECTOR2(34, 8);
		_levelName = "Spiral Maze";
		CreateLevel8();
	}
	else if (i== 9){
		//_defaultPlayerPos = D3DXVECTOR2(1,8);
		_levelName = "Incomplete (BOSS)";
		CreateLevel9();
	}
}

void Level::CreateLevel1(){

	if (!_isComplete())
	{
	//Chip
	_enemyList->push_back(new Chip(7,7,2));
	_enemyList->push_back(new Chip(34,19,3));
	}

	//Soldiers
	_enemyList->push_back(new Soldier(7, 3, 270,2600,DIRECTION_LEFT,5));
	_enemyList->push_back(new Soldier(6, 6, 180));
	_enemyList->push_back(new Soldier(9, 18, 90));
	_enemyList->push_back(new Soldier(9, 14, 90));
	_enemyList->push_back(new Soldier(12, 9, 90, 1600, DIRECTION_RIGHT,7));
	_enemyList->push_back(new Soldier(25, 14, 180, 2000, DIRECTION_UP, 6));
	
	_enemyList->push_back(new Soldier(27, 4, 180));
	_enemyList->push_back(new Soldier(34, 4, 180));
	_enemyList->push_back(new Soldier(27, 15, 0));
	_enemyList->push_back(new Soldier(34, 15, 0));
		

	//Caged Zombies
	_enemyList->push_back(new Zombie(29, 12, 90, 3400, DIRECTION_RIGHT, 3));
	_enemyList->push_back(new Zombie(32, 10, 270, 13000, DIRECTION_DOWN, 2));
	_enemyList->push_back(new Zombie(27, 8, 180, 1200, DIRECTION_LEFT, 3));
	_enemyList->push_back(new Zombie(31, 6, 0, 800, DIRECTION_DOWN, 6));
	_enemyList->push_back(new Zombie(30, 12, 0, 1100, DIRECTION_RIGHT, 2));
	_enemyList->push_back(new Zombie(28, 6, 0, 4000, DIRECTION_DOWN, 5));
	_enemyList->push_back(new Zombie(34, 10, 90, 1000, DIRECTION_LEFT, 3));
	_enemyList->push_back(new Zombie(29, 8, 270, 500, DIRECTION_UP, 3));
	_enemyList->push_back(new Zombie(33, 13, 180, 2100, DIRECTION_LEFT, 3));

	//Scientist
	_enemyList->push_back(new Scientist(30, 15, 0));
	_enemyList->push_back(new Scientist(17, 6, 90));
	_enemyList->push_back(new Scientist(20, 6, 270));
	_enemyList->push_back(new Scientist(18, 16, 90));
	_enemyList->push_back(new Scientist(33, 15, 0));

}

//Starting Level
void Level::CreateLevel2() {

	//Scientist
	_enemyList->push_back(new Scientist(23, 8, 90));
	_enemyList->push_back(new Scientist(6, 11, 90));

	_enemyList->push_back(new Scientist(2, 15, 0));
	_enemyList->push_back(new Scientist(17, 16, 90));
	//_enemyList->push_back(new Scientist(10, 8, 0));
	_enemyList->push_back(new Scientist(5, 16, 90,2000, DIRECTION_UP,2));
	_enemyList->push_back(new Scientist(30, 15, 0));
	
	_enemyList->push_back(new Scientist(28, 6, 270, 800, DIRECTION_RIGHT, 1));
	_enemyList->push_back(new Scientist(15, 1, 0, 1000, DIRECTION_DOWN, 4));
	_enemyList->push_back(new Scientist(13, 15, 0, 1500, DIRECTION_LEFT, 3));

	_enemyList->push_back(new Soldier(31, 19, 180));
	_enemyList->push_back(new Soldier(30, 19, 270));
	_enemyList->push_back(new Soldier(31, 22, 0));
	_enemyList->push_back(new Soldier(30, 22, 270));

	_enemyList->push_back(new Soldier(33, 7, 0));
	_enemyList->push_back(new Zombie(35, 3, 270));
	_enemyList->push_back(new Zombie(35, 4, 90));
	_enemyList->push_back(new Zombie(33, 4, 180));

	if (!_isComplete())
	{
	//chips
	_enemyList->push_back(new Chip(33,3,1));
	_enemyList->push_back(new TutorialChip(2,5,-1));
	_enemyList->push_back(new TutorialChip(20,10,-2));
	_enemyList->push_back(new TutorialChip(23,15,-3));
	_enemyList->push_back(new TutorialChip(33,10,-4));
	}

}

//Third Level 
void Level::CreateLevel3() {
	
	if (!_isComplete())
	{
		//Chip
		_enemyList->push_back(new Chip(17,7,chipId++));
		_enemyList->push_back(new Chip(33,20,chipId++));
		_enemyList->push_back(new Chip(33,3,chipId++));
	}

	//ZOMBIES
	_enemyList->push_back(new Zombie(2, 12, 90, 1000, DIRECTION_RIGHT, 4));
	_enemyList->push_back(new Zombie(3, 10, 270, 3000, DIRECTION_LEFT, 6));
	_enemyList->push_back(new Zombie(7, 8, 180, 1500, DIRECTION_DOWN, 8));
	_enemyList->push_back(new Zombie(31, 6, 0, 500, DIRECTION_DOWN, 2));
	_enemyList->push_back(new Zombie(30, 12, 0, 250, DIRECTION_LEFT, 2));
	_enemyList->push_back(new Zombie(18, 6, 0, 350, DIRECTION_DOWN, 4));
	_enemyList->push_back(new Zombie(12, 11, 1900, DIRECTION_LEFT, 3));
	_enemyList->push_back(new Zombie(9, 8, 270, 1600, DIRECTION_RIGHT, 4));
	_enemyList->push_back(new Zombie(33, 13, 180, 900, DIRECTION_DOWN, 3));
	
	_enemyList->push_back(new Zombie(33, 19, 90, 1000, DIRECTION_LEFT, 3));
	_enemyList->push_back(new Zombie(31, 20, 270, 550, DIRECTION_DOWN, 3));
	_enemyList->push_back(new Zombie(30, 21, 180, 1800, DIRECTION_DOWN,2));

	

	//Soldiers
	_enemyList->push_back(new Soldier(13, 3, 180, 2000, DIRECTION_DOWN, 3));
	_enemyList->push_back(new Soldier(13, 22, 270));
	_enemyList->push_back(new Soldier(18, 22, 90));

	
	_enemyList->push_back(new Soldier(27, 16, 90, 3500, DIRECTION_LEFT, 4));


}

//The Orchard
void Level::CreateLevel4() {


	//Scientist
	_enemyList->push_back(new Scientist(4, 2, 270));

	//Soldier
	_enemyList->push_back(new Soldier(17, 8, 180, 2000, DIRECTION_DOWN, 4));
	
	_enemyList->push_back(new Soldier(21, 9, 90));
	_enemyList->push_back(new Soldier(21, 6, 90));
	_enemyList->push_back(new Soldier(23, 18, 270));
	_enemyList->push_back(new Soldier(23, 15, 270));

	_enemyList->push_back(new Soldier(5, 10, 90));
	_enemyList->push_back(new Soldier(7, 16, 270));

	if (!_isComplete())
	{
	//chips
	_enemyList->push_back(new Chip(5,15,3));
	_enemyList->push_back(new Chip(21,12,4));
	}

}

//The Garden
void Level::CreateLevel5()
{
	//Add Zombies
	_enemyList->push_back(new Zombie(28, 12, 90, 1000, DIRECTION_RIGHT, 3));
	_enemyList->push_back(new Zombie(18, 10, 270, 1500, DIRECTION_DOWN, 4));
	_enemyList->push_back(new Zombie(22, 8, 180, 2000, DIRECTION_RIGHT, 5));
	_enemyList->push_back(new Zombie(26, 9, 180, 500, DIRECTION_DOWN, 2));
	_enemyList->push_back(new Zombie(23, 11, 180, 1800, DIRECTION_LEFT, 3));

	
	//SOLDIERS
	//Bottom
	_enemyList->push_back(new Soldier(5, 22, 0));
	_enemyList->push_back(new Soldier(8, 21, 180));
	_enemyList->push_back(new Soldier(13, 19, 0));
	_enemyList->push_back(new Soldier(17, 19, 0));
	//Top
	_enemyList->push_back(new Soldier(25, 2, 0));
	_enemyList->push_back(new Soldier(22, 1, 180));
	_enemyList->push_back(new Soldier(13, 4, 180));
	_enemyList->push_back(new Soldier(17, 4, 180));
	

	_enemyList->push_back(new Soldier(13, 11, 0));

		//Scientist
	//Bottom
	_enemyList->push_back(new Scientist(13, 21, 90));
	_enemyList->push_back(new Scientist(17, 21, 270));
	

	_enemyList->push_back(new Scientist(30, 16, 180));

	if (!_isComplete())
	{
		//chips
		_enemyList->push_back(new Chip(1,21,chipId++));
		_enemyList->push_back(new Chip(34,2,chipId++));
	}
}
//The Training Gound
void Level::CreateLevel6()
{
	if (!_isComplete())
	{
		//chips
		_enemyList->push_back(new Chip(2,7,chipId++));
		_enemyList->push_back(new Chip(33,1,chipId++));
	}
	//Scientiest
	_enemyList->push_back(new Scientist(30, 15, 90));
	
	//Zombies
	_enemyList->push_back(new Zombie(31, 2, 90, 1000, DIRECTION_LEFT));
	_enemyList->push_back(new Zombie(28, 1, 270, 500, DIRECTION_DOWN, 2));
	_enemyList->push_back(new Zombie(33, 2, 0, 750, DIRECTION_LEFT, 3));
	_enemyList->push_back(new Zombie(32, 7, 180, 400, DIRECTION_DOWN, 3));

	
	//Soldier
	
	_enemyList->push_back(new Soldier(3, 7, 180));
	_enemyList->push_back(new Soldier(3, 10, 0));
	_enemyList->push_back(new Soldier(3, 11, 180));
	_enemyList->push_back(new Soldier(3, 14, 0));
	
	_enemyList->push_back(new Soldier(6, 9, 90,2000,DIRECTION_RIGHT,2));
}
//Thwe River
void Level::CreateLevel7()
{
	//Zombies
	_enemyList->push_back(new Zombie(31, 2, 90));
	_enemyList->push_back(new Zombie(28, 4, 270));
	_enemyList->push_back(new Zombie(33, 3, 180));

	//Soldier
	
	_enemyList->push_back(new Soldier(5, 18, 0));
	_enemyList->push_back(new Soldier(8, 21, 180));
	_enemyList->push_back(new Soldier(13, 16, 90));
	_enemyList->push_back(new Soldier(7, 8, 270));
	
	
	_enemyList->push_back(new Soldier(25, 3, 0));

	if (!_isComplete())
	{
		//Chip
		_enemyList->push_back(new Chip(34,1,chipId++));
		_enemyList->push_back(new Chip(20,12,chipId++));
	}

}
//Spiral Maze
void Level::CreateLevel8()
{
	//Soldiers
	_enemyList->push_back(new Soldier(13, 1, 180));
	_enemyList->push_back(new Soldier(17, 1, 180));
	
	if (!_isComplete())
	{	
		//chips
		_enemyList->push_back(new Chip(15,11,chipId++));
		_enemyList->push_back(new Chip(1,22,chipId++));
	}
	
	//Add Zombies
	_enemyList->push_back(new Zombie(3, 15, 180));
	_enemyList->push_back(new Zombie(10, 20, 0));
	_enemyList->push_back(new Zombie(32, 18, 270));

}
//BOSS LEVEL
void Level::CreateLevel9()
{


}


// --------------------------------------------------------------------------
// Parse
// --------------------------------------------------------------------------
void Level::ParseFile(int levelNumber)
{

	// Convert the level name to a string
	string levelNumStr;
	std::stringstream out;
	out << levelNumber;
	levelNumStr = out.str();

    // Get the file name
    string levelname = "level";
    levelname += levelNumStr;           // Append the level number to the string
    levelname += ".txt";                // Append the file extension
    
    ifstream myReadFile;                
    myReadFile.open(levelname);

    string output = ""; 
    
    // Open the file and parse it as a single string
    if (myReadFile.is_open()) {
        
        int counter = 0;
        while (!myReadFile.eof()) {
            
            string temp;
            myReadFile >> temp;
            output.append(temp); 
            
        }
    }
    myReadFile.close();
	
	// Parse the string
	for (int y = 0; y < WINDOW_HEIGHT; y++)
	{
        for (int x = 0; x < WINDOW_WIDTH; x++ )
        {
            switch (output[x + (y * WINDOW_WIDTH )]) {
                case CHAR_TILE_GRASS :
                    _backgroundList->push_back(new GameObject(x,y,TILE_GRASS));
                    break;
                    
                case CHAR_TILE_TAR :
                    _backgroundList->push_back(new GameObject(x,y,TILE_TAR));
                    break;
                    
                case CHAR_TILE_ROOF :
                    _backgroundList->push_back(new GameObject(x,y,TILE_ROOF));
                    break;
                    
                case CHAR_TILE_GRAVEL :
                    _backgroundList->push_back(new GameObject(x,y,TILE_GRAVEL));
                    break;
                    
                case CHAR_TILE_BRICK_W :
                    _backgroundList->push_back(new GameObject(x,y,TILE_BRICK_W));
                    break;

				case CHAR_TILE_TREE :
                    _backgroundList->push_back(new GameObject(x,y,TILE_TREE));
                    break;

				case CHAR_TILE_TREE_2 :
                    _backgroundList->push_back(new GameObject(x,y,TILE_TREE_2));
                    break;
				case CHAR_TILE_TILE :
                    _backgroundList->push_back(new GameObject(x,y,TILE_TILE));
					break;
				case CHAR_TILE_WATER :
                    _backgroundList->push_back(new GameObject(x,y,TILE_WATER));
                    break;

                    
                    
				default:
                    break;
            }//switch
        }//inner-for
	}// for
}//parser

void Level::ParseFile(int levelNumber, char nomnomnom)
{

	// Convert the level name to a string
	string levelNumStr;
	std::stringstream out;
	out << levelNumber;
	levelNumStr = out.str();

    // Get the file name
    string levelname = "level";
    levelname += levelNumStr;           // Append the level number to the string
	levelname += "layer";				//indicate that this is a different layer
    levelname += ".txt";                // Append the file extension
    
    ifstream myReadFile;                
    myReadFile.open(levelname);

    string output = ""; 
    
    // Open the file and parse it as a single string
    if (myReadFile.is_open()) {
        
        int counter = 0;
        while (!myReadFile.eof()) {
            
            string temp;
            myReadFile >> temp;
            output.append(temp); 
            
        }
    }
    myReadFile.close();
	
	// Parse the string
	for (int y = 0; y < WINDOW_HEIGHT; y++)
	{
        for (int x = 0; x < WINDOW_WIDTH; x++ )
        {
            switch (output[x + (y * WINDOW_WIDTH )]) {
				case '0':
					continue;
                case CHAR_TILE_FENCE :
                    _entityList->push_back(new Entity(x,y,TILE_FENCE));
                    break;
                    
                case CHAR_TILE_FRIDGE :
                    _entityList->push_back(new Entity(x,y,TILE_FRIDGE));
                    break;
                    
                case CHAR_TILE_BOTTLES :
                    _entityList->push_back(new Entity(x,y,TILE_BOTTLES));
                    break;
                    
                case CHAR_TILE_TREE :
                    _entityList->push_back(new Entity(x,y,TILE_TREE));
                    break;
                    
                case CHAR_TILE_TREE_2 :
                    _entityList->push_back(new Entity(x,y,TILE_TREE_2));
                    break;

				case CHAR_TILE_BLOCK :
                    _entityList->push_back(new Entity(x,y,TILE_BLOCK));
                    break;
				case CHAR_TILE_UPPIPE :
                    _entityList->push_back(new Entity(x,y,TILE_UPPIPE));
					break;
				case CHAR_TILE_UPPIPE_TURN :
                    _entityList->push_back(new Entity(x,y,TILE_UPPIPE_TURN));
					break;
				case CHAR_TILE_SIDE_PIPE :
                    _entityList->push_back(new Entity(x,y,TILE_SIDEPIPE));
					break;
				case CHAR_TILE_SIDEPIPE_END :
                    _entityList->push_back(new Entity(x,y,TILE_SIDEPIPE_END));
					break;
				case CHAR_TILE_UPPIPE_END :
                    _entityList->push_back(new Entity(x,y,TILE_UPPIPE_END));
					break;
				case CHAR_TILE_WATER :
                    _entityList->push_back(new Water(x,y,TILE_WATER));
                    break;
             
                default:
                    break;
            }//switch
        }//inner-for
	}// for
}//parser

void Level::setComplete(bool mybool)
{
	isComplete = mybool;
}

bool Level::_isComplete()
{
	return isComplete;
}


void Level::SetDefaultPosition(int x, int y)
{
	_defaultPlayerPos = D3DXVECTOR2(x,y); 
}


// Getters
vector<GameObject *> * Level::GetResetList() { return _resetList; }
vector<Entity *> * Level::GetEnemyList() { return _enemyList; }
vector<Entity *> * Level::GetEntityList() { return _entityList; }
vector<GameObject *> * Level::GetBackgroundList() { return _backgroundList; }
vector<GameObject *> * Level::GetStaticList() { return _staticList; }
string Level::GetLevelName() { return _levelName; }
D3DXVECTOR2 Level::GetDefaultPlayerPos(){ return _defaultPlayerPos; }


