## About
This is an ncurses game where you direct your cursor through a labyrinth, with the added twist that the characters <, >, v, and ^ can only be traversed in the direction which they point towards.

This is the first non-trivial program I've written in C, based on an idea implemented on paper years ago. 

There are still a lot of bugs in it, but the first level is playable. Your game experience might vary depending on the terminal emulator and your color scheme.

![A screenshot of the labyrinth game.](/screenshot.png)

## Dependencies
* You'll need the development libraries for ncurses (*libncurses-dev* on Ubuntu) as well as a C-compiler like gcc or clang.
* GNU Make is required for the *make* command to work. The makefile assumes you have gcc installed.

## Installation
* Clone the repository: "git clone https://github.com/dandels/ncurses-labyrinth.git"
* Change directory to the downloaded repository: "cd ncurses-labyrinth"
* Run "make"
* Launch the game with "./labyrinth"

## Uninstallation
* Just remove the "ncurses-labyrinth"-directory.
