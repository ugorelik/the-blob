/***********************************************************************************
 ===================================================================================

*	File name: 		InputData.h
					==========

*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes

*	Description
		This is the struct that is used to create actions. These are then mapped on 
		to controls (keyboard, joystick etc.). Currently only keyboard is 
		implemented. 

====================================================================================		
************************************************************************************/
#pragma once

struct INPUTDATA {
	bool moveDown;
	bool moveUp;
	bool moveLeft;
	bool moveRight;
	bool possess;
	bool kill;
	bool ESC;
	bool reset;

	// DEBUG
	bool stop;
	bool transSolider;
	bool transScientist;
	bool transBlob;

	void Clear() {
		moveDown = false;
		moveUp = false;
		moveLeft = false;
		moveRight = false;
		possess = false;
		kill = false;
		ESC = false;
		reset = false;
		stop = false;
		transSolider = false;
		transScientist = false;
		transBlob = false;
	}
};