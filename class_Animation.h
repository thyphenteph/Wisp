#pragma once

class Animation {
public:
	int handle[600];//10sまで
	double pos[2];
	double ratio;//倍率
	int sizex;//実際のサイズ
	int sizey;
	double angle;

	int count = 600;
	int length = 0;

	void sethandle(int handle0[], int length0) {
		length = length0;
		for (int i = 0; i < length; i++) {
			handle[i] = handle0[i];
		}
		count = 600;
	}
	void setpos(double posx0, double posy0) {
		pos[0] = posx0;
		pos[1] = posy0;
	}
	void setsize(int sizex0) {//横のサイズから倍率決定
		GetGraphSize(handle[0], &sizex, &sizey);
		ratio = (double)sizex0 / (double)sizex;
	}
	void setangle(double angle0) {//引数の時点ではdeg
		angle = deg2rad(angle0);
	}
	void start() {
		count = 0;
	}
	void end() {
		count = 600;
	}

	void draw() {//常時実行
		if (count < length) {
			DrawRotaGraph(pos[0], pos[1], ratio, angle, handle[count], TRUE, FALSE);
			count++;
		}
		else {
			count = 600;
		}
	}
};

Animation graphlvupuse[3];
Animation slashstart[4];
Animation slashhit[enemiesmax];
Animation shot1break[shot1_maxmem]; 
Animation shot1breakcore[shot1_maxmem];
Animation shot1hit[shot1_maxmem];
Animation shot2hit[shot2_maxmem];
Animation shot4hit[shot1_maxmem][enemiesmax];
Animation breakshot_around;
Animation breakshot_charge[3];
Animation breakshot_laser_p;
Animation breakshot_back[3];
Animation shotenemy1break[shotenemy1_maxmem];
Animation shotenemy1breakcore[shotenemy1_maxmem];
Animation enemydeath[enemiesmax];
Animation left[enemiesmax];


class AnimeRect :public Animation {
public:
	double ratio[2];

	virtual void setsize(int sizex0, int sizey0) {
		GetGraphSize(handle[0], &sizex, &sizey);
		ratio[0] = (double)sizex0 / (double)sizex;
		ratio[1] = (double)sizey0 / (double)sizey;

	}

	virtual void draw() {
		if (count <= length) {
			DrawRotaGraph3(pos[0], pos[1], sizex / 2, sizey / 2, ratio[0], ratio[1], angle, handle[count], TRUE, FALSE);
			count++;
		}
		else {
			count = 600;
		}
	}
};

AnimeRect breakshot_laser_s[3];


class AutoFlash :public Animation {
public:
	unsigned int color;
	double alpha;

	void set(int h, int s, int v, int length0, double alpha0) {
		color = GetColorHSV(h, s, v);
		length = length0;
		alpha = alpha0;
	}

	virtual void draw() {
		if (count <= length) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha * (double)(length - count) / length);
			DrawBox(0, 0, SCREEN_X, SCREEN_Y, color, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			count++;
		}
		else {
			count = 600;
		}
	}
};

AutoFlash autoflash;