#include "Board.h"
#include <assert.h>

Board::Board(Graphics & gfx)
	:
	gfx(gfx)
{}

void Board::DrawCell(const Location & loc, Color c) {
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	gfx.DrawRectDim(loc.x * cellDim + (Graphics::ScreenWidth - width * cellDim) / 2 + 1, loc.y*cellDim + (Graphics::ScreenHeight - height * cellDim) / 2 + 1, cellDim - 1, cellDim - 1, c);
}

int Board::GetWidth() const {
	return width;
}

int Board::GetHeight() const {
	return height;
}

int Board::GetDim() const {
	return cellDim;
}

bool Board::Inside(const Location& loc) const {
	return loc.x >= 0 && loc.x < width && loc.y >= 0 && loc.y < height;
}