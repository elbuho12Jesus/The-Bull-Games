#include "Globals.h"
#include "Timer.h"
#include "SDL.h"

float Timer::stopTime;
float Timer::stop;
float Timer::realStop;
bool Timer::pause;
void Timer::Start() 
{
	stopTime = 0.0f;
	stop = 0.0f;
	realStop = 0.0f;
	pause = false;	
}

float Timer::GetTimeWithoutStop(float a) {
	return float(SDL_GetTicks())- a;
}

void Timer::Read() {
	if (pause) {
		LOG_ENGINE("Time is puase in: %f", stop);
	}else{
		LOG_ENGINE("Time is: %f", GetTimeWithoutStop(stopTime));
	}	
}
void Timer::Stop() {	
	if (pause) {		
		pause = false;
		stopTime += GetTimeWithoutStop(realStop);
	}	else {
		stop = GetTimeWithoutStop(stopTime);
		realStop= float(SDL_GetTicks());		
		LOG_ENGINE("Time is: %f", stop);
		pause = true;
	}
}

