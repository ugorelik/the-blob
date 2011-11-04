
#include "StoryText.h"
#include "Global.h"
#include "InputData.h"
#include <sstream>
#include <string>

using std::stringstream;
using std::string;

StoryText::StoryText(int chipNumber, stack<GameState *> * stateStack)
	: GameState(stateStack)
{
	switch (chipNumber)
	{

	// Tutorial Text
	case -1:
		_renderStr = TUTORIAL_1;
		break;
	case -2:
		_renderStr = TUTORIAL_2;
		break;
	case -3:
		_renderStr = TUTORIAL_3;
		break;
	case -4:
		_renderStr = TUTORIAL_4;
		break;


	case 1:
		_renderStr = STORY_1;
		break;
	case 2:
		_renderStr = STORY_2;
		break;
	case 3:
		_renderStr = STORY_3;
		break;
	case 4:
		_renderStr = STORY_4;
		break;
	default : 
		_renderStr = STORY_DEFAULT;
		break;
	}
}


// ======================================================================================================
// ------------------------------------------------------------------------------------------------------
//		RENDERER
// ======================================================================================================
void StoryText::Render()
{
	StartRendering(); // Direct3D.cpp

	stringstream out;
	
	out << _renderStr;
	_renderStr = out.str();
	DrawFontWhite(0,0,1000, 500, _renderStr, _renderStr.length());

	StopRendering();							// Direct3D.cpp
}

// ======================================================================================================
// ------------------------------------------------------------------------------------------------------
//		LOGIC
// ======================================================================================================
bool StoryText::Logic(int time)
{
	if (_inputData->possess) {
		_stackState->pop();
		return true;
	}
	return false;
}

void StoryText::LoadGraphics()
{
	LoadFont();
	return;
}