////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL - core
//
//		Author: Pablo Ram�n Soria 
//		Date: 2013/04/08
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Time and time functions

#ifndef _BOVIL_CORE_TIME_TIME_H_
#define _BOVIL_CORE_TIME_TIME_H_

#if defined(__linux__)
	#include <sys/time.h>
#elif defined(_WIN32)
	#include <Windows.h>
#endif

namespace BOViL {
	class STime {
	public:
		// --- Singleton life cycle ---
		static void init();
		static STime* get();        // Returns the singleton instance
		static void end();

	public: // --- Public interface ---
		double getTime();

	private:
		STime();
	private:
		// Singleton instance
		static STime* sTime; // Static data definition
		// members
		#if defined(__linux__)
			static timeval mInitTime;
		#elif defined (_WIN32)
			static LARGE_INTEGER mInitTime;
		#endif
	};

	//------------------------------------------------------------------------------------------------------------------
	inline STime * STime::get() {
		return sTime;
	}

	//------------------------------------------------------------------------------------------------------------------
	inline double STime::getTime() {
	#if defined (__linux__)
			// Get current time
			timeval currentTime;
			gettimeofday(&currentTime, 0);
			return double(currentTime.tv_sec - mInitTime.tv_sec) + double(currentTime.tv_usec - mInitTime.tv_usec) / 1000000;
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

}        // namespace BOViL

#endif // _BOVIL_CORE_TIME_TIME_H_
