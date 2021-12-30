#include <Windows.h>
#include "StopWatch.h"
#include "Game.h"

Stopwatch::Stopwatch()
{
	Reset();
}

void Stopwatch::Start()
{
	if (!isRunning)
	{
		isRunning = true;
		startTime = (DWORD) GetTickCount64();
	}
}

void Stopwatch::Stop()
{
	if (isRunning)
	{
		DWORD endTime = (DWORD)GetTickCount64();
		DWORD elapsedPeriod = endTime - startTime;
		elapsed += elapsedPeriod;
		isRunning = false;
	}
}

void Stopwatch::Reset()
{
	elapsed = 0;
	startTime = (DWORD)GetTickCount64();
	isRunning = false;
}

void Stopwatch::Restart()
{
	Reset();
	Start();
}

bool Stopwatch::IsRunning()
{
	return isRunning;
}

long Stopwatch::Elapsed()
{
	return GetElapsedTime();
}

long Stopwatch::GetElapsedTime()
{
	long timeElapsed = elapsed;

	if (isRunning)
	{
		DWORD currentTime = (DWORD)GetTickCount64();
		long currentElapsed = currentTime - startTime;
		timeElapsed += currentElapsed;
	}
	return timeElapsed;
}
