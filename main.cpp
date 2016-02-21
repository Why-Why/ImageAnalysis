#include <iostream>
#include <cstdio>
#include "./Base/include/config.h"
#include "./Base/include/function.h"

using namespace std;

int num[10000];

bool judge(const COLOR a) {
	if(a.color) return 1;
	return 0;
}

int main() {
	IMAGE a;

	a.readJPG("a.jpg");
	a[9][9].getYColor();

	return 0;
}
