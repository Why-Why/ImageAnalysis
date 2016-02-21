// function.cpp : the implement of function.h.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/function.h"

// Dist Function.
inline double distE(const POS &a,const POS &b) {
	double dx=a.x-b.x,dy=a.y-b.y;
	return sqrt(dx*dx+dy*dy);
}

int dist4(const POS &a,const POS &b) {
	return abs(a.x-b.x)+abs(a.y-b.y);
}

int dist8(const POS &a,const POS &b) {
	return max(abs(a.x-b.x),abs(a.y-a.y));
}

// Distance transform function.
// save the result,the function the judge a color 1 or 0,the dist function.
int dist_Transform(const IMAGE &image,int *res,bool (*judge) (const COLOR),int (*dist) (const POS &,const POS &)) {
	const COLOR *buf=image.getBuf();
	if(NULL==buf) return NO_IMAGE_ERROR;

	const int AL[4][2]={{-1,-1},{-1,0},{-1,1},{0,-1}};
	const int BR[4][2]={{0,1},{1,-1},{1,0},{1,1}};

	int cou=0;
	SIZE size=image.getSize();

	// Step 1, init.
	for(int i=0;i<size.height;++i)
		for(int j=0;j<size.width;++j) {
			if(judge(buf[cou])) res[cou]=0;
			else res[cou]=INF;
			++cou;
		}

	// Step 2, bottom-right to top-left.
	for(int i=size.height-1;i>=0;--i)
		for(int j=size.width-1;j>=0;--j) {
			--cou;
			for(int k=0;k<4;++k)
				if(i+BR[k][0]<size.height && j+BR[k][1]<size.width && j+BR[k][1]>=0)
					res[cou]=min(res[cou], \
						res[cou+BR[k][0]*size.width+BR[k][1]] + \
						dist(POS(i,j),POS(i+BR[k][0],j+BR[k][1])));
		}

	// Step 3, top-left to bottom-right.
	for(int i=0;i<size.height;++i)
		for(int j=0;j<size.width;++j) {
			for(int k=0;k<4;++k)
				if(i+AL[k][0]>=0 && j+AL[k][1]<size.width && j+AL[k][1]>=0)
					res[cou]=min(res[cou], \
						res[cou+AL[k][0]*size.width+AL[k][1]] + \
						dist(POS(i,j),POS(i+AL[k][0],j+AL[k][1])));
			++cou;
		}

	return NO_ERROR;
}

int dist_Transform(const IMAGE &image,double *res,bool (*judge) (const COLOR),double (*dist) (const POS &,const POS &)) {
	const COLOR *buf=image.getBuf();
	if(NULL==buf) return NO_IMAGE_ERROR;

	const int AL[4][2]={{-1,-1},{-1,0},{-1,1},{0,-1}};
	const int BR[4][2]={{0,1},{1,-1},{1,0},{1,1}};

	int cou=0;
	SIZE size=image.getSize();

	// Step 1, init.
	for(int i=0;i<size.height;++i)
		for(int j=0;j<size.width;++j) {
			if(judge(buf[cou])) res[cou]=0;
			else res[cou]=INF;
			++cou;
		}

	// Step 2, bottom-right to top-left.
	for(int i=size.height-1;i>=0;--i)
		for(int j=size.width-1;j>=0;--j) {
			--cou;
			for(int k=0;k<4;++k)
				if(i+BR[k][0]<size.height && j+BR[k][1]<size.width && j+BR[k][1]>=0)
					res[cou]=min(res[cou], \
						res[cou+BR[k][0]*size.width+BR[k][1]] + \
						dist(POS(i,j),POS(i+BR[k][0],j+BR[k][1])));
		}

	// Step 3, top-left to bottom-right.
	for(int i=0;i<size.height;++i)
		for(int j=0;j<size.width;++j) {
			for(int k=0;k<4;++k)
				if(i+AL[k][0]>=0 && j+AL[k][1]<size.width && j+AL[k][1]>=0)
					res[cou]=min(res[cou], \
						res[cou+AL[k][0]*size.width+AL[k][1]] + \
						dist(POS(i,j),POS(i+AL[k][0],j+AL[k][1])));
			++cou;
		}

	return NO_ERROR;
}
