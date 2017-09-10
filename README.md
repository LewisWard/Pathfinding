# AI Pathfinding Demo README #

### How do I get set up? ###

The project can be created using CMake, from within the 'AIDemo' directory. The project was created using Visual Studio 2015 and SDL2, so it is recommended that you use Visual Studio 2015.

Inside the 'AIDemo' directory run the cmake command: cmake .

Once the project has been created, open Visual Studio. Right click on the 'AIDemo' Project in the Solution Explorer and set it as the start up project, then you can build and run the application.

Debug and Release modes have the correct SDL lib's created in order to run. The .exe that are built can be found in the Bin directory.

### Controls ###

The player is the blue character with the letter P, the are two AI bots are purple with the letters A and B. When in the line of sight of a player, the bots will move away from the player until out of sight of the player. If there is no valid location to move directly away from the player, the bots will look for the next best valid location away from the player.

* Left mouse button: Move to location
* D Key: Enable/Disable debug draw
* Esc Key: Quit

### Who do I talk to? ###

Project author: Lewis Ward

Contact: http://www.lewis-ward.com/contact.html