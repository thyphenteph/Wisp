#pragma once

void attackshot2() {
	//モーション切り替え
	if (me.shotlevel == 2 && phase != phase_title) {
		if (keystate[KEY_INPUT_X] >= 1 && me.motion == waitid && me.hp > 0) {
			me.motion = shot2id;
			me.exp -= 2;
			PlaySoundMem(se_shot2, DX_PLAYTYPE_BACK);
			for (int i = 0; i < 1; i++) {
				if (shot2.size() < shot2_maxmem) {
					shot2.push_back(dummy2);
				}
				else {
					shot2[shot2_del].reset();
					shot2_del++;
					shot2_del %= shot2_maxmem;
				}
			}
		}
	}
	returnmotion(shot2id);
	//処理・描画
	for (int i = 0; i < shot2.size(); i++) {
		int glowlen = 10;
		double glowsize = 10;
		double bodysize = 2.5;
		double sur = 1.8;
		int alpha = 170;
		int shortest_enemies = 9999;
		shot2[i].hue = 160 + hueperlevel;
		if (shot2[i].vanishcount <= glowlen) {
			//ホーミング対象決定
			double tarpos[2] = { -1000000, 0 };
			for (int j = 1; j < enemiesmax; j++) {
				if (enemies[j].exist == 1 && enemies[j].vanishcount == 0 && getdist(shot2[i].pos, enemies[j].pos) < shortest_enemies
					&& shot2[i].count >= 10 && enemies[j].type != ene_ninja) {
					shortest_enemies = getdist(shot2[i].pos, enemies[j].pos);
					tarpos[0] = enemies[j].pos[0];
					tarpos[1] = enemies[j].pos[1];
				}
			}
			shot2[i].setdir(tarpos);
			//処理
			if (shot2[i].count == 0) {
				shot2[i].setdef();
			}
			if (shot2[i].delflag == 0) {
				shot2[i].setvel();
				shot2[i].setpos(me.pos);
			}
			shot2[i].sethistory();
			shot2[i].update();
			//描画
			if ((phase == phase_game && game.countdown == 0) || (phase == phase_oneplayer /* && oneplayer.countdown == 0 */)) {
				//残像
				for (int j = glowlen; j > 0; j--) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,
						0.6 * (alpha - j * alpha / glowlen) * (1 - (double)shot2[i].vanishcount / glowlen));
					DrawCircle(shot2[i].history[0][j], shot2[i].history[1][j], shot2[i].size - 5 - 0.6 * j,
						GetColorHSV(shot2[i].hue, 255, 255), 1);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
				}
				//本体
				if (shot2[i].vanishcount == 0) {
					DrawCircleBlur(shot2[i].pos[0], shot2[i].pos[1], shot2[i].size, gra_shot2);
				}
				for (int j = 0; j < 5; j++) {
					double viewsize = shot2[i].size - j;
					if (shot2[i].vanishcount > 0 && shot2[i].hitbox.shielded) {//シールドされた時だけ
						viewsize *= (double)shot2[i].vanishcount / 2;
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, (255 - j * 50) * (1 - (double)shot2[i].vanishcount / glowlen *0.8));
						DrawCircle(shot2[i].pos[0], shot2[i].pos[1], viewsize, GetColorHSV(shot2[i].hue, 255, 255), 0);
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
					}
				}
			}
		}
		//攻撃判定
		if (shot2[i].count == 1) {
			//shot2[i].hitbox.set(FALSE, FALSE, shot2[i].pos[0], shot2[i].pos[1], shot2[i].size, shot2[i].damage, 3,
			//	0, se_shot2hit, FALSE);
			//shot2[i].hitbox.changeshield(TRUE);
			shot2[i].hitbox.reset();
			shot2[i].hitbox.setdirect(FALSE);
			shot2[i].hitbox.setintercept(FALSE);
			shot2[i].hitbox.setshield(TRUE);
			shot2[i].hitbox.setproperty(shot2[i].size, shot2[i].damage, 3);
			shot2[i].hitbox.setlaser(FALSE, 0, 0);
			shot2[i].hitbox.sethitse(se_shot2hit);
		}
		shot2[i].hitbox.setpos(shot2[i].pos[0], shot2[i].pos[1]);
		shot2[i].hitbox.setsize(shot2[i].size);
		shot2[i].hitbox.judge(enemies, shotenemy1);
		shot2[i].hitbox.killenemy(40);
		//ヒット時エフェクト
		if(!shot2[i].hitbox.shielded){
			if (shot2[i].hitbox.hitonce && phase != phase_title && shot2[i].vanishcount == 1) {
				shot2hit[i].sethandle(gra_shot2hit, shot2hitlen);
				shot2hit[i].setpos(shot2[i].pos[0], shot2[i].pos[1]);
				shot2hit[i].setsize(250);
				shot2hit[i].setangle(RandRange(-180, 180));
				shot2hit[i].start();
			}
		}
		shot2hit[i].draw();
		//攻撃判定削除
		if (shot2[i].hitbox.hitonce) {
			shot2[i].delflag = TRUE;
			shot2[i].hitbox.del();
		}
		//DrawFormatString(shot2[i].hitbox.pos[0], shot2[i].hitbox.pos[1], GetColorHSV(0, 255, 255), "%f", shot2[i].hitbox.size);


	}
}