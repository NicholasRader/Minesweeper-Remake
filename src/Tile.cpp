#include "Tile.h"

Tile::Tile(sf::Texture& texture) : sf::Sprite(texture) { }

bool Tile::isFlagged() {
	return flagged;
}

bool Tile::isRevealed() {
	return revealed;
}

bool Tile::isMine() {
	return mined;
}

bool Tile::isDebug() {
	return debugged;
}

bool Tile::hasCleared() {
	return cleared;
}

void Tile::setFlagged(bool flag) {
	flagged = flag;
}

void Tile::setRevealed(bool reveal) {
	revealed = reveal;
}

void Tile::setMine(bool mine) {
	mined = mine;
}

void Tile::setNumNearby(int mines) {
	adjacentMines = mines;
}

void Tile::setDebug(bool debug) {
	debugged = debug;
}

void Tile::setCleared(bool clear) {
	cleared = clear;
}

int Tile::getNumNearby() {
	return adjacentMines;
}