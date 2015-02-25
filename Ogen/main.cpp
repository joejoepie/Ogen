
#include "Ogen.h"

void run(double delta)
{

}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpstr, int cmdShow)
{
	Ogen* engine = new Ogen();
	engine->init("TestWindow", 800, 600);
	engine->run(&run);
}