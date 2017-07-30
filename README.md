# Arrows - Windows Edition

Hello fellas, so this is my University project which I made for my dissertation.

I've recently converted it over to run on windows and decided I would upload it alongside my old ubuntu version, i've made some small changes to the code too!

There are a few things that you need to set up if you would like to run my game so here goes:

I have included multiple libaraies in my project which help with things such as GL maths, or image loading libraries which can be found bellow.
All of the libaries are included in the source code so if you wish to download this it should all be there.
There are just a few things you will need to do in order for the project to run on your computer at home and that is setting up the linkers and include/lib directories

I compiled this project to run on Visual Studios 15, and here is how to set up the projects:

Right click the project (Arrows - Windows) -> Select Properties
Select the VC++ Directories tab -> Select Include Directories -> Edit -> Add $(SolutionDir)deps/include/ AND $(SolutionDir)
								-> Select Library Directories -> Edit -> Add $(SolutionDir)deps/lib/ AND $(SolutionDir)Debug/
Select the Linker tab and then select the Input tab -> Select Additional Dependencies -> Add SDL2.lib SDL2main.lib opengl32.lib glew32.lib glu32.lib SOIL.lib

This should be all that is needed to set up the program, you will now be able to run the program and play!

Thanks for reading.

Included Libraries:

GLEW - Version 2.0.0:
http://glew.sourceforge.net/

SDL2.0:
https://www.libsdl.org/download-2.0.php

GLM:
http://glm.g-truc.net/0.9.8/index.html

SOIL:
http://www.lonesock.net/soil.html

Sam Bowen.

#####UBUNTU########

Thanks to load PNG for the code to help display PNG files.

A big thanks to Making Games with Ben, on youtube for the amazing tutorials which helped me get started with this project!

Grab the Download from my repository: https://github.com/CrazyRagdoll/Arrows/archive/master.zip

Requires Ubuntu 12.04/14.04

Required libraries & extensions: GLM, GLEW, SDL2.0, SOIL, OpenGL & Cmake

To Run:

Open Ubuntu terminal and navigate to ../Arrows/Build/

Enter “cmake CMakeLists.txt” to build project

Enter “make” to compile project

Enter “/Arrows” to run the project
