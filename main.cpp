#include <iostream>
#include <cstdio>
#include "./Base/include/config.h"
#include "./Base/include/function.h"

#include <cstdlib>
#include <ctime>

using namespace std;

const int len=50;

int cou[len];

int chu(double x) {
	int ret=(int)(x+0.5)+len/2;
	if(ret>=len) ret=0;
	if(ret<0) ret=0;
	return ret;
}

void show(int x) {
	while(x--) putchar('*');
	puts("");
}

int main() {
	srand(time(0));

	double a,b;

	for(int i=0;i<10000;++i) {
		rand_BoxMuller(0,100,a,b);
		++cou[chu(a)];
		++cou[chu(b)];
	}

	for(int i=1;i<len;++i) show(cou[i]);

	return 0;
}
