////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL - core
//
//		Author: Pablo Ram�n Soria 
//		Date: 2013/14/08	
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Time and time functions

// Engine headers
#include "time.h"
#include <cassert>
namespace BOViL {
	//------------------------------------------------------------------------------------------------------------------
	// Static data definition
	//------------------------------------------------------------------------------------------------------------------
	STime* STime::sTime = nullptr;	

	#if defined(__linux__)
		timeval STime::mInitTime = {0, 0};
	#elif defined (_WIN32)
		LARGE_INTEGER STime::mInitTime = { 0, 0 };
	#endif

	//------------------------------------------------------------------------------------------------------------------
	// Method implementations
	//------------------------------------------------------------------------------------------------------------------
	void STime::init() {
		assert(sTime == nullptr);
		sTime = new STime();
	}

	//------------------------------------------------------------------------------------------------------------------
	void STime::end() {
		assert(sTime != nullptr);
		delete sTime;
		sTime = nullptr;
	}

	//------------------------------------------------------------------------------------------------------------------
	double STime::getTime() {
	#if defined (__linux__)
		// Get current time
		timeval currentTime;
		gettimeofday(&currentTime, 0);
		return double(currentTime.tv_sec - mInitTime.tv_sec) + double(currentTime.tv_usec - mInitTime.tv_usec)/1000000;
	#elif defined (_WIN32)
		// Get current time
		LARGE_INTEGER largeTicks;
		QueryPerformanceCounter(&largeTicks);
		unsigned currTime = largeTicks.LowPart;
		// Convert time difference to seconds
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		return (double(currTime) / double(frequency.LowPart)) - 
							(double(mInitTime.LowPart) / double(frequency.LowPart));
	#endif 
	}

	//------------------------------------------------------------------------------------------------------------------
	STime::STime() {
		#if defined (__linux__)
			// Get current time
			gettimeofday(&mInitTime, 0);
		#elif defined (WIN32)
			// Get initial time
			QueryPerformanceCounter(&mInitTime);
		#endif
	}
	
}        // namespace BOViL
