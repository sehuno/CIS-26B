#include <stdio.h>

int fun(int x, int y) {
	if (x > y) 
	{
		printf("%d, %d\n", x, y);
		return fun(x - y, y + 5) + y;
	}
	return 0;
}

int main() {
	int result;
	result = fun(70,5);
	printf("%d\n", result);
}