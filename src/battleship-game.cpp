#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <limits>

using namespace std;

void createGameBoardPlayerOne();
void menu();
int exitGame();
int singlePlayer(string playerOne);
int twoPlayers(string playerOne, string playerTwo, int scorePlayerOne, int scorePlayerTwo);

void testInput()
{
  // this function works to try to avoid an infinite loop when the player mistakenly enters a char in a integer variable
  if (cin.fail())
  {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

void header()
{
  // this header is the small one, designed for the menu, single player and smaller pages in general
  char normal[] = {0x1b, '[', '0', ';', '3', '9', 'm', 0};
  char cyan[] = {0x1b, '[', '0', ';', '3', '6', 'm', 0};

  cout << cyan << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\";
  cout << "\n\tBattleship Game";
  cout << "\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << normal;
}

void headerTwoPlayers()
{
  // this header is the bigger one, designed for bigger pages in general
  char normal[] = {0x1b, '[', '0', ';', '3', '9', 'm', 0};
  char cyan[] = {0x1b, '[', '0', ';', '3', '6', 'm', 0};

  cout << cyan;
  cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\";
  cout << "\n\t\t\t\t\t\t\t\t  Battleship Game";
  cout << "\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\";
  cout << normal;
}

void returnExitOrPlayAgain(string playerOne)
{
  // this function works to give the opportunity for the player (single player mode) to play again, return to the menu or exit the game. 

  char normal[] = {0x1b, '[', '0', ';', '3', '9', 'm', 0};
  char yellow[] = {0x1b, '[', '0', ';', '3', '3', 'm', 0};
  char cyan[] = {0x1b, '[', '0', ';', '3', '6', 'm', 0};

  int option;

  do
  {
    cout << yellow << "\n\n1 - " << normal << "Play again";
    cout << yellow << "\n2 - " << normal << "Return to the menu";
    cout << yellow << "\n3 - " << normal << "Exit the game";
    cout << cyan << "\n\nEnter an option: " << normal;
    cin >> option;
    testInput();
  } while (option < 1 || option > 3);

  if (option == 1)
  {
    singlePlayer(playerOne);
  }
  else if (option == 2)
  {
    menu();
  }
  else if (option == 2)
  {
    exitGame();
  }
}

void returnExitOrPlayAgainTwoPlayers(string playerOne, string playerTwo, int scorePlayerOne, int scorePlayerTwo)
{
  // this function works to give the opportunity for the players (two players mode) to play again, return to the menu or exit the game. 

  char normal[] = {0x1b, '[', '0', ';', '3', '9', 'm', 0};
  char yellow[] = {0x1b, '[', '0', ';', '3', '3', 'm', 0};
  char cyan[] = {0x1b, '[', '0', ';', '3', '6', 'm', 0};

  int option;

  do
  {
    cout << yellow << "\n\n1 - " << normal << "Play again";
    cout << yellow << "\n2 - " << normal << "Return to the menu";
    cout << yellow << "\n3 - " << normal << "Exit the game";
    cout << cyan << "\n\nEnter an option: " << normal;
    cin >> option;
    testInput();
  } while (option < 1 || option > 3);

  if (option == 1)
  {
    twoPlayers(playerOne, playerTwo, scorePlayerOne, scorePlayerTwo);
  }
  else if (option == 2)
  {
    menu();
  }
  else if (option == 2)
  {
    exitGame();
  }
}

void returnOrExit()
{
  // this function works in the options: instructions and about, giving the opportunity to return to the menu or exit the game (program)

  char normal[] = {0x1b, '[', '0', ';', '3', '9', 'm', 0};
  char yellow[] = {0x1b, '[', '0', ';', '3', '3', 'm', 0};
  char cyan[] = {0x1b, '[', '0', ';', '3', '6', 'm', 0};

  int option;

  do
  {
    cout << yellow << "\n\n1 - " << normal << "Return to the menu";
    cout << yellow << "\n2 - " << normal << "Exit the game";
    cout << cyan << "\n\nEnter an option: " << normal;
    cin >> option;
    testInput();
  } while (option < 1 || option > 2);

  if (option == 1)
  {
    menu();
  }
  else if (option == 2)
  {
    exitGame();
  }
}

int verticalOrHorizontal()
{
  // this function works to support the functions that position the ships by randomly selecting if the ship will be in vertical or horizontal

  int verticalHorizontal = rand() % 2;

  if (verticalHorizontal == 0)
  {
    return 1; // vertical
  }

  if (verticalHorizontal == 1)
  {
    return 2; // horizontal
  }

  return 0;
}

void positionShipsSinglePlayer(char gameBoardPlayerOne[10][10])
{
  // this function works to position the ships in the single player game board randomly

  int numberOfShipsPlayerOne = 0, maximumnumberOfShipsPlayerOne = 5;

  int numberOfDestroyersPlayerOne = 0, maximumNumberOfDestroyersPlayerOne = 1;
  int numberOfSubmarinesPlayerOne = 0, maximumNumberOfSubmarinesPlayerOne = 1;
  int numberOfCruisersPlayerOne = 0, maximumNumberOfCruisersPlayerOne = 1;
  int numberOfBattleshipsPlayerOne = 0, maximumNumberOfBattleshipsPlayerOne = 1;
  int numberOfCarriersPlayerOne = 0, maximumNumberOfCarriersPlayerOne = 1;

  bool destroyerPositionedPlayerOne = false;
  bool submarinePositionedPlayerOne = false;
  bool cruiserPositionedPlayerOne = false;
  bool battleshipPositionedPlayerOne = false;
  bool carrierPositionedPlayerOne = false;

  while (numberOfShipsPlayerOne < maximumnumberOfShipsPlayerOne)
  {

    while (numberOfDestroyersPlayerOne < maximumNumberOfDestroyersPlayerOne && destroyerPositionedPlayerOne == false)
    {

      int aleatoryRow = rand() % 10;

      int aleatoryColumn = rand() % 10;

      if (gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W' && verticalOrHorizontal() == 1)
      {

        if (aleatoryRow < 9 && (gameBoardPlayerOne[aleatoryRow + 1][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn] = 'D';
          gameBoardPlayerOne[aleatoryRow + 1][aleatoryColumn] = 'D';
          destroyerPositionedPlayerOne = true;
        }

        else if ((aleatoryRow <= 9 && aleatoryRow >= 1) && (gameBoardPlayerOne[aleatoryRow - 1][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn] = 'D';
          gameBoardPlayerOne[aleatoryRow - 1][aleatoryColumn] = 'D';
          destroyerPositionedPlayerOne = true;
        }
      }

      if (gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W' && verticalOrHorizontal() == 2)
      {
        if (aleatoryColumn < 9 && (gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 1] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn] = 'D';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 1] = 'D';
          destroyerPositionedPlayerOne = true;
        }

        if ((aleatoryColumn <= 9 && aleatoryColumn >= 1) && (gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 1] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn] = 'D';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 1] = 'D';
          destroyerPositionedPlayerOne = true;
        }
      }
      if (destroyerPositionedPlayerOne == true)
      {
        numberOfDestroyersPlayerOne++;
        numberOfShipsPlayerOne++;
      }
    }

    while (numberOfSubmarinesPlayerOne < maximumNumberOfSubmarinesPlayerOne && submarinePositionedPlayerOne == false)
    {

      int aleatoryRow = rand() % 10;
      int aleatoryColumn = rand() % 10;

      if (gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W' && verticalOrHorizontal() == 1)
      {

        if (aleatoryRow < 8 && (gameBoardPlayerOne[aleatoryRow + 2][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow + 1][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn] = 'S';
          gameBoardPlayerOne[aleatoryRow + 1][aleatoryColumn] = 'S';
          gameBoardPlayerOne[aleatoryRow + 2][aleatoryColumn] = 'S';
          submarinePositionedPlayerOne = true;
        }

        else if (aleatoryRow <= 9 && aleatoryRow >= 2 && (gameBoardPlayerOne[aleatoryRow - 2][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow - 1][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn] = 'S';
          gameBoardPlayerOne[aleatoryRow - 1][aleatoryColumn] = 'S';
          gameBoardPlayerOne[aleatoryRow - 2][aleatoryColumn] = 'S';
          submarinePositionedPlayerOne = true;
        }
      }

      if (gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W' && verticalOrHorizontal() == 2)
      {

        if (aleatoryColumn < 8 && (gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 2] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 1] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn] = 'S';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 1] = 'S';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 2] = 'S';
          submarinePositionedPlayerOne = true;
        }

        if (aleatoryColumn <= 9 && aleatoryColumn > 1 && (gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 2] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 1] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn] = 'S';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 1] = 'S';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 2] = 'S';
          submarinePositionedPlayerOne = true;
        }
      }

      if (submarinePositionedPlayerOne == true)
      {
        numberOfSubmarinesPlayerOne++;
        numberOfShipsPlayerOne++;
      }
    }

    while (numberOfCruisersPlayerOne < maximumNumberOfCruisersPlayerOne && cruiserPositionedPlayerOne == false)
    {
      int aleatoryRow = rand() % 10;
      int aleatoryColumn = rand() % 10;

      if (gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W' && verticalOrHorizontal() == 1)
      {

        if (aleatoryRow < 8 && (gameBoardPlayerOne[aleatoryRow + 2][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow + 1][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn] = 'C';
          gameBoardPlayerOne[aleatoryRow + 1][aleatoryColumn] = 'C';
          gameBoardPlayerOne[aleatoryRow + 2][aleatoryColumn] = 'C';
          cruiserPositionedPlayerOne = true;
        }

        else if (aleatoryRow <= 9 && aleatoryRow > 1 && (gameBoardPlayerOne[aleatoryRow - 2][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow - 1][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn] = 'C';
          gameBoardPlayerOne[aleatoryRow - 1][aleatoryColumn] = 'C';
          gameBoardPlayerOne[aleatoryRow - 2][aleatoryColumn] = 'C';
          cruiserPositionedPlayerOne = true;
        }
      }

      if (gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W' && verticalOrHorizontal() == 2)
      {

        if (aleatoryColumn < 8 && (gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 2] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 1] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn] = 'C';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 1] = 'C';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 2] = 'C';
          cruiserPositionedPlayerOne = true;
        }

        if (aleatoryColumn <= 9 && aleatoryColumn > 1 && (gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 2] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 1] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn] = 'C';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 1] = 'C';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 2] = 'C';
          cruiserPositionedPlayerOne = true;
        }
      }

      if (cruiserPositionedPlayerOne == true)
      {
        numberOfCruisersPlayerOne++;
        numberOfShipsPlayerOne++;
      }
    }

    while (numberOfBattleshipsPlayerOne < maximumNumberOfBattleshipsPlayerOne && battleshipPositionedPlayerOne == false)
    {
      int aleatoryRow = rand() % 10;
      int aleatoryColumn = rand() % 10;

      if (gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W' && verticalOrHorizontal() == 1)
      {

        if (aleatoryRow < 7 && (gameBoardPlayerOne[aleatoryRow + 3][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow + 2][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow + 1][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn] = 'B';
          gameBoardPlayerOne[aleatoryRow + 1][aleatoryColumn] = 'B';
          gameBoardPlayerOne[aleatoryRow + 2][aleatoryColumn] = 'B';
          gameBoardPlayerOne[aleatoryRow + 3][aleatoryColumn] = 'B';
          battleshipPositionedPlayerOne = true;
        }

        else if (aleatoryRow <= 9 && aleatoryRow > 2 && (gameBoardPlayerOne[aleatoryRow - 3][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow - 2][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow - 1][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn] = 'B';
          gameBoardPlayerOne[aleatoryRow - 1][aleatoryColumn] = 'B';
          gameBoardPlayerOne[aleatoryRow - 2][aleatoryColumn] = 'B';
          gameBoardPlayerOne[aleatoryRow - 3][aleatoryColumn] = 'B';
          battleshipPositionedPlayerOne = true;
        }
      }

      if (gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W' && verticalOrHorizontal() == 2)
      {

        if (aleatoryColumn < 7 && (gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 3] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 2] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 1] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn] = 'B';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 1] = 'B';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 2] = 'B';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 3] = 'B';
          battleshipPositionedPlayerOne = true;
        }

        if (aleatoryColumn <= 9 && aleatoryColumn > 2 && (gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 3] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 2] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 1] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn] = 'B';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 1] = 'B';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 2] = 'B';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 3] = 'B';
          battleshipPositionedPlayerOne = true;
        }
      }
      if (battleshipPositionedPlayerOne == true)
      {
        numberOfBattleshipsPlayerOne++;
        numberOfShipsPlayerOne++;
      }
    }

    while (numberOfCarriersPlayerOne < maximumNumberOfCarriersPlayerOne)
    {
      int aleatoryRow = rand() % 10;
      int aleatoryColumn = rand() % 10;

      if (gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W' && verticalOrHorizontal() == 1)
      {

        if (aleatoryRow < 6 && (gameBoardPlayerOne[aleatoryRow + 4][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow + 3][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow + 2][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow + 1][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn] = 'K';
          gameBoardPlayerOne[aleatoryRow + 1][aleatoryColumn] = 'K';
          gameBoardPlayerOne[aleatoryRow + 2][aleatoryColumn] = 'K';
          gameBoardPlayerOne[aleatoryRow + 3][aleatoryColumn] = 'K';
          gameBoardPlayerOne[aleatoryRow + 4][aleatoryColumn] = 'K';
          carrierPositionedPlayerOne = true;
        }

        else if (aleatoryRow <= 9 && aleatoryRow > 3 && (gameBoardPlayerOne[aleatoryRow - 4][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow - 3][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow - 2][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow - 1][aleatoryColumn] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn] = 'K';
          gameBoardPlayerOne[aleatoryRow - 1][aleatoryColumn] = 'K';
          gameBoardPlayerOne[aleatoryRow - 2][aleatoryColumn] = 'K';
          gameBoardPlayerOne[aleatoryRow - 3][aleatoryColumn] = 'K';
          gameBoardPlayerOne[aleatoryRow - 4][aleatoryColumn] = 'K';
          carrierPositionedPlayerOne = true;
        }
      }

      if (gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W' && verticalOrHorizontal() == 2)
      {

        if (aleatoryColumn < 6 && (gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 4] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 3] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 2] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 1] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn] = 'K';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 1] = 'K';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 2] = 'K';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 3] = 'K';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn + 4] = 'K';
          carrierPositionedPlayerOne = true;
        }

        if (aleatoryColumn <= 9 && aleatoryColumn > 3 && (gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 4] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 3] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 2] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 1] == 'W' && gameBoardPlayerOne[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn] = 'K';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 1] = 'K';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 2] = 'K';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 3] = 'K';
          gameBoardPlayerOne[aleatoryRow][aleatoryColumn - 4] = 'K';
          carrierPositionedPlayerOne = true;
        }
      }
      if (carrierPositionedPlayerOne == true)
      {
        numberOfCarriersPlayerOne++;
        numberOfShipsPlayerOne++;
      }
    }
  }
}

void positionShipsTwoPlayers(char gameBoardPlayerOne[10][10], char gameBoardPlayerTwo[10][10])
{
  // this function randomly position the ships to two players mode by using the function of the single player and adding the ships for the second player

  positionShipsSinglePlayer(gameBoardPlayerOne); // uses the function that position the ships for the single player

  int numberOfShipsPlayerTwo = 0, maximumnumberOfShipsPlayerTwo = 5;

  int numberOfDestroyersPlayerTwo = 0, maximumNumberOfDestroyersPlayerTwo = 1;
  int numberOfSubmarinesPlayerTwo = 0, maximumNumberOfSubmarinesPlayerTwo = 1;
  int numberOfCruisersPlayerTwo = 0, maximumNumberOfCruisersPlayerTwo = 1;
  int numberOfBattleshipsPlayerTwo = 0, maximumNumberOfBattleshipsPlayerTwo = 1;
  int numberOfCarriersPlayerTwo = 0, maximumNumberOfCarriersPlayerTwo = 1;

  bool destroyerPositionedPlayerTwo = false;
  bool submarinePositionedPlayerTwo = false;
  bool cruiserPositionedPlayerTwo = false;
  bool battleshipPositionedPlayerTwo = false;
  bool carrierPositionedPlayerTwo = false;

  while (numberOfShipsPlayerTwo < maximumnumberOfShipsPlayerTwo)
  {

    while (numberOfDestroyersPlayerTwo < maximumNumberOfDestroyersPlayerTwo && destroyerPositionedPlayerTwo == false)
    {

      int aleatoryRow = rand() % 10;

      int aleatoryColumn = rand() % 10;

      if (gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W' && verticalOrHorizontal() == 1 /* VERTICAL */)
      {

        if (aleatoryRow < 9 && (gameBoardPlayerTwo[aleatoryRow + 1][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] = 'D';
          gameBoardPlayerTwo[aleatoryRow + 1][aleatoryColumn] = 'D';
          destroyerPositionedPlayerTwo = true;
        }

        else if ((aleatoryRow <= 9 && aleatoryRow >= 1) && (gameBoardPlayerTwo[aleatoryRow - 1][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] = 'D';
          gameBoardPlayerTwo[aleatoryRow - 1][aleatoryColumn] = 'D';
          destroyerPositionedPlayerTwo = true;
        }
      }

      if (gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W' && verticalOrHorizontal() == 2 /* HORIZONTAL */)
      {
        if (aleatoryColumn < 9 && (gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 1] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] = 'D';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 1] = 'D';
          destroyerPositionedPlayerTwo = true;
        }

        if ((aleatoryColumn <= 9 && aleatoryColumn >= 1) && (gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 1] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] = 'D';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 1] = 'D';
          destroyerPositionedPlayerTwo = true;
        }
      }
      if (destroyerPositionedPlayerTwo == true)
      {
        numberOfDestroyersPlayerTwo++;
        numberOfShipsPlayerTwo++;
      }
    }

    while (numberOfSubmarinesPlayerTwo < maximumNumberOfSubmarinesPlayerTwo && submarinePositionedPlayerTwo == false)
    {
      int aleatoryRow = rand() % 10;
      int aleatoryColumn = rand() % 10;

      if (gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W' && verticalOrHorizontal() == 1)
      {

        if (aleatoryRow < 8 && (gameBoardPlayerTwo[aleatoryRow + 2][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow + 1][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] = 'S';
          gameBoardPlayerTwo[aleatoryRow + 1][aleatoryColumn] = 'S';
          gameBoardPlayerTwo[aleatoryRow + 2][aleatoryColumn] = 'S';
          submarinePositionedPlayerTwo = true;
        }

        else if (aleatoryRow <= 9 && aleatoryRow >= 2 && (gameBoardPlayerTwo[aleatoryRow - 2][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow - 1][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] = 'S';
          gameBoardPlayerTwo[aleatoryRow - 1][aleatoryColumn] = 'S';
          gameBoardPlayerTwo[aleatoryRow - 2][aleatoryColumn] = 'S';
          submarinePositionedPlayerTwo = true;
        }
      }

      if (gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W' && verticalOrHorizontal() == 2)
      {

        if (aleatoryColumn < 8 && (gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 2] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 1] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] = 'S';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 1] = 'S';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 2] = 'S';
          submarinePositionedPlayerTwo = true;
        }

        if (aleatoryColumn <= 9 && aleatoryColumn > 1 && (gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 2] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 1] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] = 'S';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 1] = 'S';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 2] = 'S';
          submarinePositionedPlayerTwo = true;
        }
      }

      if (submarinePositionedPlayerTwo == true)
      {
        numberOfSubmarinesPlayerTwo++;
        numberOfShipsPlayerTwo++;
      }
    }

    while (numberOfCruisersPlayerTwo < maximumNumberOfCruisersPlayerTwo && cruiserPositionedPlayerTwo == false)
    {
      int aleatoryRow = rand() % 10;
      int aleatoryColumn = rand() % 10;

      if (gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W' && verticalOrHorizontal() == 1)
      {

        if (aleatoryRow < 8 && (gameBoardPlayerTwo[aleatoryRow + 2][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow + 1][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] = 'C';
          gameBoardPlayerTwo[aleatoryRow + 1][aleatoryColumn] = 'C';
          gameBoardPlayerTwo[aleatoryRow + 2][aleatoryColumn] = 'C';
          cruiserPositionedPlayerTwo = true;
        }

        else if (aleatoryRow <= 9 && aleatoryRow > 1 && (gameBoardPlayerTwo[aleatoryRow - 2][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow - 1][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] = 'C';
          gameBoardPlayerTwo[aleatoryRow - 1][aleatoryColumn] = 'C';
          gameBoardPlayerTwo[aleatoryRow - 2][aleatoryColumn] = 'C';
          cruiserPositionedPlayerTwo = true;
        }
      }

      if (gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W' && verticalOrHorizontal() == 2)
      {

        if (aleatoryColumn < 8 && (gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 2] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 1] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] = 'C';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 1] = 'C';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 2] = 'C';
          cruiserPositionedPlayerTwo = true;
        }

        if (aleatoryColumn <= 9 && aleatoryColumn > 1 && (gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 2] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 1] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] = 'C';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 1] = 'C';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 2] = 'C';
          cruiserPositionedPlayerTwo = true;
        }
      }

      if (cruiserPositionedPlayerTwo == true)
      {
        numberOfCruisersPlayerTwo++;
        numberOfShipsPlayerTwo++;
      }
    }

    while (numberOfBattleshipsPlayerTwo < maximumNumberOfBattleshipsPlayerTwo && battleshipPositionedPlayerTwo == false)
    {
      int aleatoryRow = rand() % 10;
      int aleatoryColumn = rand() % 10;

      if (gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W' && verticalOrHorizontal() == 1)
      {

        if (aleatoryRow < 7 && (gameBoardPlayerTwo[aleatoryRow + 3][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow + 2][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow + 1][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] = 'B';
          gameBoardPlayerTwo[aleatoryRow + 1][aleatoryColumn] = 'B';
          gameBoardPlayerTwo[aleatoryRow + 2][aleatoryColumn] = 'B';
          gameBoardPlayerTwo[aleatoryRow + 3][aleatoryColumn] = 'B';
          battleshipPositionedPlayerTwo = true;
        }

        else if (aleatoryRow <= 9 && aleatoryRow > 2 && (gameBoardPlayerTwo[aleatoryRow - 3][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow - 2][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow - 1][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] = 'B';
          gameBoardPlayerTwo[aleatoryRow - 1][aleatoryColumn] = 'B';
          gameBoardPlayerTwo[aleatoryRow - 2][aleatoryColumn] = 'B';
          gameBoardPlayerTwo[aleatoryRow - 3][aleatoryColumn] = 'B';
          battleshipPositionedPlayerTwo = true;
        }
      }

      if (gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W' && verticalOrHorizontal() == 2)
      {

        if (aleatoryColumn < 7 && (gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 3] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 2] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 1] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] = 'B';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 1] = 'B';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 2] = 'B';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 3] = 'B';
          battleshipPositionedPlayerTwo = true;
        }

        if (aleatoryColumn <= 9 && aleatoryColumn > 2 && (gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 3] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 2] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 1] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] = 'B';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 1] = 'B';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 2] = 'B';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 3] = 'B';
          battleshipPositionedPlayerTwo = true;
        }
      }
      if (battleshipPositionedPlayerTwo == true)
      {
        numberOfBattleshipsPlayerTwo++;
        numberOfShipsPlayerTwo++;
      }
    }

    while (numberOfCarriersPlayerTwo < maximumNumberOfCarriersPlayerTwo)
    {
      int aleatoryRow = rand() % 10;
      int aleatoryColumn = rand() % 10;

      if (gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W' && verticalOrHorizontal() == 1)
      {

        if (aleatoryRow < 6 && (gameBoardPlayerTwo[aleatoryRow + 4][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow + 3][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow + 2][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow + 1][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] = 'K';
          gameBoardPlayerTwo[aleatoryRow + 1][aleatoryColumn] = 'K';
          gameBoardPlayerTwo[aleatoryRow + 2][aleatoryColumn] = 'K';
          gameBoardPlayerTwo[aleatoryRow + 3][aleatoryColumn] = 'K';
          gameBoardPlayerTwo[aleatoryRow + 4][aleatoryColumn] = 'K';
          carrierPositionedPlayerTwo = true;
        }

        else if (aleatoryRow <= 9 && aleatoryRow > 3 && (gameBoardPlayerTwo[aleatoryRow - 4][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow - 3][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow - 2][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow - 1][aleatoryColumn] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] = 'K';
          gameBoardPlayerTwo[aleatoryRow - 1][aleatoryColumn] = 'K';
          gameBoardPlayerTwo[aleatoryRow - 2][aleatoryColumn] = 'K';
          gameBoardPlayerTwo[aleatoryRow - 3][aleatoryColumn] = 'K';
          gameBoardPlayerTwo[aleatoryRow - 4][aleatoryColumn] = 'K';
          carrierPositionedPlayerTwo = true;
        }
      }

      if (gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W' && verticalOrHorizontal() == 2)
      {

        if (aleatoryColumn < 6 && (gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 4] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 3] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 2] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 1] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] = 'K';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 1] = 'K';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 2] = 'K';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 3] = 'K';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn + 4] = 'K';
          carrierPositionedPlayerTwo = true;
        }

        if (aleatoryColumn <= 9 && aleatoryColumn > 3 && (gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 4] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 3] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 2] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 1] == 'W' && gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] == 'W'))
        {
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn] = 'K';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 1] = 'K';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 2] = 'K';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 3] = 'K';
          gameBoardPlayerTwo[aleatoryRow][aleatoryColumn - 4] = 'K';
          carrierPositionedPlayerTwo = true;
        }
      }
      if (carrierPositionedPlayerTwo == true)
      {
        numberOfCarriersPlayerTwo++;
        numberOfShipsPlayerTwo++;
      }
    }
  }
}

int exitGame()
{
  system("CLS");

  cout << "Bye!";

  system("CLS");

  exit(1);

  return 1;
}

void createGameBoardPlayerOne(char gameBoardPlayerOne[10][10])
{

  int row, column;

  for (row = 0; row < 10; row++)
  {
    for (column = 0; column < 10; column++)
    {
      gameBoardPlayerOne[row][column] = 'W';
    }
  }
}

void createGameBoardPlayerTwo(char gameBoardPlayerTwo[10][10])
{

  int row, column;

  for (row = 0; row < 10; row++)
  {
    for (column = 0; column < 10; column++)
    {
      gameBoardPlayerTwo[row][column] = 'W';
    }
  }
}

void createMaskPlayerOne(char gameMaskPlayerOne[10][10])
{
  int row, column;

  for (row = 0; row < 10; row++)
  {
    for (column = 0; column < 10; column++)
    {
      gameMaskPlayerOne[row][column] = '*';
    }
  }
}

void createMaskPlayerTwo(char gameMaskPlayerTwo[10][10])
{

  int row, column;

  for (row = 0; row < 10; row++)
  {
    for (column = 0; column < 10; column++)
    {
      gameMaskPlayerTwo[row][column] = '*';
    }
  }
}

void displayGameMaskSinglePlayer(char gameMaskPlayerOne[10][10], char gameBoardPlayerTwo[10][10])
{

  // there was a need to create different functions to display the game mask due to the spaces and general displaying on the screen
  
  char normal[] = {0x1b, '[', '0', ';', '3', '9', 'm', 0};
  char red[] = {0x1b, '[', '0', ';', '3', '1', 'm', 0};
  char green[] = {0x1b, '[', '0', ';', '3', '2', 'm', 0};
  char yellow[] = {0x1b, '[', '0', ';', '3', '3', 'm', 0};
  char blue[] = {0x1b, '[', '0', ';', '3', '4', 'm', 0};

  int row, column;
  int numericRow = 0, numericColumn = 0;
  int count;

  char letters[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

  cout << "\n\n";

  cout << "     ";
  for (count = 1; count < 11; count++)
  {
    cout << yellow << " " << count;
    cout << normal;
  }

  cout << "\n";

  cout << "     ";

  for (count = 0; count < 10; count++)
  {
    cout << normal << " |";
  }

  cout << "\n";

  for (row = 0; row < 10; row++)
  {
    cout << yellow << letters[numericRow] << normal << " -- ";
    cout << normal;
    numericRow++;
    for (column = 0; column < 10; column++)
    {
      switch (gameMaskPlayerOne[row][column])
      {
      case 'W':
        cout << blue << " " << gameMaskPlayerOne[row][column] << normal;
        break;
      case 'X':
        cout << red << " " << gameMaskPlayerOne[row][column] << normal;
        break;
      case 'D':
        cout << green << " " << gameMaskPlayerOne[row][column] << normal;
        break;
      case 'C':
        cout << green << " " << gameMaskPlayerOne[row][column] << normal;
        break;
      case 'S':
        cout << green << " " << gameMaskPlayerOne[row][column] << normal;
        break;
      case 'B':
        cout << green << " " << gameMaskPlayerOne[row][column] << normal;
        break;
      case 'K':
        cout << green << " " << gameMaskPlayerOne[row][column] << normal;
        break;
      default:
        cout << " " << gameMaskPlayerOne[row][column];
      }
    }
    cout << "\n";
  }
}

void displayGameMaskPlayerOne(char gameMaskPlayerOne[10][10], char gameBoardPlayerOne[10][10])
{

  char normal[] = {0x1b, '[', '0', ';', '3', '9', 'm', 0};
  char red[] = {0x1b, '[', '0', ';', '3', '1', 'm', 0};
  char green[] = {0x1b, '[', '0', ';', '3', '2', 'm', 0};
  char yellow[] = {0x1b, '[', '0', ';', '3', '3', 'm', 0};
  char blue[] = {0x1b, '[', '0', ';', '3', '4', 'm', 0};

  int row, column;
  int numericRow = 0, numericColumn = 0;
  int count;

  char letters[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

  cout << "\n\n";

  cout << "\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033\t\t\t\t\t\t\t\t\t\t";

  cout << "1";
  cout << "     ";
  for (count = 1; count < 11; count++)
  {
    cout << yellow << " " << count;
  }

  cout << "\n";

  cout << "     \t\t\t\t\t\t\t\t\t\t     ";

  for (count = 0; count < 10; count++)
  {
    cout << normal << " |";
  }

  cout << "\n";
  cout << "\t\t\t\t\t\t\t\t\t\t";
  for (row = 0; row < 10; row++)
  {
    cout << yellow << letters[numericRow] << normal << " -- ";
    numericRow++;
    for (column = 0; column < 10; column++)
    {
      switch (gameMaskPlayerOne[row][column])
      {
      case 'W':
        cout << blue << " " << gameMaskPlayerOne[row][column] << normal;
        break;
      case 'X':
        cout << red << " " << gameMaskPlayerOne[row][column] << normal;
        break;
      case 'D':
        cout << green << " " << gameMaskPlayerOne[row][column] << normal;
        break;
      case 'C':
        cout << green << " " << gameMaskPlayerOne[row][column] << normal;
        break;
      case 'S':
        cout << green << " " << gameMaskPlayerOne[row][column] << normal;
        break;
      case 'B':
        cout << green << " " << gameMaskPlayerOne[row][column] << normal;
        break;
      case 'K':
        cout << green << " " << gameMaskPlayerOne[row][column] << normal;
        break;
      default:
        cout << " " << gameMaskPlayerOne[row][column];
      }
    }
    cout << "\n";
    cout << "\t\t\t\t\t\t\t\t\t\t";
  }
}

void displayGameMaskPlayerTwo(char gameMaskPlayerTwo[10][10], char gameBoardPlayerTwo[10][10])
{

  char normal[] = {0x1b, '[', '0', ';', '3', '9', 'm', 0};
  char red[] = {0x1b, '[', '0', ';', '3', '1', 'm', 0};
  char green[] = {0x1b, '[', '0', ';', '3', '2', 'm', 0};
  char yellow[] = {0x1b, '[', '0', ';', '3', '3', 'm', 0};
  char blue[] = {0x1b, '[', '0', ';', '3', '4', 'm', 0};

  int row, column;
  int numericRow = 0, numericColumn = 0;
  int count;

  char letters[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

  cout << "\n\n";

  cout << "     ";
  for (count = 1; count < 11; count++)
  {
    cout << yellow << " " << count;
    cout << normal;
  }

  cout << "\n";

  cout << "     ";

  for (count = 0; count < 10; count++)
  {
    cout << normal << " |";
  }

  cout << "\n";

  for (row = 0; row < 10; row++)
  {
    cout << yellow << letters[numericRow] << normal << " -- ";
    cout << normal;
    numericRow++;
    for (column = 0; column < 10; column++)
    {
      switch (gameMaskPlayerTwo[row][column])
      {
      case 'W':
        cout << blue << " " << gameMaskPlayerTwo[row][column] << normal;
        break;
      case 'X':
        cout << red << " " << gameMaskPlayerTwo[row][column] << normal;
        break;
      case 'D':
        cout << green << " " << gameMaskPlayerTwo[row][column] << normal;
        break;
      case 'C':
        cout << green << " " << gameMaskPlayerTwo[row][column] << normal;
        break;
      case 'S':
        cout << green << " " << gameMaskPlayerTwo[row][column] << normal;
        break;
      case 'B':
        cout << green << " " << gameMaskPlayerTwo[row][column] << normal;
        break;
      case 'K':
        cout << green << " " << gameMaskPlayerTwo[row][column] << normal;
        break;
      default:
        cout << " " << gameMaskPlayerTwo[row][column];
      }
    }
    cout << "\n";
  }
}

void displayGameBoardPlayerOne(char gameBoardPlayerOne[10][10], int manualPosition)
{

  char normal[] = {0x1b, '[', '0', ';', '3', '9', 'm', 0};
  char green[] = {0x1b, '[', '0', ';', '3', '2', 'm', 0};
  char yellow[] = {0x1b, '[', '0', ';', '3', '3', 'm', 0};
  char blue[] = {0x1b, '[', '0', ';', '3', '4', 'm', 0};

  int row, column;
  int numericRow;
  int count;
  char letters[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
  cout << "\n\n";

  if (manualPosition == 0)
  {
    cout << "\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\t\t\t\t";
  }

  if (manualPosition == 2)
  {
    cout << "\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\t\t\t\t";
  }

  cout << "     ";

  if (manualPosition == 2)
  {
    cout << "\033[A\033[A\033[A                                                ";
  }

  for (count = 1; count < 11; count++)
  {
    cout << yellow << " " << count << normal;
  }

  cout << "\n";

  cout << "     ";

  if (manualPosition == 2)
  {
    cout << normal << " | | | | | | | | | |                                                            ";
  }

  for (count = 0; count < 10; count++)
  {
    cout << " |";
  }

  cout << "\n";
  if (manualPosition == 2)
  {
    cout << "\t\t\t\t\t\t\t\t\t\t";
  }
  numericRow = 0;
  for (row = 0; row < 10; row++)
  {
    cout << yellow << letters[numericRow] << normal << " -- ";
    numericRow++;
    for (column = 0; column < 10; column++)
    {
      switch (gameBoardPlayerOne[row][column])
      {
      case 'W':
        cout << blue << " " << gameBoardPlayerOne[row][column] << normal;
        break;
      case 'D':
        cout << green << " " << gameBoardPlayerOne[row][column] << normal;
        break;
      case 'C':
        cout << green << " " << gameBoardPlayerOne[row][column] << normal;
        break;
      case 'S':
        cout << green << " " << gameBoardPlayerOne[row][column] << normal;
        break;
      case 'B':
        cout << green << " " << gameBoardPlayerOne[row][column] << normal;
        break;
      case 'K':
        cout << green << " " << gameBoardPlayerOne[row][column] << normal;
        break;
      default:
        cout << " " << gameBoardPlayerOne[row][column];
      }
    }
    cout << "\n";
    if (manualPosition == 2)
    {
      cout << "\t\t\t\t\t\t\t\t\t\t";
    }
  }
}

void displayGameBoardPlayerTwo(char gameBoardPlayerTwo[10][10])
{

  char normal[] = {0x1b, '[', '0', ';', '3', '9', 'm', 0};
  char green[] = {0x1b, '[', '0', ';', '3', '2', 'm', 0};
  char yellow[] = {0x1b, '[', '0', ';', '3', '3', 'm', 0};
  char blue[] = {0x1b, '[', '0', ';', '3', '4', 'm', 0};

  int row, column;
  int numericRow;
  int count;
  char letters[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
  cout << "\n\n";
  cout << "\n\n\n";

  cout << "     ";
  for (count = 1; count < 11; count++)
  {
    cout << yellow << " " << count << normal;
  }

  cout << "\n";

  cout << "     ";

  for (count = 0; count < 10; count++)
  {
    cout << " |";
  }

  cout << "\n";
  numericRow = 0;
  for (row = 0; row < 10; row++)
  {
    cout << yellow << letters[numericRow] << normal << " -- ";
    numericRow++;
    for (column = 0; column < 10; column++)
    {
      switch (gameBoardPlayerTwo[row][column])
      {
      case 'W':
        cout << blue << " " << gameBoardPlayerTwo[row][column] << normal;
        break;
      case 'D':
        cout << green << " " << gameBoardPlayerTwo[row][column] << normal;
        break;
      case 'C':
        cout << green << " " << gameBoardPlayerTwo[row][column] << normal;
        break;
      case 'S':
        cout << green << " " << gameBoardPlayerTwo[row][column] << normal;
        break;
      case 'B':
        cout << green << " " << gameBoardPlayerTwo[row][column] << normal;
        break;
      case 'K':
        cout << green << " " << gameBoardPlayerTwo[row][column] << normal;
        break;
      default:
        cout << " " << gameBoardPlayerTwo[row][column];
      }
    }
    cout << "\n";
  }
}

void manualPositionShips(char gameBoardPlayerOne[10][10], char gameBoardPlayerTwo[10][10], string playerOne, string playerTwo)
{
  // this whole function is meant to give the player the freedom to position the ships without exploring failures to cheat
  // if the player tries to cheat with any failure that may be in this code, the positioning won't end and the player will have to exit the game
  // !work on a implementation to avoid such failures to happen!

  char normal[] = {0x1b, '[', '0', ';', '3', '9', 'm', 0};
  char yellow[] = {0x1b, '[', '0', ';', '3', '3', 'm', 0};
  char purple[] = {0x1b, '[', '0', ';', '3', '5', 'm', 0};
  char green[] = {0x1b, '[', '0', ';', '3', '2', 'm', 0};

  char letters[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

  int i;

  int numberOfShipsPlayerOne = 0, maximumNumberOfShipsPlayerOne = 5;

  int numberOfDestroyersPlayerOne = 0, maximumNumberOfDestroyersPlayerOne = 1;
  int numberOfSubmarinesPlayerOne = 0, maximumNumberOfSubmarinesPlayerOne = 1;
  int numberOfCruisersPlayerOne = 0, maximumNumberOfCruisersPlayerOne = 1;
  int numberOfBattleshipsPlayerOne = 0, maximumNumberOfBattleshipsPlayerOne = 1;
  int numberOfCarriersPlayerOne = 0, maximumNumberOfCarriersPlayerOne = 1;

  bool destroyerPositionedPlayerOne = false;
  bool submarinePositionedPlayerOne = false;
  bool cruiserPositionedPlayerOne = false;
  bool battleshipPositionedPlayerOne = false;
  bool carrierPositionedPlayerOne = false;

  while (numberOfShipsPlayerOne < maximumNumberOfShipsPlayerOne)
  {

    while (numberOfDestroyersPlayerOne < maximumNumberOfDestroyersPlayerOne && destroyerPositionedPlayerOne == false)
    {

      int chosenColumn;

      int destroyerPositions = 0;

      bool validPosition = false;

      char chosenRow;

      int rowAttempt;

      if (destroyerPositions == 0)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerOne(gameBoardPlayerOne, 1);
          cout << yellow << "\n\nPOSITIONING DESTROYER: D D" << normal;
          cout << purple << "\n\n[" << playerOne << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerOne << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;

          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerOne[rowAttempt][chosenColumn] = 'D';
      destroyerPositions++;

      validPosition = false;

      if (destroyerPositions == 1)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerOne(gameBoardPlayerOne, 1);
          cout << yellow << "\n\nPOSITIONING DESTROYER: D D" << normal;
          cout << purple << "\n\n[" << playerOne << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerOne << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'D') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'D') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'D') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'D'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerOne[rowAttempt][chosenColumn] = 'D';
      destroyerPositions++;

      if (destroyerPositions == 2)
      {
        destroyerPositionedPlayerOne = true;
        numberOfDestroyersPlayerOne++;
        numberOfShipsPlayerOne++;
      }
    }

    while (numberOfSubmarinesPlayerOne < maximumNumberOfSubmarinesPlayerOne && submarinePositionedPlayerOne == false)
    {

      int chosenColumn;

      int submarinePositions = 0;

      bool validPosition = false;

      char chosenRow;

      int rowAttempt;

      if (submarinePositions == 0)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerOne(gameBoardPlayerOne, 1);
          cout << yellow << "\n\nPOSITIONING SUBMARINE: S S S" << normal;
          cout << purple << "\n\n[" << playerOne << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerOne << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerOne[rowAttempt][chosenColumn] = 'S';
      submarinePositions++;

      validPosition = false;

      if (submarinePositions == 1)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerOne(gameBoardPlayerOne, 1);
          cout << yellow << "\n\nPOSITIONING SUBMARINE: S S S" << normal;
          cout << purple << "\n\n[" << playerOne << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerOne << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'S' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'S' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'S') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'S') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'S' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'S' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'S') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'S') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'S' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'S') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'S' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'S'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerOne[rowAttempt][chosenColumn] = 'S';
      submarinePositions++;

      validPosition = false;

      if (submarinePositions == 2)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerOne(gameBoardPlayerOne, 1);
          cout << yellow << "\n\nPOSITIONING SUBMARINE: S S S" << normal;
          cout << purple << "\n\n[" << playerOne << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerOne << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'S' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'S') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'S' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'S') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'S' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'S') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'S' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'S') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'S' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'S') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'S' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'S'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerOne[rowAttempt][chosenColumn] = 'S';
      submarinePositions++;

      if (submarinePositions == 3)
      {
        submarinePositionedPlayerOne = true;
        numberOfSubmarinesPlayerOne++;
        numberOfShipsPlayerOne++;
      }
    }

    while (numberOfCruisersPlayerOne < maximumNumberOfCruisersPlayerOne && cruiserPositionedPlayerOne == false)
    {

      int rowAttempt;

      int chosenColumn;

      int cruiserPositions = 0;

      bool validPosition = false;

      char chosenRow;

      if (cruiserPositions == 0)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerOne(gameBoardPlayerOne, 1);
          cout << yellow << "\n\nPOSITIONING CRUISER: C C C" << normal;
          cout << purple << "\n\n[" << playerOne << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerOne << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerOne[rowAttempt][chosenColumn] = 'C';
      cruiserPositions++;

      validPosition = false;

      if (cruiserPositions == 1)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerOne(gameBoardPlayerOne, 1);
          cout << yellow << "\n\nPOSITIONING CRUISER: C C C" << normal;
          cout << purple << "\n\n[" << playerOne << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerOne << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'C' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'C' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'C') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'C') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'C' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'C' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'C') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'C') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'C' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'C') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'C' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'C'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerOne[rowAttempt][chosenColumn] = 'C';
      cruiserPositions++;

      validPosition = false;

      if (cruiserPositions == 2)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerOne(gameBoardPlayerOne, 1);
          cout << yellow << "\n\nPOSITIONING CRUISER: C C C" << normal;
          cout << purple << "\n\n[" << playerOne << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerOne << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'C' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'C') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'C' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'C') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'C' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'C') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'C' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'C') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'C' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'C') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'C' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'C'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerOne[rowAttempt][chosenColumn] = 'C';
      cruiserPositions++;

      if (cruiserPositions == 3)
      {
        cruiserPositionedPlayerOne = true;
        numberOfCruisersPlayerOne++;
        numberOfShipsPlayerOne++;
      }
    }

    while (numberOfBattleshipsPlayerOne < maximumNumberOfBattleshipsPlayerOne && battleshipPositionedPlayerOne == false)
    {

      int rowAttempt;

      int chosenColumn;

      int battleshipPositions = 0;

      bool validPosition = false;

      char chosenRow;

      if (battleshipPositions == 0)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerOne(gameBoardPlayerOne, 1);
          cout << yellow << "\n\nPOSITIONING BATTLESHIP: B B B B" << normal;
          cout << purple << "\n\n[" << playerOne << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerOne << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerOne[rowAttempt][chosenColumn] = 'B';
      battleshipPositions++;

      validPosition = false;

      if (battleshipPositions == 1)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerOne(gameBoardPlayerOne, 1);
          cout << yellow << "\n\nPOSITIONING BATTLESHIP: B B B B" << normal;
          cout << purple << "\n\n[" << playerOne << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerOne << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerOne[rowAttempt][chosenColumn] = 'B';
      battleshipPositions++;

      validPosition = false;

      if (battleshipPositions == 2)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerOne(gameBoardPlayerOne, 1);
          cout << yellow << "\n\nPOSITIONING BATTLESHIP: B B B B" << normal;
          cout << purple << "\n\n[" << playerOne << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerOne << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'B'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerOne[rowAttempt][chosenColumn] = 'B';
      battleshipPositions++;

      validPosition = false;

      if (battleshipPositions == 3)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerOne(gameBoardPlayerOne, 1);
          cout << yellow << "\n\nPOSITIONING BATTLESHIP: B B B B" << normal;
          cout << purple << "\n\n[" << playerOne << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerOne << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'B') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'B' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'B'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerOne[rowAttempt][chosenColumn] = 'B';
      battleshipPositions++;

      if (battleshipPositions == 4)
      {
        battleshipPositionedPlayerOne = true;
        numberOfBattleshipsPlayerOne++;
        numberOfShipsPlayerOne++;
      }
    }

    while (numberOfCarriersPlayerOne < maximumNumberOfCarriersPlayerOne && carrierPositionedPlayerOne == false)
    {

      int rowAttempt;

      int chosenColumn;

      int carrierPositions = 0;

      bool validPosition = false;

      char chosenRow;

      if (carrierPositions == 0)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerOne(gameBoardPlayerOne, 1);
          cout << yellow << "\n\nPOSITIONING CARRIER: K K K K K" << normal;
          cout << purple << "\n\n[" << playerOne << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerOne << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 4][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 4][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 4] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 4] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerOne[rowAttempt][chosenColumn] = 'K';
      carrierPositions++;

      validPosition = false;

      if (carrierPositions == 1)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerOne(gameBoardPlayerOne, 1);
          cout << yellow << "\n\nPOSITIONING CARRIER: K K K K K" << normal;
          cout << purple << "\n\n[" << playerOne << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerOne << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 4][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 4][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 4][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 4][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 4][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 4][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 4][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 4][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 4] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 4] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 4] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 4] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 4] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 4] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 4] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 4] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerOne[rowAttempt][chosenColumn] = 'K';
      carrierPositions++;

      validPosition = false;

      if (carrierPositions == 2)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerOne(gameBoardPlayerOne, 1);
          cout << yellow << "\n\nPOSITIONING CARRIER: K K K K K" << normal;
          cout << purple << "\n\n[" << playerOne << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerOne << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 4][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 4][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 4][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 4][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 4][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 4][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 4][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 4][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 4][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 4][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 4][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 4][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 4] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 4] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 4] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 4] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 4] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 4] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 4] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 4] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 4] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 4] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 4] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 4] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerOne[rowAttempt][chosenColumn] = 'K';
      carrierPositions++;

      validPosition = false;

      if (carrierPositions == 3)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerOne(gameBoardPlayerOne, 1);
          cout << yellow << "\n\nPOSITIONING CARRIER: K K K K K" << normal;
          cout << purple << "\n\n[" << playerOne << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerOne << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 4][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 4][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 4][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 4][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 4][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 4][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 4][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 4][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 4] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 4] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 4] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 4] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 4] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 4] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 4] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 4] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerOne[rowAttempt][chosenColumn] = 'K';
      carrierPositions++;

      validPosition = false;

      if (carrierPositions == 4)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerOne(gameBoardPlayerOne, 1);
          cout << yellow << "\n\nPOSITIONING CARRIER: K K K K K" << normal;
          cout << purple << "\n\n[" << playerOne << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerOne << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 4][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 4][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 4] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 4] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 3][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 3][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 3] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerOne[rowAttempt + 2][chosenColumn] == 'K') || (gameBoardPlayerOne[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerOne[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerOne[rowAttempt][chosenColumn + 2] == 'K'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerOne[rowAttempt][chosenColumn] = 'K';
      carrierPositions++;

      if (carrierPositions == 5)
      {
        carrierPositionedPlayerOne = true;
        numberOfCarriersPlayerOne++;
        numberOfShipsPlayerOne++;
      }
    }
  }

  int numberOfShipsPlayerTwo = 0, maximumnumberOfShipsPlayerTwo = 5;

  int numberOfDestroyersPlayerTwo = 0, maximumNumberOfDestroyersPlayerTwo = 1;
  int numberOfSubmarinesPlayerTwo = 0, maximumNumberOfSubmarinesPlayerTwo = 1;
  int numberOfCruisersPlayerTwo = 0, maximumNumberOfCruisersPlayerTwo = 1;
  int numberOfBattleshipsPlayerTwo = 0, maximumNumberOfBattleshipsPlayerTwo = 1;
  int numberOfCarriersPlayerTwo = 0, maximumNumberOfCarriersPlayerTwo = 1;

  bool destroyerPositionedPlayerTwo = false;
  bool submarinePositionedPlayerTwo = false;
  bool cruiserPositionedPlayerTwo = false;
  bool battleshipPositionedPlayerTwo = false;
  bool carrierPositionedPlayerTwo = false;

  while (numberOfShipsPlayerTwo < maximumnumberOfShipsPlayerTwo)
  {

    while (numberOfDestroyersPlayerTwo < maximumNumberOfDestroyersPlayerTwo && destroyerPositionedPlayerTwo == false)
    {

      int rowAttempt;

      int chosenColumn;

      int destroyerPositions = 0;

      bool validPosition = false;

      char chosenRow;

      if (destroyerPositions == 0)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerTwo(gameBoardPlayerTwo);
          cout << yellow << "\n\nPOSITIONING DESTROYER: D D" << normal;
          cout << purple << "\n\n[" << playerTwo << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerTwo << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerTwo[rowAttempt][chosenColumn] = 'D';
      destroyerPositions++;

      validPosition = false;

      if (destroyerPositions == 1)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerTwo(gameBoardPlayerTwo);
          cout << yellow << "\n\nPOSITIONING DESTROYER: D D" << normal;
          cout << purple << "\n\n[" << playerTwo << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerTwo << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'D') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'D') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'D') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'D'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerTwo[rowAttempt][chosenColumn] = 'D';
      destroyerPositions++;

      if (destroyerPositions == 2)
      {
        destroyerPositionedPlayerTwo = true;
        numberOfDestroyersPlayerTwo++;
        numberOfShipsPlayerTwo++;
      }
    }

    while (numberOfSubmarinesPlayerTwo < maximumNumberOfSubmarinesPlayerTwo && submarinePositionedPlayerTwo == false)
    {

      int rowAttempt;

      int chosenColumn;

      int submarinePositions = 0;

      bool validPosition = false;

      char chosenRow;

      if (submarinePositions == 0)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerTwo(gameBoardPlayerTwo);
          cout << yellow << "\n\nPOSITIONING SUBMARINE: S S S" << normal;
          cout << purple << "\n\n[" << playerTwo << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerTwo << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerTwo[rowAttempt][chosenColumn] = 'S';
      submarinePositions++;

      validPosition = false;

      if (submarinePositions == 1)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerTwo(gameBoardPlayerTwo);
          cout << yellow << "\n\nPOSITIONING SUBMARINE: S S S" << normal;
          cout << purple << "\n\n[" << playerTwo << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerTwo << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'S' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'S' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'S') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'S') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'S' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'S' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'S') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'S') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'S' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'S') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'S' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'S'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerTwo[rowAttempt][chosenColumn] = 'S';
      submarinePositions++;

      validPosition = false;

      if (submarinePositions == 2)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerTwo(gameBoardPlayerTwo);
          cout << yellow << "\n\nPOSITIONING SUBMARINE: S S S" << normal;
          cout << purple << "\n\n[" << playerTwo << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerTwo << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'S' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'S') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'S' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'S') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'S' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'S') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'S' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'S') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'S' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'S') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'S' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'S'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerTwo[rowAttempt][chosenColumn] = 'S';
      submarinePositions++;

      if (submarinePositions == 3)
      {
        submarinePositionedPlayerTwo = true;
        numberOfSubmarinesPlayerTwo++;
        numberOfShipsPlayerTwo++;
      }
    }

    while (numberOfCruisersPlayerTwo < maximumNumberOfCruisersPlayerTwo && cruiserPositionedPlayerTwo == false)
    {

      int rowAttempt;

      int chosenColumn;

      int cruiserPositions = 0;

      bool validPosition = false;

      char chosenRow;

      if (cruiserPositions == 0)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerTwo(gameBoardPlayerTwo);
          cout << yellow << "\n\nPOSITIONING CRUISER: C C C" << normal;
          cout << purple << "\n\n[" << playerTwo << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerTwo << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerTwo[rowAttempt][chosenColumn] = 'C';
      cruiserPositions++;

      validPosition = false;

      if (cruiserPositions == 1)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerTwo(gameBoardPlayerTwo);
          cout << yellow << "\n\nPOSITIONING CRUISER: C C C" << normal;
          cout << purple << "\n\n[" << playerTwo << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerTwo << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'C' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'C' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'C') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'C') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'C' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'C' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'C') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'C') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'C' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'C') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'C' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'C'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerTwo[rowAttempt][chosenColumn] = 'C';
      cruiserPositions++;

      validPosition = false;

      if (cruiserPositions == 2)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerTwo(gameBoardPlayerTwo);
          cout << yellow << "\n\nPOSITIONING CRUISER: C C C" << normal;
          cout << purple << "\n\n[" << playerTwo << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerTwo << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'C' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'C') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'C' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'C') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'C' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'C') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'C' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'C') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'C' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'C') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'C' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'C'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerTwo[rowAttempt][chosenColumn] = 'C';
      cruiserPositions++;

      if (cruiserPositions == 3)
      {
        cruiserPositionedPlayerTwo = true;
        numberOfCruisersPlayerTwo++;
        numberOfShipsPlayerTwo++;
      }
    }

    while (numberOfBattleshipsPlayerTwo < maximumNumberOfBattleshipsPlayerTwo && battleshipPositionedPlayerTwo == false)
    {

      int rowAttempt;

      int chosenColumn;

      int battleshipPositions = 0;

      bool validPosition = false;

      char chosenRow;

      if (battleshipPositions == 0)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerTwo(gameBoardPlayerTwo);
          cout << yellow << "\n\nPOSITIONING BATTLESHIP: B B B B" << normal;
          cout << purple << "\n\n[" << playerTwo << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerTwo << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerTwo[rowAttempt][chosenColumn] = 'B';
      battleshipPositions++;

      validPosition = false;

      if (battleshipPositions == 1)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerTwo(gameBoardPlayerTwo);
          cout << yellow << "\n\nPOSITIONING BATTLESHIP: B B B B" << normal;
          cout << purple << "\n\n[" << playerTwo << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerTwo << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerTwo[rowAttempt][chosenColumn] = 'B';
      battleshipPositions++;

      validPosition = false;

      if (battleshipPositions == 2)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerTwo(gameBoardPlayerTwo);
          cout << yellow << "\n\nPOSITIONING BATTLESHIP: B B B B" << normal;
          cout << purple << "\n\n[" << playerTwo << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerTwo << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'B'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerTwo[rowAttempt][chosenColumn] = 'B';
      battleshipPositions++;

      validPosition = false;

      if (battleshipPositions == 3)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerTwo(gameBoardPlayerTwo);
          cout << yellow << "\n\nPOSITIONING BATTLESHIP: B B B B" << normal;
          cout << purple << "\n\n[" << playerTwo << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerTwo << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'B' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'B') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'B' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'B'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerTwo[rowAttempt][chosenColumn] = 'B';
      battleshipPositions++;

      if (battleshipPositions == 4)
      {
        battleshipPositionedPlayerTwo = true;
        numberOfBattleshipsPlayerTwo++;
        numberOfShipsPlayerTwo++;
      }
    }

    while (numberOfCarriersPlayerTwo < maximumNumberOfCarriersPlayerTwo && carrierPositionedPlayerTwo == false)
    {

      int rowAttempt;

      int chosenColumn;

      int carrierPositions = 0;

      bool validPosition = false;

      char chosenRow;

      if (carrierPositions == 0)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerTwo(gameBoardPlayerTwo);
          cout << yellow << "\n\nPOSITIONING CARRIER: K K K K K" << normal;
          cout << purple << "\n\n[" << playerTwo << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerTwo << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 4][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 4][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 4] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 4] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerTwo[rowAttempt][chosenColumn] = 'K';
      carrierPositions++;

      validPosition = false;

      if (carrierPositions == 1)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerTwo(gameBoardPlayerTwo);
          cout << yellow << "\n\nPOSITIONING CARRIER: K K K K K" << normal;
          cout << purple << "\n\n[" << playerTwo << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerTwo << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 4][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 4][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 4][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 4][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 4][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 4][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 4][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 4][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 4] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 4] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 4] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 4] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 4] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 4] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 4] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 4] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerTwo[rowAttempt][chosenColumn] = 'K';
      carrierPositions++;

      validPosition = false;

      if (carrierPositions == 2)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerTwo(gameBoardPlayerTwo);
          cout << yellow << "\n\nPOSITIONING CARRIER: K K K K K" << normal;
          cout << purple << "\n\n[" << playerTwo << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerTwo << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 4][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 4][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 4][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 4][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 4][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 4][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 4][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 4][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 4][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 4][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 4][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 4][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 4] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 4] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 4] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 4] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 4] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 4] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 4] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 4] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 4] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 4] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 4] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 4] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerTwo[rowAttempt][chosenColumn] = 'K';
      carrierPositions++;

      validPosition = false;

      if (carrierPositions == 3)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerTwo(gameBoardPlayerTwo);
          cout << yellow << "\n\nPOSITIONING CARRIER: K K K K K" << normal;
          cout << purple << "\n\n[" << playerTwo << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerTwo << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 4][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 4][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 4][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 4][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 4][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 4][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 4][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 4][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 4] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 4] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 4] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 4] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 4] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 4] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 4] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 4] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerTwo[rowAttempt][chosenColumn] = 'K';
      carrierPositions++;

      validPosition = false;

      if (carrierPositions == 4)
      {

        do
        {
          system("CLS");
          displayGameBoardPlayerTwo(gameBoardPlayerTwo);
          cout << yellow << "\n\nPOSITIONING CARRIER: K K K K K" << normal;
          cout << purple << "\n\n[" << playerTwo << "] Enter the " << green << "LETTER" << purple << " (row) of the position: " << normal;
          cin >> chosenRow;
          cout << purple << "\n[" << playerTwo << "] Enter the " << green << "NUMBER" << purple << " (column) of the position: " << normal;
          cin >> chosenColumn;
          for (i = 0; i < 10; i++)
          {
            if (toupper(chosenRow) == letters[i])
            {
              rowAttempt = i;
            }
          }

          chosenColumn--;

          if ((gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 4][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 4][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 4] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 4] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 3][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 3][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 3] == 'W') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 3] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt - 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt - 2][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 1][chosenColumn] == 'K' && gameBoardPlayerTwo[rowAttempt + 2][chosenColumn] == 'K') || (gameBoardPlayerTwo[rowAttempt][chosenColumn] == 'W' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn - 2] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 1] == 'K' && gameBoardPlayerTwo[rowAttempt][chosenColumn + 2] == 'K'))
          {
            validPosition = true;
          }
          else
          {
            cout << yellow << "\n[Invalid position, try again!]" << normal;
          }
        } while (validPosition == false);
      }

      gameBoardPlayerTwo[rowAttempt][chosenColumn] = 'K';
      carrierPositions++;

      if (carrierPositions == 5)
      {
        carrierPositionedPlayerTwo = true;
        numberOfCarriersPlayerTwo++;
        numberOfShipsPlayerTwo++;
      }
    }
  }
}

int twoPlayers(string playerOne, string playerTwo, int scorePlayerOne, int scorePlayerTwo)
{

  char normal[] = {0x1b, '[', '0', ';', '3', '9', 'm', 0};
  char yellow[] = {0x1b, '[', '0', ';', '3', '3', 'm', 0};
  char purple[] = {0x1b, '[', '0', ';', '3', '5', 'm', 0};
  char cyan[] = {0x1b, '[', '0', ';', '3', '6', 'm', 0};
  char green[] = {0x1b, '[', '0', ';', '3', '2', 'm', 0};

  system("CLS");

  int option;

  char gameBoardPlayerOne[10][10];
  char gameBoardPlayerTwo[10][10];
  char gameMaskPlayerOne[10][10];
  char gameMaskPlayerTwo[10][10];

  createGameBoardPlayerOne(gameBoardPlayerOne);
  createGameBoardPlayerTwo(gameBoardPlayerTwo);
  createMaskPlayerOne(gameMaskPlayerOne);
  createMaskPlayerTwo(gameMaskPlayerTwo);

  do
  {
    headerTwoPlayers();

    cout << yellow << "\n\n1 - " << normal << "Position the ships manually";
    cout << yellow << "\n2 - " << normal << "Position the ships randomly";
    cout << cyan << "\n\nEnter an option: " << normal;
    cin >> option;
    testInput();

  } while (option < 1 || option > 2);

  if (option == 1)
  {
    manualPositionShips(gameBoardPlayerOne, gameBoardPlayerTwo, playerOne, playerTwo);
  }
  else if (option == 2)
  {
    positionShipsTwoPlayers(gameBoardPlayerTwo, gameBoardPlayerOne);
  }

  int row, column;
  int rowAttempt, columnAttempt;
  int i;
  int shipsHitsAmountPlayerOne = 0, shipsHitsAmountPlayerTwo = 0;

  int destroyerAmountPlayerOne = 0, destroyerAmountPlayerTwo = 0;
  int submarineAmountPlayerOne = 0, submarineAmountPlayerTwo = 0;
  int cruiserAmountPlayerOne = 0, cruiserAmountPlayerTwo = 0;
  int battleshipAmountPlayerOne = 0, battleshipAmountPlayerTwo = 0;
  int carrierAmountPlayerOne = 0, carrierAmountPlayerTwo = 0;

  bool destroyerRemainingPlayerOne = true, destroyerRemainingPlayerTwo = true;
  bool submarineRemainingPlayerOne = true, submarineRemainingPlayerTwo = true;
  bool cruiserRemainingPlayerOne = true, cruiserRemainingPlayerTwo = true;
  bool battleshipRemainingPlayerOne = true, battleshipRemainingPlayerTwo = true;
  bool carrierRemainingPlayerOne = true, carrierRemainingPlayerTwo = true;

  char rowLetter;
  char letters[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

  string messageShipOrWater = "";

  string destroyerPlayerOne = "[ ] Destroyer: (D D)", destroyerPlayerTwo = "[ ] Destroyer: (D D)";
  string submarinePlayerOne = "[ ] Submarine: (S S S)", submarinePlayerTwo = "[ ] Submarine: (S S S)";
  string cruiserPlayerOne = "[ ] Cruiser: (C C C)", cruiserPlayerTwo = "[ ] Cruiser: (C C C)";
  string battleshipPlayerOne = "[ ] Battleship: (B B B B)", battleshipPlayerTwo = "[ ] Battleship: (B B B B)";
  string carrierPlayerOne = "[ ] Carrier: (K K K K K)", carrierPlayerTwo = "[ ] Carrier: (K K K K K)";

  int playerWon = 0;

  bool playerOneTurn = true;

  while (playerWon == 0)
  {

    bool hitWater = false;
    bool hitShip = false;
    bool invalidPositionPlayerOne = true;
    bool invalidPositionPlayerTwo = true;

    system("CLS");

    headerTwoPlayers();

    displayGameMaskPlayerTwo(gameMaskPlayerTwo, gameBoardPlayerTwo);

    cout << purple << "\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\t\t\t\t[Player's Two ships]";
    cout << normal;
    if (destroyerRemainingPlayerTwo == true)
    {
      cout << "\n\t\t\t\t" << destroyerPlayerTwo;
    }
    else
    {
      cout << "\n\t\t\t\t[X] Destroyer: (D D)";
    }

    if (cruiserRemainingPlayerTwo == true)
    {
      cout << "\n\t\t\t\t" << cruiserPlayerTwo;
    }
    else
    {
      cout << "\n\t\t\t\t[X] Cruiser: (C C C)";
    }

    if (submarineRemainingPlayerTwo == true)
    {
      cout << "\n\t\t\t\t" << submarinePlayerTwo;
    }
    else
    {
      cout << "\n\t\t\t\t[X] Submarine: (S S S)";
    }

    if (battleshipRemainingPlayerTwo == true)
    {
      cout << "\n\t\t\t\t" << battleshipPlayerTwo;
    }
    else
    {
      cout << "\n\t\t\t\t[X] Battleship: (B B B B)";
    }

    if (carrierRemainingPlayerTwo == true)
    {
      cout << "\n\t\t\t\t" << carrierPlayerTwo;
    }
    else
    {
      cout << "\n\t\t\t\t[X] Carrier: (K K K K K)";
    }

    displayGameMaskPlayerOne(gameMaskPlayerOne, gameBoardPlayerOne);

    cout << purple << "\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\t\t\t\t[Player's One ships]" << normal;

    cout << "\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << destroyerPlayerOne;

    cout << "\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << cruiserPlayerOne;

    cout << "\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << submarinePlayerOne;

    cout << "\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << battleshipPlayerOne;

    cout << "\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << carrierPlayerOne;

    cout << yellow << "\n\n\n\n\n\n\n\n\nScore: " << playerOne << " [" << scorePlayerOne << "] X [" << scorePlayerTwo << "] " << playerTwo << normal;

    cout << yellow << "\n\n"
         << messageShipOrWater << normal;

    if (playerOneTurn == true)
    {
      playerOneTurn = false;
      do
      {
        cout << purple << "\n\n[" << playerOne << "] Enter a " << green << "LETTER" << purple << " according to its respective row: " << normal;
        cin >> rowLetter;
        testInput();
        cout << purple << "\n[" << playerOne << "] Enter a " << green << "NUMBER" << purple << " according to its respective column: " << normal;
        cin >> columnAttempt;
        testInput();

        for (i = 0; i < 10; i++)
        {
          if (toupper(rowLetter) == letters[i])
          {
            rowAttempt = i;
          }
        }

        if (gameMaskPlayerTwo[rowAttempt][columnAttempt - 1] == '*')
        {
          invalidPositionPlayerOne = false;
        }

        if (gameMaskPlayerTwo[rowAttempt][columnAttempt - 1] != '*')
        {
          cout << yellow << "\n[You already tried that position!]" << normal;
        }

      } while (invalidPositionPlayerOne == true);

      if (gameBoardPlayerTwo[rowAttempt][columnAttempt - 1] == 'D' || gameBoardPlayerTwo[rowAttempt][columnAttempt - 1] == 'C' || gameBoardPlayerTwo[rowAttempt][columnAttempt - 1] == 'S' || gameBoardPlayerTwo[rowAttempt][columnAttempt - 1] == 'B' || gameBoardPlayerTwo[rowAttempt][columnAttempt - 1] == 'K')
      {
        system("CLS");
        messageShipOrWater = "[You hit a ship!]";

        hitShip = true;
        shipsHitsAmountPlayerOne++;
        gameMaskPlayerTwo[rowAttempt][columnAttempt - 1] = 'X';
      }

      else if (gameBoardPlayerTwo[rowAttempt][columnAttempt - 1] == 'W')
      {
        system("CLS");
        messageShipOrWater = "[You hit the water!]";

        hitWater = true;

        gameMaskPlayerTwo[rowAttempt][columnAttempt - 1] = gameBoardPlayerTwo[rowAttempt][columnAttempt - 1];
      }

      switch (gameBoardPlayerTwo[rowAttempt][columnAttempt - 1])
      {

      case 'D':
        destroyerAmountPlayerTwo++;
        break;

      case 'C':
        cruiserAmountPlayerTwo++;
        break;

      case 'S':
        submarineAmountPlayerTwo++;
        break;

      case 'B':
        battleshipAmountPlayerTwo++;
        break;

      case 'K':
        carrierAmountPlayerTwo++;
        break;
      }

      if (destroyerAmountPlayerTwo == 2)
      {
        destroyerPlayerTwo = "[X] Destroyer: (D D)";
        destroyerRemainingPlayerTwo = false;
      }
      if (cruiserAmountPlayerTwo == 3)
      {
        cruiserPlayerTwo = "[X] Cruiser: (C C C)";
        cruiserRemainingPlayerTwo = false;
      }
      if (submarineAmountPlayerTwo == 3)
      {
        submarinePlayerTwo = "[X] Submarine: (S S S)";
        submarineRemainingPlayerTwo = false;
      }
      if (battleshipAmountPlayerTwo == 4)
      {
        battleshipPlayerTwo = "[X] Battleship: (B B B B)";
        battleshipRemainingPlayerTwo = false;
      }
      if (carrierAmountPlayerTwo == 5)
      {
        carrierPlayerTwo = "[X] Carrier: (K K K K K)";
        carrierRemainingPlayerTwo = false;
      }

      for (row = 0; row < 10; row++)
      {
        for (column = 0; column < 10; column++)
        {
          if (destroyerRemainingPlayerTwo == false && gameBoardPlayerTwo[row][column] == 'D')
          {
            gameMaskPlayerTwo[row][column] = gameBoardPlayerTwo[row][column];
          }

          if (cruiserRemainingPlayerTwo == false && gameBoardPlayerTwo[row][column] == 'C')
          {
            gameMaskPlayerTwo[row][column] = gameBoardPlayerTwo[row][column];
          }

          if (submarineRemainingPlayerTwo == false && gameBoardPlayerTwo[row][column] == 'S')
          {
            gameMaskPlayerTwo[row][column] = gameBoardPlayerTwo[row][column];
          }

          if (battleshipRemainingPlayerTwo == false && gameBoardPlayerTwo[row][column] == 'B')
          {
            gameMaskPlayerTwo[row][column] = gameBoardPlayerTwo[row][column];
          }

          if (carrierRemainingPlayerTwo == false && gameBoardPlayerTwo[row][column] == 'K')
          {
            gameMaskPlayerTwo[row][column] = gameBoardPlayerTwo[row][column];
          }
        }
      }
    }
    else if (playerOneTurn == false)
    {
      playerOneTurn = true;
      do
      {
        cout << purple << "\n\n[" << playerTwo << "] Enter a " << green << "LETTER" << purple << " according to its respective row: " << normal;
        cin >> rowLetter;
        testInput();
        cout << purple << "\n[" << playerTwo << "] Enter a " << green << "NUMBER" << purple << " according to its respective column: " << normal;
        cin >> columnAttempt;
        testInput();

        for (i = 0; i < 10; i++)
        {
          if (toupper(rowLetter) == letters[i])
          {
            rowAttempt = i;
          }
        }

        if (gameMaskPlayerOne[rowAttempt][columnAttempt - 1] == '*')
        {
          invalidPositionPlayerTwo = false;
        }

        if (gameMaskPlayerOne[rowAttempt][columnAttempt - 1] != '*')
        {
          cout << yellow << "\n[You already tried that position!]" << normal;
        }

      } while (invalidPositionPlayerTwo == true);

      if (gameBoardPlayerOne[rowAttempt][columnAttempt - 1] == 'D' || gameBoardPlayerOne[rowAttempt][columnAttempt - 1] == 'C' || gameBoardPlayerOne[rowAttempt][columnAttempt - 1] == 'S' || gameBoardPlayerOne[rowAttempt][columnAttempt - 1] == 'B' || gameBoardPlayerOne[rowAttempt][columnAttempt - 1] == 'K')
      {
        system("CLS");
        messageShipOrWater = "[You hit a ship!]";

        hitShip = true;
        shipsHitsAmountPlayerTwo++;
        gameMaskPlayerOne[rowAttempt][columnAttempt - 1] = 'X';
      }
      else if (gameBoardPlayerOne[rowAttempt][columnAttempt - 1] == 'W')
      {
        system("CLS");
        messageShipOrWater = "[You hit the water!]";

        hitWater = true;

        gameMaskPlayerOne[rowAttempt][columnAttempt - 1] = gameBoardPlayerOne[rowAttempt][columnAttempt - 1];
      }

      switch (gameBoardPlayerOne[rowAttempt][columnAttempt - 1])
      {

      case 'D':
        destroyerAmountPlayerOne++;
        break;

      case 'C':
        cruiserAmountPlayerOne++;
        break;

      case 'S':
        submarineAmountPlayerOne++;
        break;

      case 'B':
        battleshipAmountPlayerOne++;
        break;

      case 'K':
        carrierAmountPlayerOne++;
        break;
      }

      if (destroyerAmountPlayerOne == 2)
      {
        destroyerRemainingPlayerOne = false;
        destroyerPlayerOne = "[X] Destroyer: (D D)";
      }
      if (cruiserAmountPlayerOne == 3)
      {
        cruiserRemainingPlayerOne = false;
        cruiserPlayerOne = "[X] Cruiser: (C C C)";
      }
      if (submarineAmountPlayerOne == 3)
      {
        submarineRemainingPlayerOne = false;
        submarinePlayerOne = "[X] Submarine: (S S S)";
      }
      if (battleshipAmountPlayerOne == 4)
      {
        battleshipRemainingPlayerOne = false;
        battleshipPlayerOne = "[X] Battleship: (B B B B)";
      }
      if (carrierAmountPlayerOne == 5)
      {
        carrierRemainingPlayerOne = false;
        carrierPlayerOne = "[X] Carrier: (K K K K K)";
      }

      for (row = 0; row < 10; row++)
      {
        for (column = 0; column < 10; column++)
        {
          if (destroyerRemainingPlayerOne == false && gameBoardPlayerOne[row][column] == 'D')
          {
            gameMaskPlayerOne[row][column] = gameBoardPlayerOne[row][column];
          }

          if (cruiserRemainingPlayerOne == false && gameBoardPlayerOne[row][column] == 'C')
          {
            gameMaskPlayerOne[row][column] = gameBoardPlayerOne[row][column];
          }

          if (submarineRemainingPlayerOne == false && gameBoardPlayerOne[row][column] == 'S')
          {
            gameMaskPlayerOne[row][column] = gameBoardPlayerOne[row][column];
          }

          if (battleshipRemainingPlayerOne == false && gameBoardPlayerOne[row][column] == 'B')
          {
            gameMaskPlayerOne[row][column] = gameBoardPlayerOne[row][column];
          }

          if (carrierRemainingPlayerOne == false && gameBoardPlayerOne[row][column] == 'K')
          {
            gameMaskPlayerOne[row][column] = gameBoardPlayerOne[row][column];
          }
        }
      }
    }

    if (shipsHitsAmountPlayerOne == 17)
    {
      playerWon = 1;
      scorePlayerOne++;
    }
    else if (shipsHitsAmountPlayerTwo == 17)
    {
      playerWon = 2;
      scorePlayerTwo++;
    }
  }

  if (playerWon == 1)
  {
    system("CLS");
    headerTwoPlayers();
    displayGameBoardPlayerTwo(gameBoardPlayerTwo);
    displayGameBoardPlayerOne(gameBoardPlayerOne, 2);
    cout << yellow << "\n[" << playerOne << "] Congratulations, YOU WON!" << normal;
    returnExitOrPlayAgainTwoPlayers(playerOne, playerTwo, scorePlayerOne, scorePlayerTwo);
  }
  else if (playerWon == 2)
  {
    system("CLS");
    headerTwoPlayers();
    displayGameBoardPlayerTwo(gameBoardPlayerTwo);
    displayGameBoardPlayerOne(gameBoardPlayerOne, 2);
    cout << yellow << "\n[" << playerTwo << "] Congratulations, YOU WON!" << yellow;
    returnExitOrPlayAgainTwoPlayers(playerOne, playerTwo, scorePlayerOne, scorePlayerTwo);
  }

  return 0;
}

int singlePlayer(string playerOne)
{

  char normal[] = {0x1b, '[', '0', ';', '3', '9', 'm', 0};
  char yellow[] = {0x1b, '[', '0', ';', '3', '3', 'm', 0};
  char purple[] = {0x1b, '[', '0', ';', '3', '5', 'm', 0};
  char cyan[] = {0x1b, '[', '0', ';', '3', '6', 'm', 0};
  char green[] = {0x1b, '[', '0', ';', '3', '2', 'm', 0};

  system("CLS");

  cout << "\n";
  header();

  char gameBoardPlayerOne[10][10];
  char gameMaskPlayerOne[10][10];

  createGameBoardPlayerOne(gameBoardPlayerOne);

  createMaskPlayerOne(gameMaskPlayerOne);

  positionShipsSinglePlayer(gameBoardPlayerOne);

  int maximumAttempts = 22, attempts = 0;

  int rowAttempt, columnAttempt;
  int shipsHitsAmountPlayerOne = 0;
  int remainingAttempts;
  int i;
  int row, column;

  int destroyerAmountPlayerOne = 0;
  int submarineAmountPlayerOne = 0;
  int cruiserAmountPlayerOne = 0;
  int battleshipAmountPlayerOne = 0;
  int carrierAmountPlayerOne = 0;

  bool destroyerRemainingPlayerOne = true;
  bool submarineRemainingPlayerOne = true;
  bool cruiserRemainingPlayerOne = true;
  bool battleshipRemainingPlayerOne = true;
  bool carrierRemainingPlayerOne = true;

  char rowLetter;
  char letters[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

  string destroyer = "[ ] Destroyer: (D D)";
  string cruiser = "[ ] Cruiser: (C C C)";
  string submarine = "[ ] Submarine: (S S S)";
  string battleship = "[ ] Battleship: (B B B B)";
  string carrier = "[ ] Carrier: (K K K K K)";

  string messageShipOrWater = "";

  int gameState = 0;

  while (gameState == 0)
  {

    bool hitWater = false;
    bool hitShip = false;
    bool invalidPositionPlayerOne = true;

    system("CLS");

    header();

    remainingAttempts = maximumAttempts - attempts;

    displayGameMaskSinglePlayer(gameMaskPlayerOne, gameBoardPlayerOne);

    cout << purple << "\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\033[A\t\t\t\t[Ships]" << normal;

    cout << "\n\t\t\t\t" << destroyer;

    cout << "\n\t\t\t\t" << cruiser;

    cout << "\n\t\t\t\t" << submarine;

    cout << "\n\t\t\t\t" << battleship;

    cout << "\n\t\t\t\t" << carrier;

    cout << yellow << "\n\n\n\n\n\n"
         << messageShipOrWater << normal;

    cout << yellow << "\n\nRemaining attempts: " << remainingAttempts << normal;

    do
    {
      cout << yellow << "\n\n[" << playerOne << "] Enter a" << green << " LETTER " << yellow << "according to its respective row: " << normal;
      cin >> rowLetter;
      testInput();
      cout << yellow << "\n[" << playerOne << "] Enter a" << green << " NUMBER " << yellow << "according to its respective column: " << normal;
      cin >> columnAttempt;
      testInput();

      for (i = 0; i < 10; i++)
      {
        if (toupper(rowLetter) == letters[i])
        {
          rowAttempt = i;
        }
      }

      if (gameMaskPlayerOne[rowAttempt][columnAttempt - 1] == '*')
      {
        invalidPositionPlayerOne = false;
      }

      if (gameMaskPlayerOne[rowAttempt][columnAttempt - 1] != '*')
      {
        cout << yellow << "\n[You already tried that position!]" << normal;
      }

    } while (invalidPositionPlayerOne == true);

    if (gameBoardPlayerOne[rowAttempt][columnAttempt - 1] == 'D' || gameBoardPlayerOne[rowAttempt][columnAttempt - 1] == 'C' || gameBoardPlayerOne[rowAttempt][columnAttempt - 1] == 'S' || gameBoardPlayerOne[rowAttempt][columnAttempt - 1] == 'B' || gameBoardPlayerOne[rowAttempt][columnAttempt - 1] == 'K')
    {
      system("CLS");
      messageShipOrWater = "You hit a ship!";
      hitShip = true;
      shipsHitsAmountPlayerOne++;
      gameMaskPlayerOne[rowAttempt][columnAttempt - 1] = 'X';
    }
    else if (gameBoardPlayerOne[rowAttempt][columnAttempt - 1] == 'W')
    {
      system("CLS");
      messageShipOrWater = "You hit the water!";
      hitWater = true;
      attempts++;
      gameMaskPlayerOne[rowAttempt][columnAttempt - 1] = gameBoardPlayerOne[rowAttempt][columnAttempt - 1];
    }

    switch (gameBoardPlayerOne[rowAttempt][columnAttempt - 1])
    {

    case 'D':
      destroyerAmountPlayerOne++;
      break;

    case 'C':
      cruiserAmountPlayerOne++;
      break;

    case 'S':
      submarineAmountPlayerOne++;
      break;

    case 'B':
      battleshipAmountPlayerOne++;
      break;

    case 'K':
      carrierAmountPlayerOne++;
      break;

    default:

      break;
    }

    if (destroyerAmountPlayerOne == 2)
    {
      destroyer = "[X] Destroyer: (D D)";
      destroyerRemainingPlayerOne = false;
    }
    if (cruiserAmountPlayerOne == 3)
    {
      cruiser = "[X] Cruiser: (C C C)";
      cruiserRemainingPlayerOne = false;
    }
    if (submarineAmountPlayerOne == 3)
    {
      submarine = "[X] Submarine: (S S S)";
      submarineRemainingPlayerOne = false;
    }
    if (battleshipAmountPlayerOne == 4)
    {
      battleship = "[X] Battleship: (B B B B)";
      battleshipRemainingPlayerOne = false;
    }
    if (carrierAmountPlayerOne == 5)
    {
      carrier = "[X] Carrier: (K K K K K)";
      carrierRemainingPlayerOne = false;
    }

    for (row = 0; row < 10; row++)
    {
      for (column = 0; column < 10; column++)
      {
        if (destroyerRemainingPlayerOne == false && gameBoardPlayerOne[row][column] == 'D')
        {
          gameMaskPlayerOne[row][column] = gameBoardPlayerOne[row][column];
        }

        if (cruiserRemainingPlayerOne == false && gameBoardPlayerOne[row][column] == 'C')
        {
          gameMaskPlayerOne[row][column] = gameBoardPlayerOne[row][column];
        }

        if (submarineRemainingPlayerOne == false && gameBoardPlayerOne[row][column] == 'S')
        {
          gameMaskPlayerOne[row][column] = gameBoardPlayerOne[row][column];
        }

        if (battleshipRemainingPlayerOne == false && gameBoardPlayerOne[row][column] == 'B')
        {
          gameMaskPlayerOne[row][column] = gameBoardPlayerOne[row][column];
        }

        if (carrierRemainingPlayerOne == false && gameBoardPlayerOne[row][column] == 'K')
        {
          gameMaskPlayerOne[row][column] = gameBoardPlayerOne[row][column];
        }
      }
    }

    if (shipsHitsAmountPlayerOne == 17)
    {
      gameState = 1;
    }

    if (maximumAttempts - attempts == 0 && gameState != 1)
    {
      gameState = 2;
    }
  }

  if (gameState == 1)
  {
    system("CLS");
    displayGameBoardPlayerOne(gameBoardPlayerOne, 1);
    cout << yellow << "\nCongratulations you won!!" << normal;
    returnExitOrPlayAgain(playerOne);
  }

  if (gameState == 2 && maximumAttempts - attempts == 0)
  {
    system("CLS");

    displayGameBoardPlayerOne(gameBoardPlayerOne, 1);
    cout << yellow << "\nYou lost!" << normal;

    returnExitOrPlayAgain(playerOne);
  }

  return 0;
}

void menu()
{
  char normal[] = {0x1b, '[', '0', ';', '3', '9', 'm', 0};
  char yellow[] = {0x1b, '[', '0', ';', '3', '3', 'm', 0};
  char cyan[] = {0x1b, '[', '0', ';', '3', '6', 'm', 0};

  system("CLS");

  int option;
  string playerOne, playerTwo;

  do
  {
    header();
    cout << "\n"
         << yellow << "1 - " << normal << "Single player";
    cout << "\n"
         << yellow << "2 - " << normal << "Two Players";
    cout << "\n"
         << yellow << "3 - " << normal << "Instructions";
    cout << "\n"
         << yellow << "4 - " << normal << "About";
    cout << "\n"
         << yellow << "5 - " << normal << "Exit";
    cout << cyan << "\n\nEnter an option: " << normal;
    cin >> option;
    testInput();
    system("CLS");
  } while (option < 1 || option > 5);

  switch (option)
  {
  case 1:
    header();
    cout << cyan << "\n\nEnter your name: " << normal;
    cin >> playerOne;
    singlePlayer(playerOne);
    break;

  case 2:
    header();
    cout << cyan << "\n\n[Player 1] Enter your name: " << normal;
    cin >> playerOne;
    cout << cyan << "\n[Player 2] Enter your name: " << normal;
    cin >> playerTwo;
    twoPlayers(playerOne, playerTwo, 0, 0);
    break;

  case 3:
    headerTwoPlayers();
    cout << "\n\nThe objective of the game is to try and sink all of other player's before they sink all of your ships.";
    cout << "\nYou try to hit the ships by calling the coordinates of one of the '*' on the board.";
    cout << "\n'W' means water and 'X' means a hit ship (when the ship is sunken the 'x' are replaced by the letter of the ship).";
    cout << "\nEach player has 5 ships: Destroyer (D ~ 2 spaces), Cruiser (C ~ 3 spaces), Submarine (S ~ 3 spaces), Battleship (B ~ 4 spaces) and Carrier (K ~ 5 spaces).";
    cout << "\nIf you choose singleplayer, you'll have 22 attempts to guess where the computer's ships are.";
    cout << "\nIf you choose the two players option, you can choose between manual positioning the ships (each one of the players will have to coordinate the positions of \ntheir own ships) or random positioning the ships, in which the computer will randomly position the ships for the players. In this option there's no maximum attempts,\nthe game only ends when one of the players hits every one of the other's ships first.";
    cout << yellow << "\nPAY ATTENTION! TWO PLAYERS REQUIRE FULL SCREEN!" << normal;
    returnOrExit();
    break;

  case 4:
    header();
    cout << yellow << "\n\nGame created by Vinicius Medeiros.\n2020." << normal;
    returnOrExit();
    break;

  case 5:
    exitGame();
    break;
  }
}

int main()
{

  srand((unsigned)time(NULL));

  menu();

  return 0;
}