
#include <iostream>

#include "Game.h"

using namespace std;

int main ()
{

	Game game;
	game.initTest();

	game.run();

	cout << endl;
	system("PAUSE");
	return 1;
}