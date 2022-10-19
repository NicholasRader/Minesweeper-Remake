#include <SFML/Graphics.hpp>

#include "Random.h"
#include "TextureManager.h"
#include "Tile.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

void setup(vector<Tile> &tileVector, int cols, int rows, int mines) {
    for (int i = 0; i < rows; i++) {
        for (int x = 0; x < cols; x++) {
            Tile tile(TextureManager::GetTexture("tile_hidden"));
            tile.setPosition((x * tile.getTextureRect().width), (i * tile.getTextureRect().height));
            tileVector.push_back(tile);
        }
    }

    vector<int> mineLocs;
    for (int i = 0; i < mines; i++) {
        int placement = Random::Int(0, (rows * cols) - 1);

        bool unique = true;

        for (unsigned int x = 0; x < mineLocs.size(); x++) {
            if (mineLocs.at(x) == placement) {
                unique = false;
            }
        }

        if (unique) {
            tileVector.at(placement).setMine(true);
            mineLocs.push_back(placement);
        }
        else {
            i--;
        }
    }

    for (unsigned int i = 0; i < tileVector.size(); i++) {
        if (i == 0) {
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + 1));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + cols));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i + cols) + 1));
        }
        else if (i == (cols - 1)) {
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - 1));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + cols));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i + cols) - 1));
        }
        else if (i == ((cols * rows) - cols)) {
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - cols));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i - cols) + 1));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + 1));
        }
        else if (i == ((cols * rows) - 1)) {
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - cols));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i - cols) - 1));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - 1));
        }
        else if (i % cols == 0) {
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - cols));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i - cols) + 1));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + 1));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + cols));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i + cols) + 1));
        }
        else if (i % cols == (cols - 1)) {
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - cols));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i - cols) - 1));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - 1));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + cols));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i + cols) - 1));
        }
        else if (i > 0 && i < (cols - 1)) {
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - 1));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + 1));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i + cols) - 1));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + cols));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i + cols) + 1));
        }
        else if (i > ((cols * rows) - cols) && i < ((cols * rows) - 1)) {
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - 1));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + 1));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i - cols) - 1));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - cols));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i - cols) + 1));
        }
        else {
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i - cols) - 1));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - cols));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i - cols) + 1));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - 1));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + 1));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i + cols) - 1));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + cols));
            tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i + cols) + 1));
        }

        int nearMines = 0;
        for (unsigned int x = 0; x < tileVector.at(i).adjacentTiles.size(); x++) {
            if (tileVector.at(i).adjacentTiles.at(x)->isMine()) {
                nearMines++;
            }
        }
        tileVector.at(i).setNumNearby(nearMines);

    }
}

void setupTest(string filePath, vector<Tile> &tileVector, int cols, int rows) {
    ifstream fileStream(filePath);

    if (fileStream.is_open()) {
        for (int i = 0; i < rows; i++) {
            for (int x = 0; x < cols; x++) {
                Tile tile(TextureManager::GetTexture("tile_hidden"));
                tile.setPosition((x * tile.getTextureRect().width), (i * tile.getTextureRect().height));
                tileVector.push_back(tile);
            }
        }

        for (unsigned int i = 0; i < tileVector.size(); i++) {
			char check = '0';
			fileStream >> check;
            if (check == '1') {
                tileVector.at(i).setMine(true);
            }
        }

        for (unsigned int i = 0; i < tileVector.size(); i++) {
            if (i == 0) {
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + 1));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + cols));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i + cols) + 1));
            }
            else if (i == (cols - 1)) {
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - 1));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + cols));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i + cols) - 1));
            }
            else if (i == ((cols * rows) - cols)) {
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - cols));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i - cols) + 1));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + 1));
            }
            else if (i == ((cols * rows) - 1)) {
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - cols));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i - cols) - 1));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - 1));
            }
            else if (i % cols == 0) {
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - cols));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i - cols) + 1));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + 1));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + cols));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i + cols) + 1));
            }
            else if (i % cols == (cols - 1)) {
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - cols));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i - cols) - 1));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - 1));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + cols));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i + cols) - 1));
            }
            else if (i > 0 && i < (cols - 1)) {
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - 1));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + 1));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i + cols) - 1));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + cols));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i + cols) + 1));
            }
            else if (i > ((cols * rows) - cols) && i < ((cols * rows) - 1)) {
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - 1));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + 1));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i - cols) - 1));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - cols));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i - cols) + 1));
            }
            else {
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i - cols) - 1));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - cols));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i - cols) + 1));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i - 1));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + 1));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i + cols) - 1));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at(i + cols));
                tileVector.at(i).adjacentTiles.push_back(&tileVector.at((i + cols) + 1));
            }

            int nearMines = 0;
            for (unsigned int x = 0; x < tileVector.at(i).adjacentTiles.size(); x++) {
                if (tileVector.at(i).adjacentTiles.at(x)->isMine()) {
                    nearMines++;
                }
            }
            tileVector.at(i).setNumNearby(nearMines);

        }
    }
    else {
        cout << "File not opened." << endl;
    }
}

int main()
{
    ifstream fileStream("boards/config.cfg");

    int numCols = 0;
    int numRows = 0;
    int numMines = 0;

    if (fileStream.is_open()) {
        fileStream >> numCols;
        fileStream >> numRows;
        fileStream >> numMines;
    }
    else {
        cout << "File not opened." << endl;
    }

    fileStream.close();

    sf::RenderWindow window(sf::VideoMode(numCols * 32, (numRows * 32) + 88), "Minesweeper");

    vector<Tile> tiles;

    setup(tiles, numCols, numRows, numMines);

    sf::Sprite happy(TextureManager::GetTexture("face_happy"));
    sf::Sprite win(TextureManager::GetTexture("face_win"));
    sf::Sprite lose(TextureManager::GetTexture("face_lose"));

    sf::Sprite debug(TextureManager::GetTexture("debug"));
    sf::Sprite test1(TextureManager::GetTexture("test_1"));
    sf::Sprite test2(TextureManager::GetTexture("test_2"));
    sf::Sprite test3(TextureManager::GetTexture("test_3"));
    
    bool gameOver = false;
    bool hasLost = false;
    bool debugOn = false;

    int tilesLeft = (numCols * numRows) - numMines;
    int numFlags = 0;
    int numMinesTemp = 0;

    while (window.isOpen())
    {

        sf::Vector2i pos = sf::Mouse::getPosition(window);
        int posX = pos.x;
        int posY = pos.y;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    for (unsigned int i = 0; i < tiles.size(); i++) {
                        if (!gameOver && posX >= tiles.at(i).getPosition().x && posX <= tiles.at(i).getPosition().x + tiles.at(i).getTextureRect().width && posY >= tiles.at(i).getPosition().y && posY <= tiles.at(i).getPosition().y + tiles.at(i).getTextureRect().height) {
                            if (!tiles.at(i).isFlagged()) {
                                tiles.at(i).setRevealed(true);
                            }
                        }
                    }

                    if (!gameOver && posX >= debug.getPosition().x && posX <= debug.getPosition().x + debug.getTextureRect().width && posY >= debug.getPosition().y && posY <= debug.getPosition().y + debug.getTextureRect().height) {
                        debugOn = !debugOn;
                    }

                    if (posX >= happy.getPosition().x && posX <= happy.getPosition().x + happy.getTextureRect().width && posY >= happy.getPosition().y && posY <= happy.getPosition().y + happy.getTextureRect().height) {
                        tiles.clear();
                        numMinesTemp = 0;
                        setup(tiles, numCols, numRows, numMines);
                        gameOver = false;
                        hasLost = false;
                        tilesLeft = (numCols * numRows) - numMines;
                        numFlags = 0;
                    }

                    if (posX >= test1.getPosition().x && posX <= test1.getPosition().x + test1.getTextureRect().width && posY >= test1.getPosition().y && posY <= test1.getPosition().y + test1.getTextureRect().height) {
                        tiles.clear();
                        setupTest("boards/testboard1.brd", tiles, numCols, numRows);
                        numMinesTemp = 0;
                        for (unsigned int i = 0; i < tiles.size(); i++) {
                            if (tiles.at(i).isMine()) {
                                numMinesTemp++;
                            }
                        }
                        gameOver = false;
                        hasLost = false;
                        tilesLeft = (numCols * numRows) - numMinesTemp;
                        numFlags = 0;
                    }

                    if (posX >= test2.getPosition().x && posX <= test2.getPosition().x + test2.getTextureRect().width && posY >= test2.getPosition().y && posY <= test2.getPosition().y + test2.getTextureRect().height) {
                        tiles.clear();
                        setupTest("boards/testboard2.brd", tiles, numCols, numRows);
                        numMinesTemp = 0;
                        for (unsigned int i = 0; i < tiles.size(); i++) {
                            if (tiles.at(i).isMine()) {
                                numMinesTemp++;
                            }
                        }
                        gameOver = false;
                        hasLost = false;
                        tilesLeft = (numCols * numRows) - numMinesTemp;
                        numFlags = 0;
                    }

                    if (posX >= test3.getPosition().x && posX <= test3.getPosition().x + test3.getTextureRect().width && posY >= test3.getPosition().y && posY <= test3.getPosition().y + test3.getTextureRect().height) {
                        tiles.clear();
                        setupTest("boards/testboard3.brd", tiles, numCols, numRows);
                        numMinesTemp = 0;
                        for (unsigned int i = 0; i < tiles.size(); i++) {
                            if (tiles.at(i).isMine()) {
                                numMinesTemp++;
                            }
                        }
                        gameOver = false;
                        hasLost = false;
                        tilesLeft = (numCols * numRows) - numMinesTemp;
                        numFlags = 0;
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Right) {
                    for (unsigned int i = 0; i < tiles.size(); i++) {
                        if (!gameOver && posX >= tiles.at(i).getPosition().x && posX <= tiles.at(i).getPosition().x + tiles.at(i).getTextureRect().width && posY >= tiles.at(i).getPosition().y && posY <= tiles.at(i).getPosition().y + tiles.at(i).getTextureRect().height) {
                            if (tiles.at(i).isFlagged()) {
                                tiles.at(i).setFlagged(false);
                                numFlags--;
                            }
                            else if (!tiles.at(i).isRevealed()) {
                                tiles.at(i).setFlagged(true);
                                numFlags++;
                            }
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);

        if (!debugOn && !gameOver) {
            for (unsigned int i = 0; i < tiles.size(); i++) {
                if (tiles.at(i).isMine() && tiles.at(i).isRevealed()) {
                    tiles.at(i).setDebug(false);
                }
            }
        }

        for (unsigned int i = 0; i < tiles.size(); i++) {
            window.draw(tiles.at(i));
            if (tiles.at(i).isFlagged()) {
                sf::Sprite flag(TextureManager::GetTexture("flag"));
                flag.setPosition(tiles.at(i).getPosition());
                window.draw(flag);
            }
            if (tiles.at(i).isRevealed() && !tiles.at(i).isMine()) {
                sf::Sprite space(TextureManager::GetTexture("tile_revealed"));
                space.setPosition(tiles.at(i).getPosition());
                window.draw(space);

                if (tiles.at(i).getNumNearby() == 0 && !tiles.at(i).hasCleared()) {
                    for (unsigned int x = 0; x < tiles.at(i).adjacentTiles.size(); x++) {
                        if (!tiles.at(i).adjacentTiles.at(x)->isFlagged()) {
                            tiles.at(i).adjacentTiles.at(x)->setRevealed(true);
                        }
                    }
                }
                else if (tiles.at(i).getNumNearby() == 1) {
                    sf::Sprite number1(TextureManager::GetTexture("number_1"));
                    number1.setPosition(tiles.at(i).getPosition());
                    window.draw(number1);
                }
                else if (tiles.at(i).getNumNearby() == 2) {
                    sf::Sprite number2(TextureManager::GetTexture("number_2"));
                    number2.setPosition(tiles.at(i).getPosition());
                    window.draw(number2);
                }
                else if (tiles.at(i).getNumNearby() == 3) {
                    sf::Sprite number3(TextureManager::GetTexture("number_3"));
                    number3.setPosition(tiles.at(i).getPosition());
                    window.draw(number3);
                }
                else if (tiles.at(i).getNumNearby() == 4) {
                    sf::Sprite number4(TextureManager::GetTexture("number_4"));
                    number4.setPosition(tiles.at(i).getPosition());
                    window.draw(number4);
                }
                else if (tiles.at(i).getNumNearby() == 5) {
                    sf::Sprite number5(TextureManager::GetTexture("number_5"));
                    number5.setPosition(tiles.at(i).getPosition());
                    window.draw(number5);
                }
                else if (tiles.at(i).getNumNearby() == 6) {
                    sf::Sprite number6(TextureManager::GetTexture("number_6"));
                    number6.setPosition(tiles.at(i).getPosition());
                    window.draw(number6);
                }
                else if (tiles.at(i).getNumNearby() == 7) {
                    sf::Sprite number7(TextureManager::GetTexture("number_7"));
                    number7.setPosition(tiles.at(i).getPosition());
                    window.draw(number7);
                }
                else if (tiles.at(i).getNumNearby() == 8) {
                    sf::Sprite number8(TextureManager::GetTexture("number_8"));
                    number8.setPosition(tiles.at(i).getPosition());
                    window.draw(number8);
                }
                if (!tiles.at(i).hasCleared()) {
                    tiles.at(i).setCleared(true);
                    tilesLeft--;
                }
            }
            else if (tiles.at(i).isRevealed() && tiles.at(i).isMine()) {
				for (unsigned int y = 0; y < tiles.size(); y++) {
                    if (tiles.at(y).isMine()) {
                        tiles.at(y).setRevealed(true);
                        sf::Sprite mine(TextureManager::GetTexture("mine"));
                        mine.setPosition(tiles.at(y).getPosition());
                        window.draw(mine);
                    }
				}
                gameOver = true;
                hasLost = true;
            }
        }

        if (debugOn) {
            for (unsigned int i = 0; i < tiles.size(); i++) {
                if (tiles.at(i).isMine()) {
                    tiles.at(i).setDebug(true);
                    sf::Sprite mine(TextureManager::GetTexture("mine"));
                    mine.setPosition(tiles.at(i).getPosition());
                    window.draw(mine);
                }
            }
        }

        if (tilesLeft == 0) {
            gameOver = true;
        }

        int counter = numMines - numFlags;
        if (numMinesTemp > 0) {
            counter = numMinesTemp - numFlags;
        }

        if (counter < 0) {
            sf::Sprite digitsN(TextureManager::GetTexture("digits"));
            digitsN.setTextureRect(sf::IntRect(210, 0, 21, 32));
            digitsN.setPosition(0, (numRows * 32));
            window.draw(digitsN);
            counter *= -1;
        }

        if ((counter / 100) % 10 == 9) {
            sf::Sprite digits9(TextureManager::GetTexture("digits"));
            digits9.setTextureRect(sf::IntRect(189, 0, 21, 32));
            digits9.setPosition(digits9.getTextureRect().width, (numRows * 32));
            window.draw(digits9);
        }
        else if ((counter / 100) % 10 == 8) {
            sf::Sprite digits8(TextureManager::GetTexture("digits"));
            digits8.setTextureRect(sf::IntRect(168, 0, 21, 32));
            digits8.setPosition(digits8.getTextureRect().width, (numRows * 32));
            window.draw(digits8);
        }
        else if ((counter / 100) % 10 == 7) {
            sf::Sprite digits7(TextureManager::GetTexture("digits"));
            digits7.setTextureRect(sf::IntRect(147, 0, 21, 32));
            digits7.setPosition(digits7.getTextureRect().width, (numRows * 32));
            window.draw(digits7);
        }
        else if ((counter / 100) % 10 == 6) {
            sf::Sprite digits6(TextureManager::GetTexture("digits"));
            digits6.setTextureRect(sf::IntRect(126, 0, 21, 32));
            digits6.setPosition(digits6.getTextureRect().width, (numRows * 32));
            window.draw(digits6);
        }
        else if ((counter / 100) % 10 == 5) {
            sf::Sprite digits5(TextureManager::GetTexture("digits"));
            digits5.setTextureRect(sf::IntRect(105, 0, 21, 32));
            digits5.setPosition(digits5.getTextureRect().width, (numRows * 32));
            window.draw(digits5);
        }
        else if ((counter / 100) % 10 == 4) {
            sf::Sprite digits4(TextureManager::GetTexture("digits"));
            digits4.setTextureRect(sf::IntRect(84, 0, 21, 32));
            digits4.setPosition(digits4.getTextureRect().width, (numRows * 32));
            window.draw(digits4);
        }
        else if ((counter / 100) % 10 == 3) {
            sf::Sprite digits3(TextureManager::GetTexture("digits"));
            digits3.setTextureRect(sf::IntRect(63, 0, 21, 32));
            digits3.setPosition(digits3.getTextureRect().width, (numRows * 32));
            window.draw(digits3);
        }
        else if ((counter / 100) % 10 == 2) {
            sf::Sprite digits2(TextureManager::GetTexture("digits"));
            digits2.setTextureRect(sf::IntRect(42, 0, 21, 32));
            digits2.setPosition(digits2.getTextureRect().width, (numRows * 32));
            window.draw(digits2);
        }
        else if ((counter / 100) % 10 == 1) {
            sf::Sprite digits1(TextureManager::GetTexture("digits"));
            digits1.setTextureRect(sf::IntRect(21, 0, 21, 32));
            digits1.setPosition(digits1.getTextureRect().width, (numRows * 32));
            window.draw(digits1);
        }
        else if ((counter / 100) % 10 == 0) {
            sf::Sprite digits0(TextureManager::GetTexture("digits"));
            digits0.setTextureRect(sf::IntRect(0, 0, 21, 32));
            digits0.setPosition(digits0.getTextureRect().width, (numRows * 32));
            window.draw(digits0);
        }

        if ((counter / 10) % 10 == 9) {
            sf::Sprite digits9(TextureManager::GetTexture("digits"));
            digits9.setTextureRect(sf::IntRect(189, 0, 21, 32));
            digits9.setPosition(2 * digits9.getTextureRect().width, (numRows * 32));
            window.draw(digits9);
        }
        else if ((counter / 10) % 10 == 8) {
            sf::Sprite digits8(TextureManager::GetTexture("digits"));
            digits8.setTextureRect(sf::IntRect(168, 0, 21, 32));
            digits8.setPosition(2 * digits8.getTextureRect().width, (numRows * 32));
            window.draw(digits8);
        }
        else if ((counter / 10) % 10 == 7) {
            sf::Sprite digits7(TextureManager::GetTexture("digits"));
            digits7.setTextureRect(sf::IntRect(147, 0, 21, 32));
            digits7.setPosition(2 * digits7.getTextureRect().width, (numRows * 32));
            window.draw(digits7);
        }
        else if ((counter / 10) % 10 == 6) {
            sf::Sprite digits6(TextureManager::GetTexture("digits"));
            digits6.setTextureRect(sf::IntRect(126, 0, 21, 32));
            digits6.setPosition(2 * digits6.getTextureRect().width, (numRows * 32));
            window.draw(digits6);
        }
        else if ((counter / 10) % 10 == 5) {
            sf::Sprite digits5(TextureManager::GetTexture("digits"));
            digits5.setTextureRect(sf::IntRect(105, 0, 21, 32));
            digits5.setPosition(2 * digits5.getTextureRect().width, (numRows * 32));
            window.draw(digits5);
        }
        else if ((counter / 10) % 10 == 4) {
            sf::Sprite digits4(TextureManager::GetTexture("digits"));
            digits4.setTextureRect(sf::IntRect(84, 0, 21, 32));
            digits4.setPosition(2 * digits4.getTextureRect().width, (numRows * 32));
            window.draw(digits4);
        }
        else if ((counter / 10) % 10 == 3) {
            sf::Sprite digits3(TextureManager::GetTexture("digits"));
            digits3.setTextureRect(sf::IntRect(63, 0, 21, 32));
            digits3.setPosition(2 * digits3.getTextureRect().width, (numRows * 32));
            window.draw(digits3);
        }
        else if ((counter / 10) % 10 == 2) {
            sf::Sprite digits2(TextureManager::GetTexture("digits"));
            digits2.setTextureRect(sf::IntRect(42, 0, 21, 32));
            digits2.setPosition(2 * digits2.getTextureRect().width, (numRows * 32));
            window.draw(digits2);
        }
        else if ((counter / 10) % 10 == 1) {
            sf::Sprite digits1(TextureManager::GetTexture("digits"));
            digits1.setTextureRect(sf::IntRect(21, 0, 21, 32));
            digits1.setPosition(2 * digits1.getTextureRect().width, (numRows * 32));
            window.draw(digits1);
        }
        else if ((counter / 10) % 10 == 0) {
            sf::Sprite digits0(TextureManager::GetTexture("digits"));
            digits0.setTextureRect(sf::IntRect(0, 0, 21, 32));
            digits0.setPosition(2 * digits0.getTextureRect().width, (numRows * 32));
            window.draw(digits0);
        }

        if ((counter) % 10 == 9) {
            sf::Sprite digits9(TextureManager::GetTexture("digits"));
            digits9.setTextureRect(sf::IntRect(189, 0, 21, 32));
            digits9.setPosition(3 * digits9.getTextureRect().width, (numRows * 32));
            window.draw(digits9);
        }
        else if ((counter) % 10 == 8) {
            sf::Sprite digits8(TextureManager::GetTexture("digits"));
            digits8.setTextureRect(sf::IntRect(168, 0, 21, 32));
            digits8.setPosition(3 * digits8.getTextureRect().width, (numRows * 32));
            window.draw(digits8);
        }
        else if ((counter) % 10 == 7) {
            sf::Sprite digits7(TextureManager::GetTexture("digits"));
            digits7.setTextureRect(sf::IntRect(147, 0, 21, 32));
            digits7.setPosition(3 * digits7.getTextureRect().width, (numRows * 32));
            window.draw(digits7);
        }
        else if ((counter) % 10 == 6) {
            sf::Sprite digits6(TextureManager::GetTexture("digits"));
            digits6.setTextureRect(sf::IntRect(126, 0, 21, 32));
            digits6.setPosition(3 * digits6.getTextureRect().width, (numRows * 32));
            window.draw(digits6);
        }
        else if ((counter) % 10 == 5) {
            sf::Sprite digits5(TextureManager::GetTexture("digits"));
            digits5.setTextureRect(sf::IntRect(105, 0, 21, 32));
            digits5.setPosition(3 * digits5.getTextureRect().width, (numRows * 32));
            window.draw(digits5);
        }
        else if ((counter) % 10 == 4) {
            sf::Sprite digits4(TextureManager::GetTexture("digits"));
            digits4.setTextureRect(sf::IntRect(84, 0, 21, 32));
            digits4.setPosition(3 * digits4.getTextureRect().width, (numRows * 32));
            window.draw(digits4);
        }
        else if ((counter) % 10 == 3) {
            sf::Sprite digits3(TextureManager::GetTexture("digits"));
            digits3.setTextureRect(sf::IntRect(63, 0, 21, 32));
            digits3.setPosition(3 * digits3.getTextureRect().width, (numRows * 32));
            window.draw(digits3);
        }
        else if ((counter) % 10 == 2) {
            sf::Sprite digits2(TextureManager::GetTexture("digits"));
            digits2.setTextureRect(sf::IntRect(42, 0, 21, 32));
            digits2.setPosition(3 * digits2.getTextureRect().width, (numRows * 32));
            window.draw(digits2);
        }
        else if ((counter) % 10 == 1) {
            sf::Sprite digits1(TextureManager::GetTexture("digits"));
            digits1.setTextureRect(sf::IntRect(21, 0, 21, 32));
            digits1.setPosition(3 * digits1.getTextureRect().width, (numRows * 32));
            window.draw(digits1);
        }
        else if ((counter) % 10 == 0) {
            sf::Sprite digits0(TextureManager::GetTexture("digits"));
            digits0.setTextureRect(sf::IntRect(0, 0, 21, 32));
            digits0.setPosition(3 * digits0.getTextureRect().width, (numRows * 32));
            window.draw(digits0);
        }

        happy.setPosition((numCols * 32) / 2, (numRows * 32));
        window.draw(happy);

        if (gameOver && !hasLost) {
            win.setPosition((numCols * 32) / 2, (numRows * 32));
            window.draw(win);
        }
        else if (gameOver) {
            lose.setPosition((numCols * 32) / 2, (numRows * 32));
            window.draw(lose);
        }

        debug.setPosition(((numCols * 32) / 2) + 128, (numRows * 32));
        window.draw(debug);

        test1.setPosition(((numCols * 32) / 2) + 192, (numRows * 32));
        window.draw(test1);

        test2.setPosition(((numCols * 32) / 2) + 256, (numRows * 32));
        window.draw(test2);

        test3.setPosition(((numCols * 32) / 2) + 320, (numRows * 32));
        window.draw(test3);


        window.display();
    }

    return 0;
}