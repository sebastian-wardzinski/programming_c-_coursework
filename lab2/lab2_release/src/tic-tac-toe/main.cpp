//
//  main.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <iostream>

#include <tic-tac-toe/playMove.h>

using namespace std;
using namespace sf;


int main() {

    /************************************************************************************************************/
    /* The following variables define the state of the game                                                     */
    /************************************************************************************************************/

    // You should complete the following declarations
    // Make sure to initalize the variables
    int row, col, i, j;
    // The game board array
    int gameBoard[3][3] = {Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty};
    
    // An boolean that represents the turn in the game
    bool turnX = true;
    // A boolean to represent if the move is valid
    bool validMove = true;
    // A boolean to represent if the game is over
    bool is_game_over = false;

    // An integer that represents the win code
    int winCode = 0;
    
    /************************************************************************************************************/
    /* Insert code that loads the various images used by the game and creates the sprites                       */
    /* The loading of the X image is shown. Repreat for the rest of the images                                  */
    /************************************************************************************************************/

    // Get the X image
    sf::Texture X_texture;
    if (!X_texture.loadFromFile("X.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite X_sprite(X_texture);

    // Get the O image
    sf::Texture O_texture;
    if (!O_texture.loadFromFile("O.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite O_sprite(O_texture);
    
    // Get the blank image
    sf::Texture blank_texture;
    if (!blank_texture.loadFromFile("blank.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite blank_sprite(blank_texture);    
    
    /************************************************************************************************************/
    /* Insert code that creates the window and displays it                                                      */
    /************************************************************************************************************/

    // First, we find the sizes of the images so we can determine the size of the window we must create
    // The images (X, O and Blank) are assumed to be square are are all of the same size
    // Thus, we just find the size of one of them

    // The tile size is the size of the images
    const int tileSize = X_texture.getSize().x;
    
    // The cell borders (thick lines) are rectangles
    // The size of these rectangles is 1/20th of the size of the tile by 3 cell sizes plus 2 barWidth's
    const int barWidth = tileSize/20;
    const int barHeight = boardSize*tileSize + (boardSize-1)*barWidth;

    // The size of the window in pixels can now be calculated
    const int windowSize = boardSize*tileSize + (boardSize-1)*barWidth;

    // Create the main window: it has a title bar and a close button, but is not resizable
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "ECE244 Tic-Tac-Toe", sf::Style::Titlebar | sf::Style::Close);

    // Set the Icon that appears in the task bar when the window is minimized
    // Insert you code here, see the lab handout
    sf::Image tictacIcon;
    if (!tictacIcon.loadFromFile("icon.jpg")) {
        return EXIT_FAILURE;
    }
    window.setIcon(tictacIcon.getSize().x,
    tictacIcon.getSize().y,
    tictacIcon.getPixelsPtr());

    // Create the horizonal (vertical) borders as rectangles of sizes barWidth and barHeight (berHeight and barWidth)
    // Insert your code here
    //
    // Change the size
    
    sf::RectangleShape borderVer1(sf::Vector2f(barWidth, barHeight));
    sf::RectangleShape borderVer2(sf::Vector2f(barWidth, barHeight));
    sf::RectangleShape borderHor1(sf::Vector2f(barHeight, barWidth));
    sf::RectangleShape borderHor2(sf::Vector2f(barHeight, barWidth));
    sf::RectangleShape winLine(sf::Vector2f(barWidth*2, barHeight));

    
    // Set the position
    borderVer1.setPosition(tileSize,0);
    borderVer2.setPosition(tileSize*2 ,0);
    borderHor1.setPosition(0,tileSize);
    borderHor1.setPosition(0,tileSize*2);
    
    // Set the orientation in relation to the x axis
    // NOT NEEDED
    // Set the fill color to white
    borderVer1.setFillColor(sf::Color(0, 0, 0));
    borderVer2.setFillColor(sf::Color(0, 0, 0));
    borderHor1.setFillColor(sf::Color(0, 0, 0));
    borderHor2.setFillColor(sf::Color(0, 0, 0));

    // Draw the rectangle
    window.draw(borderVer1);
    window.draw(borderVer2);
    window.draw(borderHor1);
    window.draw(borderHor2);
    
    int tileOffset = tileSize+barWidth;
    
    // Now actually update the display window
    // prints all the blank spots at the start of the game
    
    blank_sprite.setPosition(0,0);
    window.draw(blank_sprite);
    blank_sprite.setPosition(tileOffset,0);
    window.draw(blank_sprite);
    blank_sprite.setPosition(tileOffset*2,0);
    window.draw(blank_sprite);
    blank_sprite.setPosition(0,tileOffset);
    window.draw(blank_sprite);
    blank_sprite.setPosition(tileOffset,tileOffset);
    window.draw(blank_sprite);
    blank_sprite.setPosition(tileOffset*2,tileOffset);
    window.draw(blank_sprite);
    blank_sprite.setPosition(0,tileOffset*2);
    window.draw(blank_sprite);
    blank_sprite.setPosition(tileOffset,tileOffset*2);
    window.draw(blank_sprite);
    blank_sprite.setPosition(tileOffset*2,tileOffset*2);
    window.draw(blank_sprite);
    
    window.display();

    /************************************************************************************************************/
    /* This is the main event loop of the code                                                                  */
    /************************************************************************************************************/

    // Start the game loop that runs as long as the window is open
    while (window.isOpen()) {
        // The event
        sf::Event event;

        // Process the events
        while (window.pollEvent(event)) {

            // This is the handling of the close window event
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }

            // Left mouse button pressed: get the click position and play the move
            // is_game_over is a variable you should define above
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && winCode == 0) {
                // left mouse button is pressed: get the coordinates in pixels
                // Insert your code to get the coordinates here
                sf::Vector2i localPosition = Mouse::getPosition(window);
                // Convert the pixel coordinates into game board rows and columns
                // Just divide by tileSize
                // Observe that the x axis is the rows and the y axis is the columns
                // Also make sure that row and column values are valid
                // Insert your code below
                row = localPosition.x/tileOffset;
                col = localPosition.y/tileOffset;
             
                // Play the move by calling the playMove function
                // Insert your code below
                playMove(gameBoard, row, col, turnX, validMove, is_game_over, winCode);
                
                
                for(i=0;i<3;i++){
                    for(j=0;j<3;j++){
                        if(gameBoard[i][j] == 0){
                            blank_sprite.setPosition(i*tileOffset,j*tileOffset);
                            window.draw(blank_sprite);
                        }
                        else if(gameBoard[i][j] == 1){
                            X_sprite.setPosition(i*tileOffset,j*tileOffset);
                            window.draw(X_sprite);
                        }
                        else if(gameBoard[i][j] == -1){
                            O_sprite.setPosition(i*tileOffset,j*tileOffset);
                            window.draw(O_sprite);
                        }

                    }
                }
                
                if(winCode != 0){
                    
                    switch(winCode){ 
                            case 4:                                         // cases 4,5,6 are the horizontal win lines
                                winLine.setPosition(0,tileSize/2);
                                winLine.rotate(-90);
                                winLine.setFillColor(sf::Color(0, 0, 0));
                                window.draw(winLine);
                                break;
                            case 5: 
                                winLine.setPosition(0,3*tileSize/2);
                                winLine.rotate(-90);
                                winLine.setFillColor(sf::Color(0, 0, 0));
                                window.draw(winLine);
                                break; 
                            case 6:
                                winLine.setPosition(0,5*tileSize/2);
                                winLine.rotate(-90);
                                winLine.setFillColor(sf::Color(0, 0, 0));
                                window.draw(winLine);
                                break;
                            case 1:                                         // cases 1,2,3 are the vertical win lines
                                winLine.setPosition(tileSize/2,0);
                                winLine.setFillColor(sf::Color(0, 0, 0));
                                window.draw(winLine);
                                break; 
                            case 2:
                                winLine.setPosition(3*tileSize/2,0);
                                winLine.setFillColor(sf::Color(0, 0, 0));
                                window.draw(winLine);
                                break;
                            case 3: 
                                winLine.setPosition(5*tileSize/2,0);
                                winLine.setFillColor(sf::Color(0, 0, 0));
                                window.draw(winLine);
                                break; 
                            case 7:                                         // cases 7,8 are the two diagonals
                                winLine.setPosition(tileSize/2,tileSize/2);
                                winLine.rotate(-45);
                                winLine.setFillColor(sf::Color(0, 0, 0));
                                window.draw(winLine);
                                break;
                            case 8: 
                                winLine.setPosition(tileSize/2,5*tileSize/2);
                                winLine.rotate(-135);
                                winLine.setFillColor(sf::Color(0, 0, 0));
                                window.draw(winLine);
                                break; 
              
                    }
                }
                window.display();
            }
       
        }

        // Insert code to draw the tiles using the sprites created earlier
        // You must determine the position of each cell on the grid, taking into account the width of
        // the border and then position the sprite there and draw it.
        // Draw the entire board, cell borders included,
        // reflecting any move that has just happened (check the gameBoard array)
        
        
        // Further, if the game is over and one player wins, you must create and draw a rectangle of
        // windowSize width and 10 pixels height to indicate the winning marks
        // The fill of this rectangle should be white

        // Insert your code here

        // Display to the window
     
                
    }
    
    return EXIT_SUCCESS;
}
