#pragma once
#include "Graphics.h"
#include "Location.h"

class Board {
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	int GetWidth() const;
	int GetHeight() const;
	int GetDim() const;
	bool Inside(const Location& loc) const;
private:
	static constexpr int cellDim = 10;
	static constexpr int width = 70;
	static constexpr int height = 50;
	Graphics& gfx;
};