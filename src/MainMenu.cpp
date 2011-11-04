
#include "MainMenu.h"
#include "TutorialMenu.h"
#include "Global.h"
#include "InputData.h"
#include <sstream>
#include <string>

using std::stringstream;
using std::string;

MainMenu::MainMenu(stack<GameState *> * stateStack)
	: GameState(stateStack)
{
	_currentItem = true;
	_startGameMenuItem = "Begin";
	_tutoriaMenuItem = "How to Play";
}


// ======================================================================================================
// ------------------------------------------------------------------------------------------------------
//		RENDERER
// ======================================================================================================
void MainMenu::Render()
{
	StartRendering(); // Direct3D.cpp


	if (_currentItem)
	{
		DrawFontWhite(0,0,1000, 100, _startGameMenuItem, _startGameMenuItem.length());
		DrawFontRed(0,100,1000, 500, _tutoriaMenuItem, _tutoriaMenuItem.length());
	} else {
		DrawFontRed(0,0,1000, 100, _startGameMenuItem, _startGameMenuItem.length());
		DrawFontWhite(0,100,1000, 500, _tutoriaMenuItem, _tutoriaMenuItem.length());
	}
	
	string instructions = "Use arrow keys to select, space to accept.";
	DrawFontRed(0,300,1000, 500, instructions, instructions.length());

	StopRendering();							// Direct3D.cpp
}

// ======================================================================================================
// ------------------------------------------------------------------------------------------------------
//		LOGIC
// ======================================================================================================
bool MainMenu::Logic(int time)
{

	static int delay = 0;



	
	if (time - delay > 70)
	{
		delay = time;

		// Toggle what is selected
		if (_inputData->moveUp || _inputData->moveDown) {
			_currentItem = !_currentItem;
		}

			if (_inputData->possess) {

			if (_currentItem) {
				// Pop to launch the game
				_stackState->pop();
				return true;
			} else {
				// Tutorial
				_stackState->push(new TutorialMenu(_stackState));
			}
		}
	}
	




	return false;
}

void MainMenu::LoadGraphics()
{
	LoadFont();
	return;
}