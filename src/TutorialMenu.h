/***********************************************************************************
 ===================================================================================

*	File name: 		GameObject.h
					==========

*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes

*	Description
		TutorialMenu < GameState
		Tutorial sub menu for the main menu.

====================================================================================		
************************************************************************************/
#pragma once
#ifndef TUTORIAL_MENU_H
#define TUTORIAL_MENU_H

#include "GameState.h"
#include <stack>
#include <string>

using std::stack;
using std::string;

class TutorialMenu : public GameState
{

public:
	TutorialMenu(stack<GameState *> *);

	virtual bool Logic(int);
	virtual void Render();
	virtual void LoadGraphics();

private:
	string _text;
};

#endif