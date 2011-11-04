/***********************************************************************************
 ===================================================================================

*	File name: 		GameObject.h
					============

*	Authors: Uri Gorelik, Michael Anderson, Eric Rhodes

*	Description
		Super class for all game objects, i.e. Entity, Solider, Scientist, Zombies.

====================================================================================		
************************************************************************************/
////PREAMBLE
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H



#include "Sprite.h"

////CLASS DEFINITION
class GameObject{
	public:

		// Constructors
		GameObject();
		GameObject(int x, int y);
		GameObject(int x, int y, int frame);
		GameObject(int x, int y, int frame, float heading);

		// Getters
		int GetFrame();
		D3DXVECTOR3 GetPosition();
		D3DXVECTOR2 GetRelativePostion();
		float GetHeading();
		bool FlaggedForRemove();
		void FlagToRemove();
		
		// Setters
		void SetHeading(float);	//TEMP
		virtual void SetPosition(int, int);
		virtual void SetFrame(int x);


		D3DXVECTOR3 vel, pos;
	protected:
		float _heading;
		int _frame;
		bool _toRemove;
};

#endif