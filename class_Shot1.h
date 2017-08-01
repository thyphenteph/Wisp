#pragma once

class Shot1 :public Shot {
public:
	double speeddef = 40;
	double damagedef = 5;
	double sizedef = 10;

	Hitbox hitbox;


	void setdef() {
		randomness = 3;
		dir = RandRange(-randomness, randomness);
		speed = speeddef + RandRange(-10, 10);
		damage = damagedef;
		size = sizedef;
		hue = shot1hue;
	}

	void setvel() {
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
		else {//âÊñ äO
			delflag = 1;
		}

		if (delflag == 1) {//è¡ãé
			vanishcount++;
		}
	}
	void reset() {
		speed = 40;
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
				PlaySoundMem(se_shot1hit, DX_PLAYTYPE_BACK);
			}
			return 1;
		}
		else {
			return 0;
		}
	}
};

std::vector<Shot1> shot1;
Shot1 dummy1;
int shot1_del = 0;