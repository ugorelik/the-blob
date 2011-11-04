/***********************************************************************************
 ===================================================================================

*	File name: 		StoryText.h
					============

*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes

*	Description
		StoryText < GameState
		Stores the text for the chips and the tutorials

*	TODO
		Parse the story text from a file.

====================================================================================		
************************************************************************************/
#pragma once
#ifndef STORY_TEXT_H
#define STORY_TEXT_H

#define TUTORIAL_1 "[Tutorial 1]\n\nAs a blob, you are capable of possessing people.\nTo do so, sneak up behind them and HOLD [SPACEBAR]\nYou can use this to disguise yourself, or use your host's\nstrengths to defeat certain enemies.\nIf you collide with an enemy you will die and the level\nwill restart."
#define TUTORIAL_2 "[Tutorial 2]\n\nAfter a certain number of steps, your unfortunate \nhost will explode due to a problematic chemical reaction.\nYou can also trigger this at any time by pressing [X].\nAs a result, scientists are liable to\ntreat you as an object of abject terror.\nSoldiers are likely to just kill you though.\n\nTry scaring that scientist by murdering his friend by \npressing [x] while infront of him."
#define TUTORIAL_3 "[Tutorial 3]\n\nIf you are killed, the level will instantly restart.\nYou can also restart it any time by pressing [BACKSPACE]\nUse a disguise to get past the soldiers.\nPress [ESCAPE] at any point to check controls."
#define TUTORIAL_4 "[Tutorial 4]\n\nGreen chips hold keys to your past!\nYou must collect all chips and exit a level\n without dying to complete it\nAlso, unless you are a soldier, contact with a zombie\nis fatal and not recommended.\nSoldiers kill zombies."

#define STORY_1 "JOURNAL ENTRY - 01 -\n\nDr. Rhodes, 2012-03-08\n\nThis will be my first of many journal entries that\nI will use to keep a record of my work here at Triple\nHelix Industries. I am very excited to start work on\nthe new project; what we are trying to achieve is\nbeyond anything I would have possibly imagined. I\nhave to go and meet the team, I will write more\nin the weeks to come.\n\nEMPLOYEE PROFILE\n\nDr. Gary Rhodes\n\nGraduated from Carleton University Bio-Medical Engineering 1998\n\nGraduated from Harvard Medical School Magna Cum Laude 2003\n\n2003-2012 - Work for Pentagon – CLASSIFIED\n\nMarch 2012, hired as head of Advanced Bio-Medical Research and Experimentation Division at Triple Helix Industries."
#define STORY_2 "JOURNAL ENTRY - 02 -\n\nDr. Rhodes, 2012-03-10\n\nCLASSIFIED\nUsing genetic  engineering, we’ve been able to create\nnew lifeforms with superhuman capabilities. But we are\nunable to imbue them with true sentience, leaving them\nas little more than animals. I’ll have to consult with\nthe neuroscience department."
#define STORY_3 "JOURNAL ENTRY - 03 -\n\nDr. Rhodes, 2012-03-28\n\nBrilliant! We’ve engineered a process by which we can\ntransfer a being’s consciousness from one brain to another.\nIf all goes according to plan, we’ll begin testing\non mice next week."
#define STORY_4 "JOURNAL ENTRY - 04 -\n\nDr. Rhodes, 2012-04-08\n\nSuccess! We transferred the mind of a mouse from\nit’s natural body into one of our creation. We’ll begin\ntesting on successively more mentally complex\nlifeforms before we begin human testing."
#define STORY_5 "JOURNAL ENTRY - 05 -\n\nDr. Rhodes, 2012-04-10\n\nAn interesting side effect of the consciousness\ntransferal became apparent today. The mindless bodies of\nthe animals have shown the tendency to regain some level\nof consciousness after a period of time. Perhaps we are merely\ncopying their mind into our engineered bodies."
#define STORY_6 "JOURNAL ENTRY - 06 -\n\nDr. Rhodes, 2012-06-13\n\nThe time for human testing has arrived. The company\nlawyers have insisted that only an informed, consenting\nvolunteer be used for the first human test. I have volunteered\nmyself. The others see my decision as risky, but I have faith\nin my abilities. I will be the first to transcend\nto a higher form of life!"
#define STORY_7 "JOURNAL ENTRY - 07 -\n\nDr. Gorelik, 2012-06-14\n\nHuman testing did not go well. Dr. Rhodes has not regained\nconsciousness since the transfer, and his new body\nhas begun to destabilize into what appears to be the stem\ncell serum used to create it. We’ve kept his original body\nchilled so that we can attempt to transfer his\nmind back once he comes to."
#define STORY_8 "JOURNAL ENTRY - 08 -\n\nDr. Anderson, 2012-06-18\n\nThe destabilization of Dr. Rhodes new body has taken an\ninteresting turn. The scientists have started referring to\nit as “The Blob”. He’s become a viscous green goo.\nTesting indicates his new form has similarities to both stem and\nnerve cells. In theory, he could reshape himself to some degree, and\nwould have interesting interactions with\nother creature’s nervous systems. Still no hypothesis\nas to what is causing the change."
#define STORY_9 "JOURNAL ENTRY - 09 -\n\nDr. Gorelik, 2012-06-20\n\nSome kind of neurological disease has begun spreading\nthrough the staff, transforming them into what can only be\ndescribed as zombies. An evacuation  order has been\nissued for the lab. I couldn’t get out before the lab was\nsealed. I’m trapped here. If someone finds this,\ntell my family I love them."
#define STORY_10 "JOURNAL ENTRY - 10 -\n\nDr. Anderson, 2012-06-22\n\nIt’s chaos. Martial law\nhas been declared, and the soldiers have begun shooting\nanyone they fear may be infected. They’ve all but enslaved\nthe surviving scientists, forcing us to work around the clock\nuncovering the source, and cure for, the zombie outbreak."
#define STORY_11 "JOURNAL ENTRY - 11 -\n\nDr. Anderson, 2012-06-24\n\nWe’ve made some progress. The virus appears to be a\nmodified form of one of the serums used in our consciousness\ntransferal system. It spreads through bodily fluids\nand overwrites portions of it’s victims higher brain functions\nwith a feral need to spread the virus. The source\nof the outbreak must have been one of the animals we tested.\nIf we could find which one, we could perhaps develop a cure.\nBut how could one of the lab animals have modified the serum?"
#define STORY_12 "JOURNAL ENTRY - 12 -\n\nDr. Anderson, 2012-06-24\n\nWe made a terrible mistake. The mindless bodies of\nthe animals didn’t regain consciousness, they were\nreverting to a more animalistic state. In animals, the change\nwasn’t noticeable. But Dr. Rhodes’ body, deprived of it’s\nhuman mind, devolved into a vicious beast intent on fulfilling\nhis darker impulses. He is the source of the zombie outbreak.\nThe only way to stop the outbreak would be to reunite Rhodes’\nmind with his errant body. A difficult task, as\nhis body is now in control of a zombie horde."
#define STORY_13 "JOURNAL ENTRY - 13 -\n\nSgt. J. Rambo , 2012-06-26\n\nZombies ain’t so tough. Nothing like what I went\nthrough in ‘Nam. Gonna kill my way to their leader."

#define STORY_INTRO "You awaken in a darkened laboratory... your laboratory?\nYou can't remember. Were you human once?\nIt sounds like something is happening outside.\nTry picking up that blue chip.\nUse the arrow keys to move around."

#define STORY_DEFAULT "@@@@@@@@@@@@@@@@@||||\\\\\|||\||\\\\||||@@@@!!||@||\!!!!!\n\n[Data Corrupted]"

#define STORY_OUTTRO "You are responsible for the zombie outbreak.\nAnd only you can end it.\nYou must hunt down the Zombie Overlord and\nreclaim your body to save mankind."

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
	int _id;
};

#endif