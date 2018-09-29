/**
Christopher Galdi
2299616
galdi@chapman.edu
CPSC 350-01
Assignment 2
main.cpp
**/

#include <iostream>
#include "HeadingInputFile.h"
#include "Game.h"

using namespace std;

int main(int argc, char**argv)
{
  ControllingInput ci;
  Game game;
  int **myMap;
  int height = 0;
  int width = 0;
  double density = 0; //where you are configuring input output for game classic

  cout << "You are entering the Game of Life. Please choose a play mode. " << endl;

  int inputMode = ci.AskOptionInput(3, "Classic Mode (0), Doughnut Mode (1), Mirror Mode (2): ", "mode");
  game.setMode(inputMode);
  int outputNum = ci.AskOptionInput(3, "With a pause (0), Press the 'Enter' key to view the next result (1), or Print all to file (2): ", "Output Type");
  int inputValue = ci.AskOptionInput(2, "Map File (0) or Random Assignment (1)", "Type");

  if (outputNum == 0) //chose a pause
  {
    game.setOutputNum(outputNum);
  }
  else if (outputNum == 1)
  {
    game.setOutputNum(outputNum);
  }
  else if (outputNum == 2) //writing everything to a file
  {
    game.setOutputNum(outputNum);
    string outFileName;
    cout << "Enter file name you would like to print to: " << endl;
    cin >> outFileName;
    game.setOutputFile(outFileName);
  }
  if (inputValue == 0) //map file
	{
		while (height < 3 || width < 3)
		{
			string validFileName = ci.ValidatePath();
			myMap = game.readInitialFile(validFileName);
			//when calling runSimulate use the following input parameters
			//runSimulate(mappointer, mode, height, width)
			height = game.getHeight(validFileName);
			width = game.getWidth(validFileName);
			if (height >= 3 && width >= 3)
			{
				game.runMapSimulate(myMap, inputMode, height, width);
			}
		}
	}
  else if (inputValue == 1) //random assignment
  {
    height = ci.AskRow();
    game.setHeight(height);
    width = ci.AskColumn();
    game.setWidth(width);
    density = ci.AskPercentage();
    game,setDensity(density);
    game.runRandomSimulate();
  }
}
