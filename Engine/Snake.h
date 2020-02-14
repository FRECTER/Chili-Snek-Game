#pragma once
#include "Board.h"

class Snake {
private:
	class Segment {
	public:
		void InitHead(const Location& in_loc);
		void InitBody(Color target_c);
		void Follow(const Segment& next);
		void MoveBy(const Location& d_loc);
		void Draw(Board& board) const;
		const Location& getLocation() const;
	private:
		Location loc;
		Color c;
	};

public:
	Snake(const Location& loc);
	void MoveBy(const Location& d_loc);
	Location NextHeadLocation(const Location& d_loc) const;
	void Grow();
	void Draw(Board& board) const;
	bool InTileNOHEAD(const Location& check) const;
	bool InTile(const Location& check) const;
	int GetLength() const;
private:
	static constexpr Color headColor = Colors::Yellow;
	int usingSeg = 1;
	Color bodyColor = { 0,255,0 };
	static constexpr int MaxSeg = 1000;
	Segment segments[MaxSeg];
};