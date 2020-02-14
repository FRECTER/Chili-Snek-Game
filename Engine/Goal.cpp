#include "Goal.h"

Goal::Goal(std::mt19937& rng, const Board& board, const Snake& snake) {
	Respawn(rng, board, snake);
}

void Goal::Respawn(std::mt19937& rng, const Board& board, const Snake& snake) {
	std::uniform_int_distribution<int> xDist(0, board.GetWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, board.GetHeight() - 1);
	Location new_loc;
	do {
		new_loc.x = xDist(rng);
		new_loc.y = yDist(rng);
	} while (snake.InTile(new_loc));
	loc = new_loc;
}

void Goal::Draw(Board& board) const {
	board.DrawCell(loc, c);
}

const Location& Goal::getLocation() const {
	return loc;
}