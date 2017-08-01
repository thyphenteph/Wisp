#pragma once

void attackshot4() {
	//モーション切り替え
	if (me.shotlevel == 4 && phase != phase_title) {
		if (keystate[KEY_INPUT_X] >= 1 && me.motion == waitid && me.hp > 0) {
			me.motion = shot4id;
			me.exp -= 4;
			for (int i = 0; i < 1; i++) {
				PlaySoundMem(se_shot4, DX_PLAYTYPE_BACK);
				if (shot4.size() < shot4_maxmem) {
					shot4.push_back(dummy4);
					dummy4.reset();
				}
				else {
					shot4[shot4_del].reset();
					shot4_del++;
					shot4_del %= shot4_maxmem;
				}
			}
		}
	}
	returnmotion(shot4id);
	//処理・描画
	for (int i = 0; i < shot4.size(); i++) {
		int glowlen = 20;
		double glowsize = 10;
		double bodysize = 2.5;
		double sur = 1.8;
		int alpha = 170;
		int shortest_enemies = 9999;
		if (shot4[i].vanishcount <= glowlen) {
			//ホーミング対象決定
			double tarpos[2];
			int targetid;
			do {
				targetid = RandRange(0, enemiesmax - 1);
				int sum = 0;//HP残ってる敵の数
				for (int j = 1; j < enemiesmax; j++) {
					if (enemies[j].hp > 0 && enemies[j].exist == 1 && enemies[j].type != ene_ninja) {
						sum++;
					}
				}
				//DrawFormatString(leftlimit, uplimit, GetColorHSV(0, 255, 255), "%d", sum);
				if (sum == 0) {
					targetid = -1;
					break;
				}
			} while (enemies[targetid].hp <= 0 || enemies[targetid].exist == 0);
			//targetid = 0;
			if (targetid >= 0) {
				tarpos[0] = enemies[targetid].pos[0];
				tarpos[1] = enemies[targetid].pos[1];
			}
			else {
				tarpos[0] = 1000000;
				tarpos[1] = SCREEN_Y / 2;
			}
			//DrawCircle(tarpos[0], tarpos[1], 5, GetColorHSV(0, 255, 255), 1);
			//処理
			if (shot4[i].count == 0) {
				shot4[i].setdef();
				shot4[i].dir = (keystate[KEY_INPUT_X] - 1) * 4 + 180 * (i % 2 == 0) - 90;
			}
			if (shot4[i].delflag == 0) {
				shot4[i].setvel();
				shot4[i].setpos(me.pos);
			}
			if (shot4[i].count == shot4[i].laserframe && shot4[i].canhit[0] == 1 && shot4[i].changed == 0) {
				shot4[i].changetolaser(tarpos);
				if (phase != phase_title) PlaySoundMem(se_shot4laser, DX_PLAYTYPE_BACK);
			}
			if (shot4[i].count > shot4[i].laserframe + 20) {
				shot4[i].reset();
			}
			shot4[i].update();
			//描画
			if ((phase == phase_game && game.countdown == 0) || (phase == phase_oneplayer /* && oneplayer.countdown == 0 */)) {
				//レーザー
				for (int a = 1; a > 0; a--) {
					int j = shot4[i].vanishcount;
					int kmax = 4;
					if (shot4[i].count > shot4[i].laserframe && shot4[i].changed == 1) {
						SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
						for (int k = kmax - 1; k >= 0; k--) {
							alpha = 220;
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0.6 * (alpha - j * alpha / glowlen));
							DrawLine(shot4[i].laserpos[0], shot4[i].laserpos[1],
								shot4[i].pos[0], shot4[i].pos[1],
								GetColorHSV(shot4[i].hue, 255, 255), (glowsize - j * glowsize / glowlen) * (k + 2) * 0.5);
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0.8 * (alpha - j * alpha / glowlen));
							DrawCircle(shot4[i].pos[0], shot4[i].pos[1], (glowsize - j * glowsize / glowlen) * (k + 2) * 0.5,
								GetColorHSV(shot4[i].hue, 255, 255), 1);
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
						}
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, 1.2 * (alpha - j * alpha / glowlen));
						DrawLine(shot4[i].laserpos[0], shot4[i].laserpos[1],
							shot4[i].pos[0], shot4[i].pos[1],
							GetColorHSV(shot4[i].hue, 0, 255), (glowsize - j * glowsize / glowlen));
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0.8 * (alpha - j * alpha / glowlen));
						for (int k = 0; k < 3; k++) {
							DrawCircle(shot4[i].pos[0], shot4[i].pos[1], (glowsize - j * glowsize / glowlen) * (0.6 + 0.15 * k),
								GetColorHSV(shot4[i].hue, 0, 255), 1);
						}
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
					}
				}
				//実体
				if (shot4[i].count < shot4[i].laserframe) {
					int p[4][2];
					p[0][0] = bodysize * 10 * cos(deg2rad(shot4[i].dir));//右
					p[0][1] = bodysize * 10 * sin(deg2rad(shot4[i].dir));
					p[1][0] = bodysize * 3 * cos(deg2rad(shot4[i].dir + 120));//下
					p[1][1] = bodysize * 3 * sin(deg2rad(shot4[i].dir + 120));
					p[2][0] = bodysize * 8 * cos(deg2rad(shot4[i].dir + 180));//左
					p[2][1] = bodysize * 8 * sin(deg2rad(shot4[i].dir + 180));
					p[3][0] = bodysize * 3 * cos(deg2rad(shot4[i].dir - 120));//上
					p[3][1] = bodysize * 3 * sin(deg2rad(shot4[i].dir - 120));
					int mex = shot4[i].pos[0];
					int mey = shot4[i].pos[1];
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha * 0.5 * (10 - 0.5*shot4[i].vanishcount) / 10);
					DrawQuadrangle(mex + p[0][0] * sur, mey + p[0][1] * sur, mex + p[1][0] * sur, mey + p[1][1] * sur,
						mex + p[2][0] * sur, mey + p[2][1] * sur, mex + p[3][0] * sur, mey + p[3][1] * sur,
						GetColorHSV(shot4[i].hue, 255, 255), 1);//周囲
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (10 - shot4[i].vanishcount) / 10);
					
					DrawTriangle(mex, mey, mex + p[0][0], mey + p[0][1], //右下
						mex + p[1][0], mey + p[1][1], GetColorHSV(shot4[i].hue, 255, 200), 1);
					DrawTriangle(mex, mey, mex + p[1][0], mey + p[1][1], //左下
						mex + p[2][0], mey + p[2][1], GetColorHSV(shot4[i].hue, 255, 170), 1);
					DrawTriangle(mex, mey, mex + p[2][0], mey + p[2][1], //左上
						mex + p[3][0], mey + p[3][1], GetColorHSV(shot4[i].hue, 255, 220), 1);
					DrawTriangle(mex, mey, mex + p[3][0], mey + p[3][1], //右上
						mex + p[0][0], mey + p[0][1], GetColorHSV(shot4[i].hue, 255, 255), 1);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
				}
			}
			//判定消去(レーザー消滅)
			/*
			if (shot4[i].vanishcount >= glowlen - 5) {
				for (int j = 0; j < enemiesmax; j++) {
					shot4[i].canhit[j] = 0;
				}
			}*/
		}

		//攻撃判定
		if (shot4[i].count == 1) {
			//shot4[i].hitbox.set(0, 1, shot4[i].pos[0], shot4[i].pos[1], shot4[i].size, shot4[i].damage, 3,
			//	0, se_shot1hit, 0);
			shot4[i].hitbox.reset();
			shot4[i].hitbox.setdirect(FALSE);
			shot4[i].hitbox.setintercept(TRUE);
			shot4[i].hitbox.setshield(FALSE);
			shot4[i].hitbox.setproperty(shot4[i].size, shot4[i].damage, 3);
			shot4[i].hitbox.setlaser(FALSE, 0, 0);
			shot4[i].hitbox.sethitse(se_shot1hit);
		}
		if (shot4[i].changed) {//レーザーに変形
			shot4[i].hitbox.setintercept(FALSE);
			shot4[i].hitbox.setlaser(TRUE, shot4[i].laserpos[0], shot4[i].laserpos[1]);
			shot4[i].hitbox.setproperty(shot4[i].size, shot4[i].damage, 0);
			shot4[i].hitbox.sethitse(0);
		}
		shot4[i].hitbox.setpos(shot4[i].pos[0], shot4[i].pos[1]);
		shot4[i].hitbox.judge(enemies, shotenemy1);
		if (!shot4[i].changed) {
			shot4[i].hitbox.killenemy(40);
		}
		else {
			shot4[i].hitbox.killenemy(80);
		}
		//判定消去(相殺)
		if (shot4[i].hitbox.interceptonce) {
			shot4[i].delflag = TRUE;
			shot4[i].hitbox.del();
		}
		//判定消去(直接)
		if (!shot4[i].changed && shot4[i].hitbox.hitonce) {
			shot4[i].delflag = TRUE;
			shot4[i].hitbox.del();
		}
		//判定消去(レーザー消滅)
		if (shot4[i].vanishcount >= glowlen - 5) {
			shot4[i].hitbox.del();
		}

		//ヒット時エフェクト
		for (int j = 0; j < enemiesmax; j++) {
			if (shot4[i].hitbox.hittime[j] == 1 && !shot4[i].hitbox.interceptonce) {
				//レーザーヒット
				shot4hit[i][j].sethandle(gra_shot4hit, shot4hitlen);
				shot4hit[i][j].setpos(enemies[j].pos[0], enemies[j].pos[1]);
				shot4hit[i][j].setsize(300);
				shot4hit[i][j].setangle(RandRange(-180, 180));
				shot4hit[i][j].start();
			}
			shot4hit[i][j].draw();

			//DrawFormatString(200 + 40*i, 100 + 20*j, GetColorHSV(310,255,255),"%d", shot4[i].hitbox.hittime[j]);
		}
	}
}