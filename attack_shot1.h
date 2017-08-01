#pragma once

void attackshot1() {
	//モーション切り替え
	if (me.shotlevel == 1 && phase != phase_title) {
		//VSモード
		if (game.countdown == 0 && game.remain > 0) {
			if (keystate[KEY_INPUT_X] >= 1 && me.motion == waitid && me.hp > 0) {
				me.motion = shot1id;
				//me.exp--;
				PlaySoundMem(se_shot1, DX_PLAYTYPE_BACK);
				for (int i = 0; i < 1; i++) {
					if (shot1.size() < shot1_maxmem) {
						shot1.push_back(dummy1);
					}
					else {
						shot1[shot1_del].reset();
						shot1_del++;
						shot1_del %= shot1_maxmem;
					}
				}
			}
		}
		/*
		//1Pモード
		else if (oneplayer.countdown == 0 && oneplayer.remain > 0) {
			if (keystate[KEY_INPUT_X] >= 1 && me.motion == waitid && me.hp > 0) {
				me.motion = shot1id;
				//me.exp--;
				for (int i = 0; i < 1; i++) {
					PlaySoundMem(se_shot1, DX_PLAYTYPE_BACK);
					if (shot1.size() < shot1_maxmem) {
						shot1.push_back(dummy1);
					}
					else {
						shot1[shot1_del].reset();
						shot1_del++;
						shot1_del %= shot1_maxmem;
					}
				}
			}
		}*/
	}
	returnmotion(shot1id);

	//処理・描画
	for (int i = 0; i < shot1.size(); i++) {
		int glowlen = 10;
		double glowsize = 10;
		double bodysize = 2.5 * shot1[i].sizedef / 10;
		double sur = 1.8;
		int alpha = 170;
		if (shot1[i].vanishcount <= 30) {
			//処理
			if (shot1[i].count == 0) {
				shot1[i].setdef();
			}
			if (shot1[i].delflag == 0) {
				shot1[i].setvel();
				shot1[i].setpos(me.pos);
			}
			shot1[i].sethistory();
			shot1[i].update();
			//描画
			if ((phase == phase_game && game.countdown == 0) || (phase == phase_oneplayer /* && oneplayer.countdown == 0 */)) {
				//残像
				for (int j = glowlen; j > 0; j--) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0.6*(alpha - j * alpha / glowlen));
					DrawLine(shot1[i].history[0][j], shot1[i].history[1][j],
						shot1[i].history[0][j - 1], shot1[i].history[1][j - 1],
						GetColorHSV(shot1[i].hue, 255, 255), glowsize - j * glowsize / glowlen);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
				}
				//本体
				int p[4][2];
				p[0][0] = bodysize * 10 * cos(deg2rad(shot1[i].dir));//右
				p[0][1] = bodysize * 10 * sin(deg2rad(shot1[i].dir));
				p[1][0] = bodysize * 3 * cos(deg2rad(shot1[i].dir + 120));//下
				p[1][1] = bodysize * 3 * sin(deg2rad(shot1[i].dir + 120));
				p[2][0] = bodysize * 8 * cos(deg2rad(shot1[i].dir + 180));//左
				p[2][1] = bodysize * 8 * sin(deg2rad(shot1[i].dir + 180));
				p[3][0] = bodysize * 3 * cos(deg2rad(shot1[i].dir - 120));//上
				p[3][1] = bodysize * 3 * sin(deg2rad(shot1[i].dir - 120));
				int mex = shot1[i].pos[0];
				int mey = shot1[i].pos[1];
				if (shot1[i].vanishcount == 0) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
					DrawQuadrangle(mex + p[0][0] * sur, mey + p[0][1] * sur, mex + p[1][0] * sur, mey + p[1][1] * sur,
						mex + p[2][0] * sur, mey + p[2][1] * sur, mex + p[3][0] * sur, mey + p[3][1] * sur,
						GetColorHSV(shot1[i].hue, 255, 255), 1);//周囲
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
					DrawTriangle(mex, mey, mex + p[0][0], mey + p[0][1], //右下
						mex + p[1][0], mey + p[1][1], GetColorHSV(shot1[i].hue, 255, 200), 1);
					DrawTriangle(mex, mey, mex + p[1][0], mey + p[1][1], //左下
						mex + p[2][0], mey + p[2][1], GetColorHSV(shot1[i].hue, 255, 170), 1);
					DrawTriangle(mex, mey, mex + p[2][0], mey + p[2][1], //左上
						mex + p[3][0], mey + p[3][1], GetColorHSV(shot1[i].hue, 255, 220), 1);
					DrawTriangle(mex, mey, mex + p[3][0], mey + p[3][1], //右上
						mex + p[0][0], mey + p[0][1], GetColorHSV(shot1[i].hue, 255, 255), 1);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
				}
				else {

				}
			}
		}
		//攻撃判定
		if (shot1[i].count == 1) {
			//shot1[i].hitbox.set(FALSE, FALSE, shot1[i].pos[0], shot1[i].pos[1], shot1[i].size, shot1[i].damage, 2, 0, se_shot1hit, FALSE);
			shot1[i].hitbox.reset();
			shot1[i].hitbox.setdirect(FALSE);
			shot1[i].hitbox.setintercept(FALSE);
			shot1[i].hitbox.setshield(TRUE);
			shot1[i].hitbox.setproperty(shot1[i].size, shot1[i].damage, 2);
			shot1[i].hitbox.setlaser(FALSE, 0, 0);
			shot1[i].hitbox.sethitse(se_shot1hit);
		}
		shot1[i].hitbox.setpos(shot1[i].pos[0], shot1[i].pos[1]);
		shot1[i].hitbox.judge(enemies, shotenemy1);
		shot1[i].hitbox.killenemy(40);
		//ヒット時エフェクト
		if (shot1[i].hitbox.hitonce && phase != phase_title && shot1[i].vanishcount == 1) {
			shot1break[i].sethandle(gra_shot1break, glassbreaklen);
			shot1break[i].setpos(shot1[i].pos[0], shot1[i].pos[1]);
			shot1break[i].setsize(300);
			shot1break[i].setangle(RandRange(-180, 180));
			shot1break[i].start();
			//shield
			if (shot1[i].hitbox.shielded) {
				shot1breakcore[i].sethandle(gra_shot1breakcore, glassbreaklen);
				shot1breakcore[i].setpos(shot1[i].pos[0], shot1[i].pos[1]);
				shot1breakcore[i].setsize(300);
				shot1breakcore[i].setangle(shot1[i].dir);
				shot1breakcore[i].start();
			}
			//その他
			else {
				shot1hit[i].sethandle(gra_shot1hit, shot1hitlen);
				shot1hit[i].setpos(shot1[i].pos[0], shot1[i].pos[1]);
				shot1hit[i].setsize(400);
				shot1hit[i].setangle(shot1[i].dir + RandRange(-4, 4));
				shot1hit[i].start();
			}
		}
		//エフェクト描画
		{
			shot1break[i].draw();
			//シールドされた
			shot1breakcore[i].draw();
			//ヒットした
			shot1hit[i].draw();
		}

		if (shot1[i].hitbox.hitonce) {
			shot1[i].delflag = TRUE;
			shot1[i].hitbox.del();
		}
		//DrawFormatString(shot1[i].hitbox.pos[0], shot1[i].hitbox.pos[1], GetColorHSV(0, 255, 255), 
			//"%.0f, %d", shot1[i].hitbox.size, shot1[i].hitbox.exist);
	}
}