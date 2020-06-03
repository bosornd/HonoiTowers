#include <stdio.h>
#include <math.h>

void hanoi_move(int from, int to)
{
	printf("move plate from T%d to T%d\n", from, to);
}

void hanoi_tower(int n, int from, int to, int temp)
{
	if (n == 1) hanoi_move(from, to);
	else {
		hanoi_tower(n - 1, from, temp, to);
		hanoi_move(from, to);
		hanoi_tower(n - 1, temp, to, from);
	}
}

int main()
{
	int N = 3, SEQ = pow(2, N) - 1;			// SEQ = 2^N - 1

	printf("Recursive version of hanoi tower!!!\n");
	hanoi_tower(N, 0, 2, 1);		// move from tower 0 to tower 2 using tower 1

	printf("Iterative version of hanoi tower!!!\n");
	for (int m = 1; m <= SEQ; m++) {
		hanoi_move((m & m - 1) % 3, ((m | m - 1) + 1) % 3);
	}

	return 0;
}