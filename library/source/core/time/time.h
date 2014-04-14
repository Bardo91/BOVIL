////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Color Cluster Segmentation Stereo Tracking
//
//		Author: Pablo Ram�n Soria (Based on Carmelo's J. Fern�ndez-Ag�era Tortosa (a.k.a. Technik) code)
//		Date: 2013/11/08
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Time and time functions

#ifndef _VISUAL_TRACKING_UI_TIME_H_
#define _VISUAL_TRACKING_UI_TIME_H_

#if defined(__linux__)
	#include <sys/time.h>
#elif defined(_WIN32)
	#include <Windows.h>
#endif

namespace BOViL
{
	class STime
	{
			/// \brief this system provides time meassures to game. time is considered constant along a whole frame.
	public:
		// --- Singleton life cycle ---
		static void init();
		static STime* get();        // Returns the singleton instance
		static void end();

	public: // --- Public interface ---
		double frameTime();

	private:
		STime();
		void update();        // Update time system
	private:
		// Singleton instance
		static STime* sTime; // Static data definition
		// last frame duration.
		double mFrameTime;
		// Internal use.
		#if defined(__linux__)
			timeval mLastTime;
		#endif
		#if defined (_WIN32)
			unsigned mLastTime;
		#endif
	};

	//------------------------------------------------------------------------------------------------------------------
	inline double STime::frameTime()
	{
		update();
		return mFrameTime;
	}

	//------------------------------------------------------------------------------------------------------------------
	inline STime * STime::get()
	{
		return sTime;
	}

}        // namespace BOViL

#endif // _VISUAL_TRACKING_UI_TIME_H_
