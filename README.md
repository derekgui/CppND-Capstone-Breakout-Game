# CPPND:CapStone Classic Breakout Game

This project is the Capstone project for my [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).
The Capstone Project gives me a chance to integrate what I've learned throughout this program. 

### Spec
The core game logic according to [Wikipedia](https://en.wikipedia.org/wiki/Breakout_(video_game)):
1. Breakout begins with eight rows of bricks, with each two rows a different color. The color order from the bottom up is yellow, green, orange and red. 
2. Using a single ball, the player must knock down as many bricks as possible by using the walls and/or the paddle below to ricochet the ball against the bricks and eliminate them. 
3. If the player's paddle misses the ball's rebound, he or she will lose a turn. 
4. The player has three turns to try to clear two screens of bricks. 
5. Yellow bricks earn one point each, green bricks earn three points, orange bricks earn five points and the top-level red bricks score seven points each. 
6. The paddle shrinks to one-half its size after the ball has broken through the red row and hit the upper wall. 
7. Ball speed increases at specific intervals: after four hits, eight hits, after twelve hits.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.  

## Cloning

When cloning this project, be sure to use the `--recurse-submodules` flag. Using HTTPS:
```
git clone https://github.com/derekgui/CppND-Capstone-Breakout-Game.git 
--recurse-submodules
```
or with SSH:
```
git clone git@github.com:derekgui/CppND-Capstone-Breakout-Game.git 
--recurse-submodules
```

## Compiling and Running

### Compiling
To compile the project, first, create a `build` directory and change to that directory:
```
mkdir build && cd build
```
From within the `build` directory, then run `cmake` and `make` as follows:
```
cmake ..
make
```
### Run Testing

The executables will be placed in the `bin` directory. From within `build`, you can run the project as follows:
```
../bin/test
```
### Run Game
From within `build`, you can run the project as follows:
```
../bin/SDL2Breakout
```