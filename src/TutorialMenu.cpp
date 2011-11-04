
#include "TutorialMenu.h"
#include "Global.h"
#include "InputData.h"
#include <sstream>
#include <string>

using std::stringstream;
using std::string;

TutorialMenu::TutorialMenu(stack<GameState *> * stateStack)
	: GameState(stateStack)
{
	_text = "CONTROLS\nRestart Level - Backspace\nMovement - Arrow Keys\nPossess - Spacebar\nKill Possessed Target - x\nView Controls - ESC\n\nImportant Information\nYou must retrieve ALL chips\non a level and leave that level\nwithout dying to beat that level\nPress [Spacebar] to continue";
}


// ======================================================================================================
// ------------------------------------------------------------------------------------------------------
//		RENDERER
// ======================================================================================================
void TutorialMenu::Render()
{
	StartRendering(); // Direct3D.cpp

	DrawFontRed(0,100,1000, 500, _text, _text.length());

	StopRendering();							// Direct3D.cpp
}

// ======================================================================================================
// ------------------------------------------------------------------------------------------------------
//		LOGIC
// ======================================================================================================
bool TutorialMenu::Logic(int time)
{
	static int delay = time;
	/*
	if (time - delay > 70)
	{
		delay = time;
		if (_inputData->possess) {
			// Pop to launch the menu
			_stackState->pop();
			return true;
		}

	}*/

	

	if (_inputData->possess && time - delay > 1000) {
			_stackState->pop();
			return true;
	}
	
	return false;
}

void TutorialMenu::LoadGraphics()
{
	LoadFont();
	return;
}