#pragma once
#include <chrono>

class FrameTimer {
public:
	FrameTimer() {
		last = std::chrono::steady_clock::now();
	}
	float Mark() {
		const auto old = last;
		last = std::chrono::steady_clock::now();
		std::chrono::steady_clock::duration duration = last - old;
		return duration.count();
	}
private:
	std::chrono::steady_clock::time_point last;
};