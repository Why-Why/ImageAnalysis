// getImage.cpp : The implement of getImage.h.

#include "../include/getImage.h"

// Get additive and Gaussian noise.
// The size of Noise Image, the sigma, The result buffer(need enough memory before).
int get_addGaus_Noise(const SIZE &size,double sigma,int * res) {
	int len=size.width*size.height;
	double t1,t2;
	int tt1,tt2;

	for(int i=0;i<len-1;i+=2) {
		rand_BoxMuller(0,sigma,t1,t2);
		tt1=min(255,max(0,(int)(t1+0.5)));
		tt2=min(255,max(0,(int)(t2+0.5)));
		res[i]=tt1;
		res[i+1]=tt2;
	}
	if(len&1) {
		rand_BoxMuller(0,sigma,t1,t2);
		tt1=min(255,max(0,(int)(t1+0.5)));
		res[len-1]=tt1;
	}

	return NO_ERROR;
}
