#pragma once

class Me {
public:
	double size = 20;
	double vel[2] = { 0, 0 };
	double veldir = 0;
	double posstart[2] = { FRAME_LEFT + 100, (SCREEN_Y - FRAME_DOWN) / 2 };
	double pos[2] = { FRAME_LEFT + 100, (SCREEN_Y - FRAME_DOWN) / 2 };
	double history[2][60];
	double hpmax = 100;
	double hp = hpmax;
	int motion = 0;
	int hitstop = 0;

	int maxlevel = 4;
	int maxexp[4] = { 800, 1000, 1500, 1800 };
	int lvmaxflag = 0;
	int exp = 0;
	int level = 1;
	int shotlevel = 1;



	int count = 0;
	int frame = 0;

	void setvel() {
		if (vel[0] >= 0) {
			veldir = asin(vel[1] / pow(vel[0] * vel[0] + vel[1] * vel[1], 0.5));
		}
		else {
			veldir = PI - asin(vel[1] / pow(vel[0] * vel[0] + vel[1] * vel[1], 0.5));
		}

		if (keystate[KEY_INPUT_UP] == 0 && keystate[KEY_INPUT_DOWN] == 0
			&& keystate[KEY_INPUT_RIGHT] == 0 && keystate[KEY_INPUT_LEFT] == 0) {//ì¸óÕÇ»Çµ
			vel[0] *= 0.93;
			vel[1] *= 0.93;
		}
		else {
			vel[0] *= 0.98;
			vel[1] *= 0.98;
		}
	}
	void setpos() {
		if (hitstop == 0) {
			pos[0] += vel[0];
			pos[1] += vel[1];
		}
	}
	void sethistory() {
		if (count == 0) {
			for (int i = 0; i < 2; i++) {
				for (int j = 60 - 1; j >= 0; j--) {
					history[i][j] = pos[i];
				}
			}
		}
		else {
			if (hitstop == 0) {
				for (int i = 0; i < 2; i++) {
					for (int j = 60 - 1; j > 0; j--) {
						history[i][j] = history[i][j - 1];
					}
					history[i][0] = pos[i];
				}
			}
		}
	}
	void update(int countdown) {
		if (hitstop == 0) {
			count++;
		}
		else {
			hitstop--;
		}
		//expèàóù
		if (shotlevel == 1) {
			if (countdown != 0) {
				exp = 0;
			}
			if (level < maxlevel) {
				exp++;
				lvmaxflag = 0;
				if (exp >= maxexp[level - 1]) {
					exp %= maxexp[level - 1];
					level++;
				}
			}
			else {
				if (exp < maxexp[level - 1]) {
					//exp++;
					exp = maxexp[level - 1];
					lvmaxflag = 0;
				}
				else {
					exp = maxexp[level - 1];
					//lvmaxflag = 1;
				}
			}
		}
		else {
			if (exp > 0) {
				exp--;
			}
			else {
				shotlevel = 1;
			}
		}
	}

	void reset() {
		vel[0] = 0;
		vel[1] = 0;
		pos[0] = posstart[0];
		pos[1] = posstart[1];
		hp = hpmax;
		motion = 0;
		frame = 0;
		hitstop = 0;

		exp = 0;
		level = 1;
		shotlevel = 1;

		for (int i = 0; i < 2; i++) {
			for (int j = 60 - 1; j >= 0; j--) {
				history[i][j] = pos[i];
			}
		}
	}
};
Me me;
