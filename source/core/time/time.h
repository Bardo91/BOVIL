////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Color Cluster Segmentation Stereo Tracking
//
//		Author: Pablo Ramón Soria (Based on Carmelo's J. Fernández-Agüera Tortosa (a.k.a. Technik) code)
//		Date: 2013/11/08
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Time and time functions

#ifndef _VISUAL_TRACKING_UI_TIME_H_
#define _VISUAL_TRACKING_UI_TIME_H_

namespace BOViL
{
	class STime
	{
			/// \brief this system provides time meassures to game. time is considered constant along a whole frame.
	public:
			// --- Singleton life cycle ---
			static void init();
			static STime* get();        ///< Returns the singleton instance
			static void end();
			static bool isInitialized();

	public: // --- Public interface ---
			double frameTime();

	private:
			STime();
			void update();        ///< Update time system
	private:
			// Singleton instance
			static STime* sTime;

			// last frame duration.
			double mFrameTime;

			// Internal use.
	#if defined(_linux)
		int mLastTime;
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