#pragma once
#include <chrono>

class Stopwatch
{
public:
	Stopwatch();

	virtual void Start();
	virtual void Stop();
	virtual void Reset();
	virtual void Restart();

	virtual bool IsRunning();

	virtual long Elapsed();

protected:
	long elapsed;

	DWORD startTime;
	bool isRunning;
	long GetElapsedTime();
};