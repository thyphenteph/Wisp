#pragma once

class Title {
public:
	int centerpos[2] = { SCREEN_X / 2, 175 };
	int count = 0;
	int flagfade = 0;
	const int fadetime = 40;
	int fade = 0;

	int select = 0;
	const int modepos[2][2] = { {500,350}, {500,400} };
	SingleGraph marker;


	void control() {
		//モード選択操作
		if (!flagfade) {
			if (keystate[KEY_INPUT_DOWN] == 1 || keystate[KEY_INPUT_UP] == 1) {
				select++;
				select %= 2;
				PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
			}
		}
		//決定
		if (keystate[KEY_INPUT_Z] == 1 && !flagfade) {
			flagfade = TRUE;
			PlaySoundMem(se_start, DX_PLAYTYPE_BACK);
		}
	}

	void draw() {
		if (count == 0) {
			for (int i = 0; i < 5; i++) {
				GraphFilter(gra_titlecircle[i], DX_GRAPH_FILTER_HSB, 1, 160 + hueperlevel * i, 0, 0);
			}
		}
		//周囲エフェクト処理
		for (int i = 0; i < 5; i++) {
			surround[i].pos[0] = 320 * cos(deg2rad((3 + 0.5*i) * count));
			surround[i].pos[1] = 120 * sin(deg2rad(1.05*(3 + 0.5*i) * count));
			if (me.hitstop == 0) {
				//surround[i].setpos();
				surround[i].sethistory();
			}
			surround[i].update();
		}
		//周囲エフェクト描画
		for (int i = 0; i < 5; i++) {
			for (int j = 19; j > 0; j--) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - 12 * j);
				DrawLine(centerpos[0] + surround[i].history[0][j], centerpos[1] + surround[i].history[1][j],
					centerpos[0] + surround[i].history[0][j - 1], centerpos[1] + surround[i].history[1][j - 1], GetColorHSV(190 + 6 * i, 255, 255), 2);
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			//DrawCircleBlur(centerpos[0] + surround[i].pos[0], centerpos[1] + surround[i].pos[1], 5, gra_titlecircle[i]);

			for (int j = 1; j <= 4; j++) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50 * j);
				DrawCircle(centerpos[0] + surround[i].pos[0], centerpos[1] + surround[i].pos[1], 8 - j, GetColorHSV(190 + 6 * i, 255, 255), 1);

			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		//文字"Wisp"
		for (int i = 0; i < 5; i++) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100 + i * 20);
			DrawStringToHandle(390 - 5 * i, 100 - 5 * i, "Wisp", GetColorHSV(260 - 20 * i + 20 * sin(deg2rad(count * 5)), 255, 255), font_title);
		}
		//文字"Press Z"
		for (int i = 0; i < 5; i++) {
			if (flagfade && count > fadetime) {//フェードイン/アウト中&&フェードイン終了
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, (100 + i * 20) * (double)(fadetime - fade) / fadetime);
			}
			else {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100 + i * 20);
			}
			DrawStringToHandle(450 + i, 475 + i, "Press Z", GetColorHSV(240, 120, 200 + 30 * sin(deg2rad(count * 10))), font_start);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		//モード選択
		for (int i = 0; i < 5; i++) {
			if (flagfade && count > fadetime && select == 0) {//フェードイン/アウト中&&フェードイン終了
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, (100 + i * 20) * (count % 15 > 7));
			}
			else {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100 + i * 20);
			}
			DrawStringToHandle(modepos[0][0] + i, modepos[0][1] + i, "VS Mode", GetColorHSV(240, 10 * i, 200 + 30 * sin(deg2rad(count * 10))), font_select);

			if (flagfade && count > fadetime && select == 1) {//フェードイン/アウト中&&フェードイン終了
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, (100 + i * 20) * (count % 15 > 7));
			}
			else {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100 + i * 20);
			}
			DrawStringToHandle(modepos[1][0] + i, modepos[1][1] + i, "1 P Mode (Trial )", GetColorHSV(240, 10 * i, 200 + 30 * sin(deg2rad(count * 10))), font_select);
			DrawStringToHandle(modepos[1][0] + i, modepos[1][1] + 30 + i, "", GetColorHSV(240, 10 * i, 200 + 30 * sin(deg2rad(count * 10))), font_select);
			if (i < 3) {
				//DrawStringToHandle(modepos[1][0] + 200 + i, modepos[1][1] + 8 + i, "Not Ready...", GetColorHSV(240, 10 * i, 100 + 30 * sin(deg2rad(count * 10))), font_timemini);
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		//モード選択マーカー
		int markerpos[2] = { modepos[select][0] - 55, modepos[select][1] + 20 };
		double markervelx = 2 * sin(deg2rad(count * 10));
		if (count == 0) {
			marker.reset();
			marker.set(gra_titleselect, markerpos[0], markerpos[1], 0.5, 90, TRUE, 30);
		}
		if (marker.pos[1] < markerpos[1] - 10) {
			marker.setvel(markervelx, 10);
		}
		else if (marker.pos[1] > markerpos[1] + 10) {
			marker.setvel(markervelx, -10);
		}
		else {
			marker.setvel(markervelx, 0);
			marker.pos[1] = markerpos[1];
		}
		marker.setpos();
		marker.draw(100);
		marker.update();
	}
	void fadeinout(int type) {//1:out 2:in
		if (type == 1) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * fade / fadetime);
		}
		else if (type == 2) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (fadetime - fade) / fadetime);
		}
		DrawBox(0, 0, SCREEN_X, SCREEN_Y, GetColorHSV(0, 0, 0), 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}

	void update() {
		count++;
#if DEBUG
		DrawFormatString(0, 0, GetColorHSV(0, 0, 255), "%d", fade);
		DrawFormatString(0, 20, GetColorHSV(0, 0, 255), "%d", flagfade);
#endif
		if (flagfade != 0) {
			if (fade < fadetime) {
				fade++;
			}
			else {
				fade = 0;
				flagfade = 0;
			}
		}
	}

	void reset() {
		count = 0;
		fade = 0;
		flagfade = 0;
	}
};
Title title;

class Handi {
public:
	int count = 0;
	int flagfade = 0;
	int fadetime = 40;
	int fade = 0;
	bool back = FALSE;

	void control() {
		if (flagfade == 0) {
			//ハンディキャップ変更
			if (fabs(handicap - 1.0) > 0.001) {
				if (keystate[KEY_INPUT_RIGHT] > 1 && handicap > 0.5) {
					handicap -= 0.01;
				}
				if (keystate[KEY_INPUT_LEFT] > 1 && handicap < 1.5) {
					handicap += 0.01;
				}
			}
			else {
				if (keystate[KEY_INPUT_RIGHT] == 1) {
					handicap -= 0.01;
				}
				if (keystate[KEY_INPUT_LEFT] == 1) {
					handicap += 0.01;
				}
			}
			//フェーズ移行
			//ゲームへ
			if (keystate[KEY_INPUT_Z] == 1 && flagfade == 0) {
				flagfade = 1;
				back = FALSE;
				PlaySoundMem(se_start, DX_PLAYTYPE_BACK);
			}
			//タイトルへ
			if (keystate[KEY_INPUT_X] == 1 && flagfade == 0) {
				flagfade = 1;
				back = TRUE;
				PlaySoundMem(se_cancel, DX_PLAYTYPE_BACK);
			}
		}
	}
	void draw() {
		//文字"Handicap"
		for (int i = 0; i < 5; i++) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100 + i * 20);
			DrawStringToHandle(420 + i, 100 + i, "Handicap", GetColorHSV(160, 120, 200 + 30 * sin(deg2rad(count * 10))), font_start);
		}
		//文字
		int height = 350;
		int left = 250;
		int right = SCREEN_X - 250;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawFormatString(left - 30, height - 30, GetColorHSV(200, 255, 200 + 30 * sin(deg2rad(count * 10))), "Wisp");
		DrawFormatString(right - 35, height - 30, GetColorHSV(20, 255, 200 + 30 * sin(deg2rad(count * 10))), "Core");
		//線本体
		DrawLine(left, height, right, height, GetColorHSV(0, 0, 200 + 30 * sin(deg2rad(count * 20))), 4);
		//目盛
		DrawLine(left, height - 10, left, height + 10, GetColorHSV(0, 0, 200 + 30 * sin(deg2rad(count * 20))), 2);
		DrawLine(SCREEN_X / 2, height - 10, SCREEN_X / 2, height + 10, GetColorHSV(0, 0, 200 + 30 * sin(deg2rad(count * 20))), 2);
		DrawLine(right, height - 10, right, height + 10, GetColorHSV(0, 0, 200 + 30 * sin(deg2rad(count * 20))), 2);
		//横に走るやつ
		int vel = 30;
		if (left + vel * (count % 60) - 20 < right) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
			DrawBox(getmax(left, left + vel * (count % 60) - 20), height + 2, getmin(right, left + vel * (count % 60) + 20), height - 2, GetColorHSV(200 - vel / 3.5 * (count % 60), 255, 255), 1);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		//指針
		double pointpos = (handicap - 1) * (right - SCREEN_X) * 2.8 + SCREEN_X / 2;
		DrawTriangle(pointpos, height + 15, pointpos - 6, height + 70, pointpos + 6, height + 70, GetColorHSV(0, 0, 200 + 30 * sin(deg2rad(count * 20))), 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128 * (1 + sin(deg2rad(count * 20))));
		if (handicap < 1.5) {
			DrawTriangle(pointpos - 60, height + 45, pointpos - 30, height + 40, pointpos - 30, height + 50, GetColorHSV(200, 80, 200 + 30 * sin(deg2rad(count * 20))), 1);
		}
		if (handicap > 0.5) {
			DrawTriangle(pointpos + 60, height + 45, pointpos + 30, height + 40, pointpos + 30, height + 50, GetColorHSV(20, 80, 200 + 30 * sin(deg2rad(count * 20))), 1);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

#if DEBUG
		DrawFormatString(0, 40, GetColorHSV(0, 0, 255), "%f", handicap);
#endif
	}

	void fadeinout(int type) {//1:out 2:in
		if (type == 1) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * fade / fadetime);
		}
		else if (type == 2) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (fadetime - fade) / fadetime);
		}
		DrawBox(0, 0, SCREEN_X, SCREEN_Y, GetColorHSV(0, 0, 0), 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}

	void update() {
		count++;
#if DEBUG
		DrawFormatString(0, 0, GetColorHSV(0, 0, 255), "%d", fade);
		DrawFormatString(0, 20, GetColorHSV(0, 0, 255), "%d", flagfade);
#endif
		if (flagfade != 0) {
			if (fade < fadetime) {
				fade++;
			}
			else {
				fade = 0;
				flagfade = 0;
			}
		}
	}

	void reset() {
		count = 0;
		fade = 0;
		flagfade = 0;
		back = FALSE;
	}
};
Handi handi;

class Game {
public:
	int count = 0;
	int flagfade = 0;
	int fadetime = 40;
	int fade = 0;
	const int countdowndef = 180;
	int countdown = countdowndef; //カウントダウンの残り時間
	int remain = 99;

	void drawtime() {
		if (remain > 0 && countdown == 0) {
			remain = (99 * 60 - count + countdowndef) / 60;
		}
		else {
			remain = 99;
		}

		DrawFormatStringToHandle(556 + 2, downlimit + 5 + 2, GetColorHSV(30 + remain * 2, 200, 180 + 20 * sin(deg2rad(count * 5))), font_timemini, "Time");
		DrawFormatStringToHandle(556, downlimit + 5, GetColorHSV(0, 0, 200 + 20 * sin(deg2rad(count * 5))), font_timemini, "Time");
		//DrawFormatStringToHandle(558, downlimit - 15, GetColorHSV(0, 0, 200 + 20 * sin(deg2rad(count * 5))), font_time, "%d", font0[3 * (count % 60) + 15]);
		DrawFormatStringToHandle(558, downlimit + 35, GetColorHSV(0, 0, 20 + 20 * sin(deg2rad(count * 5))), font_time, "%d", remain / 10);
		DrawFormatStringToHandle(596, downlimit + 35, GetColorHSV(0, 0, 20 + 20 * sin(deg2rad(count * 5))), font_time, "%d", remain % 10);

#if DEBUG
		DrawFormatString(0, 0, GetColorHSV(0, 0, 255), "%d", fade);
		DrawFormatString(0, 20, GetColorHSV(0, 0, 255), "%d", flagfade);
		DrawFormatString(0, 40, GetColorHSV(0, 0, 255), "%d", count - countdowndef);
#endif

		if (flagfade == 0) {
			if (countdown > 0) {
				DrawFormatStringToHandle(440, 150, GetColorHSV(160 + countdown / 2, 255, 220 + 20 * sin(deg2rad(count * 5))), font_title, "%d", countdown / 60 + 1);
				if (countdown % 60 == 59) {
					PlaySoundMem(se_countdown, DX_PLAYTYPE_BACK);
				}
			}
			else if (count - countdowndef < 50) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (1 - (count - countdowndef) / 50.0));
				DrawFormatStringToHandle(380, 150, GetColorHSV(20, 255, 220 + 20 * sin(deg2rad(count * 5))), font_title, "GO");
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
				if (count - countdowndef == 0) {
					PlaySoundMem(se_countdown, DX_PLAYTYPE_BACK);
					PlaySoundMem(se_countdownend, DX_PLAYTYPE_BACK);
				}
			}
		}
	}
	int getresult(Me me, Enemy core) {
		if (me.hp <= 0 && remain > 0) {
			return 2;
		}
		else if (core.hp <= 0 && remain > 0) {
			return 1;
		}
		else if (remain <= 0) {
			return 1;
		}
		else {
			return 0;
		}
	}

	void fadeinout(int type) {//1:out 2:in
		if (type == 1) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * fade / fadetime);
		}
		else if (type == 2) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (fadetime - fade) / fadetime);
		}
		DrawBox(0, 0, SCREEN_X, SCREEN_Y, GetColorHSV(0, 0, 0), 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}

	void update() {
		if (flagfade == 0) {
			count++;
			if (countdown > 0) {
				countdown--;
			}
		}

		if (flagfade != 0) {
			if (fade < fadetime) {
				fade++;
			}
			else {
				fade = 0;
				flagfade = 0;
			}
		}

		//マウス画面内固定
#if !DEBUG
		mousewindow(15);
#endif
	}

	void reset() {
		countdown = countdowndef;
		count = 0;
		fade = 0;
		flagfade = 0;
		remain = 99;
	}
};
Game game;

class Pause {
public:
	int count = 0;
	/*
	const int fadetime = 40;
	bool flagfade = FALSE;
	int fade = 0;
	*/

	void draw(int flag) {
		DrawBox(0, 0, SCREEN_X, SCREEN_Y, GetColorHSV(220, 120, 40), 1);
		//文字"Pause"
		if (flag == 1) {//Wisp
			for (int i = 0; i < 5; i++) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100 + i * 20);
				DrawStringToHandle(350 + i, 100 + i, "Wisp Pause", GetColorHSV(200, 180, 200 + 30 * sin(deg2rad(count * 10))), font_start);
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			DrawStringToHandle(SCREEN_X - 500, 20, "Back to title : C + SPACE", GetColorHSV(160, 50, 200 + 30 * sin(deg2rad(count * 10))), font_totitle);
		}
		else {//Core
			for (int i = 0; i < 5; i++) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100 + i * 20);
				DrawStringToHandle(350 + i, 100 + i, "Core Pause", GetColorHSV(20, 180, 200 + 30 * sin(deg2rad(count * 10))), font_start);
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			DrawStringToHandle(SCREEN_X - 500, 20, "Back to title : LEFT + RIGHT", GetColorHSV(0, 50, 200 + 30 * sin(deg2rad(count * 10))), font_totitle);
		}
	}

	void back(int flag) {
		//タイトルへ戻る
		if (flag == 1) {//Wisp
			if (keystate[KEY_INPUT_C] && keystate[KEY_INPUT_SPACE] == 1 && !fade.fadeflag) {
				fade.set(FADEOUT, 40, phase_title);
				fade.start();
				title.reset();
				initialize();
				PlaySoundMem(se_cancel, DX_PLAYTYPE_BACK);
			}
		}
		else {//Core
			if (mousestate[MOUSE_INPUT_LEFT] && mousestate[MOUSE_INPUT_RIGHT] == 1) {
				fade.set(FADEOUT, 40, phase_title);
				fade.start();
				title.reset();
				initialize();
				PlaySoundMem(se_cancel, DX_PLAYTYPE_BACK);
			}
		}
	}
	/*
	void fadeinout(int type) {//1:out 2:in
		if (type == 1) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * fade / fadetime);
		}
		else if (type == 2) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (fadetime - fade) / fadetime);
		}
		DrawBox(0, 0, SCREEN_X, SCREEN_Y, GetColorHSV(0, 0, 0), 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}*/

	void update() {
		count++;
	}

	void reset() {
		count = 0;
	}
};
Pause pause;

class Oneplayer :public Game {

};
Oneplayer oneplayer;

class Result {
public:
	int count = 0;
	int flagfade = 0;
	int fadetime = 40;
	int fade = 0;
	int result = 0;


	void draw() {
		//文字"Result"
		for (int i = 0; i < 5; i++) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100 + i * 20);
			if (result == 0) {
				DrawStringToHandle(400 + i, 200 + i, "Wow!Draw!", GetColorHSV(0, 0, 200 + 30 * sin(deg2rad(count * 10))), font_start);
			}
			else if (result == 1) {
				DrawStringToHandle(400 + i, 200 + i, "Wisp won!", GetColorHSV(160, 255, 220 + 30 * sin(deg2rad(count * 10))), font_start);
			}
			else {
				DrawStringToHandle(400 + i, 200 + i, "Core won!", GetColorHSV(20, 255, 220 + 30 * sin(deg2rad(count * 10))), font_start);
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	void fadeinout(int type) {//1:out 2:in
		if (type == 1) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * fade / fadetime);
		}
		else if (type == 2) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (fadetime - fade) / fadetime);
		}
		DrawBox(0, 0, SCREEN_X, SCREEN_Y, GetColorHSV(0, 0, 0), 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}

	void update() {
		count++;
#if DEBUG
		DrawFormatString(0, 0, GetColorHSV(0, 0, 255), "%d", fade);
		DrawFormatString(0, 20, GetColorHSV(0, 0, 255), "%d", flagfade);
#endif
		if (flagfade != 0) {
			if (fade < fadetime) {
				fade++;
			}
			else {
				fade = 0;
				flagfade = 0;
			}
		}
	}

	void reset() {
		count = 0;
		fade = 0;
		flagfade = 0;
	}
};
Result result;