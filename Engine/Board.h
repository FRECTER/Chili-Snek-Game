#pragma once
#include "Graphics.h"
#include "Location.h"
#include <random>

class Board {
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	int GetWidth() const;
	int GetHeight() const;
	int GetDim() const;
	bool Inside(const Location& loc) const;
	bool CheckObs(const Location& loc) const;
	void SpawnObs(std::mt19937& rng, const Location& loc, const class Snake& snake, const class Goal& goal);

private:
	static constexpr int cellDim = 10;
	static constexpr int width = 70;
	static constexpr int height = 50;
	Graphics& gfx;
	bool haveObs[width * height] = { false };
};