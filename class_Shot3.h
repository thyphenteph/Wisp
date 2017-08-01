#pragma once

class Shot3triangle {
public:
	double pos[3][2];
	double angle;
	double angvel = 8;
	double size = 20;

	int count = 0;


	void setangle(double angle0) {
		if (count == 0) {
			angle = angle0;
		}
		else {
			angle += angvel;
		}
	}
	void setpos(double delay) {
		pos[0][0] = size * cos(deg2rad(angle - delay));
		pos[0][1] = size * sin(deg2rad(angle - delay));
		pos[1][0] = size * cos(deg2rad(angle - delay + 120));
		pos[1][1] = size * sin(deg2rad(angle - delay + 120));
		pos[2][0] = size * cos(deg2rad(angle - delay + 240));
		pos[2][1] = size * sin(deg2rad(angle - delay + 240));
	}
	void update() {
		count++;
	}
};

class Shot3 :public Shot {
public:
	double speeddef = 35;
	double damagedef = 5;
	double sizedef = 13;

	int explosiontime = 20;

	int canhit[enemiesmax];

	Shot3triangle tri;
	Shot3triangle triglow[20];

	Hitbox hitbox;

	void setdef(bool dirchoice) {
		randomness = 0;
		if (dirchoice) {
			dir = 5;
		}
		else {
			dir = -5;
		}
		speed = speeddef;
		damage = damagedef;
		size = sizedef;
		hue = shot1hue + hueperlevel * 2;
		range = 45;
	}

	void setvel() {
		if (count == 0) {
			dir = RandRange(-randomness, randomness);
			//speed += RandRange(-10, 10);
		}
		speed *= 0.95;
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
		if (count == 0) {//çUåÇîªíËon
			for (int j = 0; j < enemiesmax; j++) {
				canhit[j] = 1;
			}
		}

		if (IN_SCREEN && count < range) {//âÊñ ì‡&éıñΩì‡
			count++;
			tri.setangle(0);
			tri.setpos(0);
			tri.update();
			for (int i = 1; i < 20; i++) {
				triglow[i].setangle(0);
				triglow[i].setpos(i * triglow[i].angvel);
				triglow[i].update();
			}
		}
		else {//âÊñ äOoréıñΩêsÇ´ÇΩ
			delflag = 1;
		}

		if (delflag == 1) {//è¡ãé
			vanishcount++;
		}
	}
	void reset() {
		damage = damagedef;
		speed = speeddef;
		size = sizedef;
		delflag = 0;
		count = 0;
		vanishcount = 0;
	}
	void explosion() {
		if (vanishcount < explosiontime) {
			if (vanishcount == 1) {
				size = 25;
				//damage = 18;//çUåÇîªíËon		
			}
			else {
				size += 5;
			}
		}
	}
	int hitenemy(Enemy a) {
		if (getdist(pos, a.pos) <= size + a.size) {
			delflag = 1;
			return 1;
		}
		else {
			return 0;
		}
	}
};

std::vector<Shot3> shot3;
Shot3 dummy3;
int shot3_del = 0;

