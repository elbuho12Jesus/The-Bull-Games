#pragma once
struct Timer {
public:	
	static void Start();
	static void Read();
	static void Stop();
	

private:	
	static float GetTimeWithoutStop(float a);
	static float stopTime;
	static float stop;
	static float realStop;
	static bool pause;	

};