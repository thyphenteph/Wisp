#define DEBUG 0

#include <DxLib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "prototype.h"
#include "defines.h"
#include "global.h"
#include "function_general.h"
#include "class_Fade.h"
#include "class_bg.h"
#include "class_SingleGraph.h"
#include "class_Animation.h"
#include "class_Enemy.h"
#include "class_Me.h"
#include "class_Hitbox.h"
//#include "class_EnemyHitbox.h"
#include "class_Core.h"
#include "class_Shot.h"
#include "class_Shot1.h"
#include "class_Shot2.h"
#include "class_Shot3.h"
#include "class_Shot4.h"
#include "class_Slash.h"
#include "class_Breakshot.h"
#include "class_Shotenemy1.h"
#include "class_Hitdamagenum.h"
#include "function_other.h"
#include "class_Mouseicon.h"
#include "phase.h"
#include "move_enemy.h"
#include "move_shotenemy1.h"
#include "action_me.h"
#include "action_enemy.h"
#include "attack_slash.h"
#include "attack_shot1.h"
#include "attack_shot2.h"
#include "attack_shot3.h"
#include "attack_shot4.h"
#include "attack_breakshot.h"
#include "action_shotenemy1.h"
#include "class_button.h"

double postest[2] = { 500, 300 };
Hitbox hitbox_test;


void yokutsukau() {
	//escÇ≈ÉQÅ[ÉÄèIóπ
	if (keystate[KEY_INPUT_ESCAPE] == 1) {
		phase = 5;
	}

	//ÉâÉìÉLÉìÉO
	FILE *fp;
	char *name = "ranking.bin";
	const int command = 5;
	int rank[command];
	int finalscore;//ÉOÉçÅ[ÉoÉãä÷êîÇ÷
	fp = fopen(name, "rb");
	fread(rank, sizeof(int), command, fp);
	fclose(fp);
	for (int i = 0; i < command; i++) {
		if (finalscore >= rank[i]) {
			for (int j = command - 2; j >= i; j--) {
				rank[j + 1] = rank[j];
			}
			rank[i] = finalscore;
			break;
		}
	}
	fp = fopen(name, "wb");
	fwrite(rank, sizeof(int), 5, fp);
	fclose(fp);

	//ÉtÉFÅ[ÉhÉCÉìÅEÉAÉEÉg
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - count * 6);
	DrawBox(0, 0, 640, 480, GetColor(255, 255, 255), 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}


void drawmouseicon() {
	SetMouseDispFlag(FALSE);//É}ÉEÉXîÒï\é¶
	mouseicon.sethistory(mouse_d, count);
	for (int i = 0; i < mouseicon.length - 1; i++) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255.0 * (mouseicon.length - i) / mouseicon.length);
		DrawLine(mouseicon.history[i][0], mouseicon.history[i][1], mouseicon.history[i + 1][0], mouseicon.history[i + 1][1], GetColorHSV(20, 255, 255), 6.0 * (mouseicon.length - i) / mouseicon.length);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (5 + sin(deg2rad(count * 5))) / 6);
	DrawCircleBlur(mouse[0], mouse[1], 8.0, gra_mouseiconhead);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void process_bg() {
	//îwåièàóù
	for (int i = 0; i < numstar; i++) {
		bgstar[i].setpos();
		bgstar[i].update();
	}
	for (int i = 0; i < numbgbox; i++) {
		bg[i].setpos();
		bg[i].update();
	}

	//îwåiï`âÊ
	DrawBox(0, 0, SCREEN_X, SCREEN_Y, GetColorHSV(240, 200, 15), 1);
	for (int i = 0; i < numstar; i++) {
		if (bgstar[i].view == 1) {
			DrawCircle(bgstar[i].pos[0], bgstar[i].pos[1], bgstar[i].radius, bgstar[i].color, 1);
		}
	}
	for (int i = 0; i < numbgbox; i++) {
		for (int j = 0; j < 10; j++) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, -bg[i].vel * 8 - 14 * j);
			DrawBox(bg[i].pos[0] - j, bg[i].pos[1] - j, bg[i].pos[0] + bg[i].size[0] + j, bg[i].pos[1] + bg[i].size[1] + j,
				bg[i].color, 0);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		for (int j = 1; j < 20; j++) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, -bg[i].vel * 8 - 7 * j);
			DrawBox(bg[i].pos[0] + j, bg[i].pos[1] + j, bg[i].pos[0] + bg[i].size[0] - j, bg[i].pos[1] + bg[i].size[1] - j,
				bg[i].color, 0);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		//DrawFormatString(0, 20 * i, GetColor(255, 255, 255), "pos:(%.1f, %.1f) size:(%.1f, %.1f)", bg[i].pos[0], bg[i].pos[1], bg[i].size[0], bg[i].size[1]);
	}
}

void setframe() {
	unsigned int framecolor = GetColorHSV(0, 0, 120);
	DrawBox(0, 0, SCREEN_X, uplimit - 5, framecolor, 1);//è„
	DrawBox(rightlimit + 5, 0, SCREEN_X, SCREEN_Y, framecolor, 1);//âE
	DrawBox(0, downlimit + 5, SCREEN_X, SCREEN_Y, framecolor, 1);//â∫
	DrawBox(0, 0, leftlimit - 5, SCREEN_Y, framecolor, 1);//ç∂
	for (int i = 0; i <= 5; i++) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - 50 * i);
		DrawBox(leftlimit - 5 + i, uplimit - 5 + i, rightlimit + 5 - i, downlimit + 5 - i, framecolor, 0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

void sethpback() {
	//WispHPìôîwåi
	for (int i = 0; i < 5; i++) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - 50 * i);
		DrawBox(10 - i, wisphp_ul[1] - 5 - i, wisphp_dr[0] + 10 + i, wisplv_dr[1] + 5 + i, GetColorHSV(240, 200, 20), 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	//CoreHPìôîwåi
	for (int i = 0; i < 5; i++) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - 50 * i);
		DrawBox(corehp_ul[0] - 140 - i, corehp_ul[1] - 5 - i, corehp_dr[0] + 10 + i, coresm_dr[1] + 5 + i, GetColorHSV(240, 200, 20), 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

void drawwisphp() {
	//é©ã@HP
	DrawFormatString(wisphp_ul[0] - 125, wisphp_ul[1], GetColorHSV(120, 220, 255), "Wisp HP");
	DrawBox(wisphp_ul[0], wisphp_ul[1], wisphp_dr[0], wisphp_dr[1], GetColorHSV(0, 0, 0), 1);//HPÉQÅ[ÉWîwåi
	DrawBox(wisphp_ul[0], wisphp_ul[1], //HPÉQÅ[ÉWñ{ëÃ
		wisphp_ul[0] + (wisphp_dr[0] - wisphp_ul[0]) * ((double)me.hp / me.hpmax), wisphp_dr[1],
		GetColorHSV(120 - 120 / (double)me.hpmax * (me.hpmax - me.hp), 255 - 125 * (1 - cos(deg2rad(count * 5))), 255), 1);
	DrawBox(wisphp_ul[0], wisphp_ul[1], wisphp_dr[0], wisphp_dr[1], GetColorHSV(120, 255, 180), 0);//HPÉQÅ[ÉWòg
#if DEBUG
	if (keystate[KEY_INPUT_A] >= 1 && me.hp > 0) {//ÉfÉoÉbÉOóp
		me.hp--;
	}
	if (keystate[KEY_INPUT_S] >= 1) {
		me.hp = me.hpmax;
	}
#endif
	for (int i = 0; i < 5; i++) {//ògÇÃåı
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (255 - 50 * i) * (sin(deg2rad(count * 5)) + 1) * 0.5);
		DrawBox(wisphp_ul[0] - i, wisphp_ul[1] - i, wisphp_dr[0] + i, wisphp_dr[1] + i, GetColorHSV(120, 255, 180), 0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

void drawwisplv() {
	DrawFormatString(wisphp_ul[0] - 125, wisplv_ul[1], GetColorHSV(240, 220, 255), "Wisp LV");
	DrawBox(wisplv_ul[0], wisplv_ul[1], wisplv_dr[0], wisplv_dr[1], GetColorHSV(0, 0, 0), 1);//LVÉQÅ[ÉWîwåi
	DrawBox(wisplv_ul[0], wisplv_ul[1], //LVÉQÅ[ÉWñ{ëÃ
		wisplv_ul[0] + (wisplv_dr[0] - wisplv_ul[0]) * ((double)me.exp / me.maxexp[me.level - 1]), wisplv_dr[1],
		GetColorHSV(160 + (me.level - 1) * hueperlevel, 255 - 125 * (1 - cos(deg2rad(count * 5))), 255), 1);
	if (me.shotlevel == 1) {
		if (me.lvmaxflag == 0) {
			DrawFormatString(wisplv_ul[0] + 5, wisplv_ul[1],
				GetColorHSV(160 + (me.level - 1) * hueperlevel, 255 - 125 * (1 - sin(deg2rad(count * 5))), 255), "LV %d", me.level);
		}
		else {
			/*
			DrawFormatString(wisplv_ul[0] + 5, wisplv_ul[1],
				GetColorHSV(0, 255 - 125 * (1 - sin(deg2rad(count * 10))), 255), "LV MAX");
			*/
		}
	}
	else {
		DrawBox(wisplv_ul[0], wisplv_ul[1], //LVÉQÅ[ÉWñ{ëÃ
			wisplv_ul[0] + (wisplv_dr[0] - wisplv_ul[0]) * ((double)me.exp / me.maxexp[me.level - 1]), wisplv_dr[1],
			GetColorHSV(160 + me.level* hueperlevel, 255 - 125 * (1 - cos(deg2rad(count * 10))), 255), 1);
		DrawFormatString(wisplv_ul[0] + 5, wisplv_ul[1],
			GetColorHSV(160 + me.level * hueperlevel, 255 - 125 * (1 - sin(deg2rad(count * 10))), 255), "Using LV %d", me.level + 1);
	}
	DrawBox(wisplv_ul[0], wisplv_ul[1], wisplv_dr[0], wisplv_dr[1], GetColorHSV(240, 255, 180), 0);//LVÉQÅ[ÉWòg
	for (int i = 0; i < 5; i++) {//ògÇÃåı
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (255 - 50 * i) * (sin(deg2rad(count * 5)) + 1) * 0.5);
		DrawBox(wisplv_ul[0] - i, wisplv_ul[1] - i, wisplv_dr[0] + i, wisplv_dr[1] + i, GetColorHSV(240, 255, 180), 0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

void process_core() {
	if (flagsummon == 0 || summonmouse == 1) {
		//ÉzÉCÅ[ÉãÇ…ÇÊÇÈëIë
		int wheel = GetMouseWheelRotVol();
		if (wheel != 0) {
			PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
		}
		if (wheel < 0) {
			summontype++;
		}
		else if (wheel > 0) {
			summontype--;
		}
		if (summontype < 0) {
			summontype = ene_bossg;
		}
		if (summontype > ene_bossg) {
			summontype = 0;
		}
		//ÉNÉäÉbÉNÇ…ÇÊÇÈëIë
		for (int i = 0; i < ene_bossg + 1; i++) {
			if (mousestate[MOUSE_INPUT_LEFT] >= 1 && i != summontype) {
				if (mouse[0] >= summonbutton[i].pos[0] && mouse[0] <= summonbutton[i].pos[0] + summonbutton[i].size[0]
					&& mouse[1] >= summonbutton[i].pos[1] && mouse[1] <= summonbutton[i].pos[1] + summonbutton[i].size[1]) {

					summontype = i;
					PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
				}
			}
		}
		if (game.countdown == 0) {
			core.update();
		}
	}
}

void drawcorehp() {
	//CoreHP
	DrawFormatString(corehp_ul[0] - 135, corehp_ul[1], GetColorHSV(120, 220, 255), "Core HP");
	DrawBox(corehp_ul[0], corehp_ul[1], corehp_dr[0], corehp_dr[1], GetColorHSV(0, 0, 0), 1);//HPÉQÅ[ÉWîwåi
	DrawBox(corehp_ul[0], corehp_ul[1], //HPÉQÅ[ÉWñ{ëÃ
		corehp_ul[0] + (corehp_dr[0] - corehp_ul[0]) * ((double)enemies[0].hp / enemies[0].hpmax), corehp_dr[1],
		GetColorHSV(120 - 120.0 / enemies[0].hpmax * (enemies[0].hpmax - enemies[0].hp), 255, 255 - 80 * (1 - cos(deg2rad(count * 5)))), 1);
	DrawBox(corehp_ul[0], corehp_ul[1], corehp_dr[0], corehp_dr[1], GetColorHSV(120, 255, 180), 0);//HPÉQÅ[ÉWòg
#if DEBUG
	if (keystate[KEY_INPUT_D] >= 1 && enemies[0].hp > 0) {//ÉfÉoÉbÉOóp
		enemies[0].hp--;
		if (keystate[KEY_INPUT_D] >= 30) {
			enemies[0].hp -= 4;
		}
	}
	if (keystate[KEY_INPUT_F] >= 1) {
		enemies[0].hp = enemies[0].hpmax;
	}
#endif

	for (int i = 0; i < 5; i++) {//ògÇÃåı
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (255 - 50 * i) * (sin(deg2rad(count * 5)) + 1) * 0.5);
		DrawBox(corehp_ul[0] - i, corehp_ul[1] - i, corehp_dr[0] + i, corehp_dr[1] + i, GetColorHSV(120, 255, 180), 0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

void drawcoresm() {
	DrawFormatString(corehp_ul[0] - 135, coresm_ul[1], GetColorHSV(20, 220, 255), "Summon");
	DrawBox(coresm_ul[0], coresm_ul[1], coresm_dr[0], coresm_dr[1], GetColorHSV(0, 0, 0), 1);//SummonÉQÅ[ÉWîwåi
	DrawBox(coresm_ul[0], coresm_ul[1], //SummonÉQÅ[ÉWñ{ëÃ
		coresm_ul[0] + (coresm_dr[0] - coresm_ul[0]) * ((double)core.summon / core.summonmax), coresm_dr[1],
		GetColorHSV(20, 255, 255 - 80 * (1 - cos(deg2rad(count * 5)))), 1);
	//ÉQÅ[ÉWégópó 
	int color;
	if (core.summon >= ene_gauge[summontype]) {
		color = GetColorHSV(210, 255, 255);
	}
	else {
		color = GetColorHSV(350, 255, 255);
	}
	for (int i = 0; i < 5; i++) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (255 - 50 * i) * (cos(deg2rad(count * 10)) + 1) * 0.5);
		DrawBox(coresm_ul[0] + (coresm_dr[0] - coresm_ul[0]) * (getmax(0, (double)core.summon - ene_gauge[summontype]) / core.summonmax) + i,
			coresm_ul[1] + i,
			coresm_ul[0] + (coresm_dr[0] - coresm_ul[0]) * ((double)core.summon / core.summonmax) - i, coresm_dr[1] - i,
			color, 0);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawBox(coresm_ul[0], coresm_ul[1], coresm_dr[0], coresm_dr[1], GetColorHSV(20, 255, 180), 0);//SummonÉQÅ[ÉWòg
	for (int i = 0; i < 5; i++) {//ògÇÃåı
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (255 - 50 * i) * (sin(deg2rad(count * 5)) + 1) * 0.5);
		DrawBox(coresm_ul[0] - i, coresm_ul[1] - i, coresm_dr[0] + i, coresm_dr[1] + i, GetColorHSV(20, 255, 180), 0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

Hitbox lvupusehit;
void lvupuse() {
	const int size = 500;
	if ((phase == phase_game && game.count == 1) || (phase == phase_oneplayer && oneplayer.count == 1)) {
		//çUåÇîªíË
		lvupusehit.reset();
		lvupusehit.del();
	}
#if DEBUG
	DrawFormatString(leftlimit + 50, uplimit + 50, GetColorHSV(0, 255, 255), "%d", lvupusehit.hittime[1]);
#endif
	//âï˙
	if (keystate[KEY_INPUT_C] == 1 && me.shotlevel == 1 && me.motion != breakshotid && me.level >= 2) {
		//me.motion = 0;
		if (me.lvmaxflag == 0) {
			me.shotlevel = me.level;
			me.level--;
			me.exp = me.maxexp[me.level - 1];
			PlaySoundMem(se_lvupuse, DX_PLAYTYPE_BACK);
			//ÉGÉtÉFÉNÉg
			graphlvupuse[me.level - 1].sethandle(gra_lvupuse[me.level - 1], lvupuselen);
			graphlvupuse[me.level - 1].setpos(me.pos[0], me.pos[1]);
			graphlvupuse[me.level - 1].setsize(size);
			graphlvupuse[me.level - 1].setangle(RandRange(-180, 180));
			graphlvupuse[me.level - 1].start();
			//çUåÇîªíË
			lvupusehit.reset();
			lvupusehit.setdirect(FALSE);
			lvupusehit.setintercept(TRUE);
			lvupusehit.setshield(FALSE);
			lvupusehit.setproperty(size * 0.10 / 2, 60, 25);
			lvupusehit.setpos(me.pos[0], me.pos[1]);
			lvupusehit.setlaser(FALSE, 0, 0);
			lvupusehit.sethitse(0);
		}
		else { //É{ÉÄìIÇ»Åc ñ¢é¿ëï
			me.shotlevel = 1;
			me.level = 1;
			me.exp = 0;
		}
	}
	//ÉGÉtÉFÉNÉgï`âÊ
	graphlvupuse[me.level - 1].draw();
	//îªíËèàóù
	lvupusehit.judge(enemies, shotenemy1);
	lvupusehit.killenemy(100);
	switch (graphlvupuse[me.level - 1].count) {
	case 1:
		lvupusehit.size = size * 0.28 / 2;
		break;
	case 2:
		lvupusehit.size = size * 0.46 / 2;
		break;
	case 3:
		lvupusehit.size = size * 0.62 / 2;
		break;
	case 4:
		lvupusehit.size = size * 0.75 / 2;
		break;
	case 5:
		lvupusehit.size = size * 0.80 / 2;
		break;
	case 8:
		lvupusehit.del();
		break;
	}


	if (me.shotlevel == 1 && me.exp == me.maxexp[me.level - 1] - 1) {//LVup
		if (me.level < me.maxlevel) {
			PlaySoundMem(se_lvup, DX_PLAYTYPE_BACK);
		}
		else {
			PlaySoundMem(se_lvmax, DX_PLAYTYPE_BACK);
		}
	}
	if (me.shotlevel != 1 && me.exp <= 1) {//ã≠âªèÛë‘èIóπ
		PlaySoundMem(se_lvupend, DX_PLAYTYPE_BACK);
	}
}

void drawsummon() {
	for (int i = 0; i < ene_bossg + 1; i++) {
		if (summonbutton[i].count == 0) {
			summonbutton[i].id = i;
			summonbutton[ene_boss].size[1] = 70;
			summonbutton[ene_bossg].size[1] = 70;
			summonbutton[i].setname();
			dummybutton.pos[1] = uplimit + 10;
			dummybutton.size[1] = 0;
			if (i == 0) {
				summonbutton[i].setpos(dummybutton);
			}
			else {
				summonbutton[i].setpos(summonbutton[i - 1]);
			}
		}
		int blur = 5;
		for (int j = 0; j < blur; j++) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (blur - j) / blur);
			DrawBox(summonbutton[i].pos[0] - j, summonbutton[i].pos[1] - j, summonbutton[i].pos[0] + summonbutton[i].size[0] + j,
				summonbutton[i].pos[1] + summonbutton[i].size[1] + j, summonbutton[i].color, 1);
			if (summontype == i) {
				DrawBox(summonbutton[i].pos[0] - j, summonbutton[i].pos[1] - j, summonbutton[i].pos[0] + summonbutton[i].size[0] + j,
					summonbutton[i].pos[1] + summonbutton[i].size[1] + j,
					GetColorHSV(ene_hue[i], ene_saturation[i], ene_value[i] * (0.5 * (1 + cos(deg2rad(summonbutton[i].count))))), 1);
				summonbutton[i].update();
			}
			else {
				summonbutton[i].count = 0;
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		if (summontype == i) {
			DrawFormatString(summonbutton[i].pos[0], summonbutton[i].pos[1], GetColorHSV(ene_hue[i],
				ene_saturation[i], ene_value[i] * (0.5 * (1 + sin(deg2rad(summonbutton[i].count))))),
				"%s", summonbutton[i].name);
		}
		else {
			DrawFormatString(summonbutton[i].pos[0], summonbutton[i].pos[1], GetColorHSV(ene_hue[i],
				ene_saturation[i], ene_value[i] * (0.5 * (1 + sin(deg2rad(summonbutton[i].count))))),
				"%s", summonbutton[i].name);
		}

		if (core.summon - ene_gauge[i] <= 0) {
			DrawFormatString(summonbutton[i].pos[0], summonbutton[i].pos[1] + summonbutton[i].size[1] - 20, GetColorHSV(0, 0, 180 * (0.5 * (1 + sin(deg2rad(game.count * 5))))), "Not enough!");
		}
	}
}

void hiteffect() {
	//É_ÉÅÅ[ÉWï\é¶
	for (int i = 0; i < enemiesmax; i++) {
		for (int j = 0; j < 50; j++) {//j:íeid
			if (hitdamagenum[j][i].exist == 1) {
				hitdamagenum[j][i].setpos(enemies[i].pos);
				hitdamagenum[j][i].update();
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, hitdamagenum[j][i].alpha);
				DrawFormatString(hitdamagenum[j][i].pos[0], hitdamagenum[j][i].pos[1],
					GetColorHSV(240 - hitdamagenum[j][i].count * 10, 255, 255), "%d", hitdamagenum[j][i].damage);
				if (hitdamagenum[j][i].count >= 20) {
					hitdamagenum[j][i].exist = 0;
				}
			}
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void drawenemyhp() {
	//HPï\é¶
	for (int i = 1; i < enemiesmax; i++) {
		if (enemies[i].exist == 1) {
			if (enemies[i].vanishcount == 0) {
				int hpgauge_ul[2] = { enemies[i].pos[0] - 30 * enemies[i].size / 20, enemies[i].pos[1] - 30 * enemies[i].size / 20 };
				int hpgauge_size[2] = { 60 * enemies[i].size / 20, 5 * enemies[i].size / 20 };
				int hpgauge_hue = 130 * enemies[i].hp / (enemies[i].hpmax + 0.01);
				DrawBox(hpgauge_ul[0], hpgauge_ul[1],
					hpgauge_ul[0] + hpgauge_size[0] * enemies[i].hp / (enemies[i].hpmax + 0.01), hpgauge_ul[1] + hpgauge_size[1],
					GetColorHSV(hpgauge_hue, 255 - 125 * (1 - sin(deg2rad(enemies[i].count * 5))), 255), 1);//HPÉÅÉCÉì
				DrawBox(hpgauge_ul[0], hpgauge_ul[1],
					hpgauge_ul[0] + hpgauge_size[0], hpgauge_ul[1] + hpgauge_size[1],
					GetColorHSV(hpgauge_hue, 255, 200), 0);//HPòg	
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			}
		}
	}
}




void process_title() {
	process_bg();
	title.draw();
	if (title.count == 0) {
		StopSoundMem(bgm_game);
		StopSoundMem(bgm_result);
		if (!handi.back) {
			PlaySoundMem(bgm_title, DX_PLAYTYPE_BACK);
		}
		shot1.push_back(dummy1);
		shot2.push_back(dummy2);
		shot3.push_back(dummy3);
		shot4.push_back(dummy4);

		game.reset();
	}

	//slash
	attackslash();

	//shotLV1
	attackshot1();

	//shotLV2
	attackshot2();

	//shotLV3
	attackshot3();

	//shotLV4
	attackshot4();

	if (title.count <= title.fadetime) {
		title.flagfade = 2;
	}
	else {
		//ëÄçÏéÛït
		title.control();
		//ÉtÉFÅ[ÉhÉCÉìèIóπ
		if (title.count == title.fadetime + 1) {
			title.flagfade = 0;
		}
		//ÉtÉFÅ[ÉhÉAÉEÉgèIóπ
		if (title.fade == title.fadetime) {
			if (title.select == 0) {
				handi.reset();
				phase = phase_handi;
			}
			else if (title.select == 1) {
				oneplayer.reset();
				phase = phase_oneplayer;
			}
		}
	}
	if (title.flagfade != 0) {
		title.fadeinout(title.flagfade);
	}
	title.update();
}

void process_handi() {
	process_bg();
	process_me();
	if (!handi.flagfade) {
		handi.control();
	}
	handi.draw();
	if (handi.count <= handi.fadetime) {
		handi.flagfade = 2;
	}
	else {
		if (handi.count == handi.fadetime + 1) {
			handi.flagfade = 0;
		}
		if (handi.fade == handi.fadetime) {
			if (!handi.back) {
				me.hpmax = 100;
				me.hpmax *= pow(handicap, 2);
				me.hp = me.hpmax;
				game.reset();
				phase = phase_game;
			}
			else {
				title.reset();
				phase = phase_title;
			}
		}
	}
	if (handi.flagfade != 0) {
		handi.fadeinout(handi.flagfade);
	}
	handi.update();
}

void process_pause() {
	pause.draw(flagpause);
	pause.back(flagpause);
	pause.update();
}

void process_game(bool flagonep) {
	if (game.count == 0) {
		StopSoundMem(bgm_title);
		core.setdef();
		enemies[0].type = ene_core;
		enemies[0].reset();
	}
	if (game.count == 1) {
		for (int i = 0; i <= ene_bossg; i++) {
			GraphFilter(gra_summon[i], DX_GRAPH_FILTER_HSB, 1, ene_hue[i], ene_saturation[i] - 255, ene_value[i] - 255);
		}
		PlaySoundMem(bgm_game, DX_PLAYTYPE_BACK);
	}

	//É|Å[ÉY
	if (game.count > 0 && fade.fadeflag == 0) {
		if (!keystate[KEY_INPUT_C] && keystate[KEY_INPUT_SPACE] == 1) {
			PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
			if (flagpause == 0) {
				flagpause = 1;
			}
			else if (flagpause == 1) {
				flagpause = 0;
			}
		}
		else if (!flagonep && (!mousestate[MOUSE_INPUT_LEFT] && mousestate[MOUSE_INPUT_RIGHT] == 1)) {
			PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
			if (flagpause == 0) {
				flagpause = 2;
			}
			else if (flagpause == 2) {
				flagpause = 0;
			}
		}
	}

	if (flagpause == 0) {

		//îwåi
		process_bg();

		//Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`

		//enemy
		process_enemy();

		//Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`

		//breakshot
		attackbreakshot();

		//slash
		attackslash();

		//shotLV1
		attackshot1();

		//shotLV2
		attackshot2();

		//shotLV3
		attackshot3();

		//shotLV4
		attackshot4();

		//Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`

		//ìGshot1
		attack_shotenemy1();

		//Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`

		//é©ã@èàóù
		process_me();

		//ÉqÉbÉgÉGÉtÉFÉNÉg
		hiteffect();

		//enemyéÄñS
		for (int i = 1; i < enemiesmax; i++) {
			if (enemies[i].hp <= 0 && enemies[i].exist == 1) {
				if (enemies[i].vanishcount == 25) {
					//SE
					if (enemies[i].type == ene_boss || enemies[i].type == ene_bossg) {
						PlaySoundMem(se_bossdeath, DX_PLAYTYPE_BACK);
					}
					else {
						PlaySoundMem(se_enemydeath, DX_PLAYTYPE_BACK);
					}
					//ÉGÉtÉFÉNÉg
					enemydeath[i].sethandle(gra_enemydeath[enemies[i].type], enemydeathlen);
					enemydeath[i].setpos(enemies[i].pos[0], enemies[i].pos[1]);
					enemydeath[i].setsize(600 * 20.0 / enemies[i].size);
					enemydeath[i].setangle(RandRange(-180, 180));
					enemydeath[i].start();
				}
				enemydeath[i].draw();
				/*
				if (enemies[i].vanishcount < 10) {
					if (enemies[i].vanishcount == 1) {
						if (enemies[i].type == ene_boss || enemies[i].type == ene_bossg) {
							PlaySoundMem(se_bossdeath, DX_PLAYTYPE_BACK);
						}
						else {
							PlaySoundMem(se_enemydeath, DX_PLAYTYPE_BACK);
						}
					}
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
					DrawCircleBlur(enemies[i].pos[0], enemies[i].pos[1], enemies[i].vanishcount * enemies[i].size, gra_summon[enemies[i].type]);
					//DrawFormatString(enemies[i].pos[0], enemies[i].pos[1], GetColorHSV(0, 0, 255), "Ç†");

					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
				}*/
			}
		}

		//èIóπèàóù
		result.result = game.getresult(me, enemies[0]);
		//WispéÄñS
		if (me.hp <= 0) {
			effectmedeath.draw(me);
			effectmedeath.update();
			if (effectmedeath.count > 120) {
				game.flagfade = 1;
				StopSoundMem(bgm_game);
			}
		}

		//CoreéÄñS
		if (!flagonep) {

			if (enemies[0].hp <= 0) {
				effectcoredeath.drawcore(enemies[0]);
				effectcoredeath.update();
				if (effectcoredeath.count > 120) {
					game.flagfade = 1;
					StopSoundMem(bgm_game);
				}
			}
		}

		//É^ÉCÉÄÉAÉbÉv
		if (!flagonep) {

			if (game.remain <= 0) {
				game.flagfade = 1;
				StopSoundMem(bgm_game);
			}
		}

		//LVupégóp
		lvupuse();

		//âÊñ ÉtÉâÉbÉVÉÖ
		autoflash.draw();

		//ìGHP
		drawenemyhp();

		//òg
		setframe();

		//HPîwåi
		sethpback();

		//WispHPï\é¶
		drawwisphp();

		//WispLVï\é¶
		drawwisplv();

		if (!flagonep) {
			//Coreèàóù
			process_core();

			//CoreHPï\é¶
			drawcorehp();

			//Summonï\é¶
			drawcoresm();

			//écÇËéûä‘
			game.drawtime();

			//É{É^Éì
			drawsummon();
		}

		if (flagonep) {
			if (game.countdown == game.countdowndef - 1) {
				game.countdown = 0;
			}
		}


		//Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`


		//ÉfÉoÉbÉOóp
#if DEBUG
		if (keystate[KEY_INPUT_V] >= 1) {
			me.exp = me.maxexp[me.level - 1] - 5;
		}
		if (keystate[KEY_INPUT_B] == 1) {
			if (me.shotlevel == 1) {
				me.level--;
				me.exp = 5;
			}
			else {
				me.exp = 5;
			}
		}

		//DrawFormatString(leftlimit, uplimit, GetColorHSV(0, 255, 255), "%d", enemies[0].hp);
		//enemies[0].pos[0] = 900;
		//enemies[0].pos[1] = 300;

		DrawFormatString(100, 200, GetColorHSV(0, 0, 255), "count = %d", game.count);

		/*
		DrawCircle(10, 10, 10, GetColorHSV(160, 255, 255), 1);
		DrawFormatString(0, 20, GetColorHSV(160, 255, 255), "10");
		DrawCircle(15, 50, 15, GetColorHSV(160 + hueperlevel, 255, 255), 1);
		DrawFormatString(2, 65, GetColorHSV(160 + hueperlevel, 255, 255), "15");
		DrawCircle(20, 100, 20, GetColorHSV(160 + hueperlevel * 2, 255, 255), 1);
		DrawFormatString(5, 120, GetColorHSV(160 + hueperlevel * 2, 255, 255), "20");
		*/

		/*
		double linepos[2] = { 0, 0 };
		double lineposend[2] = { 1000,500 };
		DrawLine(linepos[0], linepos[1], lineposend[0], lineposend[1], GetColorHSV(0, 0, 255));
		DrawFormatString(leftlimit, uplimit + 20, GetColorHSV(0, 0, 255), "mouse:(%4d, %4d)", mouse[0], mouse[1]);
		DrawFormatString(leftlimit, uplimit + 40, GetColorHSV(0, 0, 255), "dist: %4.0f",distpointtoline(mouse, linepos, 0.5));
		*/

		if (hitbox_test.exist) {
			DrawCircle(me.pos[0], me.pos[1], 40, GetColorHSV(45, 255, 255), 0);
			hitbox_test.pos[0] = me.pos[0];
			hitbox_test.pos[1] = me.pos[1];
			hitbox_test.judge(enemies, shotenemy1);
			if (keystate[KEY_INPUT_M] == 1) {
				hitbox_test.del();
			}
		}
		else {
			if (keystate[KEY_INPUT_M] == 1) {
				hitbox_test.set(TRUE, TRUE, me.pos[0], me.pos[1], 40, 20, 8, 0, se_slash, 0);
			}
		}

		//DrawCircle(enemies[0].pos[0], enemies[0].pos[1], 100, GetColorHSV(0, 255, 255), 0, 1);
#endif

		//ëŒêÌäJén
		//DrawFormatString(0, 60, GetColorHSV(0, 0, 255), "%d", game.countdown);
		if (game.fade < game.fadetime && game.countdown == game.countdowndef) {
			game.flagfade = 2;
		}
		else if (game.countdown == game.countdowndef) {
			game.flagfade = 0;
			game.fade = 0;
		}
		/*
		if (result.result != 0) {
			game.flagfade = 1;
			StopSoundMem(bgm_game);
		}*/

		//ÉtÉFÅ[ÉhÉAÉEÉgé¿çs
		if (game.flagfade != 0) {
			game.fadeinout(game.flagfade);
		}

		//åàíÖ
		if (result.result != 0) {
			if (game.fade < game.fadetime) {
				int time = 10;
				if (game.fade <= time) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, game.fade * 255.0 / time);
				}
				else if (game.fade < time + 10) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
				}
				else {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / ((game.fade - (time + 10)) * 0.2 + 1));
				}
				if (game.remain > 0) {
					DrawStringToHandle(250, 150, "Game!", GetColorHSV(110, 255, 255), font_title);
				}
				else {
					DrawStringToHandle(250, 150, "Time!", GetColorHSV(110, 255, 255), font_title);
				}
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			}
			if (game.fade == game.fadetime) {
				result.reset();
				phase = phase_result;
			}
		}


		game.update();
		if ((keystate[KEY_INPUT_Q] == 1 || keystate[KEY_INPUT_Q] >= 20) && game.flagfade == 0) {
			game.count += 120;
		}
	}
	else {
		process_pause();
	}

	//ìGíeìÆçÏ
	if (game.count > 1) {
		move_shotenemy1();
	}
}

void process_oneplayer() {
	process_game(TRUE);
}

void process_result() {
	process_bg();
	process_me();
	if (result.flagfade != 1 || result.fade < result.fadetime - 1) {
		result.draw();
	}

	if (result.count <= result.fadetime) {
		result.flagfade = 2;
	}
	else {
		if (result.count == result.fadetime + 1) {
			result.flagfade = 0;
			PlaySoundMem(bgm_result, DX_PLAYTYPE_BACK);
		}
		if (keystate[KEY_INPUT_Z] == 1 && result.flagfade == 0) {
			result.flagfade = 1;
			PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
		}
		if (result.fade == result.fadetime) {
			title.reset();
			handi.reset();
			game.reset();
			effectmedeath.reset();
			result.reset();
			initialize();
			phase = phase_title;
		}
	}
	if (result.flagfade != 0) {
		result.fadeinout(result.flagfade);
	}
	result.update();
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);//Log.txtÇê∂ê¨ÇµÇ»Ç¢ÇÊÇ§Ç…ê›íË
	SetMainWindowText("Now Loading...");
	SetWindowIconID(101);
	ChangeWindowMode(TRUE);//îÒëSâÊñ Ç…ÉZÉbÉg
	SetGraphMode(SCREEN_X, SCREEN_Y, 32);//âÊñ ÉTÉCÉYéwíË
	if (DxLib_Init() == 1) { return -1; }//èâä˙âªÇ…é∏îséûÇ…ÉGÉâÅ[ÇìfÇ©ÇπÇƒèIóπ

	enemydef();
	loadsozai();

	SRand((unsigned)time(NULL));

	SetFontSize(18);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);

	SetMainWindowText("Wisp");

	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//ó†âÊñ è¡Ç∑
		SetDrawScreen(DX_SCREEN_BACK);//ï`âÊêÊÇó†âÊñ Ç…

		keyupdate();//ÉLÅ[ì¸óÕèÛë‘ÇçXêVÇ∑ÇÈÅié©çÏä÷êîÅj
		mouseupdate();//É}ÉEÉXì¸óÕèÛë‘ÇçXêVÇ∑ÇÈÅié©çÏä÷êîÅj
		GetMousePoint(&mouse[0], &mouse[1]);//É}ÉEÉXç¿ïWéÊìæ
		mouse_d[0] = mouse[0];
		mouse_d[1] = mouse[1];

		count++;

		switch (phase) {
		case phase_title:
			//É^ÉCÉgÉã
			process_title();
			break;
		case phase_handi:
			process_handi();
			break;
		case phase_game:
			process_game(FALSE);
			break;
		case phase_oneplayer:
			process_oneplayer();
			break;
		case phase_result:
			process_result();
			break;
		case -1:
			return 0;
			break;
		}

#if DEBUG
		DrawFormatString(100, 120, GetColorHSV(300, 255, 255), "motion = %d - %d", me.motion, me.frame);
		DrawFormatString(SCREEN_X - 150, SCREEN_Y - 30, GetColor(0, 0, 255), "phase = %d", phase);
		//DrawFormatString(300, 400, GetColor(0, 0, 255), "%d", me.motion);
#endif
		drawmouseicon();

		fade.draw();

		ScreenFlip();//ó†âÊñ Çï\âÊñ Ç…ÉRÉsÅ[
	}
	DxLib_End();

	return 0;
}