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

}        // namespace BOViL

#endif // _BOVIL_CORE_TIME_TIME_H_
