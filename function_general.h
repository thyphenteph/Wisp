#pragma once

char buf[256] = { 0 };//キー
int keystate[256] = { 0 };
//キー入力状態を更新する関数
void keyupdate()
{
	GetHitKeyStateAll(buf);
	for (int i = 0; i < 256; i++)
	{
		if (buf[i] == 1) keystate[i]++;
		else keystate[i] = 0;
	}
}

int mousestate[256] = { 0 };
//マウス入力状態を更新する関数
void mouseupdate() {
	int m = GetMouseInput();
	for (int i = 0; i < 256; i++) {
		if ((m & i) != 0) {
			mousestate[i]++;
		}
		else mousestate[i] = 0;
	}
}

int RandRange(int min, int max) {
	int a;

	a = GetRand(max - min) + min;

	return a;
}

double RandRange(double min, double max){
	double a;

	a = GetRand(max - min) + min;

	return a;
}

unsigned int GetColorHSV(int h, int s, int v) {
	double max = (double)v;
	double min = (double)(max - ((s / 255.0) * max));
	double r, g, b;
	//色相を0～359に
	h = h % 360;
	if (h < 0) {
		h += 360;
	}
	//RGB変換
	if (h < 60) {
		r = max;
		g = (double)((h / 60.0)*(max - min) + min);
		b = min;
	}
	else if (h < 120) {
		r = (double)(((120.0 - h) / 60.0)*(max - min) + min);
		g = max;
		b = min;
	}
	else if (h < 180) {
		r = min;
		g = max;
		b = (double)(((h - 120.0) / 60.0) * (max - min) + min);
	}
	else if (h < 240) {
		r = min;
		g = (double)(((240.0 - h) / 60.0) * (max - min) + min);
		b = max;
	}
	else if (h < 300) {
		r = (double)(((h - 240.0) / 60.0) * (max - min) + min);
		g = min;
		b = max;
	}
	else {
		r = max;
		g = min;
		b = (double)(((360.0 - h) / 60.0) * (max - min) + min);
	}

	//DrawFormatString(0, 0, GetColor(255, 255, 255), "h:%d s:%d v:%d", h, s, v);
	//DrawFormatString(0, 40, GetColor(255, 255, 255), "r:%.0f g:%.0f b:%.0f", r, g, b);

	return GetColor((int)r, (int)g, (int)b);
}

double deg2rad(double deg) {
	double rad = deg * PI / 180;

	return rad;
}

double getdist(double pos1[], double pos2[]) {
	double dist = pow(pow(pos1[0] - pos2[0], 2) + pow(pos1[1] - pos2[1], 2), 0.5);

	return dist;
}

double distpointtoline(double point[], double linepos[], double lineslope) {
	double dist;
	double intercept = linepos[1] - lineslope * linepos[0];

	//lineslope * linepos[0] - 1 * linepos[1] + intercept = 0
	dist = fabs(lineslope * point[0] - 1 * point[1] + intercept) / pow(pow(lineslope, 2) + pow(-1, 2), 0.5);

	//DrawFormatString(leftlimit, downlimit - 60, GetColorHSV(0, 120, 255), "intercept: %.0f", intercept);


	return dist;
}

double getmin(double a, double b) {
	if (a > b) {
		return b;
	}
	else {
		return a;
	}
}
double getmax(double a, double b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

void fadeinout(int type, int fade, int fadetime) {//1:out 2:in
	if (type == 1) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * fade / fadetime);
	}
	else if (type == 2) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (fadetime - fade) / fadetime);
	}
	DrawBox(0, 0, SCREEN_X, SCREEN_Y, GetColorHSV(0, 0, 0), 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

bool prob(double probablity) {
	int max = 100000000;
	
	if ((double)GetRand(max) / max < probablity) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}