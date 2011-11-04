#pragma once

#include "Global.h"
#include "InputData.h"
#include "Timing.h"
#include "GameState.h"
#include "Game.h"

#include <stack>

class GameState;

INPUTDATA inputData;

using std::stack;

void MainLoop()
{
	stack<GameState *> * gameStateStack;
	gameStateStack = new stack<GameState *>();

	gameStateStack->push(new Game(gameStateStack));


	while(HandleMessages())
	{
		_int64 start = GetAccurateTime();	// Start the timer
		GameState * currentGameState = gameStateStack->top();

		bool deleteState = false;
		
		currentGameState->Input();
		deleteState = currentGameState->Logic(start);
		currentGameState->Render();

		if (deleteState)
		{
			// Should have already been popped off the stack
			delete currentGameState;
		}

		_int64 end = start - GetAccurateTime();
		int timeToSleep = AccurateTimeToMillis(end);
		Sleep(16 - timeToSleep);
	} 

	// Delete the stack and it's contents
}