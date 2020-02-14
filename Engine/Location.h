#pragma once

class Location {
public:
	void Add(const Location& d) {
		x += d.x;
		y += d.y;
	}
	bool operator==(const Location& check) const {
		return x == check.x && y == check.y;
	}
	int x;
	int y;
};