#pragma once

void attackslash() {
	//モーション切り替え
	if (phase != phase_title) {
		//VSモード
		if (game.countdown == 0 && game.remain > 0) {
			if (keystate[KEY_INPUT_Z] == 1 && me.motion != slashid && me.motion != breakshotid && me.hp > 0) {
				me.motion = slashid;
				me.frame = 0;
				slash.reset();
			}
		}
		//1Pモード
		if (oneplayer.countdown == 0 && oneplayer.remain > 0) {
			if (keystate[KEY_INPUT_Z] == 1 && me.motion != slashid && me.motion != breakshotid && me.hp > 0) {
				me.motion = slashid;
				me.frame = 0;
				slash.reset();
			}
		}
	}
	returnmotion(slashid);

	//処理
	if (me.hitstop == 0) {
		slash.setpos();
		slash.hitpos[0] = me.pos[0] + slash.offset + slash.bodysize * 6 * cos(deg2rad(slash.angle));
		slash.hitpos[1] = me.pos[1] + slash.bodysize * 6 * sin(deg2rad(slash.angle));
		slash.sethistory(me);
	}
	slash.update();
	//モーション・描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	if (me.motion == slashid) {
		//残像描画
		/*
		for (int i = 0; i < 15; i++) {
			DrawFormatString(leftlimit, uplimit + 30 * (i+1), GetColor(255, 255, 255), "(%3.0f, %3.0f), (%3.0f, %3.0f)",
				slash.history[0][0][i], slash.history[0][1][i], slash.history[1][0][i], slash.history[1][1][i]);
		}*/
		int attackstart = 10;
		for (int j = 14; j > 0; j--) {
			double alpha;
			for (int i = 0; i < 10; i++) {
				double a = 1;
				if (me.frame < attackstart) {
					alpha = me.frame;
				}
				else if (me.frame >= attackstart && me.frame < attackstart + 16) {
					alpha = 50 - 10 * j + 10 * i;
				}
				else {
					alpha = 50 - 10 * j + 10 * i - (me.frame - 36) * 12;
				}
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
				DrawQuad(slash.history[0][0][j] + a * i, slash.history[0][1][j] + a * i,
					slash.history[1][0][j] + a * i, slash.history[1][1][j] + i,
					slash.history[0][0][j - 1] - a * i, slash.history[0][1][j - 1] - a * i,
					slash.history[1][0][j - 1] - a * i, slash.history[1][1][j - 1] - a * i,
					GetColorHSV(230, 255 - i * 20, 255), 1);
			}

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		//本体描画
		/*
		DrawTriangle(me.pos[0] + slash.pos[0][0], me.pos[1] + slash.pos[0][1], me.pos[0] + slash.pos[1][0], me.pos[1] + slash.pos[1][1],
		me.pos[0] + slash.pos[2][0], me.pos[1] + slash.pos[2][1], GetColorHSV(230, 255, 255), 1);
		*/
		//判定・描画処理
		if (me.hitstop == 0) {
			if (me.frame >= attackstart && me.frame < attackstart + 3) {
				if (me.frame == attackstart) {
					PlaySoundMem(se_slash, DX_PLAYTYPE_BACK);
				}
				slash.angle += 50;
				slash.bodysize += 5;
				if (me.frame == attackstart + 1) {
					//slash.hitbox.set(TRUE, TRUE, slash.hitpos[0], slash.hitpos[1], slash.size, slash.damage, slash.hitstop,
					//	0, se_slashhit, FALSE);
					slash.hitbox.reset();
					slash.hitbox.setdirect(TRUE);
					slash.hitbox.setintercept(TRUE);
					slash.hitbox.setshield(FALSE);
					slash.hitbox.setproperty(slash.size, slash.damage, slash.hitstop);
					slash.hitbox.setlaser(FALSE, 0, 0);
					slash.hitbox.sethitse(se_slashhit);
					/*
					for (int j = 0; j < enemiesmax; j++) {
						slash.canhit[j] = 1;
					}*/
				}
			}
			else if (me.frame >= attackstart + 3 && me.frame < attackstart + 6) {
				slash.angle += 20;
				slash.bodysize -= 3;
			}
			else {
				slash.hitbox.del();
				/*
				for (int j = 0; j < enemiesmax; j++) {
					slash.canhit[j] = 0;
				}*/
				if (me.frame > attackstart + 10) {
					slash.bodysize *= 0.9;
				}
			}
		}

		//スタート時キラキラ
		for (int i = 0; i < 4; i++) {
			double pos[2] = { me.pos[0] + RandRange(-40, 40), me.pos[1] + RandRange(-40, 40) };
			if (me.frame == i) {
				slashstart[i].sethandle(gra_slashstart, kiralen);
				slashstart[i].setpos(pos[0], pos[1]);
				slashstart[i].setsize(20);
				slashstart[i].setangle(RandRange(-180,180));
				slashstart[i].start();
			}

			slashstart[i].setpos(pos[0], pos[1]);
			slashstart[i].draw();
		}
		//ヒットエフェクト
		for (int i = 0; i < enemiesmax; i++) {
			if (slash.hitbox.hittime[i] == 1) {
				slashhit[i].sethandle(gra_slashhit, slashhit1len);
				slashhit[i].setpos(enemies[i].pos[0], enemies[i].pos[1]);
				slashhit[i].setsize(400);
				slashhit[i].setangle(0);
				slashhit[i].start();
			}
			slashhit[i].draw();
			//DrawFormatString(leftlimit + 50 * (int)(i / 20), uplimit + 20 * (int)(i % 20), GetColorHSV(0, 255, 255), "%d", slashhit[i].count);
		}

		//攻撃判定更新
		if (slash.hitbox.exist) {
			slash.hitbox.setpos(slash.hitpos[0], slash.hitpos[1]);
			slash.hitbox.setsize(slash.size);
			slash.hitbox.judge(enemies, shotenemy1);
		}
		slash.hitbox.killenemy(75);
	}
}
