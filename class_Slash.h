#pragma once

class Slash {
public:
	double angle = -150;
	double offset = 10;
	double bodysize = 3;
	double pos[3][2];
	double history[2][2][15];
	double hitpos[2];
	double damage = 50;
	double hitstop = 10.0;
	double defsize = 3.5;
	double size;
	int hue = 160;

	int delflag = 0;
	int canhit[enemiesmax] = { 0 };
	int count = 0;
	int vanishcount = 0;

	Hitbox hitbox;

	void setpos() {
		pos[0][0] = offset + bodysize * 3 * cos(deg2rad(angle));//根本
		pos[0][1] = bodysize * 3 * sin(deg2rad(angle));
		pos[1][0] = offset + bodysize * 10 * cos(deg2rad(angle));//先端
		pos[1][1] = bodysize * 10 * sin(deg2rad(angle));
		pos[2][0] = offset + bodysize * 5 * cos(deg2rad(angle + 20));//角
		pos[2][1] = bodysize * 5 * sin(deg2rad(angle + 20));
	}
	void sethistory(Me me) {
		if (count == 0) {
			for (int k = 0; k < 2; k++) {
				for (int i = 0; i < 2; i++) {//x,y
					for (int j = 15 - 1; j >= 0; j--) {//時間
						history[k][i][j] = me.pos[i] + pos[k][i];//根本：0, 先端：1
					}
				}
			}
		}
		else {
			for (int k = 0; k < 2; k++) {
				for (int i = 0; i < 2; i++) {
					for (int j = 15 - 1; j > 0; j--) {
						history[k][i][j] = history[k][i][j - 1];
					}
					history[k][i][0] = me.pos[i] + pos[k][i];
				}
			}
		}
	}
	void update() {
		count++;
		size = defsize * bodysize;
		if (delflag == 1) {//消去
			vanishcount++;
		}
	}
	void reset() {
		angle = -150;
		bodysize = 3;
		delflag = 0;
		count = 0;
		vanishcount = 0;
	}
	int hitenemy(Enemy a) {
		for (int i = 0; i < 3; i++) {
			if (getdist(hitpos, a.pos) <= size + a.size) {
				delflag = 1;
				return 1;
			}
			else {
				return 0;
			}
		}
	}
	int hitshot(Shotenemy1 shot) {
		if (getdist(hitpos, shot.pos) <= size + shot.size) {
			delflag = 1;
			if (vanishcount == 0) {
				PlaySoundMem(se_shot1hit, DX_PLAYTYPE_BACK);
			}
			return 1;
		}
		else {
			return 0;
		}
	}

};

Slash slash;