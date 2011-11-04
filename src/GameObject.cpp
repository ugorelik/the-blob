///////////////////////////////////////////////////////////////
///		GameObject.cpp
///		Author: Eric Rhodes
///		Summary: Implements the GameObject class
///////////////////////////////////////////////////////////////

#include "GameObject.h"


// --------------------------------------------------------------------------
// Constructors
// --------------------------------------------------------------------------
GameObject::GameObject() {
	pos.x = 0;
	pos.y = 0;
	vel.x = 0;
	vel.y = 0;
	_heading = 0.0f;
	_frame = 0;
	_toRemove = false;
}

GameObject::GameObject(int x, int y){
	pos.x = (float)(x * TILE_SIZE);
	pos.y = (float)(y * TILE_SIZE);
	vel.x = 0;
	vel.y = 0;
	_heading = 0.0f;
	_frame = 0;
	_toRemove = false;
}

GameObject::GameObject(int x, int y, int frame){
	pos.x = (float)(x*TILE_SIZE);
	pos.y = (float)(y*TILE_SIZE);
	vel.x = 0;
	vel.y = 0;
	_heading = 0.0f;
	_frame = frame;
	_toRemove = false;
}

GameObject::GameObject(int x, int y, int frame, float heading){
	pos.x = (float)(x *TILE_SIZE);
	pos.y = (float)(y *TILE_SIZE);
	vel.x = 0;
	vel.y = 0;
	_heading = heading;
	_frame = frame;
	_toRemove = false;
}


// --------------------------------------------------------------------------
// Setters
// --------------------------------------------------------------------------
void GameObject::SetHeading(float h) { _heading = h; }
void GameObject::SetFrame(int x)   { _frame = x;  }

void GameObject::SetPosition(int x, int y)
{
	pos.x = (float)(x *TILE_SIZE);
	pos.y = (float)(y *TILE_SIZE);
	vel.x = 0;
	vel.y = 0;
}

// --------------------------------------------------------------------------
// Getters
// --------------------------------------------------------------------------
int GameObject::GetFrame() { return _frame; }
float GameObject::GetHeading() { return _heading; }
bool GameObject::FlaggedForRemove() { return _toRemove; }
void GameObject::FlagToRemove() { _toRemove = true; }

D3DXVECTOR3 GameObject::GetPosition(){
	return D3DXVECTOR3 (pos.x/TILE_SIZE,pos.y/TILE_SIZE,0);
}

D3DXVECTOR2 GameObject::GetRelativePostion(){
	return D3DXVECTOR2(pos.x/TILE_SIZE,pos.y/TILE_SIZE);
}
