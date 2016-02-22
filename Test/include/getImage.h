// getImage.h : Get the special image, noisy image.

#ifndef GETIMAGE_H
#define GETIMAGE_H

#include "../../Base/include/config.h"
#include "../../Base/include/function.h"

// Get additive and Gaussian gray noise.
// Page 21 for book, algorithm 2.3.
// Gray is in range [0,255].
int get_addGaus_Noise(const SIZE &,double,int *);

#endif
