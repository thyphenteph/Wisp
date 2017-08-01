#pragma once

class Shot4 :public Shot {
public:
	double targetdir = 0;
	double dirfix = 4;
	double speeddef = 10;
	double damagedef = 3;
	double sizedef = 10;

	int laserframe = 60;
	double laserpos[2];

	int changed = 0;
	int canhit[enemiesmax];

	Hitbox hitbox;


	void setdef() {
		randomness = 180;
		//dir = RandRange(-randomness, randomness);
		speed = speeddef;
		damage = damagedef;
		size = sizedef;
		hue = shot1hue + hueperlevel * 3;
		for (int i = 0; i < enemiesmax; i++) {
			canhit[i] = 1;
		}
	}
	
	void changetolaser(double targetpos[]) {
		if (targetpos[1] >= pos[1]) {
			targetdir = 45 / PI * acos((targetpos[0] - pos[0]) / pow(pow(targetpos[0] - pos[0], 2) + pow(targetpos[1] - pos[1], 2), 0.5));
		}
		else {
			targetdir = -45 / PI * acos((targetpos[0] - pos[0]) / pow(pow(targetpos[0] - pos[0], 2) + pow(targetpos[1] - pos[1], 2), 0.5));
		}
		dir = targetdir;
		//speed = 1500;
		damage = 6;
		size = sizedef - 3;
		laserpos[0] = pos[0] + 2500 * cos(deg2rad(targetdir));
		laserpos[1] = pos[1] + 2500 * sin(deg2rad(targetdir));
		changed = TRUE;
	}
	void setvel() {
		if (count < laserframe) {
			speed *= 0.95;
		}
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
		if (count <= laserframe) {
			count++;
		}
		else {//ƒŒ[ƒU[”­ŽËŒã
			delflag = 1;
		}

		if (delflag == 1) {//Á‹Ž
			vanishcount++;
		}
	}
	void reset() {
		speed = speeddef;
		changed = 0;
		delflag = 0;
		count = 0;
		vanishcount = 0;
	}
	int hitenemy(Enemy a) {
		if (count <= laserframe) {
			if (getdist(pos, a.pos) <= size + a.size) {
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
		else {
			if (distpointtoline(a.pos, laserpos, (laserpos[1] - pos[1]) / (laserpos[0] - pos[0])) <= size + a.size &&
				((a.pos[0] > laserpos[0] && a.pos[0] < pos[0]) || (a.pos[0] < laserpos[0] && a.pos[0] > pos[0]))) {
				delflag = 1;
				return 1;
			}
			else {
				return 0;
			}
		}
	}
};

class Shot4hit {
public:
	int exist = 0;
	double speeddef = 8;
	double speed = speeddef;
	double vel[2];
	double dir = 0;
	double pos[2];
	double radiusdef = 5;
	double radius = radiusdef;
	double alphadef = 250;
	double alpha = alphadef;

	int count = 0;

	void setvel() {
		if (count == 0) {
			dir = RandRange(-180, 180);
		}
		else {
			vel[0] = speed * cos(deg2rad(dir));
			vel[1] = speed * sin(deg2rad(dir));
			speed *= 0.9;
		}
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
		count++;
		if (count > 0) {
			radius *= 0.93;
			if (count > 6) {
				alpha *= 0.93;
			}
		}
	}
	void reset() {
		count = 0;
		speed = speeddef + RandRange(-5, 5);
		radius = radiusdef;
		alpha = alphadef;
	}
};

std::vector<Shot4> shot4;
Shot4 dummy4;
int shot4_del = 0;

//const int shot4hitnum = 8;
//Shot4hit shot4hit[enemiesmax][shot4hitnum];
