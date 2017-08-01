#pragma once

class Shotenemy1 :public Shot {
public:
	int type = -1;
	int type_2 = -1;
	double speeddef = 40;
	double damagedef = 5;
	double sizedef = 6;
	double targetdir;
	int saturation;
	int value;
	int hitstop;
	bool intercepted = FALSE;
	int intercepttime = 0;

	void setdef(Me me, Enemy enemy) {
		pos[0] = enemy.pos[0];
		pos[1] = enemy.pos[1];
		damage = damagedef;
		hitstop = 3;
		size = sizedef;
		if (me.pos[1] >= pos[1]) {
			targetdir = 45 / PI * acos((me.pos[0] - pos[0]) / pow(pow(me.pos[0] - pos[0], 2) + pow(me.pos[1] - pos[1], 2), 0.5));
		}
		else {
			targetdir = -45 / PI * acos((me.pos[0] - pos[0]) / pow(pow(me.pos[0] - pos[0], 2) + pow(me.pos[1] - pos[1], 2), 0.5));
		}
		saturation = 255;
		value = 255;
	}

	void setvel() {
		vel[0] = speed * cos(deg2rad(dir));
		vel[1] = speed * sin(deg2rad(dir));
	}
	void setpos() {
		pos[0] += vel[0];
		pos[1] += vel[1];
	}
	void update() {
		if (IN_SCREEN) {
			count++;
		}
		else {//âÊñ äO
			delflag = 1;
			vanishcount = 15;
		}

		if (delflag == 1) {//è¡ãé
			vanishcount++;
			if (intercepted) {
				intercepttime++;
			}
		}
	}
	void reset() {
		speed = 40;
		delflag = 0;
		count = 0;
		vanishcount = 0;
		intercepted = FALSE;
		intercepttime = 0;
	}
	int hitme(Me me) {
		if (getdist(pos, me.pos) <= size + me.size) {
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

std::vector<Shotenemy1> shotenemy1;
Shotenemy1 dummyenemy1;
int shotenemy1_del = 0;