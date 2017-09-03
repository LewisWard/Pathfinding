// Author : Lewis Ward
// Date: 29/08/2017
#include "Demo.h"

int main(int argc, char *argv[])
{
	float dt = 0.0f;

	Demo* TheDemo = new Demo();
	
	while (TheDemo->IsPlaying())
	{
		// get delta time
		dt = updateTimerDT();
		TheDemo->Update(dt);
		TheDemo->Draw();
	}

	delete TheDemo;

	return 0;
}
