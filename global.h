#pragma once

int phase = 0;//タイトル, ゲーム　切り替え

int count = 0;//フレームカウント

int mouse[2];//マウス座標
double mouse_d[2];//マウス座標（double）

int motionframe[10] =
{   0, 50,//未使用, slash
	5, 8,//shot1, shot2
	20, 4,//shot3, shot4
	150, 0,//ブレイクショット, 未使用
	0, 0
};

const int waitid = 0;
const int slashid = 1;
const int shot1id = 2;
const int shot2id = 3;
const int shot3id = 4;
const int shot4id = 5;
const int breakshotid = 6;

const int shot1hue = 160;

const int hueperlevel = 50;

int wisphp_ul[2] = { 140, SCREEN_Y - 64 };
int wisphp_dr[2] = { wisphp_ul[0] + 400, wisphp_ul[1] + 20 };
int wisplv_ul[2] = { wisphp_ul[0], SCREEN_Y - 34 };
int wisplv_dr[2] = { wisplv_ul[0] + 350, wisplv_ul[1] + 20 };

int corehp_ul[2] = { 780, SCREEN_Y - 64 };
int corehp_dr[2] = { corehp_ul[0] + 400, corehp_ul[1] + 20 };
int coresm_ul[2] = { corehp_ul[0], SCREEN_Y - 34 };
int coresm_dr[2] = { coresm_ul[0] + 400, coresm_ul[1] + 20 };



//const int enemytype = 10;
const int enemiesmax = 100;

const int shot1_maxmem = 20;
const int shot2_maxmem = 20;
const int shot3_maxmem = 10;
const int shot4_maxmem = 20;

const int shotenemy1_maxmem = 400;

int enemiesnum;

double handicap = 1.0;


int summonid = 1;
int summontype = 0;
double possummon[2] = { 0,0 };
int summonalpha = 0;
int flagsummon = 0;
int summonmouse = 0;

double shieldsize = 3.5;

const int ene_debug = -1;
const int ene_common = 0;
const int ene_escape = 1;
const int ene_rush = 2;
const int ene_ninja = 3;
const int ene_shield = 4;
const int ene_boss = 5;
const int ene_bossg = 6;
const int ene_core = 9;

int ene_debugsize;
int ene_size[10];

unsigned int ene_debugcolor;
int ene_hue[10];
int ene_saturation[10];
int ene_value[10];
int ene_color[10];

int ene_debughpmax;
int ene_hpmax[10];
int ene_gauge[10];
int ene_summonframe[10];
int ene_exp[10];

int flagpause = 0;


class circle {
public:
	double vel[2] = { 0, 0 };
	double vel_dir = 0;
	double pos[2];
	double history[2][60];
	double radius;

	int count = 0;

	void setpos() {
		pos[0] += vel[0];
		pos[1] += vel[1];
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
			for (int i = 0; i < 2; i++) {
				for (int j = 60 - 1; j > 0; j--) {
					history[i][j] = history[i][j - 1];
				}
				history[i][0] = pos[i];
			}
		}
	}
	void update() {
		count++;
	}
};

circle surround[10];
circle glow[20];
circle surround_ene[enemiesmax][10];
