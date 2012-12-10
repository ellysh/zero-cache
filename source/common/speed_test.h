#ifndef SPEED_TEST_H
#define SPEED_TEST_H

#include <iostream>

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

#ifndef STREAM
#define STREAM cout
#endif

#define PRE_TIME_MEASURE(function) \
    STREAM << function; \
    struct timeval start, end; \
    long mtime, seconds, useconds; \
    gettimeofday(&start, NULL);

#define POST_TIME_MEASURE \
    gettimeofday(&end, NULL); \
    seconds  = end.tv_sec  - start.tv_sec; \
    useconds = end.tv_usec - start.tv_usec; \
    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5; \
    STREAM << " - " << mtime << " milliseconds" << endl;

#endif