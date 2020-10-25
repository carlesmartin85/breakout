# CPPND: Capstone Breakout Game

This game was designed as the Capstone project of the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

In this project, I attempted to emulate the original arcade console version of [Breakout](https://en.wikipedia.org/wiki/Breakout_(video_game)), first designed and built by Steve Wozniak for Atari in 1976.

Once you begin the game, use the spacebar to launch the ball at the beginning of each round and move the paddle back and forth with the left and right arrow keys, trying your best to keep the ball from going off the bottom edge of the screen.

All of the files for this project are contained within the .src folder, which contains individual .h/.cpp files for each of the classes required for the game: paddle, brick, and ball, as well as .h/.cpp files for the renderer, controller, and  game, in addition to the main .h/.cpp files that launch the game.

![Breakout Image](https://drive.google.com/uc?export=view&id=1sIID0hhqhWSKvIaBSgo4QVJjw3aNH10S)

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./breakout`.

## Udacity Rubric Points

* __Compiling and testing__
    * The project compiles and runs without errors


* __Loops, Functions, I/O__
    * The project demonstrates an understanding of C++ functions and control structures
        * This occurs throughout the entire project
    * The project accepts user input and processes the input
        * This occurs in the controller.cpp file

* __Object Oriented Programming__
    * The project uses Object Oriented Programming techniques
        * This occurs in the paddle.h/.cpp, ball.h/.cpp, block.h/.cpp, and game.h/.cpp files
    * Classes use appropriate access specifiers for class members
        * This occurs in the paddle.h/.cpp, ball.h/.cpp, block.h/.cpp, and game.h/.cpp files
    * Class constructors utilize member initialization lists
        * This occurs in block.h on line 12
    * Classes abstract implementation details from their interfaces
        * This occurs in the private member variables in paddle.h/.cpp, ball.h/.cpp, block.h/.cpp, and game.h/.cpp files
    * Classes encapsulate behavior
        * This occurs in the paddle.h/.cpp, ball.h/.cpp, block.h/.cpp, and game.h/.cpp files

* __Memory Management__
    * The project makes use of references in function declarations
        * This occurs in game.h on lines 38-41 and 44-47, and in the corresponding function definitions in game.cpp
    * The project uses destructors appropriately
        * This occurs in the renderer.h on line 18 and in the corresponding implementation in renderer.cpp on lines 39-42