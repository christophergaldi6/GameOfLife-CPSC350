/**
Christopher Galdi
2299616
galdi@chapman.edu
CPSC 350-01
Assignment 2
Game.cpp
**/

#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(){

}
Game::~Game(){

}
void Game::runRandomSimulate() //function that runs a random simulator for the Game
{
  srand (time(NULL));//variables for random Assignment
  x = width;
  y = height;
  regularity = density;

  currentMap = 1;
  temp = new int *[x]; //initializes temp array and map2
  map2 = new int *[x];
  for (int i = 0; i < x; ++i)//width prior to height
  {
    map2[i] = new int[y];
    temp[i] = new int[y];
    for (int j = 0; j < y; ++j)
    {
      temp[i][j] = 0;
      temp[i][j] = 0;
    }
  }

  map1 = new int * [x]
//using density (regularity) we can populate the grid
  for (int i =0; i < x; ++i)
  {
    map[i] = new int[y];
    for (int j = 0; j < y; ++j)
    {
      if ((double)rand() / (double)RAND_MAX <= regularity)
      {
        map1[i][j] = 1;
      }
      else
      {
        map1[i][j] = 0;
      }
    }
  }
  //Comment
  switch(outputNum) //switch statement gets the output number from main, and uses the case statements to run between different modes
  {
    case 0: //sleep case
      cout << "First Generation: " << currentMap << endl;
      cout << printMapConsole(x, y, map1);
      sleep(2);
      break;
    case 1: //"Enter" case
      cout << "First Generation: " << currentMap << endl;
      cout << printMapConsole(x, y, map1);
      cin.get();
      break;
    case 2: //write to file
      o.open(outputFile.c_str(),ofstream::out | ofstream::trunc);
      o << "Initial Generation: " << endl;
      printMapConsole(x, y, map1);
      break;
  }
  //Main loop where everything outputs every time the user presses Enter
  bool stop = false;

  while (!stop)
  {
    if (currentMap == 1)
    {
      temp = simulateNext(map1, mode, x, y);
      for (int i = 0; i < x; ++i)
      {
        for (int j = 0; j < y; j++)
        {

          map2[i][j] = temp[i][j];
        }
      }
      currentMap++;
      if (outputNum == 0 || outputNum == 1)
      {
        cout << "Generation: " << currentMap << endl;
        cout << printMapConsole(x, y, map2);
      }
      else
      {
        o <<"Generation: " << currentMap << endl;
        printMapConsole(x, y, map2);
      }
      else if (currentMap >= 2)
      {
        for (int i = 0; i < x; ++i)
        {
          for (int j = 0; j < y; ++j)
          {
            map1[i][j] = map2[i][j];
          }
        }
        temp = simulateNext(map1, mode, x, y);

        for (int i = 0; i < x; ++i)
        {
          for (int j = 0; j < y; ++j)
          {
            map2[i][j] = temp[i][j];
          }
        }
        currentMap++;
        if(outputNum == 0 || outputNum == 1)
        {
          cout <<"Generation: " << currentMap << endl;
          printMapConsole(x, y, map2);
        }
        else
        {
          o << "Generation: " << currentMap << endl;
          printMapConsole(x, y, map2);
        }
      }

      stop = CheckingError(map1, map2, currentMap, x, y); //checks whether it is empty or not

      switch (outputNum)
      {
        case 0:
        {
          sleep(2);
          break;
        }
        case 1:
        {
          string userInput = " ";
          userInput = cin.get();
          if(userInput == "n")
          {
            stop = true;
          }
          break;
        }
        case 2:
        {
          break;
        }
      }
    }
    o.close();
   }

   void Game::runMapSimulate(int **map, int mode, int x, int y)//used to map the file
   {
     cin.get();
     currentMap = 1;

     temp = new int *[x];
     map2 = new int *[x];
     for (int i = 0; i < x; ++i)
     {
       map2[i] = new int[y];
       temp[i] = new int[y];
       for (int j = 0; j < y; ++j)
       {
         temp[i][j] = 0;
         map2[i][j] = 0;
       }
     }

     //build and initialize map1
     map1 = map;
     //call printMapConsole to make sure that correct x and y are used
     switch (outputNum)
     {
       case 0 ... 1:
       {
         cout << "Inititial Generation: " << currentMap << endl;
         cout << printMapConsole(x, y, map1);
         break;
       }
       case 2:
       {
         o.open(outputFile.c_str(), ofstream::out | ofstream::trunc); //opens file ofstream
         o << "Initial Generation: " << endl;
         printMapConsole (x, y, map1)
         break;
       }
     }

     //Main loop where everything runs and outputs every time the user presses Enter
     bool stop = false;
     if (outputNum == 1)
     {
       cin.get();
     }
     //cout << "Entered runSimulate" << endl;
     while (!stop)
     {
       if (currentMap == 1)
       {
         temp = simulateNext(map1, mode, x, y);

         map2 = temp;

         //calculates next generation
         currentMap++;
         if (outputNum == 0 || outputNum == 1)
         {
           cout << "Generation: " << currentMap << endl;
           cout << printMapConsole(x, y, map2);
         }
         else if (outputNum == 2)
         {
           o << "Generation: " << currentMap << endl;
           printMapConsole(x, y, map2);
         }
         //currentMap = 2;
       }
       else if (currentMap >= 2)
       {
         for (int i = 0; i < x; ++i)
         {
           for (int j = 0; j < y; ++j)
           {
             map1[i][j] = map2[i][j];
           }
         }

         temp = simulateNext(map1, mode, x, y);
         for (int i = 0; i < x; ++i)
         {
           for (int j = 0; j < y; ++j)
           {
             map2[i][j] = temp[i][j];
           }
         }
         //cout << "Print map1 Generation " << currentMap << endl;
         //printMapConsole(x, y, map1);
         currentMap++;
         if (outputNum == 0 || outputNum == 1)
         {
           cout << "Generation: " << currentMap << endl;
           cout << printMapConsole(x, y, map2);
         }
         else //saving it to file
         {
           o << "Generation: " << currentMap << endl;
           printMapConsole(x, y, map2);
         }
         //printMapConsole to see if x and y are valid
         //printMapConsole(x, y, map2);
        // currentMap = 1;
       }

       stop = CheckingError(map1, map2, currentMap, x, y);
       switch (outputNum)
       {
         case 0:
           {
             sleep(2);
             break;
           }
         case 1:
           {
             string userInput = " ";
             userInput = cin.get();
             if (userInput == "n")
             {
               stop = true;
             }
             break;
           }
         case 2:
           {
             break;
           }
       }
     }
     o.close();    // closes the output file
    }

    bool Game::CheckingError(int **map1, int **map2, int currentMap, int x, int y) //checks whether grid is empty or not
    {
     bool stop = false;
     bool moles = false;
     for(int i = 0; i < x; ++i)
     {
       for (int j = 0; j < y; ++j)
       {
         if (map2[i][j] == 1)
         {
           moles = true;
           break;
         }
       }
       if (moles == true)
       {
         break;
       }
     }

     if (moles == false)
     {
       if (outputNum == 0 || outputNum ==1)
       {
         cout << "Grid is empty. The END." << endl;
       }
       else
       {
         o << "Grid is empty. The END.";
         o << endl;
       }
       stop = true;
     }

     bool smoke = false;
     for(int i = 0; i < x; ++i)
     {
       for (int j = 0; j < y; ++j)
       {
         if (map1[i][j] != map2[i][j])
         {
           smoke = true;
           break;
         }
       }
       if (smoke == true)
       {
         break;
       }
     }
     if (smoke == false)
     {
       if (outputNum == 0 || outputNum == 1)
       {
         cout << "End of generation" << endl;
       }
       else
       {
         o << "End of generation";
         o << endl;
       }
       stop = true;
     }

     if(currentMap == 1001)//this makes it so you cant go longer than 1000 generations
     {
       if(outputNum == 0 || outputNum == 1)
       {
         cout << "Generation is too long" << endl;
       }
       else
       {
         o << "Generation is too long";
         o << endl;
       }
       stop = true;
     }
     return stop;
    }


    int **Game::simulateNext(int **map, int mode, int x, int y) //Mode Location
    {
     for (int i = 0; i < x; ++i)
     {
       for (int j = 0; j < y; ++j)
       {
         short neighbors = 0;
         switch (mode)
         {
           //individually checking all the neighbors for all cases
           case 0: //classic mode
           {
             //standard case checking (not sides)
             if (i > 0 && i < x - 1 && j > 0 && j < y - 1)
             {
               neighbors += checkNeighboring(map, i, j);
             }
             //left side
             else if (i == 0 && j > 0 && j < y - 1)
             {
               for (int k = 0; k < 2; ++k)
               {
                 for(int l = -1; l < 2; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }
             //right side
             else if (i == x - 1 && j > 0 && j < y - 1)
             {
               for (int k = -1; k < 1; ++k)
               {
                 for(int l = -1; l < 2; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }
             //top side
             else if (j == 0 && i > 0 && i < x - 1)
             {
               //cout<<"5";
               for (int k = -1; k < 2; ++k)
               {
                 for(int l = 0; l < 2; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }
             //bottom side
             else if (j == y - 1 && i > 0 && i < x - 1)
             {
               //cout<<"4";
               for (int k = -1; k < 2; ++k)
               {
                 for(int l = -1; l < 1; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }
             //top left
             else if (i == 0 && j == 0)
             {
               for (int k = 0; k < 2; ++k)
               {
                 for(int l = 0; l < 2; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }
             //bottom left
             else if (i == 0 && j == y - 1)
             {
               for (int k = 0; k < 2; ++k)
               {
                 for(int l = -1; l < 1; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }
             //bottom right
             else if (i == x - 1 && j == y - 1)
             {
               for (int k = -1; k < 1; ++k)
               {
                 for(int l = -1; l < 1; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }
             //top right
             else if (i == x - 1 && j == 0)
             {
               for (int k = -1; k < 1; ++k)
               {
                 for(int l = 0; l < 2; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }

             //setting temp array with the processed array
             if (map[i][j] == 1)
             {
               --neighbors;
             }

             if (neighbors == 2)
             {
               temp[i][j] = map[i][j];
             }

             else if (neighbors <= 1 || neighbors >= 4)
             {
               temp[i][j] = 0;
             }

             else if (neighbors == 3)
             {
               temp[i][j] = 1;
             }
             break;
           }
           case 1: //Doughnut mode
           {
             if (i > 0 && i < x - 1 && j > 0 && j < y - 1)
             {
               neighbors += checkNeighboring(map, i, j);
             }
             //left side
             else if (i == 0 && j > 0 && j < y - 1)
             {
               for (int l = -1; l < 2; ++l)
               {
                 neighbors += map[x - 1][j + l];
               }
               for (int k = 0; k < 2; ++k)
               {
                 for(int l = -1; l < 2; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }
             //right side
             else if (i == x - 1 && j > 0 && j < y - 1)
             {
               for (int l = -1; l < 2; ++l)
               {
                 neighbors += map[0][j + l];
               }
               for (int k = -1; k < 1; ++k)
               {
                 for(int l = -1; l < 2; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }
             //top side
             else if (j == 0 && i > 0 && i < x - 1)
             {
               for (int k = -1; k < 2; ++k)
               {
                 neighbors += map[i + k][y - 1];
                 for(int l = 0; l < 2; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }
             //bottom side
             else if (j == y - 1 && i > 0 && i < x - 1)
             {
               for (int k = -1; k < 2; ++k)
               {
                 neighbors += map[i + k][0];
                 for(int l = -1; l < 1; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }
             //top left
             else if (i == 0 && j == 0)
             {
               neighbors += map[x - 1][y - 1] + map[x - 1][0] + map[x - 1][1];
               for (int k = 0; k < 2; ++k)
               {
                 neighbors += map[i + k][y - 1];
                 for(int l = 0; l < 2; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }
             //bottom left
             else if (i == 0 && j == y - 1)
             {
               neighbors += map[x - 1][0] + map[x - 1][y - 1] + map[x - 1][y - 2];
               for (int k = 0; k < 2; ++k)
               {
                 neighbors += map[i + k][0];
                 for(int l = -1; l < 1; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }
             //bottom right
             else if (i == x - 1 && j == y - 1)
             {
               neighbors += map[0][0] + map[0][y - 1] + map[0][y - 2];
               for (int k = -1; k < 1; ++k)
               {
                 neighbors += map[x - 1 + k][0];
                 for(int l = -1; l < 1; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }
             //top right
             else if (i == x - 1 && j == 0)
             {
               neighbors += map[0][y - 1] + map[0][0] + map[0][1];
               for (int k = -1; k < 1; ++k)
               {
                 neighbors += map[x - 1 + k][y - 1];
                 for(int l = 0; l < 2; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }

             //setting temp array with the processed array using classic rules
             //decrementing neighbor count to exclude current cell
             if (map[i][j] == 1)
             {
               --neighbors;
             }
             //stability
             if (neighbors == 2)
             {
               temp[i][j] = map[i][j];
             }
             //loneliness
             else if (neighbors <= 1 || neighbors >= 4)
             {
               temp[i][j] = 0;
             }
             //growth
             else if (neighbors == 3)
             {
               temp[i][j] = 1;
             }

             break;
           }
           case 2: //Mirror Mode
           {
             //cout << "This is Mirror Mode" << endl;
             //checks standard cases not the sides
             if (i > 0 && i < x - 1 && j > 0 && j < y - 1)
             {
               neighbors += checkNeighboring(map, i, j);
             }
             //left side
             else if (i == 0 && j > 0 && j < y - 1)
             {
               for (int l = -1; l < 2; ++l)
               {
                 neighbors += map[0][j + l];
               }
               for (int k = 0; k < 2; ++k)
               {
                 for(int l = -1; l < 2; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }
             //right side
             else if (i == x - 1 && j > 0 && j < y - 1)
             {
               for (int l = -1; l < 2; ++l)
               {
                 neighbors += map[x - 1][j + l];
               }
               for (int k = -1; k < 1; ++k)
               {
                 for(int l = -1; l < 2; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }
             //top side
             else if (j == 0 && i > 0 && i < x - 1)
             {
               for (int k = -1; k < 2; ++k)
               {
                 neighbors += map[i + k][0];
                 for(int l = 0; l < 2; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }
             //bottom side
             else if (j == y - 1 && i > 0 && i < x - 1)
             {
               for (int k = -1; k < 2; ++k)
               {
                 neighbors += map[i + k][y - 1];
                 for(int l = -1; l < 1; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }
             //top left
             else if (i == 0 && j == 0)
             {
               neighbors += map[0][0] + map[0][1];
               for (int k = 0; k < 2; ++k)
               {
                 neighbors += map[i + k][0];
                 for(int l = 0; l < 2; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }
             //bottom left
             else if (i == 0 && j == y - 1)
             {
               neighbors += map[0][y - 1] + map[0][y - 2];
               for (int k = 0; k < 2; ++k)
               {
                 neighbors += map[i + k][y - 1];
                 for(int l = -1; l < 1; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }
             //bottom right
             else if (i == x - 1 && j == y - 1)
             {
               neighbors += map[x - 1][y - 1] + map[x - 1][y - 2];
               for (int k = -1; k < 1; ++k)
               {
                 neighbors += map[x - 1 + k][y - 1];
                 for(int l = -1; l < 1; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }
             //top right
             else if (i == x - 1 && j == 0)
             {
               neighbors += map[x - 1][0] + map[x - 1][1];
               for (int k = -1; k < 1; ++k)
               {
                 neighbors += map[x - 1 + k][0];
                 for(int l = 0; l < 2; ++l)
                 {
                   neighbors += map[i + k][j + l];
                 }
               }
             }

             //setting temp array with the processed array
             if (map[i][j] == 1)
             {
               --neighbors;
             }

             if (neighbors == 2)
             {
               temp[i][j] = map[i][j];
             }

             else if (neighbors <= 1 || neighbors >= 4)
             {
               temp[i][j] = 0;
             }

             else if (neighbors == 3)
             {
               temp[i][j] = 1;
             }

             break;
           }
         }
       }
     }
     return temp;
    }

    short Game::checkNeighboring(int **map, int x, int y)
    {
     short neighbors = 0;
     for (int i = -1; i < 2; ++i)
     {
       for(int j = -1; j < 2; ++j)
       {
         neighbors += map[x+i][y+j]; // minus one for the center square;
       }
     }
     return neighbors;
    }

    int **Game::readInitialFile(string inputFileName)//opens the file inputted for the map file mode
    {
     ifstream myFile;
     string filePath = inputFileName;
     string line;
     int lineCount = 0;
     myFile.open(inputFileName.c_str());
     bool good = myFile.good();
     if (myFile.is_open())
     {
         getline(myFile,line);
         height = atoi(line.c_str()); //rows

         getline(myFile,line);
         width = atoi(line.c_str()); //columns

         if (height > 1000 || width > 1000)
         {
           cout << "Limit rows and columns to less than or equal to 1000 for better performance. :)" << endl;
           mapFile = new int *[0];
           height = 0;
           width = 0;
           good = false;
         }

         else if (height < 3 || width < 3)
         {
           cout << "IO Error: Unable to create map. Map file width and height parameters invalid.";
           mapFile = new int *[0];
           height = 0;
           width = 0;
           good = false;
         }
         else
         {
           mapFile = CreateArray(width, height);
         }
       for (int n = 0; n < height && good; ++n)
       {
         //starts from line 3 in the file
         getline(myFile,line);
         for (int m = 0; m < width && line[m] != '\n'; m++)
         {
           if (line[m] != '-' && line[m] != 'X' && line[m] != '\n' && line[m] != ' ')
           {
             cout << "Unable to create map. Incorrect syntax." << endl;
             height = 0;
             width = 0;
             return (new int *[0]);
           }
         }
         if ((n == height - 1 && (line.length() != width + 1 && line.length() != width)) || (n != height - 1 && line.length() != width + 1))
         {
           cout << "IO Error: Unable to create map. Map does not match defined array size.\n";
           mapFile = new int *[0];
           height = 0;
           width = 0;
           break;
         }

         else if ((line.size() != width + 1 && n == height - 1))
         {

         }
         LoadRowArray(line, lineCount);
         lineCount++;
       }
     }
     myFile.close();
     return mapFile;
    }
    int Game::getHeight(string fileName)
    {
     return height;
    }

    int Game::getWidth(string fileName)
    {
     return width;
    }

    void Game::setOutputNum(int inNumber)
    {
     outputNum = inNumber;
    }

    void Game::setOutputFile(string inString)
    {
     outputFile = inString;
    }

    void Game::setHeight(int inputHeight)
    {
     height = inputHeight;
    }

    void Game::setWidth(int inputWidth)
    {
     width = inputWidth;
    }

    void Game::setDensity(double inputDensity)
    {
     density = inputDensity;
    }

    void Game::setMode(int inputMode)
    {
     mode = inputMode;
    }

    string Game::printMapConsole(int height, int width, int **map) //generic print map to console
    {
     //cout<<"Start of print"<<endl;
     string outString = "";
     for (int i = 0; i < height; ++i)
     {
       for (int j = 0; j < width; ++j)
       {
         if (map[i][j] == 1)
         {
           outString += "X";
         }
         else
         {
           outString += "-";
         }
       }
       if (outputNum == 0 || outputNum == 1)
       {
         cout << outString << " : row: " << i + 1 << endl;
         outString = "";
       }
       else
       {
         o << outString << " : row: ";
         o << i;
         o << endl;
         outString = "";
       }
     }
     return outString;
    }

    int **Game::CreateArray(int width, int height) //creates the grid for the map file
    {
     //the height needs to be the outer loop
     mapFile = new int *[height];
     for (int i = 0; i < height; ++i)
     {
       //the width needs to be inner loop
       mapFile[i] = new int[width];
       for (int j = 0; j < width; ++j)
       {
         mapFile[i][j] = 0;
       }
     }
     return mapFile;
    }

    void Game::LoadRowArray(string inString, int lineCount) //loads the array created from the map file
    {
     for(int i = 0; i < inString.length();++i)
     {
       if(inString[i] == '-')
       {
         mapFile[lineCount][i] = 0;
       }
       else
       {
         mapFile[lineCount][i] = 1;
       }
     }
    }
  }
}
}
