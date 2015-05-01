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

#include <iostream>

namespace BOViL {
	class STime {
		// Static interface
	public:
		static STime*	get();
		static void		init();
		static void		end();

	private:
		static	STime*				sTime;

		// Class interface
	public:
		double	getTime();
		void	delay(const unsigned _seconds);
		void	mDelay(const unsigned _millis);

	private:
		STime();
#if defined(__linux__)
		timeval			mInitTime;
#elif defined (_WIN32)
		LARGE_INTEGER	mInitTime;
#endif
	};

}        // namespace BOViL

#endif // _BOVIL_CORE_TIME_TIME_H_
