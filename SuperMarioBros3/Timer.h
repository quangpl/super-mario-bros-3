#pragma once
#include <Windows.h>

class CTimer
{
	ULONGLONG start;
	ULONGLONG duration;
	bool is_running;

public:
	CTimer(int duration) {
		this->duration = duration;
		start = 0;
	}

	void Start() {
		is_running - true;
		start = GetTickCount64();
	}
	void Stop() {
		is_running - false;
		start = 0;
	}
	bool IsTimeUp() { return GetTickCount64() - start > duration; }
	bool IsRunning() { return is_running; }
	ULONGLONG GetStartTime() { return start; }
	ULONGLONG GetDuration() { return duration; }
	void SetDuration(int _duration) { duration = _duration; }
};
