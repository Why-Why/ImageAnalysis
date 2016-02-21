// function.h : Base function about Image process, include math function.

#ifndef FUNCTION_H
#define FUNCTION_H

#include "config.h"

// Base Function.
template <typename T> inline T min(T a,T b) { return a<b ? a : b; }
template <typename T> inline T max(T a,T b) { return a<b ? b : a; }

// Dist Function, get the distance between two pos.
double distE(const POS &,const POS &);		// Euclidean distance.
int dist4(const POS &,const POS &);			// 4 neighbors distance.
int dist8(const POS &,const POS &);			// 8 neighbors distace.

// Distance transform algorithm.
// Page 14 for book, algorithm 2.1.
// Node : I think fig 2.10 is wrong.
int dist_Transform(const IMAGE &, int * , bool (*) (const COLOR) , int (*) (const POS &,const POS &));
int dist_Transform(const IMAGE &, double * , bool (*) (const COLOR) , double (*) (const POS &,const POS &));

// Brightness histogram algorithm.
// Page 17 for book, algorithm 2.2.
// Default the brightness is in [0,255].
int bright_Histogram(const IMAGE &, int *);

// Gaussian random numbers.
// The Box-Muller transform algorithm (https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform)
// Get two Gaussian random numbers.
int rand_BoxMuller(double &,double &);

#endif
