#pragma once

class Shot {
public:
	double dir = 0;
	double speed;
	int randomness = 3;
	double vel[2] = { 0, 0 };
	double pos[2];
	double history[2][60];
	double damage = 5;
	double size = 10;
	int hue = 160;

	int delflag = 0;
	int range;
	int count = 0;
	int vanishcount = 0;


	void sethistory() {
		if (count == 0) {
			for (int i = 0; i < 2; i++) {
				for (int j = 60 - 1; j >= 0; j--) {
					history[i][j] = pos[i];
				}
			}
		}
		else {
			for (int i = 0; i < 2; i++) {
				for (int j = 60 - 1; j > 0; j--) {
					history[i][j] = history[i][j - 1];
				}
				history[i][0] = pos[i];
			}
		}
	}
};