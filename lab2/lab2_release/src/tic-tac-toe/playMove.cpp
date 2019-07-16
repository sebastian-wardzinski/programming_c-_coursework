//
//  playMove.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <tic-tac-toe/playMove.h>

using namespace std;

void playMove(int board[3][3], int row, int col, bool& turn, bool& validMove, bool& gameOver, int& winCode) {

    // If the game is over, do nothing
    if (gameOver) return;

    // Insert your code here
    if(row>=0 && col>=0 && row<=2 && col<=2 && board[row][col]==0)
        validMove = true;
    else
        validMove = false;
       
    if(validMove){
        
        if(turn)
            board[row][col] = 1;
        else
            board[row][col] = -1;
        
        turn = !turn;
        
        bool fullBoard = true;
        
        for(int i=0;i<3;i++){                   //checks if the board is full
            for(int j=0;j<3;j++){
                if(board[i][j]==0){
                    fullBoard = false;
                }
            }
        }
        
        gameOver = fullBoard;                   //gameover (DRAW) if the board is full
    // NEED TO STILL WORK ON GAMEOVER AND WINCODE
   
    // The function must always print the output specified in the handout before it exits
    // Use the standard output (i.e., cout) to print the output
        for(int p=-1;p<2;p+=2){
            if(board[0][0]==p && board[0][1]==p && board[0][2]==p) winCode = 1; //col1
            else if(board[1][0]==p && board[1][1]==p && board[1][2]==p) winCode = 2; //col2
            else if(board[2][0]==p && board[2][1]==p && board[2][2]==p) winCode = 3; //col3
            else if(board[0][0]==p && board[1][0]==p && board[2][0]==p) winCode = 4; //row1
            else if(board[0][1]==p && board[1][1]==p && board[2][1]==p) winCode = 5; //row2
            else if(board[0][2]==p && board[1][2]==p && board[2][2]==p) winCode = 6; //row3
            else if(board[0][0]==p && board[1][1]==p && board[2][2]==p) winCode = 7;
            else if(board[2][0]==p && board[1][1]==p && board[0][2]==p) winCode = 8;
        }
        
        if(winCode !=0)            //if one of the winning combinations were reached, trigger game end
            gameOver = true;
    
    // Insert code to print the output below
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                cout << board[i][j] << " ";
            }
        }
        
        cout << row << " " << col << " " << turn <<  " " << validMove << " " << gameOver << " " << winCode << endl;
    }
}

