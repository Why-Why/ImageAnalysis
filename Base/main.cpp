#include <iostream>
#include <cstdio>
#include "./include/config.h"
#include "./include/function.h"

using namespace std;

int num[10000];

bool judge(const COLOR a) {
	if(a.color) return 1;
	return 0;
}

int main() {
	IMAGE a;

	a.test();
	dist_Transform(a,num,judge,dist4);

	int cou=0;

	for(int i=0;i<a.getSize().height;++i,cout<<endl)
		for(int j=0;j<a.getSize().width;++j)
			cout<<num[cou++]<<' ';

	return 0;
}
