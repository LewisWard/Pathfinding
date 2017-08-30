// Author : Lewis Ward
// Date: 29/08/2017
#include "Demo.h"
#include "vld.h"

int main(int argc, char *argv[])
{
	// event handler
	Events IOEvents;
	float dt = 0.0f;

	Demo* TheDemo = new Demo();

	rayCast raySight;
	float timer = 0.0f, botTimer = 0.0f, botBTimer = 0.0f;
	bool LoS = false, drawPaths = true, drawGrids = true, moveDirectionVector = false;
	
	while (TheDemo->IsPlaying())
	{
		// get delta time
		dt = updateTimerDT();

		////----------------------------------- UPDATE -----------------------------------////
		TheDemo->Update(dt);

		////-----------------------------------  DRAW  -----------------------------------////
		// set the screen to black
		TheDemo->Draw();

	}

	delete TheDemo;

	return 0;
}
