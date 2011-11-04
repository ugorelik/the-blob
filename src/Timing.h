/***********************************************************************************
 ===================================================================================

*	File name: 		Timing.h
					=========

*	Authors: Uri Gorelik

*	Description
		Used to control the FPS of the game.

====================================================================================		
************************************************************************************/
#pragma once
#include <Windows.h>
#include <math.h>

// Get the current time very accurately. 
// Must call AccurateTimeToMillis before we know what it actually is.
inline _int64 GetAccurateTime() {
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return time.QuadPart;
}

// Convert a large "accurate" time to a number of milliseconds
inline int AccurateTimeToMillis(_int64 time) {
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	return (int)floor(((float)time / (float)frequency.QuadPart) * 1000.0f);
}

// Converts a number from a rate in Hz to a number of milliseconds
// EG: 60hz -> 16 ms
inline int HzToMillis(int rate) {
	return (int)floor((1.0f / (float)rate) * 1000.0f);
}
