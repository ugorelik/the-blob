
#include "GameState.h"
#include "Sprite.h"
#include "InputData.h"

GameState::GameState(stack<GameState *> * stateStack)
{
	_sheet = new SPRITE;
	_inputData = new INPUTDATA;
	_stackState = stateStack;
}

GameState::~GameState()
{
	delete _sheet;
	delete _inputData;
}

stack<GameState *> * GameState::GetStackState()
{
	return _stackState;
}

// ======================================================================================================
// ------------------------------------------------------------------------------------------------------
//		LOGIC
// ======================================================================================================
void GameState::Input(){

	//this array will hold the results of the GetKey array
	static BYTE Keys[256];

	//fill the array with the data on which keys have been pressed
	GetKeys(&Keys[0]);

	//clear the struct
	ZeroMemory(_inputData, sizeof(INPUTDATA));	//this is important

	//put the new input information into the struct
	if (Keys[DIK_SPACE]){
		_inputData->possess = true;
	} 

	if(Keys[DIK_UP])
	_inputData->moveUp = true;
	if(Keys[DIK_DOWN])
	_inputData->moveDown = true;
	if(Keys[DIK_LEFT])
	_inputData->moveLeft = true;
	if(Keys[DIK_RIGHT])
	_inputData->moveRight = true;
	


	if (Keys[DIK_X])
		_inputData->kill = true; 
	if (Keys[DIK_ESCAPE])
		_inputData->ESC = true;
	
	// DEBUG
	if(Keys[DIK_V])
		_inputData->stop = true;
	if(Keys[DIK_1])
		_inputData->transSolider = true;
	if(Keys[DIK_2])
		_inputData->transScientist = true;
	if(Keys[DIK_0])
		_inputData->transBlob = true;

	if (Keys[DIK_BACKSPACE])
		_inputData->reset = true;
}
