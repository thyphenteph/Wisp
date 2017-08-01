#pragma once

#include "sozai.h"

class bgbox {
public:
	double size[2];
	double vel = -size[0] / 40 - size[1] / 40;
	double pos[2];
	unsigned int color;

	int count = 0;

	void setpos() {
		pos[0] += vel;
		//pos[1] += vel[1];
	}
	void update() {
		count++;
		if (count == 1) {
			size[0] = RandRange(20, 150);
			size[1] = RandRange(20, 150);
			vel = -size[0] / 40;
			pos[0] = RandRange(-20, SCREEN_X);
			pos[1] = RandRange(-20, SCREEN_Y);
			color = GetColorHSV(RandRange(0, 360), 255, 255);
		}
		if (pos[0] < -size[0]) {
			for (int i = 0; i < 2; i++) {
				size[i] = RandRange(20, 150);
			}
			vel = -size[0] / 40 - size[1] / 40;
			pos[0] = SCREEN_X + 10;
			pos[1] = RandRange(-20, SCREEN_Y);
			color = GetColorHSV(RandRange(0, 360), 255, 255);
			//count = 0;
		}
	}
};

class bgcircle {
public:
	double radius = 1;
	double vel = -0.5;
	double pos[2];
	unsigned int color;
	int view = 1;

	int count = 0;

	void setpos() {
		pos[0] += vel;
	}
	void update() {
		count++;
		if (count == 1) {
			pos[0] = RandRange(0, SCREEN_X);
			pos[1] = RandRange(0, SCREEN_Y);
			color = GetColorHSV(60 + 140 * (rand() % 2), RandRange(0, 255), RandRange(150, 255));
			radius = 1;
		}
		if (pos[0] < 0) {
			pos[0] = SCREEN_X;
			pos[1] = RandRange(0, SCREEN_Y);
			color = GetColorHSV(60 + 140 * (rand() % 2), RandRange(0, 255), RandRange(150, 255));
			//count = 0;
		}

		if (RandRange(0, 100) == 50) {
			view = 0;
		}
		else {
			view = 1;
		}
	}
};

const int numbgbox = 10;
bgbox bg[numbgbox];
const int numstar = 25;
bgcircle bgstar[numstar];