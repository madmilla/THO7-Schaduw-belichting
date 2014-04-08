#include "BaseTimer.h"
#include "Alg.h"

#include <iostream>

using namespace std;

int main(){
	BaseTimer bt;
	Alg Ag;

	bt.start();
	Ag.Gradiant(0, 1796, 1518, 2562, 1447, 2580, 1630, 1815, 1692);
	bt.stop();

	cout << bt.elapsedSeconds() << '\n';
	system("pause");
	return 0;
}