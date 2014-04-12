////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Color Cluster Segmentation Stereo Tracking
//
//		Author: Pablo Ram�n Soria (Based on Carmelo's J. Fern�ndez-Ag�era Tortosa (a.k.a. Technik) code)
//		Date: 2013/11/08
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Time and time functions

// Standard headers
#if defined(__linux__)
		#include <sys/time.h>
#elif defined (_WIN32)
		#include <Windows.h>
#endif // _linux

// Engine headers
#include "time.h"
#include <cassert>
// Used namespaces

namespace BOViL
{

	//------------------------------------------------------------------------------------------------------------------
	// Static data definitions
	STime* STime::sTime = 0;

	//------------------------------------------------------------------------------------------------------------------
	// Method implementations

	//------------------------------------------------------------------------------------------------------------------
	void STime::init()
	{
			assert(0 == sTime);
			sTime = new STime();
	}

	//------------------------------------------------------------------------------------------------------------------
	void STime::end()
	{
			if(isInitialized()){
				delete sTime;
				sTime = 0;
			}
			//assert(0 != sTime);
	}

	//------------------------------------------------------------------------------------------------------------------
	void STime::update()
	{
	#if defined (__linux__)
		// Get current time
		timeval currentTime;
		gettimeofday(&currentTime, 0);
		mFrameTime = double( currentTime.tv_sec + currentTime.tv_usec/1000000.0);

	#elif defined (_WIN32)
		// Get current time
		LARGE_INTEGER largeTicks;
		QueryPerformanceCounter(&largeTicks);
		unsigned currTime = largeTicks.LowPart;
		// Convert time difference to seconds
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		mFrameTime =  (double(currTime)/double(frequency.LowPart));
	#endif 
	}

	//------------------------------------------------------------------------------------------------------------------
	STime::STime():
			mFrameTime(0.f)
	{
	#if defined (__linux__)
			// Get current time
			timeval currentTime;
			gettimeofday(&currentTime, 0);
			mLastTime = double( currentTime.tv_sec + currentTime.tv_usec/1000000.0);
	#elif defined (WIN32)
			// Get initial time
			LARGE_INTEGER largeTicks;
			QueryPerformanceCounter(&largeTicks);
	#endif
	}
	
	//----------------------------------------------------------------------------------------------
	bool STime::isInitialized(){
		return 0 == sTime ? 0 : 1;
	}

}        // namespace vision
