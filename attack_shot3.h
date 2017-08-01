#pragma once

void attackshot3() {
	//モーション切り替え
	if (me.shotlevel == 3 && phase != phase_title) {
		//VSモード
		if (game.countdown == 0 && game.remain > 0) {
			if (keystate[KEY_INPUT_X] == 1 && me.motion == shot3id && me.hp > 0) {
				if (shot3.size() < shot3_maxmem) {
					shot3[shot3.size() - 1].delflag = 1;
				}
				else {
					shot3[(shot3_del - 1 + shot3_maxmem) % shot3_maxmem].delflag = 1;
				}
			}
			if (keystate[KEY_INPUT_X] >= 1 && me.motion == waitid && me.hp > 0) {
				me.motion = shot3id;
				me.exp -= 10;
				PlaySoundMem(se_shot3, DX_PLAYTYPE_BACK);
				for (int i = 0; i < 2; i++) {
					if (shot3.size() < shot3_maxmem) {
						shot3.push_back(dummy3);
					}
					else {
						shot3[shot3_del].reset();
						shot3_del++;
						shot3_del %= shot3_maxmem;
					}
				}
			}
		}
		//1Pモード
		else if (oneplayer.countdown == 0 && oneplayer.remain > 0) {
			if (keystate[KEY_INPUT_X] >= 1 && me.motion == waitid && me.hp > 0) {
				me.motion = shot3id;
				me.exp -= 10;
				PlaySoundMem(se_shot3, DX_PLAYTYPE_BACK);
				for (int i = 0; i < 2; i++) {
					if (shot3.size() < shot3_maxmem) {
						shot3.push_back(dummy3);
					}
					else {
						shot3[shot3_del].reset();
						shot3_del++;
						shot3_del %= shot3_maxmem;
					}
				}
			}
		}
	}
	returnmotion(shot3id);

	//処理・描画
	for (int i = 0; i < shot3.size(); i++) {
		int glowlen = 15;
		double glowsize = 10;
		double bodysize = 2.5;
		double sur = 1.8;
		int alpha = 170;
		int shortest_enemies = 9999;
		shot3[i].hue = 160 + hueperlevel * 2;
		if (shot3[i].vanishcount <= glowlen + 5) {
			//処理
			if (shot3[i].count <= 1 ) {
				shot3[i].setdef(i % 2);
			}
			if (shot3[i].delflag == 0) {
				shot3[i].setvel();
				shot3[i].setpos(me.pos);
			}
			else {
				shot3[i].explosion();
				if ((phase == phase_game && game.countdown == 0) || (phase == phase_oneplayer /* && oneplayer.countdown == 0 */)) {
					for (int j = 0; j < 5; j++) {//爆発	
						if (shot3[i].vanishcount >= 10) {
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, (255 - 50 * j) - (shot3[i].vanishcount - 9) * 10);
						}
						DrawTriangle(shot3[i].pos[0] + RandRange(-shot3[i].size, shot3[i].size), shot3[i].pos[1] + RandRange(-shot3[i].size, shot3[i].size),
							shot3[i].pos[0] + RandRange(-shot3[i].size, shot3[i].size), shot3[i].pos[1] + RandRange(-shot3[i].size, shot3[i].size),
							shot3[i].pos[0] + RandRange(-shot3[i].size, shot3[i].size), shot3[i].pos[1] + RandRange(-shot3[i].size, shot3[i].size),
							GetColorHSV(shot3[i].hue, 255 - RandRange(0, 150), 255), 0);
						if (shot3[i].vanishcount < 10) {
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - 50 * j);
						}
						DrawCircle(shot3[i].pos[0], shot3[i].pos[1], shot3[i].size - 2 * j, GetColorHSV(shot3[i].hue, 255, 255), 0, 1);
					}
				}
				if (shot3[i].vanishcount >= glowlen) {
					for (int k = 0; k < enemiesmax; k++) {
						shot3[i].canhit[k] = 0;
					}
				}
			}
			shot3[i].sethistory();
			shot3[i].update();
			//描画
			if ((phase == phase_game && game.countdown == 0) || (phase == phase_oneplayer /* && oneplayer.countdown == 0 */)) {
				if (shot3[i].vanishcount == 1 && in_screen(shot3[i].pos)) {
					PlaySoundMem(se_shot3hit, DX_PLAYTYPE_BACK);
				}
				//残像
				for (int j = glowlen; j > 0; j--) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,
						0.6 * (alpha - j * alpha / glowlen) * (1 - (double)shot3[i].vanishcount / glowlen));
					DrawTriangle(shot3[i].history[0][j] + shot3[i].triglow[j].pos[0][0] * (1 - (double)j / glowlen) / (shot3[i].vanishcount + 1),
						shot3[i].history[1][j] + shot3[i].triglow[j].pos[0][1] * (1 - (double)j / glowlen) / (shot3[i].vanishcount + 1),
						shot3[i].history[0][j] + shot3[i].triglow[j].pos[1][0] * (1 - (double)j / glowlen) / (shot3[i].vanishcount + 1),
						shot3[i].history[1][j] + shot3[i].triglow[j].pos[1][1] * (1 - (double)j / glowlen) / (shot3[i].vanishcount + 1),
						shot3[i].history[0][j] + shot3[i].triglow[j].pos[2][0] * (1 - (double)j / glowlen) / (shot3[i].vanishcount + 1),
						shot3[i].history[1][j] + shot3[i].triglow[j].pos[2][1] * (1 - (double)j / glowlen) / (shot3[i].vanishcount + 1),
						GetColorHSV(shot3[i].hue, 255, 255), 0);

					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
				}
				//本体
				for (int j = 0; j < 5; j++) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - 50 * j);
					DrawTriangle(shot3[i].pos[0] + shot3[i].tri.pos[0][0] * (1 + 0.1 * j) / (shot3[i].vanishcount + 1),
						shot3[i].pos[1] + shot3[i].tri.pos[0][1] * (1 + 0.1 * j) / (shot3[i].vanishcount + 1),
						shot3[i].pos[0] + shot3[i].tri.pos[1][0] * (1 + 0.1 * j) / (shot3[i].vanishcount + 1),
						shot3[i].pos[1] + shot3[i].tri.pos[1][1] * (1 + 0.1 * j) / (shot3[i].vanishcount + 1),
						shot3[i].pos[0] + shot3[i].tri.pos[2][0] * (1 + 0.1 * j) / (shot3[i].vanishcount + 1),
						shot3[i].pos[1] + shot3[i].tri.pos[2][1] * (1 + 0.1 * j) / (shot3[i].vanishcount + 1),
						GetColorHSV(shot3[i].hue, 255, 255), 0);

					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
				}
			}
		}
		//攻撃判定
		if (shot3[i].count == 1) {
			//shot3[i].hitbox.set(0, 0, shot3[i].pos[0], shot3[i].pos[1], shot3[i].size, shot3[i].damage, 7,
			//	0, se_shot3hit, 0);
			shot3[i].hitbox.reset();
			shot3[i].hitbox.setdirect(FALSE);
			shot3[i].hitbox.setintercept(FALSE);
			shot3[i].hitbox.setshield(FALSE);
			shot3[i].hitbox.setproperty(shot3[i].size, shot3[i].damage, 7);
			shot3[i].hitbox.setlaser(FALSE, 0, 0);
			shot3[i].hitbox.sethitse(se_shot3hit);
		}
		shot3[i].hitbox.setpos(shot3[i].pos[0], shot3[i].pos[1]);
		shot3[i].hitbox.setsize(shot3[i].size * 1.25);
		shot3[i].hitbox.judge(enemies, shotenemy1);
		shot3[i].hitbox.killenemy(90);

		if (shot3[i].delflag && shot3[i].vanishcount == 1) {//爆発開始時
			//ダメージ変更
			shot3[i].hitbox.changedamage(12);
			//ヒットSE消去
			shot3[i].hitbox.changehitse(0);
			//攻撃判定復活
			for (int j = 0; j < enemiesmax; j++) {
				shot3[i].hitbox.canhit[j] = TRUE;
			}
		}
		if (shot3[i].hitbox.hitonce) {
			shot3[i].delflag = TRUE;
		}
		//DrawFormatString(shot3[i].hitbox.pos[0], shot3[i].hitbox.pos[1], GetColorHSV(0, 255, 255), "%f", shot3[i].hitbox.size);
		if (shot3[i].vanishcount > shot3[i].explosiontime) {
			shot3[i].hitbox.del();
		}
	}
}