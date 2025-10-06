#include <iostream>
#include "TestExtins.h"
#include "TestScurt.h"
#define _CRTDBG_MAP_ALLOC
using namespace std;

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	testAll();
	testMaxMin();
	testAllExtins();
	cout<<"End";
	_CrtDumpMemoryLeaks();
}
