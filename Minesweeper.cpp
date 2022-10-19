#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
#include "TextureManager.h"
#include "Random.h"
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>


class Tile
{
public:
    float xPosition;
    float yPosition;
    float xSize;
    float ySize;
    vector<Tile*> neighbors;
    bool isMine;
    int number;
    int adjacentMines;
    bool flagged;
    int rowNumber;
    bool revealed;
    bool won;
    bool lost;
    bool smiley;
    bool debug;
    int columnNumber;

    Tile();
    void ClearBoard(int numRows, int numColumns);
    Tile(float tileWidth, float tileHeight, sf::Vector2f tilePosition);
    float SetXPosition(float xPos);
    float SetYPosition(float yPos);
    void RevealNeighbors();
};

Tile::Tile()
{
    adjacentMines = 0;
    rowNumber = 0;
    columnNumber = 0;
    number = 0;
    xSize = 0;
    ySize = 0;
    xPosition = 0;
    yPosition = 0;
    revealed = false;
    won = false;
    lost = false;
    smiley = true;
    debug = false;
    flagged = false;
    isMine = false;
    neighbors.clear();
}

float Tile::SetXPosition(float xPos)
{
    xPosition = xPos;
    return xPosition;
}

float Tile::SetYPosition(float yPos)
{
    yPosition = yPos;
    return yPosition;
}

void Tile::RevealNeighbors()
{
    if (revealed || flagged)
    {
        return;
    }
    
    if (isMine)
    {
        revealed = true;
        return;
    }

    if (adjacentMines != 0)
    {
        revealed = true;
        return;
    }

    if (adjacentMines == 0)
    {
        revealed = true;
        for (int i = 0; i < 8; i++)
        {
            if (neighbors[i] == nullptr)
            {
                continue;
            }
            if ((neighbors[i]->flagged == false) && (neighbors[i]->revealed == false))
            {
                if (neighbors[i]->adjacentMines == 0)
                {
                    neighbors[i]->RevealNeighbors();
                }

                else
                {
                    neighbors[i]->revealed = true;
                }
            }
        }
        return;
    }
}



class Board
{
public:
    vector<vector<Tile>> boardVector;
    void CreateNewBoard(int numRows, int numColumns, int numMines, int numTiles, bool test);
    void ResetVariables(int numRows, int numColumns);
};

void Board::CreateNewBoard(int numRows, int numColumns, int numMines, int numTiles, bool test)
{
    for (int i = 0; i < numRows; i++)
    {
        Tile newTile;
        vector<Tile> rows;
        for (int j = 0; j < numColumns; j++)
        {
            newTile.rowNumber = i;
            newTile.columnNumber = j;
            newTile.SetXPosition(j * 32);
            newTile.SetYPosition(i * 32);

            rows.push_back(newTile);
        }
        boardVector.push_back(rows);
    }

    if (test == false)
    {
        for (int i = 0; i < numMines; i++)
        {
            int randomNumber = Random::Int(0, numTiles - 1);
            int row = randomNumber / numColumns;
            int col = randomNumber - (row * numColumns);
            while (boardVector[row][col].isMine == true)
            {
                randomNumber = Random::Int(0, numTiles - 1);
                row = randomNumber / numColumns;
                col = randomNumber - (row * numColumns);
            }
            if (boardVector[row][col].isMine == false)
            {
                boardVector[row][col].isMine = true;
            }
        }
    }


    Tile* tilePointer;
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numColumns; j++)
        {
            if ((i == 0) && (j == 0))
            {
                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i][j + 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i + 1][j + 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i + 1][j];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);
            }

            else if ((i == 0) && (j > 0) && (j < numColumns - 1))
            {
                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i][j + 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i + 1][j + 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i + 1][j];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i + 1][j - 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i][j - 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);
            }

            else if ((i == 0) && (j == numColumns - 1))
            {
                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i + 1][j];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i + 1][j - 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i][j - 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);
            }

            else if ((i > 0) && (j == numColumns - 1) && (i < numRows - 1))
            {
                tilePointer = &boardVector[i - 1][j];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i + 1][j];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i + 1][j - 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i][j - 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i - 1][j - 1];
                boardVector[i][j].neighbors.push_back(tilePointer);
            }

            else if ((i == numRows - 1) && (j == numColumns - 1))
            {
                tilePointer = &boardVector[i - 1][j];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i][j - 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i - 1][j - 1];
                boardVector[i][j].neighbors.push_back(tilePointer);
            }

            else if ((i == numRows - 1) && (j < numColumns - 1) && (j > 0))
            {
                tilePointer = &boardVector[i - 1][j];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i - 1][j + 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i][j + 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i][j - 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i - 1][j - 1];
                boardVector[i][j].neighbors.push_back(tilePointer);
            }

            else if ((i == numRows - 1) && (j == 0))
            {
                tilePointer = &boardVector[i - 1][j];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i - 1][j + 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i][j + 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);
            }

            else if ((i < numRows - 1) && (j == 0) && (i > 0))
            {
                tilePointer = &boardVector[i - 1][j];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i - 1][j + 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i][j + 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i + 1][j + 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i + 1][j];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = nullptr;
                boardVector[i][j].neighbors.push_back(tilePointer);
            }

            else
            {
                tilePointer = &boardVector[i - 1][j];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i - 1][j + 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i][j + 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i + 1][j + 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i + 1][j];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i + 1][j - 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i][j - 1];
                boardVector[i][j].neighbors.push_back(tilePointer);

                tilePointer = &boardVector[i - 1][j - 1];
                boardVector[i][j].neighbors.push_back(tilePointer);
            }
        }
    }

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numColumns; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                if ((boardVector[i][j].neighbors[k] != nullptr) && (boardVector[i][j].neighbors[k]->isMine == true))
                {
                    boardVector[i][j].adjacentMines++;
                }
            }
        }
    }
}

void Board::ResetVariables(int numRows, int numColumns)
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numColumns; j++)
        {
            if (boardVector[i][j].isMine == true)
            {
                boardVector[i][j].isMine = false;
            }
            if (boardVector[i][j].flagged == true)
            {
                boardVector[i][j].flagged = false;
            }
            if (boardVector[i][j].adjacentMines > 0)
            {
                boardVector[i][j].adjacentMines = 0;
            }
            if (boardVector[i][j].revealed == true)
            {
                boardVector[i][j].revealed = false;
            }
            if (boardVector[i][j].lost == true)
            {
                boardVector[i][j].lost = false;
            }
        }
    }
}



int main()
{
    int randomNumber = 0;
    
    ifstream file;
    string columns;
    int numColumns;
    string rows;
    int numRows;
    string mines;
    int numMines;
    int numFlags = 0;
    int numTiles;
    int flagsRemaining;
    bool gameOver = false;
    bool debug = false;
    bool won = false;
    bool test = false;
    bool happy = true;
    bool cool = false;
    bool sad = false;
    bool canClick = true;
    int numRevealed = 0;

    //get info from the config file
    file.open("boards/config.cfg");

    getline(file, columns);
    numColumns = stoi(columns);

    getline(file, rows);
    numRows = stoi(rows);

    getline(file, mines);
    numMines = stoi(mines);
    int initialMines = numMines;

    file.close();

    numTiles = numColumns * numRows;
    unsigned int xSide = numColumns * 32;
    unsigned int ySide = (numRows * 32) + 88;
    sf::RenderWindow window(sf::VideoMode(xSide, ySide), "Minesweeper");

    Board newBoard;
    newBoard.CreateNewBoard(numRows, numColumns, numMines, numTiles, test);

    //display the window
    while (window.isOpen())
    {
        sf::Event event;

        //close the window if prompted
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if ((event.type == sf::Event::MouseButtonPressed) && (canClick == true))
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                sf::Vector2f mouseClick = sf::Vector2f(localPosition);
                float mouseXCoordinate = mouseClick.x;
                float mouseYCoordinate = mouseClick.y;

                for (int i = 0; i < numRows; i++)
                {
                    for (int j = 0; j < numColumns; j++)
                    {
                        sf::IntRect testingWindow(newBoard.boardVector[i][j].xPosition, newBoard.boardVector[i][j].yPosition, 32, 32);
                        bool contains = testingWindow.contains(mouseClick.x, mouseClick.y);

                        if (contains)
                        {
                            if (event.mouseButton.button == sf::Mouse::Right)
                            {
                                if (newBoard.boardVector[i][j].revealed == false)
                                {
                                    if (newBoard.boardVector[i][j].flagged == true)
                                    {
                                        newBoard.boardVector[i][j].flagged = false;
                                        numFlags--;
                                    }
                                    else
                                    {
                                        newBoard.boardVector[i][j].flagged = true;
                                        numFlags++;
                                    }
                                }
                            }
                            else
                            {
                                if (newBoard.boardVector[i][j].isMine == true)
                                {
                                    debug = false;
                                    newBoard.boardVector[i][j].lost = true;
                                    gameOver = true;
                                    sad = true;
                                    happy = false;
                                    cool = false;
                                    numRevealed = 0;
                                    canClick = false;

                                    for (int i = 0; i < numRows; i++)
                                    {
                                        for (int j = 0; j < numColumns; j++)
                                        {
                                            if (newBoard.boardVector[i][j].isMine == true)
                                            {
                                                newBoard.boardVector[i][j].revealed = true;
                                            }
                                        }
                                    }
                                }
                                newBoard.boardVector[i][j].RevealNeighbors();

                                numRevealed = 0;
                                for (int i = 0; i < numRows; i++)
                                {
                                    for (int j = 0; j < numColumns; j++)
                                    {
                                        if (newBoard.boardVector[i][j].revealed == true)
                                        {
                                            numRevealed++;
                                        }
                                    }
                                }

                                int numbers = numTiles - numMines;
                                
                                if (numRevealed == numbers)
                                {
                                    debug = false;
                                    gameOver = true;
                                    won = true;
                                    cool = true;
                                    happy = false;
                                    sad = false;
                                    numRevealed = 0;
                                    canClick = false;
                                    for (int i = 0; i < numRows; i++)
                                    {
                                        for (int j = 0; j < numColumns; j++)
                                        {
                                            if (newBoard.boardVector[i][j].isMine == true)
                                            {
                                                if (newBoard.boardVector[i][j].flagged == true)
                                                {
                                                    continue;
                                                }
                                                else
                                                {
                                                    newBoard.boardVector[i][j].flagged = true;
                                                    numFlags++;
                                                }
                                            }
                                        }
                                    }
                                }
                                numRevealed = 0;
                            }
                        }
                    }
                }
                sf::IntRect debugWindow(((float)numColumns * 16) + 96, ((float)numRows * 32), 64, 64);
                bool contains = debugWindow.contains(mouseClick.x, mouseClick.y);
                if (contains)
                {
                    if (debug == true)
                    {
                        debug = false;
                    }
                    else
                    {
                        debug = true;
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                sf::Vector2f mouseClick = sf::Vector2f(localPosition);
                float mouseXCoordinate = mouseClick.x;
                float mouseYCoordinate = mouseClick.y;

                sf::IntRect thisWindow(((float)numColumns * 16) - 32, ((float)numRows * 32), 64, 64);
                bool contains = thisWindow.contains(mouseClick.x, mouseClick.y);
                if (contains)
                {
                    debug = false;
                    newBoard.ResetVariables(numRows, numColumns);
                    test = false;
                    numMines = initialMines;
                    newBoard.CreateNewBoard(numRows, numColumns, numMines, numTiles, test);
                    happy = true;
                    cool = false;
                    sad = false;
                    numRevealed = 0;
                    canClick = true;
                    numFlags = 0;
                }

                sf::IntRect test1Window(((float)numColumns * 16) + 160, ((float)numRows * 32), 64, 64);
                contains = test1Window.contains(mouseClick.x, mouseClick.y);
                if (contains)
                {
                    debug = false;
                    newBoard.ResetVariables(numRows, numColumns);
                    test = true;
                    happy = true;
                    cool = false;
                    sad = false;
                    numRevealed = 0;
                    canClick = true;
                    numFlags = 0;

                    ifstream testFile;
                    testFile.open("boards/testBoard1.brd");
                    string rowInfo;
                    int testMines = 0;

                    for (int i = 0; i < numRows; i++)
                    {
                        rowInfo = "";
                        getline(testFile, rowInfo);
                        for (int j = 0; j < rowInfo.size(); j++)
                        {
                            if (rowInfo[j] == '1')
                            {
                                newBoard.boardVector[i][j].isMine = true;
                                testMines++;
                            }
                        }
                    }
                    testFile.close();
                    numMines = testMines;
                    newBoard.CreateNewBoard(numRows, numColumns, testMines, numTiles, test);
                }

                sf::IntRect test2Window(((float)numColumns * 16) + 224, ((float)numRows * 32), 64, 64);
                contains = test2Window.contains(mouseClick.x, mouseClick.y);
                if (contains)
                {
                    debug = false;
                    newBoard.ResetVariables(numRows, numColumns);
                    test = true;
                    happy = true;
                    cool = false;
                    sad = false;
                    numRevealed = 0;
                    canClick = true;
                    numFlags = 0;

                    ifstream testFile;
                    testFile.open("boards/testBoard2.brd");
                    string rowInfo;
                    int testMines = 0;

                    for (int i = 0; i < numRows; i++)
                    {
                        rowInfo = "";
                        getline(testFile, rowInfo);
                        for (int j = 0; j < rowInfo.size(); j++)
                        {
                            if (rowInfo[j] == '1')
                            {
                                newBoard.boardVector[i][j].isMine = true;
                                testMines++;
                            }
                        }
                    }
                    testFile.close();
                    numMines = testMines;
                    newBoard.CreateNewBoard(numRows, numColumns, testMines, numTiles, test);
                }

                sf::IntRect test3Window(((float)numColumns * 16) + 288, ((float)numRows * 32), 64, 64);
                contains = test3Window.contains(mouseClick.x, mouseClick.y);
                if (contains)
                {
                    debug = false;
                    newBoard.ResetVariables(numRows, numColumns);
                    test = true;
                    happy = true;
                    cool = false;
                    sad = false;
                    numRevealed = 0;
                    canClick = true;

                    ifstream testFile;
                    testFile.open("boards/testBoard3.brd");
                    string rowInfo;
                    int testMines = 0;

                    for (int i = 0; i < numRows; i++)
                    {
                        rowInfo = "";
                        getline(testFile, rowInfo);
                        for (unsigned int j = 0; j < rowInfo.size(); j++)
                        {
                            if (rowInfo[j] == '1')
                            {
                                newBoard.boardVector[i][j].isMine = true;
                                testMines++;
                            }
                        }
                    }
                    testFile.close();
                    numMines = testMines;
                    numFlags = 0;
                    newBoard.CreateNewBoard(numRows, numColumns, testMines, numTiles, test);
                }
            }
        }

        window.clear();

        flagsRemaining = numMines - numFlags;
        string digitString = to_string(flagsRemaining);
        int digitInteger;

        for (unsigned int i = 0; i < digitString.size(); i++)
        {
            //check TextureManager.cpp for relative path
            sf::Sprite digits(TextureManager::GetTexture("digits"));
            if (digitString[i] == '-')
            {
                digits.setTextureRect(sf::IntRect(210, 0, 21, 32));
                digits.setPosition((float)32 * (i + 1), ((float)numRows * 32));
                window.draw(digits);
            }
            else
            {
                digitInteger = digitString[i] - 48;
                digits.setTextureRect(sf::IntRect(21 * digitInteger, 0, 21, 32));
                digits.setPosition((float)32 * (i + 1), ((float)numRows * 32));
                window.draw(digits);
            }
        }

        sf::Sprite debugImage(TextureManager::GetTexture("debug"));
        debugImage.setPosition(((float)numColumns * 16) + 96, ((float)numRows * 32));
        window.draw(debugImage);

        sf::Sprite test1(TextureManager::GetTexture("test_1"));
        test1.setPosition(((float)numColumns * 16) + 160, ((float)numRows * 32));
        window.draw(test1);

        sf::Sprite test2(TextureManager::GetTexture("test_2"));
        test2.setPosition(((float)numColumns * 16) + 224, ((float)numRows * 32));
        window.draw(test2);

        sf::Sprite test3(TextureManager::GetTexture("test_3"));
        test3.setPosition(((float)numColumns * 16) + 288, ((float)numRows * 32));
        window.draw(test3);

        if (happy == true)
        {
            sf::Sprite faceHappy(TextureManager::GetTexture("face_happy"));
            faceHappy.setPosition(((float)numColumns * 16) - 32, ((float)numRows * 32));
            window.draw(faceHappy);
        }


        if (sad == true)
        {
            sf::Sprite faceLose(TextureManager::GetTexture("face_lose"));
            faceLose.setPosition(((float)numColumns * 16) - 32, ((float)numRows * 32));
            window.draw(faceLose);
            //sad = false;
        }

        if (cool == true)
        {
            sf::Sprite faceWin(TextureManager::GetTexture("face_win"));
            faceWin.setPosition(((float)numColumns * 16) - 32, ((float)numRows * 32));
            window.draw(faceWin);
            //cool == false;
        }



        for (int i = 0; i < numRows; i++)
        {
            for (int j = 0; j < numColumns; j++)
            {
                sf::Sprite revealedTile(TextureManager::GetTexture("tile_revealed"));
                revealedTile.setPosition(newBoard.boardVector[i][j].xPosition, newBoard.boardVector[i][j].yPosition);

                window.draw(revealedTile);

                if ((newBoard.boardVector[i][j].isMine == false) && (newBoard.boardVector[i][j].adjacentMines != 0))
                {
                    int number = newBoard.boardVector[i][j].adjacentMines;
                    string num = "number_" + to_string(number);
                    sf::Sprite numberTile(TextureManager::GetTexture(num));
                    numberTile.setPosition(newBoard.boardVector[i][j].xPosition, newBoard.boardVector[i][j].yPosition);

                    window.draw(numberTile);
                }

                if (newBoard.boardVector[i][j].isMine == true)
                {
                    sf::Sprite mine(TextureManager::GetTexture("mine"));
                    mine.setPosition(newBoard.boardVector[i][j].xPosition, newBoard.boardVector[i][j].yPosition);
                    window.draw(mine);
                }

                if (newBoard.boardVector[i][j].revealed == false)
                {
                    sf::Sprite hiddenTile(TextureManager::GetTexture("tile_hidden"));
                    hiddenTile.setPosition(newBoard.boardVector[i][j].xPosition, newBoard.boardVector[i][j].yPosition);

                    window.draw(hiddenTile);
                }

                if ((newBoard.boardVector[i][j].flagged == true) && (sad == false))
                {
                    sf::Sprite flag(TextureManager::GetTexture("flag"));
                    flag.setPosition(newBoard.boardVector[i][j].xPosition, newBoard.boardVector[i][j].yPosition);

                    window.draw(flag);
                }

                if ((newBoard.boardVector[i][j].isMine == true) && (debug == true))
                {
                    sf::Sprite mine(TextureManager::GetTexture("mine"));
                    mine.setPosition(newBoard.boardVector[i][j].xPosition, newBoard.boardVector[i][j].yPosition);
                    window.draw(mine);
                }
            }
        }
        window.display();
    }
    TextureManager::Clear();

    return 0;
}