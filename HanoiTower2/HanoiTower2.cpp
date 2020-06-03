#include <bangtal.h>

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define N		7
#define SEQ		127			//	2^N - 1 = 127

SceneID scene;
ObjectID plates[N], start;
TimerID timerAnimation;

int tower[3][N];
int top[3] = { 0 };

int count = 0;
int from[SEQ], to[SEQ];

void hanoi_move(int f, int t)
{
	from[count] = f;
	to[count] = t;

	count++;		// next
}

void hanoi_tower(int n, int from, int to, const int temp)
{
	if (n == 1) hanoi_move(from, to);
	else {
		hanoi_tower(n - 1, from, temp, to);
		hanoi_move(from, to);
		hanoi_tower(n - 1, temp, to, from);
	}
}

void stack(int t, int p)
{
	tower[t][top[t]] = p;
	locateObject(plates[p], scene, t * 300 + 149, top[t] * 50 + 200);
	top[t] ++;
}

int unstack(int t)
{
	if (top[t] > 0) {
		top[t] --;
		return tower[t][top[t]];
	}
	else return -1;		// error
}

void keyboardCallback(KeyCode code, KeyState state)
{
	if (state == KeyState::KEYBOARD_PRESSED) {
		if (count < SEQ) {
			stack(to[count], unstack(from[count]));
			count++;		// next
		}
	}
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action)
{
	if (object == start) {
		hideObject(start);

		timerAnimation = createTimer(.1f);
		startTimer(timerAnimation);
	}
}

void timerCallback(TimerID timer)
{
	if (timer == timerAnimation) {
		if (count < SEQ) {
			stack(to[count], unstack(from[count]));
			count++;	// next

			// setup timer for animation loop
			setTimer(timerAnimation, .1f);
			startTimer(timerAnimation);
		}
	}
}

int main()
{
	setKeyboardCallback(keyboardCallback);
	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);

	scene = createScene("하노이 타워", "Images/background.png");

	char path[64];
	for (int i = 0; i < N; i++) {
		sprintf(path, "Images/%d.png", i + 1);
		plates[i] = createObject(path);
		stack(0, i);
		showObject(plates[i]);
	}

	hanoi_tower(N, 0, 1, 2);
	count = 0;		// reset count to animation

	start = createObject("Images/start.png");
	locateObject(start, scene, 590, 100);
	showObject(start);

	startGame(scene);
	return 0;
}