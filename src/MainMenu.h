/***********************************************************************************
 ===================================================================================

*	File name: 		MainMenu.h
					==========

*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes

*	Description
		MainMenu < GameState
		The menu state.

====================================================================================		
************************************************************************************/
#pragma once
#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "GameState.h"
#include <stack>
#include <string>

using std::stack;
using std::string;

class MainMenu : public GameState
{

public:
	MainMenu(stack<GameState *> *);
	virtual bool Logic(int);
	virtual void Render();
	virtual void LoadGraphics();

private:
	bool _currentItem;

	string _startGameMenuItem;
	string _tutoriaMenuItem;
};

#endif