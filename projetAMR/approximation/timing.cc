/* $Id: timing.cc 1254 2007-02-19 17:52:46Z lbreuil $ */
#include "timing.h"
#include <stdio.h>
#include <unistd.h>

#define DPL_TIMING_GET_TICK(t) get_tick(&(t))
#define DPL_TIMING_TICK_DIFF(t1, t2) diff_tick(&(t1), &(t2))

#ifdef USE_PENTIUM_TIMER
#define DPL_TIMING_INTERNAL_GET_TICK(t)  __asm__ volatile("rdtsc" : "=a" ((t).sub.low), "=d" ((t).sub.high))
#define DPL_TIMING_TICK_RAW_DIFF(t1, t2) ((t2).tick - (t1).tick)
static double scale = 0.0; /* scale to convert cpu cycles into microseconds */

#else
#define DPL_TIMING_INTERNAL_GET_TICK(t) gettimeofday(&(t).timev, NULL)
#define DPL_TIMING_TICK_RAW_DIFF(t1, t2) (((t2).timev.tv_sec * 1000000L + (t2).timev.tv_usec) - ((t1).timev.tv_sec * 1000000L + (t1).timev.tv_usec))
#endif /* USE_PENTIUM_TIMER */
static long long timing_resolution;

timing::timing ()
{
	int i;
	/* correction to avoid the cost of the time measure itself */
	timing_resolution = (unsigned long long)1 << 32;
	for(i=0 ; i<10 ; i++)
	{
		timing_t t1, t2;
		long long diff;
		get_tick(&t1);
		get_tick(&t2);
		diff = DPL_TIMING_TICK_RAW_DIFF(t1, t2);
		if(diff < timing_resolution)
			timing_resolution = diff;
	}

#ifdef USE_PENTIUM_TIMER
	/*1 calibrate cpu cycle */

	timing_t t1, t2;
	struct timeval tv1,tv2;
	double diff_usec = 0;

	get_tick(&t1);
	gettimeofday(&tv1,0);
	while(diff_usec < 1000000) /* wait at least 0.1 second, even if usleep() is interrupted */
	{
		usleep(100000);
		get_tick(&t2);
		gettimeofday(&tv2,0);
		diff_usec = ((tv2.tv_sec*1e6 + tv2.tv_usec) - (tv1.tv_sec*1e6 + tv1.tv_usec));
	}
	scale = diff_usec / (double)(DPL_TIMING_TICK_DIFF(t1, t2));
	fprintf(stderr,"Timing: Pentium timing - clock at %G MHz (resolution=%lld cycles, %.2G nanosec).\n", 1/scale, timing_resolution, (timing_resolution*scale)*1000.0);
#else
	fprintf(stderr,"Timing: Use standard timer.\n");
#endif
}

timing::~timing ( ) { }


void
timing::get_tick(timing_t* t)
{
	DPL_TIMING_INTERNAL_GET_TICK(*t);
}

void
timing::fix (timing_t* t)
{
	t->tick += timing_resolution;
}

long long
timing::diff_tick(timing_t* t1, timing_t* t2)
{
	return (DPL_TIMING_TICK_RAW_DIFF(*t1, *t2) - timing_resolution);
}

double
timing::tick2usec(long long t)
{
#ifdef USE_PENTIUM_TIMER
	return (double)(t)*scale;
#else
	return (double)t;
#endif
}

double
timing::diff_usec(timing_t* t1, timing_t* t2)
{
	return (tick2usec(diff_tick(t1, t2)));
}

