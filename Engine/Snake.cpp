#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location& loc) {
	constexpr int colorNum = 13;
	constexpr Color bodyColor[colorNum] = { {0,255,0},{0,225,0},{0,195,0},{0,165,0},{0,135,0},{0,105,0},{0,75,0},{0,105,0},{0,135,0},{0,165,0},{0,195,0},{0,225,0},{0,255,0} };
	for (int i = 0; i < MaxSeg; i++)
		segments[i].InitBody(bodyColor[i % colorNum]);
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location& d_loc) {
	for (int i = usingSeg - 1; i > 0; i--)
		segments[i].Follow(segments[i - 1]);
	segments[0].MoveBy(d_loc);
}

Location Snake::NextHeadLocation(const Location& d_loc) const {
	Location l(segments[0].getLocation());
	l.Add(d_loc);
	return l;
}

void Snake::Grow() {
	if (usingSeg < MaxSeg)
		usingSeg++;
}

void Snake::Draw(Board& board) const {
	for (int i = 0; i < usingSeg; i++)
		segments[i].Draw(board);
}

bool Snake::InTileNOHEAD(const Location& check) const {
	for (int i = 0; i < usingSeg - 1; i++) {
		if (segments[i].getLocation() == check)
			return true;
	}
	return false;
}

bool Snake::InTile(const Location& check) const {
	for (int i = 0; i < usingSeg; i++) {
		if (segments[i].getLocation() == check)
			return true;
	}
	return false;
}

int Snake::GetLength() const {
	return usingSeg - 1;
}

void Snake::Segment::InitHead(const Location& in_loc) {
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody(Color target_c) {
	c = target_c;
}

void Snake::Segment::Follow(const Segment& next) {
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location& d_loc) {
	assert(abs(d_loc.x) + abs(d_loc.y) == 1);
	loc.Add(d_loc);
}

void Snake::Segment::Draw(Board& board) const {
	board.DrawCell(loc, c);
}

const Location& Snake::Segment::getLocation() const {
	return loc;
}