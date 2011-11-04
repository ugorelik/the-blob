
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
	_id = chipNumber;

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

	case 5:
		_renderStr = STORY_5;
		break;
	case 6:
		_renderStr = STORY_6;
		break;
	case 7:
		_renderStr = STORY_7;
		break;
	case 8:
		_renderStr = STORY_8;
		break;

	case 9:
		_renderStr = STORY_9;
		break;
	case 10:
		_renderStr = STORY_10;
		break;
	case 11:
		_renderStr = STORY_11;
		break;
	case 12:
		_renderStr = STORY_12;
		break;
	case 13:
		_renderStr = STORY_13;
		break;
	case -100:
		_renderStr = STORY_INTRO;
		break;
	case -200:
		_renderStr = STORY_OUTTRO;
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

	if (_id < 0) {
		DrawFontBlue(0,0,1000, 900, _renderStr, _renderStr.length());
	} else {
		DrawFontRed(0,0,1000, 900, _renderStr, _renderStr.length());
	}
	

	StopRendering();							// Direct3D.cpp
}

// ======================================================================================================
// ------------------------------------------------------------------------------------------------------
//		LOGIC
// ======================================================================================================
bool StoryText::Logic(int time)
{

	static int delay = time;

	if (_inputData->possess && time - delay > 1000) {
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