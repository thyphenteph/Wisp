#pragma once

void oneplayer_summon(){
	if (game.count % 180 == 30) {
		int type;
		
		do {
			if (RandRange(0, 100) < 8) {
				type = RandRange(5, 6);
			}
			else {
				type = RandRange(0, 4);
			}
		} while (type == ene_escape);

		enemies[summonid].type = type;
		enemies[summonid].reset();
		enemies[summonid].exist = 1;
		double postest[2] = { rightlimit + 100, center_y + RandRange(-300, 300) };
		possummon[0] = postest[0];
		possummon[1] = postest[1];
		if (summonid < enemiesmax) {
			summonid++;
		}
		else {
			summonid = 1;
		}
		PlaySoundMem(se_summon, DX_PLAYTYPE_BACK);
	}
}


void process_summon() {
	//Summon
	if (game.countdown == 0 && game.remain > 0 && enemies[0].hp > 0 && me.hp > 0) {
#if DEBUG
		if (mousestate[MOUSE_INPUT_RIGHT] % 20 == 1) {
			enemies[summonid].setpos(mouse_d);
			enemies[summonid].type = -1;
			enemies[summonid].reset();
			enemies[summonid].exist = 1;
			if (summonid < enemiesmax) {
				summonid++;
			}
			else {
				summonid = 1;
			}
		}
#endif

		if (mouse[0] > leftlimit && mouse[0] < rightlimit && mouse[1] > uplimit && mouse[1] < downlimit || flagsummon == 1) {
			//召喚継続フレーム数
			if (mousestate[MOUSE_INPUT_LEFT] > 0) {
				if (core.summon >= ene_gauge[summontype]) {
					summonmouse++;
				}
				else {
					summonmouse = 1;
				}
			}
			else {
				summonmouse = 0;
			}

			//召喚中
			if (summonmouse > 0 && summonmouse < ene_summonframe[summontype]) {
				if (mousestate[MOUSE_INPUT_LEFT] == 1) {
					enemies[0].type = ene_core;
					PlaySoundMem(se_summoncharge, DX_PLAYTYPE_BACK);
				}
				if (mousestate[MOUSE_INPUT_LEFT] >= 1) enemies[0].exist = 1;
				if (summonalpha < 170) {
					summonalpha += 20;
				}
				flagsummon = 1;
				enemies[0].invincible = FALSE;
			}
			//召喚完了
			if (summonmouse == ene_summonframe[summontype] && core.summon >= ene_gauge[summontype]) {
				enemies[summonid].type = summontype;
				enemies[summonid].reset();
				enemies[summonid].exist = 1;
				core.summon -= ene_gauge[enemies[summonid].type];
				if (summonid < enemiesmax) {
					summonid++;
				}
				else {
					summonid = 1;
				}
				PlaySoundMem(se_summon, DX_PLAYTYPE_BACK);
				flagsummon = 0;
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, summonalpha);
			DrawCircleBlur(possummon[0], possummon[1], 40, gra_summon[summontype]);
			DrawCircleBlur(possummon[0], possummon[1], 40 * (summonmouse / (ene_summonframe[summontype] + 0.01)), gra_summon[summontype]);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		summonalpha *= 0.8;
		if (summonalpha < 10) {
			flagsummon = 0;
		}
		//召喚完了時の波紋
		if (enemies[summonid - 1].exist == 1 && enemies[summonid - 1].count < 10 && summonid - 1 != 0) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, summonalpha * 1.2);
			DrawCircleBlur(enemies[summonid - 1].pos[0], enemies[summonid - 1].pos[1], enemies[summonid - 1].count * enemies[summonid - 1].size, gra_summon[enemies[summonid - 1].type]);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			double distmeene = getdist(enemies[summonid - 1].pos, me.pos);
			//召喚終了時押し出し
			if (distmeene < enemies[summonid - 1].count * enemies[summonid - 1].size) {
				me.vel[0] += (me.pos[0] - enemies[summonid - 1].pos[0]) / distmeene *(enemies[summonid - 1].size / 10.0);
				me.vel[1] += (me.pos[1] - enemies[summonid - 1].pos[1]) / distmeene *(enemies[summonid - 1].size / 10.0);
				//DrawFormatString(leftlimit, uplimit, GetColorHSV(0, 0, 255), "AAAA");
			}
		}

		//召喚点押し出し効果
		double distmecore = getdist(enemies[0].pos, me.pos);
		if (distmecore < 80) {
			me.vel[0] += (me.pos[0] - enemies[0].pos[0]) / distmecore;
			me.vel[1] += (me.pos[1] - enemies[0].pos[1]) / distmecore;
		}

		//マウス押し出し効果
		double distmemouse = getdist(mouse_d, me.pos);
		if (distmemouse < 30 && enemies[0].exist == 1) {
			me.vel[0] += (me.pos[0] - mouse_d[0]) / distmemouse * 1.0;
			me.vel[1] += (me.pos[1] - mouse_d[1]) / distmemouse * 1.0;
			me.exp++;
		}

		//召喚してない時
		if (flagsummon == 0) {
			StopSoundMem(se_summoncharge);
			enemies[0].invincible = TRUE;
		}
	}

}

void process_enemy() {
	int hitlaser[enemiesmax];

	//存在する敵の数
	enemiesnum = 0;
	for (int i = 0; i < enemiesmax; i++) {
		if (enemies[i].exist == 1) {
			enemiesnum++;
		}
	}

	//敵弾ダミー生成
	if (game.count == 1) {
		for (int i = 0; i < shotenemy1_maxmem && shotenemy1.size() < shotenemy1_maxmem; i++) {
			shotenemy1.push_back(dummyenemy1);
			shotenemy1[i].delflag = TRUE;
			shotenemy1[i].vanishcount = 15;
		}
	}

#if DEBUG
	DrawFormatString(100, 100, GetColorHSV(20, 255, 255), "%d", shotenemy1.size());
#endif

	//Summon
	if (flagsummon == 0 && enemies[summonid - 1].count > 30 || mousestate[MOUSE_INPUT_LEFT] == 1) {
		possummon[0] = mouse[0];
		possummon[1] = mouse[1];
		if (mouse[0] < rightlimit - 250) {
			possummon[0] = rightlimit - 250;
		}
		if (mouse[0] > rightlimit - 30) {
			possummon[0] = rightlimit - 30;
		}
		if (mouse[1] < uplimit + 30) {
			possummon[1] = uplimit + 30;
		}
		if (mouse[1] > downlimit - 30) {
			possummon[1] = downlimit - 30;
		}
	}

	for (int i = 0; i < enemiesmax; i++) {//i: enemiesの数
		if (enemies[i].exist == 1) {
			int start = 60;
			if (enemies[i].type == ene_rush) {
				start = 20;
			}
			if (enemies[i].vanishcount == 0) {
				if (enemies[i].count <= start) {
					enemies[i].invincible = TRUE;
				}
				else {
					enemies[i].invincible = FALSE;
					{
						//slashとの判定
						/*
						if (slash.canhit[i] == 1) {
							if (slash.hitenemy(enemies[i]) == 1) {
								me.hitstop = 10;
								enemies[i].hitstop = 10;
								PlaySoundMem(se_slashhit, DX_PLAYTYPE_BACK);
								slash.canhit[i] = 0;
								if (enemies[i].hp > slash.damage) {
									enemies[i].hp -= slash.damage;
								}
								else {
									enemies[i].hp = 0;
								}
								hitdamagenum[0][i].reset();
								hitdamagenum[0][i].exist = 1;
								hitdamagenum[0][i].setdamage(slash.damage);
							}
						}*/

						//shot1との判定
						/*
						for (int j = 0; j < shot1.size(); j++) {

							if (shot1[j].hitenemy(enemies[i]) == 1 && shot1[j].vanishcount == 0) {
								if (enemies[i].type == ene_shield) {
									PlaySoundMem(se_shield, DX_PLAYTYPE_BACK);
								}
								else {
									enemies[i].hitstop = 3;
									if (enemies[i].hp > shot1[j].damage) {
										enemies[i].hp -= shot1[j].damage;
									}
									else {
										enemies[i].hp = 0;
									}
									hitdamagenum[j][i].reset();
									hitdamagenum[j][i].exist = 1;
									hitdamagenum[j][i].setdamage(shot1[j].damage);
								}
							}
						}*/

						//shot2との判定
						/*
						for (int j = 0; j < shot2.size(); j++) {
							if (shot2[j].hitenemy(enemies[i]) == 1 && shot2[j].vanishcount == 0) {
								if (enemies[i].type == ene_shield) {
									PlaySoundMem(se_shield, DX_PLAYTYPE_BACK);
								}
								else {
									enemies[i].hitstop = 3;
									if (enemies[i].hp > shot2[j].damage) {
										enemies[i].hp -= shot2[j].damage;
									}
									else {
										enemies[i].hp = 0;
									}
									hitdamagenum[j][i].reset();
									hitdamagenum[j][i].exist = 1;
									hitdamagenum[j][i].setdamage(shot2[j].damage);
								}
							}
						}*/

						//shot3との判定
						/*
						for (int j = 0; j < shot3.size(); j++) {
							if (shot3[j].hitenemy(enemies[i]) == 1 && shot3[j].canhit[i] == 1) {
								enemies[i].hitstop = 7;
								shot3[j].canhit[i] = 0;
								if (enemies[i].hp > shot3[j].damage) {
									enemies[i].hp -= shot3[j].damage;
								}
								else {
									enemies[i].hp = 0;
								}
								if (shot3[j].vanishcount == 0) {
									hitdamagenum[j][i].reset();
									hitdamagenum[j][i].exist = 1;
									hitdamagenum[j][i].setdamage(shot3[j].damage);
								}
								else {
									hitdamagenum[(j + 25) % 50][i].reset();
									hitdamagenum[(j + 25) % 50][i].exist = 1;
									hitdamagenum[(j + 25) % 50][i].setdamage(shot3[j].damage);
								}
							}
						}*/

						//shot4との判定
						/*
						for (int j = 0; j < shot4.size(); j++) {
							//判定
							if (shot4[j].hitenemy(enemies[i]) == 1 && shot4[j].canhit[i] == 1) {
								if (shot4[j].count < shot4[j].laserframe) {//直撃
									enemies[i].hitstop = 3;
									for (int k = 0; k < enemiesmax; k++) {
										shot4[j].canhit[k] = 0;
									}
									hitdamagenum[j][i].reset();
									hitdamagenum[j][i].exist = 1;
									hitdamagenum[j][i].setdamage(shot4[j].damage);
								}
								else {//レーザー
									enemies[i].hitstop = 0;//ヒット処理
									shot4[j].canhit[i] = 0;
								}
								if (enemies[i].hp > shot4[j].damage) {
									enemies[i].hp -= shot4[j].damage;
								}
								else {
									enemies[i].hp = 0;
								}
								hitdamagenum[j][i].reset();
								hitdamagenum[j][i].exist = 1;
								hitdamagenum[j][i].setdamage(shot4[j].damage);
							}
						}*/
					}
				}
			}
			//exp処理
			if (enemies[i].vanishcount == enemies[i].vanishend) {
				if (enemies[i].hp == 0 && me.shotlevel == 1) {
					me.exp += enemies[i].exp;
				}
			}

			//本体
			if (i != 0) {//一般敵
				int beforestart[enemiesmax];
				if (enemies[i].count < start && enemies[i].count % 3 == 1) {
					beforestart[i] = 0;
				}
				else {
					beforestart[i] = 1;
				}
				//本体
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180 * (enemies[i].vanishend - enemies[i].vanishcount) / enemies[i].vanishend * beforestart[i]);
				for (int j = 0; j < 4; j++) {
					if (enemies[i].type == ene_debug) {
						DrawCircle(enemies[i].pos[0], enemies[i].pos[1], (10 + 3 * sin(deg2rad(5 * enemies[i].count)) - 2 * j) * enemies[i].size / 25, GetColorHSV(0, 0, 255), 1);
					}
					else {
						DrawCircle(enemies[i].pos[0], enemies[i].pos[1], (10 + 3 * sin(deg2rad(5 * enemies[i].count)) - 2 * j) * enemies[i].size / 25, GetColorHSV(ene_hue[enemies[i].type], ene_saturation[enemies[i].type], ene_value[enemies[i].type]), 1);
					}
				}
				for (int j = 1; j <= 5; j++) {
					unsigned int color;
					if (enemies[i].type == ene_debug) {
						color = GetColorHSV(0, 0, 255);
					}
					else if (enemies[i].type == ene_ninja || enemies[i].type == ene_shield) {
						color = GetColorHSV(ene_hue[enemies[i].type] + 30 * sin(deg2rad(5 * enemies[i].count)), ene_saturation[enemies[i].type], ene_value[enemies[i].type] * (5 - j) / 5);
					}
					else {
						color = GetColorHSV(ene_hue[enemies[i].type] + 30 * sin(deg2rad(5 * enemies[i].count)), ene_saturation[enemies[i].type] * (5 - j) / 5, ene_value[enemies[i].type] * (5 - j) / 5);
					}
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50 * j * (enemies[i].vanishend - enemies[i].vanishcount) / enemies[i].vanishend / 2 * beforestart[i]);
					DrawCircle(enemies[i].pos[0], enemies[i].pos[1], (10 + 3 * sin(deg2rad(5 * enemies[i].count))) * enemies[i].size / 20, color, 0, 10 - 1.8 * j);
				}
				//シールド
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180 * (enemies[i].vanishend - enemies[i].vanishcount) / enemies[i].vanishend * beforestart[i]);
				if (enemies[i].type == ene_shield && enemies[i].count % 3 == 1 && enemies[i].hitstop == 0 && enemies[i].vanishcount == 0) {
					DrawCircleBlur(enemies[i].pos[0], enemies[i].pos[1], enemies[i].size * shieldsize, gra_eneshieldshield);
				}

				//周囲エフェクト処理
				for (int j = 0; j < enemies[i].type + 1; j++) {
					surround_ene[i][j].pos[0] = 20 * cos(deg2rad((7 + j) * enemies[i].count)) * enemies[i].size / 20;
					surround_ene[i][j].pos[1] = 20 * sin(deg2rad(1.05*(7 + j) * enemies[i].count)) * enemies[i].size / 20;
					if (enemies[i].hitstop == 0) {
						surround_ene[i][j].sethistory();
					}
					surround_ene[i][j].update();
				}
				//周囲エフェクト描画
				for (int j = 0; j < enemies[i].type + 1; j++) {
					if (j % 5 == 0) {
						for (int k = 20; k >= 1; k--) {
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, (255 - 12 * k) * (enemies[i].vanishend - enemies[i].vanishcount) / enemies[i].vanishend * beforestart[i]);
							DrawLine(enemies[i].pos[0] + surround_ene[i][j].history[0][k], enemies[i].pos[1] + surround_ene[i][j].history[1][k],
								enemies[i].pos[0] + surround_ene[i][j].history[0][k - 1], enemies[i].pos[1] + surround_ene[i][j].history[1][k - 1],
								GetColorHSV(ene_hue[enemies[i].type] + 6 * j, ene_saturation[enemies[i].type], ene_value[enemies[i].type]), 2);
						}
					}
					for (int k = 1; k <= 4; k++) {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50 * k * (enemies[i].vanishend - enemies[i].vanishcount) / enemies[i].vanishend * beforestart[i]);
						DrawCircle(enemies[i].pos[0] + surround_ene[i][j].pos[0], enemies[i].pos[1] + surround_ene[i][j].pos[1], 5 - k,
							GetColorHSV(ene_hue[enemies[i].type] + 6 * j, ene_saturation[enemies[i].type], ene_value[enemies[i].type]), 1);
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
					}
				}
				//残像
				if (enemies[i].type == ene_debug) {
					if (enemies[i].count > 1) {
						for (int j = 9; j > 0; j--) {
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200 * (10 - j) / 10.0 * (20.0 - enemies[i].vanishcount) / 20 * beforestart[i]);
							DrawLine(enemies[i].history[j][0] - j * 8, enemies[i].history[j][1], enemies[i].history[j - 1][0] - (j - 1) * 8, enemies[i].history[j - 1][1], GetColorHSV(0, 0, 255), (10 - j) / 1.0 * enemies[i].size / 20);
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
						}
					}
				}
				else {
					if (enemies[i].count > 1) {
						for (int j = 9; j > 0; j--) {
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200 * (10 - j) / 10.0 * (20.0 - enemies[i].vanishcount) / 20 * beforestart[i]);
							DrawLine(enemies[i].history[j][0] - j * 8, enemies[i].history[j][1], enemies[i].history[j - 1][0] - (j - 1) * 8, enemies[i].history[j - 1][1], ene_color[enemies[i].type], (10 - j) / 1.0 * enemies[i].size / 20);
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
						}
					}
				}
			}

			//処理
			//死亡or左端処理
			if (enemies[i].vanishcount > enemies[i].vanishend || enemies[i].pos[0] < leftlimit - 50) {
				if (enemies[i].pos[0] < leftlimit - 50 && enemies[i].hp > 0) {//左端到達	
					core.summon += ene_exp[enemies[i].type];
					PlaySoundMem(se_summonleftlimit, DX_PLAYTYPE_BACK);
					//エフェクト
					left[i].sethandle(gra_left, leftlen);
					left[i].setpos(leftlimit + 140, enemies[i].pos[1]);
					left[i].setsize(300);
					left[i].setangle(0);
					left[i].start();
				}
				enemies[i].exist = 0;
				//死亡に関してはmainに書いてある
			}
			//移動関連
			if (enemies[i].vanishcount == 0 && enemies[i].hitstop == 0) {
				move_enemy(&enemies[i], &me);
			}
			enemies[i].setpos(possummon);
			//毎フレームやるやつ
			enemies[i].update();
		}
		else {//Core
			enemies[i].pos[0] = SCREEN_X;
			enemies[i].pos[1] = SCREEN_Y * 10;
		}
		//エフェクト描画
		left[i].draw();
	}

	/*
	//shot4ヒットエフェクト
	for (int i = 0; i < enemiesmax; i++) {
		for (int j = 0; j < shot4.size(); j++) {
			if (shot4[j].count == shot4[j].laserframe && enemies[i].vanishcount == 0) {
				for (int k = 0; k < shot4hitnum; k++) {
					shot4hit[i][k].reset();
					//DrawFormatString(leftlimit, uplimit + 20 * i, GetColorHSV(0, 255, 255), "reset");
				}
			}
			if (hitdamagenum[j][i].exist == 1 && shot4[j].changed == 1
				&& shot4[j].vanishcount < 20 && enemies[i].vanishcount <= 20) {
				for (int k = 0; k < shot4hitnum; k++) {
					if (shot4[j].count > shot4[j].laserframe) {
						shot4hit[i][k].setvel();
						shot4hit[i][k].setpos(enemies[i].pos);
						shot4hit[i][k].update();
					}
					if (shot4hit[i][k].count >= 30) {
						shot4hit[i][k].radius = 0.1;
					}
					if (shot4hit[i][k].radius >= 1) {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, shot4hit[i][k].alpha);
						DrawCircleBlur(shot4hit[i][k].pos[0], shot4hit[i][k].pos[1], shot4hit[i][k].radius, gra_shot4hit);
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
					}
					else {
						shot4hit[i][k].reset();
					}
				}
			}
		}
	}*/

	//Summon
	if (phase == phase_game) {
		process_summon();
	}
	else if (phase == phase_oneplayer) {
		oneplayer_summon();
	}
}
