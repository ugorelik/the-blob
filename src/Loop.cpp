/***********************************************************************************
 ===================================================================================

*	File name: 		Loop.cpp
					==========
*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes 

*	Description

====================================================================================		
************************************************************************************/

#pragma once
#include "Global.h"
#include "InputData.h"
#include "Timing.h"
#include "GameState.h"
#include "Game.h"
#include "MainMenu.h"
#include "StoryText.h"

#include <stack>

class GameState;

INPUTDATA inputData;

using std::stack;

void MainLoop()
{
	stack<GameState *> * gameStateStack;
	gameStateStack = new stack<GameState *>();

	gameStateStack->push(new StoryText(-200, gameStateStack));
	gameStateStack->push(new Game(gameStateStack));
//	gameStateStack->push(new StoryText(-100, gameStateStack));
//	gameStateStack->push(new MainMenu(gameStateStack));
//	gameStateStack->push(new StoryText(13,gameStateStack)); //DEBUG

	while(HandleMessages())
	{
		__int64 start = GetAccurateTime();	// Start the timer
		GameState * currentGameState = gameStateStack->top();

		bool deleteState = false;
		
		currentGameState->Input();
		deleteState = currentGameState->Logic(AccurateTimeToMillis(start));
		currentGameState->Render();

		if (deleteState)
		{
			// Should have already been popped off the stack
			delete currentGameState;
		}

		__int64 end = start - GetAccurateTime();
		int timeToSleep = AccurateTimeToMillis(end);
		Sleep(16 - timeToSleep);
	} 

	// Delete the stack and it's contents
}