/**
Christopher Galdi
2299616
galdi@chapman.edu
CPSC 350-01
Assignment 2
HeadingInputFile.cpp
**/

#include "HeadingInputFile.h"

using namespace std;

HeadingInputFile::HeadingInputFile() //sets variables to zero to be utilized
{
  int height = 0;
  int width = 0;
  int mode = 0;
}
HeadingInputFile::~HeadingInputFile()
{
  //
}
int HeadingInputFile::AskOptionInput(int options, string message, string name) //asks for input and checks of the input is a valid one or not
{
  cout <<message;
  string inputString;
  int inputNumber;
  bool valid = false;

  while (true)
  {
    valid = true; //assume input is integer

    cout << "Enter an integer value: " << endl;
    cin >> num;
    getLine(cin, inputString);

    if (cin.fail(inputString)) //checks to see if the cin is the correct type, if not it returns truw, false otherwise. reference-http://www.cplusplus.com/forum/beginner/26821/
    {
      cin.clear();//corrects the stream
      cin.ignore();//skips over invalid input
      cout << "Invalid input, please try again: " << endl;
      valid = false; //Not an integer, so it will ask you to input a new value.
      continue;
    }
    inputNumber = atoi(inputString.c_str())//converts string to integer
    if (!(inputNumber >= 0 && inputNumber < options))
    {
      cout << "Invalid " << name << ". Please Try Again"
    }
    if (name == "mode") //checks if mode is correct and uses that input.
    {
      mode = inputNumber;
      // cout << "Received mode value << inputNumber << endl;"
    }
    cout << "Your input was: " << inputNumber << endl;
    return inputNumber;
  }
}

string HeadingInputFile::ValidatePath() //checks for the existing file
{
  string filePath;
  while(true)
  {
    cout << "Enter Text File Name to Input: " << endl;
    cin >> filePath;
    struct stat buffer;
    if (!(stat(filePath.c_str(), &buffer) == 0)) //https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
    {
      cout << "File Does Not Exist: " << endl;
      continue;
    }
    else //This means that the file exists and has been located
    {
      break;
    }
  }
  return filePath;
}

int HeadingInputFile::AskRow() //asks for the height of the grid for the game
{
  string tempString;
  bool badValue = true;
  while (badValue)
  {
    cout << "Enter amount of rows in your grid: ";
    //flush the buffer
    getLine(cin, tempString);
    if (IsBadInt(tempString))
    {
      cout << "Invalid Input, please try again." << endl;
      continue;
    }

    height = atoi(tempString.c_str());

    if (height < 3)
    {
      cout << "Invalid Input, please try again." << endl;
      continue;
    }
    if (height > 1000)
    {
      cout << "Rows are limited to 1000. " << endl; //for better performance
      continue;
    }
    else
    {
      badValue = false;
    }
  }
  return height;
}

int HeadingInputFile::AskColumn() //width
{
  string tempString;
  bool badValue = true;
  while (badValue)
  {
    cout << "Enter amount of columns in grid.";
    getLine(cin, tempString);
    if (IsBadInt(tempString))
    {
      cout << "Invalid Input, please try again." << endl;
      continue;
    }
    width = atoi(tempString.c_str());

    if (width < 3)
    {
      cout << "Need a Value bigger than 3. " << endl;
      continue;
    }
    else
    {
      badValue = false;
    }
  }
  return width;
}
double HeadingInputFile::AskPercentage() //asks for a number, then converts it to a decimal
{
  string tempString;
  int tempDensity;
  bool badValue = true;
  int index = 0;
  while (badValue == true)
  {
    cout << "Invalid input, please try again."
    getLine(cin, tempString);
    if (IsBadInt(tempString))
    {
      cout << "Invalid input, please try again."
      continue;
    }
    tempDensity = atoi(tempString.c_str());
    density = double (tempDensity) / double (100);
    if ((density < 0) || (density > 1))
    {
      cout << "Invalid input, 0<input<100. Please try again."; << endl;
      continue;
    }
  }
  else
  {
     badValue = false;
  }
  return density;
}
bool HeadingInputFile::IsBadInt(string input) //checks integer if it is valid or not
{
  for (int i = 0; i < input.size(); ++i)
  {
    if (!isdigit(input[i]))
    {
      return true;
    }
  }
  return false;
}
