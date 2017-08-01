#pragma once

class Mouseicon {
public:
	const int length = 20;
	double history[20][2];
	
	void sethistory(double pos[2], int count) {
		if (count == 1) {
			for (int i = 0; i < length; i++) {
				history[i][0] = pos[0];
				history[i][1] = pos[1];
			}
		}
		else {
			for (int i = length - 1; i > 0; i--) {
				history[i][0] = history[i - 1][0];
				history[i][1] = history[i - 1][1];
			}
			history[0][0] = pos[0];
			history[0][1] = pos[1];
		}
	}
};

Mouseicon mouseicon;