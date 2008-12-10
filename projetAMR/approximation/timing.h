/* $Id: timing.h 1254 2007-02-19 17:52:46Z lbreuil $ */
/* mostly borrowed from Timing.c stuff in padico */
#ifndef TIMING_H
#define TIMING_H

#include <stdint.h>
#include <sys/types.h>
#include <sys/time.h>

/* Most compilers don't set __i586__ as they should do.
 * We assert that __i386__ ==> __i586__
 * How to fix?- maybe it could autoconf'ed
 */
#if defined(__i386__) || defined(__pentium__) || defined(__pentiumpro__) || defined(__i586__) || defined(__i686__) || defined(__k6__) || defined(__k7__) || defined(__x86_64__)
#define USE_PENTIUM_TIMER
#else
#undef USE_PENTIUM_TIMER
#endif
/**
  * class timing
  * Timing stuff for benchmarks
  */

typedef union
{
	uint64_t tick;
	struct
	{
	uint32_t low, high;
	} sub;
	struct timeval timev;
}timing_t;

class timing
{
public:
	timing ( );
	virtual ~timing ( );

	/** capture the current timer */
	void get_tick (timing_t*);

	/** zero the current timer */
	void fix (timing_t*);

	/** computes a time interval- result in ticks (=cpu cycle with Pentium timing, =microseconds else) */
	long long diff_tick(timing_t*, timing_t*);

	/** computes a time interval in microseconds */
	double diff_usec(timing_t*, timing_t*);

	/** convert a time interval from ticks into microseconds */
	double tick2usec(long long);
};

extern timing *timer;

#endif // TIMING_H
