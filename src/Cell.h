///////////////////////////////////////////////////////////////
///		Filename: Cell.h
///		Author: Eric Rhodes
///		Summary: Defines a square with an image in it
///////////////////////////////////////////////////////////////

////PREAMBLE
#ifndef CELL_H
#define CELL_H

////CLASS DEFINITION
class Cell{
	private:
		int _height, _width;
		bool _occupied;
		unsigned char _image;	//this is for testing purposes only
		//Graphic image;
	public:
		Cell();
		char draw();	//probably only for testing
		void setImage(char c);
		void setOccupied(bool o);
		bool isOccupied();	//returns true if this is occupied
};

#endif