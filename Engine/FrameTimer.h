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
		std::chrono::duration<float> duration = last - old;
		return duration.count();
	}
	std::chrono::steady_clock::time_point GetTimeStamp() {
		return last;
	}
private:
	std::chrono::steady_clock::time_point last;
};