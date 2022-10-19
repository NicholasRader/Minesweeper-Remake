#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Tile : public sf::Sprite
{
	int adjacentMines = 0;

	bool flagged = false;
	bool revealed = false;
	bool mined = false;
	bool debugged = false;
	bool cleared = false;
public:

	std::vector<Tile*> adjacentTiles;
	Tile(sf::Texture& texture);

	bool isFlagged();
	bool isRevealed();
	bool isMine();
	bool isDebug();
	bool hasCleared();

	void setFlagged(bool flag);
	void setRevealed(bool reveal);
	void setMine(bool mine);
	void setDebug(bool debug);
	void setCleared(bool clear);

	void setNumNearby(int mines);
	int getNumNearby();
};