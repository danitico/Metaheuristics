#include "Timer.h"

Timer::Timer(void) {
  getrusage( RUSAGE_SELF, &res );
  virtual_time = (double) res.ru_utime.tv_sec +
    (double) res.ru_stime.tv_sec +
    (double) res.ru_utime.tv_usec * 1.0E-6 +
    (double) res.ru_stime.tv_usec * 1.0E-6;

  gettimeofday( &tp, NULL );
  real_time =    (double) tp.tv_sec + (double) tp.tv_usec * 1.0E-6;
}

double Timer::elapsed_time(const TYPE& type) {
  if (type == REAL) {
    gettimeofday( &tp, NULL );
    return( (double) tp.tv_sec + (double) tp.tv_usec * 1.0E-6 - real_time );
  }
  else {
    getrusage( RUSAGE_SELF, &res );
    return( (double) res.ru_utime.tv_sec +
	    (double) res.ru_stime.tv_sec +
	    (double) res.ru_utime.tv_usec * 1.0E-6 +
	    (double) res.ru_stime.tv_usec * 1.0E-6
	    - virtual_time );
  }
}

void Timer::reset(){
  getrusage( RUSAGE_SELF, &res );
  virtual_time = (double) res.ru_utime.tv_sec +
    (double) res.ru_stime.tv_sec +
    (double) res.ru_utime.tv_usec * 1.0E-6 +
    (double) res.ru_stime.tv_usec * 1.0E-6;

  gettimeofday( &tp, NULL );
  real_time =    (double) tp.tv_sec + (double) tp.tv_usec * 1.0E-6;
}
