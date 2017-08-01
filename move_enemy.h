#pragma once

void move_enemy(Enemy *ene, Me *me) {
	switch ((*ene).type) {
	case ene_debug:
		//移動
		(*ene).vel[0] = 0;
		(*ene).vel[1] = 0;
		break;
	case ene_common:
		//移動
		if ((*ene).pos0[1] < center_y) {
			(*ene).vel[0] = 4 * cos(deg2rad((*ene).count * 1.5 + 90)) - 0.75;
			(*ene).vel[1] = 4 * sin(deg2rad((*ene).count * 2 + 90));
		}
		else {
			(*ene).vel[0] = 4 * cos(deg2rad((*ene).count * 1.5 + 90)) - 0.75;
			(*ene).vel[1] = -4 * sin(deg2rad((*ene).count * 2 + 90));
		}
		if ((*ene).pos[1] > downlimit - (*ene).size * 2) {
			(*ene).vel[1] = 0;
			(*ene).pos[1] = downlimit - (*ene).size * 2;
		}
		else if ((*ene).pos[1] < uplimit + (*ene).size * 2) {
			(*ene).vel[1] = 0;
			(*ene).pos[1] = uplimit + (*ene).size * 2;
		}
		//攻撃
		if ((*ene).count > 0) {//40
			//バラマキ
			if ((*ene).count % 30 == 20) {
				//PlaySoundMem(se_shot1, DX_PLAYTYPE_BACK);
				for (int i = 0; i < 2; i++) {
					shotenemy1[shotenemy1_del].reset();
					if (shotenemy1[shotenemy1_del].count == 0) {
						shotenemy1[shotenemy1_del].type = ene_common;
						shotenemy1[shotenemy1_del].setdef(*me, *ene);
						shotenemy1[shotenemy1_del].dir = RandRange(-180, 180);
						shotenemy1[shotenemy1_del].speed = 5;
						shotenemy1[shotenemy1_del].hue = ene_hue[(*ene).type];
					}
					shotenemy1_del++;
					shotenemy1_del %= shotenemy1_maxmem;
				}
			}
			//自機狙い
			if ((*ene).count % 45 == 0) {
				//PlaySoundMem(se_shot1, DX_PLAYTYPE_BACK);
				shotenemy1[shotenemy1_del].reset();
				if (shotenemy1[shotenemy1_del].count == 0) {
					shotenemy1[shotenemy1_del].type = ene_common;
					shotenemy1[shotenemy1_del].setdef(*me, *ene);
					shotenemy1[shotenemy1_del].dir = shotenemy1[shotenemy1_del].targetdir;
					shotenemy1[shotenemy1_del].speed = 7;
					shotenemy1[shotenemy1_del].hue = ene_hue[(*ene).type] - 20;
				}
				shotenemy1_del++;
				shotenemy1_del %= shotenemy1_maxmem;

			}
		}
		break;
	case ene_escape:
		//移動
		//(*ene).vel[0] = -3;
		//近接回避
		if (getdist((*me).pos, (*ene).pos) < 160 && (*me).pos[0] < (*ene).pos[0] && ((*me).motion == slashid && (*me).frame == 3)) {
			if ((*ene).pos[0] < rightlimit - (*ene).size * 2) {
				(*ene).vel[0] = 20;
				(*ene).vel[1] = 0;
			}
		}
		//右端設定
		if ((*ene).pos[0] > rightlimit - (*ene).size * 2) {
			(*ene).vel[0] = 0;
		}
		//回避から復帰x
		if ((*ene).vel[0] > -2) {
			(*ene).vel[0] -= 0.8;
		}
		//通常時
		else {
			//敵が下
			if ((*ene).pos[1] >= (*me).pos[1]) {
				if ((*ene).pos[1] < downlimit - (*ene).size * 2) {
					//回避から復帰y
					if (fabs((*ene).vel[1]) < 3.5) {
						(*ene).vel[1] += 0.2;
					}
					else {
						(*ene).vel[0] = -2;
						(*ene).vel[1] = 3.5;
					}
				}
				else {
					(*ene).vel[0] = -4;
					(*ene).vel[1] = 0;
				}
			}
			//敵が上
			else if ((*ene).pos[1] < (*me).pos[1]) {
				if ((*ene).pos[1] > uplimit + (*ene).size * 2) {
					//回避から復帰y
					if (fabs((*ene).vel[1]) < 3.5) {
						(*ene).vel[1] -= 0.2;
					}
					else {
						(*ene).vel[0] = -2;
						(*ene).vel[1] = -3.5;
					}
				}
				else {
					(*ene).vel[0] = -4;
					(*ene).vel[1] = 0;
				}
			}
			//上端切り返し
			if ((*me).pos[1] < uplimit + (*ene).size * 10 && (*ene).pos[1] <= center_y) {
				(*ene).vel[0] = -2;
				(*ene).vel[1] = 3;
			}
			//下端切り返し
			if ((*me).pos[1] > downlimit - (*ene).size * 10 && (*ene).pos[1] > center_y) {
				(*ene).vel[0] = -2;
				(*ene).vel[1] = -3;
			}
		}
		//攻撃
		break;
	case ene_rush:
		int startrush;
		startrush = 40;
		//移動
		if ((*ene).count == 0) {
			(*ene).dir = 180;
			(*ene).speed = -1.5;
		}
		else if ((*ene).count <= startrush) {
			(*ene).setdir((*me).pos, 2);//ホーミング(突進前)
		}
		else {
			(*ene).speed = 10;
			(*ene).setdir((*me).pos, 1.5);//ホーミング
		}
		(*ene).vel[0] = (*ene).speed * cos(deg2rad((*ene).dir));
		(*ene).vel[1] = (*ene).speed * sin(deg2rad((*ene).dir));
		//DrawFormatString(leftlimit, uplimit, GetColorHSV(0, 0, 255), "target:%.0f", (*ene).targetdir);
		//DrawFormatString(leftlimit, uplimit + 20, GetColorHSV(0, 0, 255), "dir:%.0f", (*ene).dir);
		if ((*ene).count > 10) {
			if ((*ene).pos[1] < uplimit - (*ene).size * 3 || (*ene).pos[1] > downlimit + (*ene).size * 3) {
				(*ene).dir = 180;
			}
		}
		//攻撃
		if ((*ene).count % 2 == 1 && (*ene).count >= startrush) {
			shotenemy1[shotenemy1_del].reset();

			if (shotenemy1[shotenemy1_del].count == 0) {
				shotenemy1[shotenemy1_del].type = ene_rush;
				shotenemy1[shotenemy1_del].setdef(*me, *ene);
				shotenemy1[shotenemy1_del].damage = 2;
				shotenemy1[shotenemy1_del].hitstop = 6;
				shotenemy1[shotenemy1_del].dir = shotenemy1[shotenemy1_del].targetdir + RandRange(-20, 20);
				shotenemy1[shotenemy1_del].speed = 10;
				shotenemy1[shotenemy1_del].hue = ene_hue[(*ene).type];
				shotenemy1[shotenemy1_del].saturation = ene_saturation[(*ene).type];
				shotenemy1[shotenemy1_del].value = ene_value[(*ene).type];
			}
			shotenemy1_del++;
			shotenemy1_del %= shotenemy1_maxmem;
		}

		break;

	case ene_ninja:
		//移動
		int requireninja;
		requireninja = (*ene).count % 100 >= 40 && (*ene).count % 100 <= 50;
		if (requireninja) {
			if ((*ene).count % 2 == 1) {
				double movepos[2];
				do {
					movepos[0] = RandRange(leftlimit + (*ene).size * 5, rightlimit - (*ene).size * 5);
					movepos[1] = RandRange(uplimit + (*ene).size * 5, downlimit - (*ene).size * 5);
				} while (getdist((*ene).pos, movepos) < 100 || getdist((*ene).pos, movepos) > 250);
				PlaySoundMem(se_ninjawarp, DX_PLAYTYPE_BACK);
				(*ene).pos[0] = movepos[0];
				(*ene).pos[1] = movepos[1];
			}
		}
		//攻撃
		if (requireninja) {
			if ((*ene).count % 2 == 1) {
				shotenemy1[shotenemy1_del].reset();

				if (shotenemy1[shotenemy1_del].count == 0) {
					shotenemy1[shotenemy1_del].type = ene_ninja;
					shotenemy1[shotenemy1_del].setdef(*me, *ene);
					shotenemy1[shotenemy1_del].damage = 1;
					shotenemy1[shotenemy1_del].hitstop = 20;
					shotenemy1[shotenemy1_del].dir = shotenemy1[shotenemy1_del].targetdir + RandRange(-5, 5);
					shotenemy1[shotenemy1_del].speed = 7;
					shotenemy1[shotenemy1_del].saturation = ene_saturation[(*ene).type];
					shotenemy1[shotenemy1_del].value = ene_value[(*ene).type] + 50;
				}
				shotenemy1_del++;
				shotenemy1_del %= shotenemy1_maxmem;

			}
		}
		break;

	case ene_shield:
		//移動
		if ((*ene).pos0[1] < center_y) {
			(*ene).vel[0] = 3 * cos(deg2rad((*ene).count * 1.2 + 90)) - 0.75;
			(*ene).vel[1] = 3 * sin(deg2rad((*ene).count * 1.7 + 90));
		}
		else {
			(*ene).vel[0] = 3 * cos(deg2rad((*ene).count * 1.2 + 90)) - 0.75;
			(*ene).vel[1] = -3 * sin(deg2rad((*ene).count * 1.7 + 90));
		}
		if ((*ene).pos[1] > downlimit - (*ene).size * 2) {
			(*ene).vel[1] = 0;
			(*ene).pos[1] = downlimit - (*ene).size * 2;
		}
		else if ((*ene).pos[1] < uplimit + (*ene).size * 2) {
			(*ene).vel[1] = 0;
			(*ene).pos[1] = uplimit + (*ene).size * 2;
		}

		//攻撃
		

		//押し出し効果
		double distmeshield;
		distmeshield = getdist((*ene).pos, (*me).pos);
		if (distmeshield < 60) {
			(*me).vel[0] += ((*me).pos[0] - (*ene).pos[0]) / distmeshield * 0.5;
			(*me).vel[1] += ((*me).pos[1] - (*ene).pos[1]) / distmeshield * 0.5;
		}

		break;
	case ene_boss:
		int random;
		random = RandRange(0, 150);
		//移動
		if (random == 150) {
			if ((*ene).pos[1] < center_y) {
				(*ene).vel[0] = RandRange(-3, 3);
				(*ene).vel[1] = 9 + RandRange(-3, 3);
			}
			else {
				(*ene).vel[0] = RandRange(-3, 3);
				(*ene).vel[1] = -9 + RandRange(-3, 3);
			}
		}
		else {
			(*ene).vel[0] *= 0.95;
			(*ene).vel[1] *= 0.95;
			if ((*ene).pos[0] > rightlimit - (*ene).size * 3 && (*ene).count > 0) {
				(*ene).vel[0] = -1;
			}
		}
		//攻撃
		if ((double)(*ene).hp / (*ene).hpmax > 0.7) {
			//3way
			if ((*ene).count > 20) {
				int shotnum = 8;
				for (int i = 0; i < shotnum; i++) {
					if ((*ene).count % 100 == 4 * i) {
						for (int j = 0; j < 3; j++) {
							shotenemy1[shotenemy1_del].reset();
							if (shotenemy1[shotenemy1_del].count == 0) {
								shotenemy1[shotenemy1_del].type = ene_boss;
								shotenemy1[shotenemy1_del].type_2 = 0;
								shotenemy1[shotenemy1_del].setdef(*me, *ene);
								shotenemy1[shotenemy1_del].damage = 5;
								shotenemy1[shotenemy1_del].hitstop = 3;
								shotenemy1[shotenemy1_del].dir = shotenemy1[shotenemy1_del].targetdir + 15 * (j - 1) + RandRange(-2 * i, 2 * i);
								shotenemy1[shotenemy1_del].speed = 5 - i * 0.35;
								shotenemy1[shotenemy1_del].hue = ene_hue[(*ene).type] + (2 - i) * 5;
								shotenemy1[shotenemy1_del].saturation = ene_saturation[(*ene).type];
								shotenemy1[shotenemy1_del].value = ene_value[(*ene).type];
							}
							shotenemy1_del++;
							shotenemy1_del %= shotenemy1_maxmem;

						}
					}
				}
			}
		}
		//乱射
		else if ((double)(*ene).hp / (*ene).hpmax > 0.4) {
			if ((*ene).count % 1 == 0) {
				for (int i = 0; i < 1; i++) {
					shotenemy1[shotenemy1_del].reset();
					if (shotenemy1[shotenemy1_del].count == 0) {
						shotenemy1[shotenemy1_del].type = ene_boss;
						shotenemy1[shotenemy1_del].type_2 = 1;
						shotenemy1[shotenemy1_del].setdef(*me, *ene);
						shotenemy1[shotenemy1_del].dir = RandRange(-180, 180);
						shotenemy1[shotenemy1_del].speed = 8;
						shotenemy1[shotenemy1_del].hue = ene_hue[(*ene).type];
						shotenemy1[shotenemy1_del].saturation = ene_saturation[(*ene).type];
						shotenemy1[shotenemy1_del].value = ene_value[(*ene).type];
					}
					shotenemy1_del++;
					shotenemy1_del %= shotenemy1_maxmem;

				}
			}
		}
		//wave
		else {
			int shotnum = 20;
			for (int i = 0; i < shotnum; i++) {
				if ((*ene).count % 80 == 2 * i) {
					for (int j = 0; j < 2; j++) {
						shotenemy1[shotenemy1_del].reset();
						if (shotenemy1[shotenemy1_del].count == 0) {
							shotenemy1[shotenemy1_del].type = ene_boss;
							shotenemy1[shotenemy1_del].type_2 = 2;
							shotenemy1[shotenemy1_del].setdef(*me, *ene);
							shotenemy1[shotenemy1_del].damage = 6;
							shotenemy1[shotenemy1_del].hitstop = 3;
							shotenemy1[shotenemy1_del].dir = shotenemy1[shotenemy1_del].targetdir + 5 * (shotnum / 2 - i) * (1 - 2 * j) + RandRange(-5, 5);
							shotenemy1[shotenemy1_del].speed = 3 + i * 0.2;
							shotenemy1[shotenemy1_del].hue = ene_hue[(*ene).type] + (2 - i) * 2;
							shotenemy1[shotenemy1_del].saturation = ene_saturation[(*ene).type];
							shotenemy1[shotenemy1_del].value = ene_value[(*ene).type];
						}
						shotenemy1_del++;
						shotenemy1_del %= shotenemy1_maxmem;

					}
				}
			}

		}
		break;
	case ene_bossg:
		random = RandRange(0, 150);
		//移動
		if (random == 150) {
			if ((*ene).pos[1] < center_y) {
				(*ene).vel[0] = RandRange(-3, 3);
				(*ene).vel[1] = 9 + RandRange(-3, 3);
			}
			else {
				(*ene).vel[0] = RandRange(-3, 3);
				(*ene).vel[1] = -9 + RandRange(-3, 3);
			}
		}
		else {
			(*ene).vel[0] *= 0.95;
			(*ene).vel[1] *= 0.95;
			if ((*ene).pos[0] > rightlimit - (*ene).size * 3 && (*ene).count > 0) {
				(*ene).vel[0] = -1;
			}
		}
		//攻撃
		if ((double)(*ene).hp / (*ene).hpmax > 0.4) {
			if ((*ene).count > 20) {
				int shotnum = 8;
				for (int i = 0; i < shotnum; i++) {
					if ((*ene).count % 60 == 2 * i) {
						for (int j = 0; j < 2; j++) {
							shotenemy1[shotenemy1_del].reset();
							if (shotenemy1[shotenemy1_del].count == 0) {
								shotenemy1[shotenemy1_del].type = ene_bossg;
								shotenemy1[shotenemy1_del].setdef(*me, *ene);
								shotenemy1[shotenemy1_del].hitstop = 3;
								shotenemy1[shotenemy1_del].damage = 2;
								shotenemy1[shotenemy1_del].dir = shotenemy1[shotenemy1_del].targetdir + 20 * (double)i / shotnum * (1 - 2 * j) + RandRange(-3, 3);
								shotenemy1[shotenemy1_del].speed = 3 + i * 0.5;
								shotenemy1[shotenemy1_del].hue = ene_hue[(*ene).type] + (2 - i) * 5;
								shotenemy1[shotenemy1_del].saturation = ene_saturation[(*ene).type];
								shotenemy1[shotenemy1_del].value = ene_value[(*ene).type];
							}
							shotenemy1_del++;
							shotenemy1_del %= shotenemy1_maxmem;

						}
					}
				}
			}
		}
		else {
			int shotnum1 = 50;
			for (int i = 0; i < shotnum1; i++) {
				if ((*ene).count % 120 == 2 * i) {
					for (int j = 0; j < 2; j++) {
						shotenemy1[shotenemy1_del].reset();
						if (shotenemy1[shotenemy1_del].count == 0) {
							shotenemy1[shotenemy1_del].type = ene_bossg;
							shotenemy1[shotenemy1_del].setdef(*me, *ene);
							shotenemy1[shotenemy1_del].hitstop = 3;
							shotenemy1[shotenemy1_del].damage = 4;
							shotenemy1[shotenemy1_del].dir = shotenemy1[shotenemy1_del].targetdir + 390 * (1 - (double)i / shotnum1) * (1 - 2 * j) + RandRange(-3, 3);
							shotenemy1[shotenemy1_del].speed = 3 + i * 0.2;
							shotenemy1[shotenemy1_del].hue = ene_hue[(*ene).type] + (2 - i) * 1.5;
							shotenemy1[shotenemy1_del].saturation = ene_saturation[(*ene).type];
							shotenemy1[shotenemy1_del].value = ene_value[(*ene).type];
						}
						shotenemy1_del++;
						shotenemy1_del %= shotenemy1_maxmem;

					}
				}
			}
			int shotnum2 = 5;
			for (int i = 0; i < shotnum2; i++) {
				if ((*ene).count % 120 == 70 - 2 * i) {
					for (int j = 0; j < 3; j++) {
						shotenemy1[shotenemy1_del].reset();
						if (shotenemy1[shotenemy1_del].count == 0) {
							shotenemy1[shotenemy1_del].type = ene_bossg;
							shotenemy1[shotenemy1_del].setdef(*me, *ene);
							shotenemy1[shotenemy1_del].hitstop = 3;
							shotenemy1[shotenemy1_del].dir = shotenemy1[shotenemy1_del].targetdir + 15 * (j - 1) + RandRange(-2 * i, 2 * i);
							shotenemy1[shotenemy1_del].speed = 6 - i * 0.5;
							shotenemy1[shotenemy1_del].hue = ene_hue[(*ene).type] + (2 - i) * 5;
							shotenemy1[shotenemy1_del].saturation = ene_saturation[(*ene).type];
							shotenemy1[shotenemy1_del].value = ene_value[(*ene).type];
						}
						shotenemy1_del++;
						shotenemy1_del %= shotenemy1_maxmem;

					}
				}
			}
		}
		break;
	case ene_core:
		(*ene).exist = flagsummon;
		(*ene).pos[0] = possummon[0];
		(*ene).pos[1] = possummon[1];
		break;
	}
}