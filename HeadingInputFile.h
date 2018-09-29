/**
Christopher Galdi
2299616
galdi@chapman.edu
CPSC 350-01
Assignment 2
HeadingInputFile.h
**/

#ifndef HEADINGINPUTFILE_H//given help from Eric Vela
#define HEADINGINPUTFILE_H //given help from Eric Vela
#include <iostream>
#include <fstream>
#include <string> //might need to include more strings
#include <stdlib.h> //for atoi function to convert string to integer
#include <cctype>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

class HeadingInputFile
{
  public:
    HeadingInputFile();
    ~HeadingInputFile();
    int AskOptionInput(int options, string message, string name);
    string ValidatePath(); //reads file
    int AskRow(); //row height
    int AskColumn(); //column height
    double AskPercentage();
    bool IsBadInt(string inputString);
    string promptPath();
    int height;
    int width;
    int mode;
    double density;

  private:
    int outputNum;
    string OutputFile;

};
