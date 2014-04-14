////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Color Cluster Segmentation Stereo Tracking
//
//		Author: Pablo Ram�n Soria (Based on Carmelo's J. Fern�ndez-Ag�era Tortosa (a.k.a. Technik) code)
//		Date: 2013/11/08
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Time and time functions

// Engine headers
#include "time.h"
#include <cassert>
// Used namespaces

namespace BOViL
{
	//------------------------------------------------------------------------------------------------------------------
	// Static data definition
	//------------------------------------------------------------------------------------------------------------------

	STime* STime::sTime = nullptr;	

	//------------------------------------------------------------------------------------------------------------------
	// Method implementations
	//------------------------------------------------------------------------------------------------------------------
	void STime::init()
	{
		assert(sTime == nullptr);
		sTime = new STime();
	}

	//------------------------------------------------------------------------------------------------------------------
	void STime::end()
	{
		assert(sTime != nullptr);
		delete sTime;
		sTime = nullptr;
	}

	//------------------------------------------------------------------------------------------------------------------
	void STime::update()
	{
	#if defined (__linux__)
		// Get current time
		timeval currentTime;
		gettimeofday(&currentTime, 0);
		mFrameTime = double(currentTime.tv_sec - mLastTime.tv_sec) + double(currentTime.tv_usec - mLastTime.tv_usec)/1000000;
		mLastTime = currentTime;

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
			gettimeofday(&mLastTime, 0);
	#elif defined (WIN32)
			// Get initial time
			LARGE_INTEGER largeTicks;
			QueryPerformanceCounter(&largeTicks);
	#endif
	}
	
}        // namespace vision
