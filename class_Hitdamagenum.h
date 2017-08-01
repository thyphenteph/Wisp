#pragma once

class Hitdamagenum {
public:
	int exist = 0;
	double pos[2];
	double vel = -0.75;
	int damage;
	int alpha = 255;

	int count = 0;


	void setdamage(int damagedef) {
		damage = damagedef * ((1000 + RandRange(-50, 50)) / 100.0);
	}
	void setpos(double pos0[]) {
		if (count == 0) {
			pos[0] = pos0[0] - 15 + RandRange(-30.0, 30.0);
			pos[1] = pos0[1] - 10 + RandRange(-10.0, 10.0);
		}
		else {
			pos[1] += vel;
		}
	}
	void update() {
		count++;
		if (count >= 10) {
			alpha -= 20;
		}
	}
	void reset() {
		count = 0;
		alpha = 255;
	}

};

Hitdamagenum hitdamagenum[50][enemiesmax];
int hitdamageid = 0;