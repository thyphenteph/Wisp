#pragma once

class Enemy {
public:
	int type = 0;
	double dir;
	double targetdir;
	double speed;
	double vel[2];
	double pos[2];
	double pos0[2];
	double postmp[2];
	double history[10][2];
	double size = 20;
	double shieldsize = 40;
	int hpmax = 100;
	int hp = hpmax;
	int exp = 50;
	int gauge;
	int summonframe;

	int hitstop = 0;

	int exist = 0;

	bool invincible = FALSE;

	int count = 0;
	int vanishcount = 0;

	double vanishend = 40.0;

	void setdir(double targetpos[], double dirfix) {
		targetdir = 45 / PI * acos((targetpos[0] - pos[0]) / pow(pow(targetpos[0] - pos[0], 2) + pow(targetpos[1] - pos[1], 2), 0.5));

		if (count >= 10 && targetpos[0] <= pos[0]) {

			if (pos[1] < targetpos[1]) {
				if (dir > targetdir) {
					dir -= dirfix;
				}
				else if (dir < targetdir) {
					dir += dirfix;
				}
			}
			else {
				if (dir > 360 - targetdir) {
					dir -= dirfix;
				}
				else if (dir < 360 - targetdir) {
					dir += dirfix;
				}
			}
		}
	}
	void setvel() {
		vel[0] = 5 * cos(deg2rad(count*1.5)) - 0.5;
		vel[1] = 5 * sin(deg2rad(count * 2));
	}
	void setpos(double possummon[]) {
		if (count == 0) {
			pos[0] = pos0[0] = possummon[0];
			pos[1] = pos0[1] = possummon[1];
			for (int i = 0; i < 10; i++) {
				history[i][0] = pos0[0];
				history[i][1] = pos0[1];
			}
		}
		else {
			if (vanishcount == 0) {
				pos[0] += vel[0];
				pos[1] += vel[1];
			}
			if (hitstop == 0) {
				for (int i = 10 - 1; i > 0; i--) {
					history[i][0] = history[i - 1][0];
					history[i][1] = history[i - 1][1];
				}
				history[0][0] = pos[0];
				history[0][1] = pos[1];
			}
		}
	}
	void update() {
		if (hp > 0) {
			if (hitstop == 0) {
				count++;
				postmp[0] = pos[0];
				postmp[1] = pos[1];
			}
			else {
				hitstop--;
				//‚Õ‚é‚Õ‚é‚³‚¹‚é
				pos[0] = postmp[0];
				pos[1] = postmp[1];
				if (hitstop > 1) {
					pos[0] += RandRange(-5, 5);
					pos[1] += RandRange(-5, 5);
				}
			}
		}
		else {
			if (hitstop == 0) {
				vanishcount++;
			}
			else {
				hitstop--;
				//‚Õ‚é‚Õ‚é‚³‚¹‚é
				pos[0] = postmp[0];
				pos[1] = postmp[1];
				if (hitstop > 1) {
					pos[0] += RandRange(-5, 5);
					pos[1] += RandRange(-5, 5);
				}
			}
		}
	}
	void reset() {
		vel[0] = 0;
		vel[1] = 0;
		hpmax = ene_hpmax[type];
		hp = hpmax;
		size = ene_size[type];
#if DEBUG
		if (type == -1) {
			size = 20;
		}
#endif
		hitstop = 0;
		count = 0;
		vanishcount = 0;
	}
};

Enemy enemies[enemiesmax];

void enemydef() {
	ene_debugsize = 20;
	ene_size[ene_common] = 18;
	ene_size[ene_escape] = 15;
	ene_size[ene_rush] = 18;
	ene_size[ene_ninja] = 18;
	ene_size[ene_shield] = 21;
	ene_size[ene_boss] = 30;
	ene_size[ene_bossg] = 40;
	ene_size[ene_core] = 30;

	ene_debugcolor = GetColorHSV(0, 0, 255);

	ene_hue[ene_common] = 60;
	ene_hue[ene_escape] = 85;
	ene_hue[ene_rush] = 50;
	ene_hue[ene_ninja] = 0;
	ene_hue[ene_shield] = 0;
	ene_hue[ene_boss] = 0;
	ene_hue[ene_bossg] = 330;
	ene_saturation[ene_common] = 255;
	ene_saturation[ene_escape] = 255;
	ene_saturation[ene_rush] = 255;
	ene_saturation[ene_ninja] = 0;
	ene_saturation[ene_shield] = 0;
	ene_saturation[ene_boss] = 255;
	ene_saturation[ene_bossg] = 255;
	ene_value[ene_common] = 255;
	ene_value[ene_escape] = 255;
	ene_value[ene_rush] = 255;
	ene_value[ene_ninja] = 60;
	ene_value[ene_shield] = 220;
	ene_value[ene_boss] = 255;
	ene_value[ene_bossg] = 255;
	ene_color[ene_common] = GetColorHSV(ene_hue[ene_common], ene_saturation[ene_common], ene_value[ene_common]);
	ene_color[ene_escape] = GetColorHSV(ene_hue[ene_escape], ene_saturation[ene_escape], ene_value[ene_escape]);
	ene_color[ene_rush] = GetColorHSV(ene_hue[ene_rush], ene_saturation[ene_rush], ene_value[ene_rush]);
	ene_color[ene_ninja] = GetColorHSV(ene_hue[ene_ninja], ene_saturation[ene_ninja], ene_value[ene_ninja]);
	ene_color[ene_shield] = GetColorHSV(ene_hue[ene_shield], ene_saturation[ene_shield], ene_value[ene_shield]);
	ene_color[ene_boss] = GetColorHSV(ene_hue[ene_boss], ene_saturation[ene_boss], ene_value[ene_boss]);
	ene_color[ene_bossg] = GetColorHSV(ene_hue[ene_bossg], ene_saturation[ene_bossg], ene_value[ene_bossg]);

	ene_debughpmax = 100;
	ene_hpmax[ene_common] = 50;
	ene_hpmax[ene_escape] = 40;
	ene_hpmax[ene_rush] = 35;
	ene_hpmax[ene_ninja] = 30;
	ene_hpmax[ene_shield] = 60;
	ene_hpmax[ene_boss] = 300;
	ene_hpmax[ene_bossg] = 500;
	ene_hpmax[ene_core] = 200;

	ene_gauge[ene_common] = 150;
	ene_gauge[ene_escape] = 100;
	ene_gauge[ene_rush] = 100;
	ene_gauge[ene_ninja] = 180;
	ene_gauge[ene_shield] = 220;
	ene_gauge[ene_boss] = 500;
	ene_gauge[ene_bossg] = 800;

	ene_summonframe[ene_common] = 25;
	ene_summonframe[ene_escape] = 20;
	ene_summonframe[ene_rush] = 40;
	ene_summonframe[ene_ninja] = 60;
	ene_summonframe[ene_shield] = 100;
	ene_summonframe[ene_boss] = 160;
	ene_summonframe[ene_bossg] = 210;

	ene_exp[ene_common] = 250;
	ene_exp[ene_escape] = 120;
	ene_exp[ene_rush] = 30;
	ene_exp[ene_ninja] = 0;
	ene_exp[ene_shield] = 300;
	ene_exp[ene_boss] = 0;
	ene_exp[ene_bossg] = 0;
}