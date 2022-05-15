#include <Arduino.h>
#include <IRremote.h>
#include <LiquidCrystal.h>
#include "RTClib.h" //Version 1.3.3
#include "remote.h"
#include "game.h"
#include "alarm.h"

//Constants for the game board
#define NUM_ROWS  3
#define NUM_COLS  5

typedef enum 
{
  PLAYER1 = 0,
  PLAYER2
}player_t;

typedef struct
{
  bool winDetected;
  char winner;
}gameResult_t;

static void ShowGameBoard(LiquidCrystal& lcd,
                          char board[NUM_ROWS][NUM_COLS])
{
  int cursorRow = 0;
  const int cursorCol = 4;
  for(int row = 0; row < NUM_ROWS; row++)
  {
    lcd.setCursor(cursorCol,cursorRow);
    cursorRow++;
    for(int col = 0; col < NUM_COLS; col++)
    {
      lcd.print(board[row][col]);
    }
  }
}

static void UpdateGameBoard(char& pressedKey,
                            LiquidCrystal& lcd,
                            char board[NUM_ROWS][NUM_COLS],
                            player_t& player)
{
  bool playerMadeAnInput = false;
  for(int row = 0; row < NUM_ROWS; row++)
  {
    for(int col = 0; col < NUM_COLS; col++)
    {
      if(pressedKey == board[row][col])
      {
        switch(player)
        {
          case PLAYER1:
            board[row][col] = 'X';
            player = PLAYER2;
            break;
          case PLAYER2:
            board[row][col] = 'O';
            player = PLAYER1;
            break;
        }
        playerMadeAnInput = true;
        break; //inner loop
      }
    }
    if(playerMadeAnInput)
    {
      break; //outer loop
    }
  }
}

static gameResult_t CheckForHorizontalWin(char gameBoard[NUM_ROWS]
                                                        [NUM_COLS])
{
  gameResult_t result = {0};
  char startOfRow;
  uint8_t numberOfMatchingPlayerInputs = 0; 
  
  for(uint8_t rowIndex = 0; rowIndex < NUM_ROWS; rowIndex++)
  {
    startOfRow = gameBoard[rowIndex][0];
    for(uint8_t colIndex = 2; colIndex < NUM_COLS; colIndex+=2)
    {
      if(startOfRow == gameBoard[rowIndex][colIndex])
      {
        numberOfMatchingPlayerInputs++;
      }
    }
    if(numberOfMatchingPlayerInputs == 2)
    {
      result.winDetected = true;
      result.winner = startOfRow;
      return result;
    }
    else
    {
      numberOfMatchingPlayerInputs = 0;
    }
  }
  return result;
}

static gameResult_t CheckForVerticalWin(char gameBoard[NUM_ROWS]
                                                      [NUM_COLS])
{
  gameResult_t result = {0};
  char startOfColumn;
  uint8_t numberOfMatchingPlayerInputs = 0;
  
  for(uint8_t colIndex = 0; colIndex < NUM_COLS; colIndex+=2)
  {
    startOfColumn = gameBoard[0][colIndex];
    for(uint8_t rowIndex = 1; rowIndex < NUM_ROWS; rowIndex++)
    {
      if(startOfColumn == gameBoard[rowIndex][colIndex])
      {
        numberOfMatchingPlayerInputs++;
      }
    }
    if(numberOfMatchingPlayerInputs == 2)
    {
      result.winDetected = true;
      result.winner = startOfColumn;
      return result;
    }
    else
    {
      numberOfMatchingPlayerInputs = 0;
    }
  }
  return result;  
}

static gameResult_t CheckForDiagonalWin(char gameBoard[NUM_ROWS]
                                                      [NUM_COLS])
{
  gameResult_t result = {0};
  //Back slash diagonal
  if((gameBoard[0][0] == gameBoard[1][2])&&(gameBoard[0][0] == gameBoard[2][4]))
  {
    result.winDetected = true;
    result.winner = gameBoard[0][0];
    return result;
  }
  //Forward slash diagonal
  if((gameBoard[0][4] == gameBoard[1][2])&&(gameBoard[0][4] == gameBoard[2][0]))
  {
    result.winDetected = true;
    result.winner = gameBoard[0][4];
    return result;
  }
  return result;
}

void PlayGame(LiquidCrystal& lcd,RTC_DS3231& rtc,IRrecv& irReceiver)
{
  lcd.clear();
  lcd.setCursor(1,3);
  lcd.print("<Press OK to exit>");
  //Array of function pointers
  static gameResult_t (*CheckWin[3])(char gameBoard[NUM_ROWS]
                                                   [NUM_COLS]) = 
  {
    CheckForHorizontalWin,
    CheckForVerticalWin,
    CheckForDiagonalWin
  };
  char gameBoard[NUM_ROWS][NUM_COLS] = 
  {
    {'1','|','2','|','3'},
    {'4','|','5','|','6'},
    {'7','|','8','|','9'}
  };
  player_t player = PLAYER1;
  while(1)
  {
    CheckAlarms(rtc);
    ShowGameBoard(lcd,gameBoard);
    irRecv_t irValue = GetIRRemoteVal(irReceiver);
    char pressedKey = GetIRKeyPress(irValue);
    if(irValue == KEY_OK)
    {
      player = PLAYER1;
      break;
    }
    UpdateGameBoard(pressedKey,lcd,gameBoard,player);
    //Check winner
    for(uint8_t i = 0; i < 3; i++)
    {
      gameResult_t result = CheckWin[i](gameBoard);
      if(result.winDetected)
      {
        lcd.setCursor(11,0);
        lcd.print("Winner:");
        lcd.setCursor(11,1);
        if(result.winner == 'X')
        {
          lcd.print("Player 1");
          break;
        }
        else if(result.winner == 'O')
        {
          lcd.print("Player 2");
          break;
        }
      }
    }    
  }
}

