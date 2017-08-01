#pragma once

//アニメーション枚数
const int lvupuselen = 20;
const int glassbreaklen = 20;
const int kiralen = 15;
const int slashhit1len = 18;
const int shot1hitlen = 18;
const int shot2hitlen = 20;
const int shot4hitlen = 25;
const int breakshot_aroundlen = 20;
const int breakshot_chargelen = 60;
const int breakshot_laser_plen = 12;
const int breakshot_laser_slen = 30;
const int breakshot_backlen = 20;
const int enemydeathlen = 20;
const int leftlen = 30;

//画像読み込み
int gra_mouseiconhead;
int gra_titlecircle[5];
int gra_titleselect;
int gra_lvupuse[3][lvupuselen];//各レベルごと
int gra_slashstart[kiralen];
int gra_slashhit[slashhit1len];
int gra_shot1break[glassbreaklen];
int gra_shot1breakcore[glassbreaklen];
int gra_shot1hit[shot1hitlen];
int gra_shot2;
int gra_shot2hit[shot2hitlen];
int gra_shot4hit[shot4hitlen];
int gra_breakshot_around[breakshot_aroundlen];
int gra_breakshot_charge[3][breakshot_chargelen];
int gra_breakshot_laser_p[breakshot_laser_plen];
int gra_breakshot_laser_s[3][breakshot_laser_slen];
int gra_breakshot_back[3][breakshot_backlen];
int gra_shotenemy1break[glassbreaklen];
int gra_shotenemy1breakcore[glassbreaklen];
int gra_enemydeath[ene_bossg + 1][enemydeathlen];
int gra_left[leftlen];
int gra_eneshieldshield;
int gra_summon[ene_bossg + 1];
int gra_medeath;
//int gra_enemydeath[enemiesmax];


//音読み込み
int se_start;
int se_cancel;
int se_countdown;
int se_countdownend;
int se_slash;
int se_slashhit;
int se_shot1;
int se_shot1hit;
int se_shot2;
int se_shot2hit;
int se_shot3;
int se_shot3hit;
int se_shot4;
int se_shot4laser;
int se_breakshot_charge;
int se_breakshot_0;
int se_breakshot_1;
int se_breakshot_hit_p;
int se_breakshot_hit_s;
int se_shield;
int se_intercept;
int se_lvup;
int se_lvmax;
int se_lvupuse;
int se_lvupend;
int se_select;
int se_summoncharge;
int se_summon;
int se_summonleftlimit;
int se_ninjawarp;
int se_enemydeath;
int se_bossdeath;
int se_medeath1;
int se_medeath2;

int bgm_title;
int bgm_game;
int bgm_result;

//フォントハンドル
int font_title;
int font_start;
int font_select;
int font_time;
int font_timemini;
int font_totitle;
//int font0[200];//[size]

void loadsozai() {
	//フォント読み込み
	LPCSTR font_path = "sozai\\TECHNOID.TTF"; // 読み込むフォントファイルのパス
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}
	ChangeFont("technoid", DX_CHARSET_DEFAULT);


	//画像読み込み
	gra_mouseiconhead = LoadGraph("sozai\\circleblur.png");
	GraphFilter(gra_mouseiconhead, DX_GRAPH_FILTER_HSB, 1, 20, 0, 0);

	for (int i = 0; i < 5; i++) {
		gra_titlecircle[i] = LoadGraph("sozai\\circleblur.png");
	}

	gra_titleselect = LoadGraph("sozai\\select.png");
	GraphFilter(gra_titleselect, DX_GRAPH_FILTER_HSB, 1, 210, -200, 100);

	for (int lv = 0; lv < 3; lv++) {
		LoadDivGraph("sozai\\lvupuse.png", lvupuselen, 5, 4, 400, 400, gra_lvupuse[lv]);
		for (int j = 0; j < lvupuselen; j++) {
			GraphFilter(gra_lvupuse[lv][j], DX_GRAPH_FILTER_HSB, 1, shot1hue + hueperlevel * (lv + 1), 0, 0);
		}
	}

	LoadDivGraph("sozai\\kira.png", kiralen, 5, 3, 100, 100, gra_slashstart);
	for (int i = 0; i < kiralen; i++) {
		GraphFilter(gra_slashstart[i], DX_GRAPH_FILTER_HSB, 1, 240, -100, 0);
	}

	LoadDivGraph("sozai\\slashhit1.png", slashhit1len, 5, 4, 400, 400, gra_slashhit);
	for (int i = 0; i < slashhit1len; i++) {
		GraphFilter(gra_slashhit[i], DX_GRAPH_FILTER_HSB, 1, 240, -100, 0);
	}

	LoadDivGraph("sozai\\glassbreak.png", glassbreaklen, 5, 4, 400, 400, gra_shot1break);
	for (int i = 0; i < glassbreaklen; i++) {
		GraphFilter(gra_shot1break[i], DX_GRAPH_FILTER_HSB, 1, shot1hue, 0, 0);
	}
	LoadDivGraph("sozai\\glassbreakcore.png", glassbreaklen, 5, 4, 400, 400, gra_shot1breakcore);
	for (int i = 0; i < glassbreaklen; i++) {
		GraphFilter(gra_shot1breakcore[i], DX_GRAPH_FILTER_HSB, 1, shot1hue, 0, 0);
	}

	LoadDivGraph("sozai\\shot1hit.png", shot1hitlen, 5, 4, 400, 400, gra_shot1hit);
	for (int i = 0; i < shot1hitlen; i++) {
		GraphFilter(gra_shot1hit[i], DX_GRAPH_FILTER_HSB, 1, shot1hue, -100, 0);
	}

	gra_shot2 = LoadGraph("sozai\\circleblur_inv.png");
	GraphFilter(gra_shot2, DX_GRAPH_FILTER_HSB, 1, 210, 0, 0);

	LoadDivGraph("sozai\\shot2hit.png", shot2hitlen, 5, 4, 400, 400, gra_shot2hit);
	for (int i = 0; i < shot2hitlen; i++) {
		GraphFilter(gra_shot2hit[i], DX_GRAPH_FILTER_HSB, 1, shot1hue + hueperlevel, 0, 0);
	}

	LoadDivGraph("sozai\\shot4hit.png", shot4hitlen, 5, 5, 300, 300, gra_shot4hit);
	for (int i = 0; i < shot4hitlen; i++) {
		GraphFilter(gra_shot4hit[i], DX_GRAPH_FILTER_HSB, 1, shot1hue + hueperlevel * 3, 0, 0);
	}

	LoadDivGraph("sozai\\breakshot_around.png", breakshot_aroundlen, 5, 4, 600, 600, gra_breakshot_around);
	for (int i = 0; i < breakshot_aroundlen; i++) {
		GraphFilter(gra_breakshot_around[i], DX_GRAPH_FILTER_HSB, 1, 0, -255, 0);
	}

	for (int lv = 1; lv < 4; lv++) {
		LoadDivGraph("sozai\\breakshot_charge.png", breakshot_chargelen, 5, 12, 600, 600, gra_breakshot_charge[lv - 1]);
		for (int i = 0; i < breakshot_chargelen; i++) {
			GraphFilter(gra_breakshot_charge[lv - 1][i], DX_GRAPH_FILTER_HSB, 1, 160 + hueperlevel * lv, 0, 0);
		}
	}

	LoadDivGraph("sozai\\breakshot_laser_p.png", breakshot_laser_plen, 5, 3, 1500, 200, gra_breakshot_laser_p);
	for (int i = 0; i < breakshot_laser_plen; i++) {
		GraphFilter(gra_breakshot_laser_p[i], DX_GRAPH_FILTER_HSB, 0, 0, 0, 0);
	}

	for (int lv = 1; lv < 4; lv++) {
		LoadDivGraph("sozai\\breakshot_laser_s.png", breakshot_laser_slen, 5, 6, 1500, 400, gra_breakshot_laser_s[lv - 1]);
		for (int i = 0; i < breakshot_laser_slen; i++) {
			GraphFilter(gra_breakshot_laser_s[lv - 1][i], DX_GRAPH_FILTER_HSB, 1, 160 + hueperlevel * lv, 0, 0);
		}
	}

	for (int lv = 1; lv < 4; lv++) {
		LoadDivGraph("sozai\\breakshot_back.png", breakshot_backlen, 5, 4, 600, 600, gra_breakshot_back[lv - 1]);
		for (int i = 0; i < breakshot_backlen; i++) {
			GraphFilter(gra_breakshot_back[lv - 1][i], DX_GRAPH_FILTER_HSB, 1, 160 + hueperlevel * lv, 0, 0);
		}
	}

	LoadDivGraph("sozai\\glassbreak.png", glassbreaklen, 5, 4, 400, 400, gra_shotenemy1break);
	for (int i = 0; i < glassbreaklen; i++) {
		GraphFilter(gra_shotenemy1break[i], DX_GRAPH_FILTER_HSB, 1, 240, (int)getmax(-400.0 * i / glassbreaklen, -255), 100);
	}
	LoadDivGraph("sozai\\glassbreakcore.png", glassbreaklen, 5, 4, 400, 400, gra_shotenemy1breakcore);
	for (int i = 0; i < glassbreaklen; i++) {
		GraphFilter(gra_shotenemy1breakcore[i], DX_GRAPH_FILTER_HSB, 1, 240, -255, 0);
	}

	for (int type = 0; type < ene_bossg + 1; type++) {
		LoadDivGraph("sozai\\enemydeath.png", enemydeathlen, 5, 4, 600, 600, gra_enemydeath[type]);
		for (int j = 0; j < enemydeathlen; j++) {
			GraphFilter(gra_enemydeath[type][j], DX_GRAPH_FILTER_HSB, 1, ene_hue[type], ene_saturation[type] - 255, ene_value[type] - 255);
		}
	}

	LoadDivGraph("sozai\\left.png", leftlen, 5, 6, 300, 300, gra_left);
	for (int i = 0; i < leftlen; i++) {
		GraphFilter(gra_left[i], DX_GRAPH_FILTER_HSB, 1, 20, -100, 0);
	}

	gra_eneshieldshield = LoadGraph("sozai\\circleblur_inv.png");
	GraphFilter(gra_eneshieldshield, DX_GRAPH_FILTER_HSB, 1, 20, -0, 0);

	for (int i = 0; i <= ene_bossg; i++) {
		gra_summon[i] = LoadGraph("sozai\\circleblur_inv.png");
	}

	gra_medeath = LoadGraph("sozai\\circleblur_inv.png");

	/*
	for (int i = 0; i <= enemiesmax; i++) {
		gra_enemydeath[i] = LoadGraph("sozai\\circleblur_inv.png");
	}
	*/

	//音読み込み
	se_start = LoadSoundMem("sozai\\lvmax.wav");
	se_cancel = LoadSoundMem("sozai\\lvupend.wav");
	se_countdown = LoadSoundMem("sozai\\countdown.wav");
	se_countdownend = LoadSoundMem("sozai\\countdownend.wav");
	se_slash = LoadSoundMem("sozai\\slash.wav");
	se_slashhit = LoadSoundMem("sozai\\slashhit.wav");
	se_shot1 = LoadSoundMem("sozai\\shot1.wav");
	se_shot1hit = LoadSoundMem("sozai\\shot1hit.wav");
	se_shot2 = LoadSoundMem("sozai\\shot2.wav");
	se_shot2hit = LoadSoundMem("sozai\\shot2hit.wav");
	se_shot3 = LoadSoundMem("sozai\\shot3.wav");
	se_shot3hit = LoadSoundMem("sozai\\shot3hit.wav");
	se_shot4 = LoadSoundMem("sozai\\shot4.wav");
	se_shot4laser = LoadSoundMem("sozai\\shot4laser.wav");
	se_breakshot_charge = LoadSoundMem("sozai\\breakshot_charge.wav");
	se_breakshot_0 = LoadSoundMem("sozai\\breakshot_0.wav");
	se_breakshot_1 = LoadSoundMem("sozai\\breakshot_1.wav");
	se_breakshot_hit_p = LoadSoundMem("sozai\\breakshot_hit_p.wav");
	se_breakshot_hit_s = LoadSoundMem("sozai\\breakshot_hit_s.wav");
	se_shield = LoadSoundMem("sozai\\shield.wav");
	se_intercept = LoadSoundMem("sozai\\intercept.wav");
	se_lvup = LoadSoundMem("sozai\\lvup.wav");
	se_lvmax = LoadSoundMem("sozai\\lvmax.wav");
	se_lvupuse = LoadSoundMem("sozai\\lvupuse.wav");
	se_lvupend = LoadSoundMem("sozai\\lvupend.wav");
	se_select = LoadSoundMem("sozai\\select.wav");
	se_summoncharge = LoadSoundMem("sozai\\summoncharge.wav");
	se_summon = LoadSoundMem("sozai\\summon.wav");
	se_summonleftlimit = LoadSoundMem("sozai\\summonleftlimit.wav");
	se_ninjawarp = LoadSoundMem("sozai\\ninjawarp.wav");;
	se_enemydeath = LoadSoundMem("sozai\\enemydeath.wav");
	se_bossdeath = LoadSoundMem("sozai\\bossdeath.wav");
	se_medeath1 = LoadSoundMem("sozai\\medeath1.wav");
	se_medeath2 = LoadSoundMem("sozai\\medeath2.wav");

	bgm_title = LoadSoundMem("sozai\\bgm_title.wav");
	bgm_game = LoadSoundMem("sozai\\bgm_game.wav");
	bgm_result = LoadSoundMem("sozai\\bgm_result.wav");

	//フォントハンドル作成
	font_title = CreateFontToHandle("technoid", 150, 9);
	font_start = CreateFontToHandle("technoid", 50, 1, DX_FONTTYPE_ANTIALIASING);
	font_select = CreateFontToHandle("technoid", 30, 1, DX_FONTTYPE_ANTIALIASING);
	font_time = CreateFontToHandle("technoid", 40, 9, DX_FONTTYPE_ANTIALIASING);
	font_timemini = CreateFontToHandle("technoid", 25, 3, DX_FONTTYPE_ANTIALIASING);
	font_totitle = CreateFontToHandle("technoid", 22, 0, DX_FONTTYPE_ANTIALIASING);
	/*
	for (int i = 1; i < 200; i++) {
		for (int j = 0; j < 10; j++) {
			font[i][j] = CreateFontToHandle("technoid", i, j, DX_FONTTYPE_ANTIALIASING);
		}
	}*/
	/*
	font[8][0] = CreateFontToHandle("technoid", 8, 0, DX_FONTTYPE_ANTIALIASING);
	font[8][2] = CreateFontToHandle("technoid", 8, 2, DX_FONTTYPE_ANTIALIASING);
	font[8][4] = CreateFontToHandle("technoid", 8, 4, DX_FONTTYPE_ANTIALIASING);
	font[8][6] = CreateFontToHandle("technoid", 8, 6, DX_FONTTYPE_ANTIALIASING);
	font[8][8] = CreateFontToHandle("technoid", 8, 8, DX_FONTTYPE_ANTIALIASING);
	font[10][0] = CreateFontToHandle("technoid", 10, 0, DX_FONTTYPE_ANTIALIASING);
	font[10][2] = CreateFontToHandle("technoid", 10, 2, DX_FONTTYPE_ANTIALIASING);
	font[10][4] = CreateFontToHandle("technoid", 10, 4, DX_FONTTYPE_ANTIALIASING);
	font[10][6] = CreateFontToHandle("technoid", 10, 6, DX_FONTTYPE_ANTIALIASING);
	font[10][8] = CreateFontToHandle("technoid", 10, 8, DX_FONTTYPE_ANTIALIASING);
	font[12][0] = CreateFontToHandle("technoid", 12, 0, DX_FONTTYPE_ANTIALIASING);
	font[12][2] = CreateFontToHandle("technoid", 12, 2, DX_FONTTYPE_ANTIALIASING);
	font[12][4] = CreateFontToHandle("technoid", 12, 4, DX_FONTTYPE_ANTIALIASING);
	font[12][6] = CreateFontToHandle("technoid", 12, 6, DX_FONTTYPE_ANTIALIASING);
	font[12][8] = CreateFontToHandle("technoid", 12, 8, DX_FONTTYPE_ANTIALIASING);*/
	for (int i = 4; i < 60; i++) {
		//font0[i*3] = CreateFontToHandle("technoid", i*3, 0, DX_FONTTYPE_ANTIALIASING);
	}


	ChangeVolumeSoundMem(200, se_shot1);
	ChangeVolumeSoundMem(200, se_shot1hit);
	ChangeVolumeSoundMem(200, se_shot2);
	ChangeVolumeSoundMem(200, se_shot2hit);
	ChangeVolumeSoundMem(200, se_shot3);
	ChangeVolumeSoundMem(200, se_shot3hit);
	ChangeVolumeSoundMem(200, se_shot4);
	ChangeVolumeSoundMem(200, se_shot4laser);
}