#pragma once

class Shot2 :public Shot {
public:
	double targetdir = 0;
	double dirfix = 3;
	double speeddef = 10;
	double damagedef = 8;
	double sizedef = 13;

	Hitbox hitbox;


	void setdef() {
		randomness = 25;
		dir = RandRange(-randomness, randomness);
		speed = speeddef;
		damage = damagedef;
		size = sizedef;
		hue = shot1hue + hueperlevel;
	}

	void setdir(double targetpos[]) {
		targetdir = 45 / PI * acos((targetpos[0] - pos[0]) / pow(pow(targetpos[0] - pos[0], 2) + pow(targetpos[1] - pos[1], 2), 0.5));

		if (count >= 10 && targetpos[0] >= pos[0]) {
			if (pos[1] < targetpos[1]) {
				if (dir > targetdir) {
					dir -= dirfix;
				}
				else if (dir < targetdir) {
					dir += dirfix;
				}
			}
			else {
				if (dir > -targetdir) {
					dir -= dirfix;
				}
				else if (dir < -targetdir) {
					dir += dirfix;
				}
			}
		}
	}
	void setvel() {
		speed += 1;
		vel[0] = speed * cos(deg2rad(dir));
		vel[1] = speed * sin(deg2rad(dir));
	}
	void setpos(double pos0[]) {
		if (count == 0) {
			pos[0] = pos0[0];
			pos[1] = pos0[1];
		}
		else {
			pos[0] += vel[0];
			pos[1] += vel[1];
		}
	}
	void update() {
		if (IN_SCREEN) {
			count++;
		}
		else {//‰æ–ÊŠO
			delflag = 1;
		}

		if (delflag == 1) {//Á‹Ž
			vanishcount++;
		}
	}
	void reset() {
		speed = speeddef;
		delflag = 0;
		count = 0;
		vanishcount = 0;
	}
	int hitenemy(Enemy a) {
		double hitdist;
		if (a.type == ene_shield) {
			hitdist = size * shieldsize + a.size;
		}
		else {
			hitdist = size + a.size;
		}
		if (getdist(pos, a.pos) <= hitdist) {
			delflag = 1;
			if (vanishcount == 0) {
				PlaySoundMem(se_shot2hit, DX_PLAYTYPE_BACK);
			}
			return 1;
		}
		else {
			return 0;
		}
	}
};

std::vector<Shot2> shot2;
Shot2 dummy2;
int shot2_del = 0;

