
#include <iostream>
#include <fstream>
#include <array>
#include <numeric>
#include <ImageLoader.h>
#include <memory>
#include <exception>
#include "example.h"
#include "testExceptions.h"

using namespace ImageLib;
using namespace std;

int main(){
	try{
		Example * x = new Example;
		x->do_it("alex.jpg");
		//int y = x->addToTen(2,9);
		//cout  << y << endl;
	}
	catch (testExceptions &cException){
		cout << cException.GetError() << endl;
	}
	catch (std::bad_alloc &cException)
	{
		cerr << "You ran out of memory!" << endl;
	}
	
}