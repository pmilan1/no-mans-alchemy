//Title: proj2.cpp 
//Author: Milan Parmar
//Date: 3/10/2021
//Description: This is main for project 2

#include "Game.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <ctime>
using namespace std;

int main () {
  srand(time(NULL));
  Game newGame;
  newGame.StartGame();
  return 0;
}
