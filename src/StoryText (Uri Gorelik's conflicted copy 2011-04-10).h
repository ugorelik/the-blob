
#pragma once
#ifndef STORY_TEXT_H
#define STORY_TEXT_H

#define TUTORIAL_1 ""
#define TUTORIAL_2 ""
#define TUTORIAL_3 ""
#define TUTORIAL_4 ""

#define STORY_1 "JOURNAL ENTRY - 01 -\n\nDr. Rhodes, 2012-03-08\n\nThis will be my first of many journal entries that I will use to keep a record of my work\n here at Triple Helix Industries. I am very excited to start work on the new project;\n what we are trying to achieve is beyond anything I would have possibly imagined.\n I have to go and meet the team, I will write more in the weeks to come.\n\nEMPLOYEE PROFILE\n\nDr. Gary Rhodes\n\nGraduated from Carleton University Bio-Medical Engineering 1998\n\nGraduated from Harvard Medical School Magna Cum Laude 2003\n\nGraduated from Oxford University 2008\n\n2008-2012 - Work for Pentagon – CLASSIFIED\n\nMarch 2012, hired as head of Advanced Bio-Medical Research and Experimentation Division at Triple Helix Industries."
#define STORY_2 "JOURNAL ENTRY - 02 -\n\nDr. Rhodes, 2012-03-10\n\nCLASSIFIED\n\nFound out what he’s working on, U.S. government knows of disease they won’t be able\n to stop. Extreme measures necessary"
#define STORY_3 "JOURNAL ENTRY - 03 -\n\nDr. Rhodes, 2012-03-28\n\nWe began the development of the prototype today. I am still questioning the ethical\n implications of our work here. But the powers at be will not listen to my \nconcerns. For the first time in my life I believe I am in over my head."
#define STORY_4 "JOURNAL ENTRY - 04 -\n\nDr. Rhodes, 2012-04-20\n\nWe have been able to successfully combine the DNA strands of several Genotypes. The development\n of the prototype is way ahead of schedule. We were able to meld a rat \ntoday. It was one of the most terrifying and exciting things I have ever witnessed. "

#define STORY_DEFAULT "@@@@@@@@@@@@@@@@@||||\\\\\|||\||\\\\||||@@@@!!||@||\!!!!!\n\n[Data Corrupted]"

#include "GameState.h"
#include <stack>
#include <string>

using std::stack;
using std::string;

class StoryText : public GameState
{

public:
	StoryText(int, stack<GameState *> *);
	virtual bool Logic(int);
	virtual void Render();
	virtual void LoadGraphics();

private:
	string _renderStr;
};

#endif