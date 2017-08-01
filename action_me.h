#pragma once

void control_me() {
	double acc = 0.3;
	if (me.hitstop == 0) {
		if (me.hp > 0) {
			if (keystate[KEY_INPUT_UP] >= 1 && me.pos[1] > uplimit) {
				me.vel[1] -= acc;
			}
			if (keystate[KEY_INPUT_DOWN] >= 1 && me.pos[1] < downlimit) {
				me.vel[1] += acc;
			}
			if (keystate[KEY_INPUT_RIGHT] >= 1 && me.pos[0] < rightlimit) {
				me.vel[0] += acc;
			}
			if (keystate[KEY_INPUT_LEFT] >= 1 && me.pos[0] > leftlimit) {
				me.vel[0] -= acc;
			}
		}
		else {
			me.vel[0] *= 0.92;
			me.vel[1] *= 0.92;
		}
		if (me.pos[1] > downlimit) {
			me.pos[1] = downlimit;
			me.vel[1] = 0;
		}
		if (me.pos[1] < uplimit) {
			me.pos[1] = uplimit;
			me.vel[1] = 0;
		}
		if (me.pos[0] > rightlimit) {
			me.pos[0] = rightlimit;
			me.vel[0] = 0;
		}
		if (me.pos[0] < leftlimit) {
			me.pos[0] = leftlimit;
			me.vel[0] = 0;
		}
	}
}

void process_me() {
#if DEBUG
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", me.count);
#endif

	//shotenemy1との判定
	if ((phase == phase_game || phase == phase_oneplayer) && me.hp > 0) {
		for (int j = 0; j < shotenemy1.size(); j++) {
			if (shotenemy1[j].hitme(me) == 1 && shotenemy1[j].vanishcount == 0) {
				if (me.hitstop < 5) {
					me.hitstop = shotenemy1[j].hitstop;
				}

				if (me.hp > shotenemy1[j].damage) {
					me.hp -= shotenemy1[j].damage;
				}
				else {
					me.hp = 0;
				}
			}
		}
	}

	//HP境界処理
	if (me.hp < 0) {
		me.hp = 0;
	}
	else if (me.hp > me.hpmax) {
		me.hp = me.hpmax;
	}

	me.setvel();
	me.setpos();
	me.sethistory();

	me.update(game.countdown);
	
	//周囲エフェクト処理
	for (int i = 0; i < 10; i++) {
		surround[i].pos[0] = 20 * cos(deg2rad((7 + i) * me.count));
		surround[i].pos[1] = 20 * sin(deg2rad(1.05*(7 + i) * me.count));
		if (me.hitstop == 0) {
			//surround[i].setpos();
			surround[i].sethistory();
		}
		surround[i].update();
	}

	//自機描画
	if (phase == phase_game || phase == phase_oneplayer) {
		double death = 0.05 * effectmedeath.count + 1;
		for (int j = 20; j > 0; j--) {//残像
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (255 - 12 * j) / death);
			DrawLine(me.history[0][j] - j * 8, me.history[1][j],
				me.history[0][j - 1] - (j - 1) * 8, me.history[1][j - 1],
				GetColorHSV(220 + 30 * sin(deg2rad(5 * (me.count - j))), 255, 255), 16 - j * 0.6);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		for (int j = 30; j > 0; j--) {//キラキラ
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (255 - 8 * j) / death);
			DrawCircle(me.history[0][j] - j * 8 + RandRange(-20 + j * 0.5, 20 - j * 0.5), me.history[1][j] + RandRange(-20 + j * 0.5, 20 - j * 0.5), 1,
				GetColorHSV(220 + 30 * sin(deg2rad(5 * (me.count - j))), 60, 255), 1);
		}
		DrawCircle(me.pos[0], me.pos[1], 10 + 3 * sin(deg2rad(5 * me.count)), GetColorHSV(220, 255, 255), 1);
		for (int i = 1; i <= 5; i++) {//本体
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50 * i);
			DrawCircle(me.pos[0], me.pos[1], (10 + 3 * sin(deg2rad(5 * me.count))) * me.size / 20, GetColorHSV(220 + 30 * sin(deg2rad(5 * me.count)), 255 - 50 * i, 255), 0, 10 - 1.8 * i);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - 6.3 * (me.count % 40));//レベル色波動
		DrawCircle(me.pos[0], me.pos[1], me.count % 40, GetColorHSV(160 + (me.shotlevel - 1) * hueperlevel, 220, 255), 0, 2);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		//周囲エフェクト描画
		for (int i = 0; i < 10; i++) {
			if (i % 2 == 0) {
				for (int j = 20-1; j > 0; j--) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, (255 - 12 * j) / death);
					DrawLine(me.pos[0] + surround[i].history[0][j] - j * (me.vel[0] + 8) , me.pos[1] + surround[i].history[1][j] - j * me.vel[1],
						me.pos[0] + surround[i].history[0][j - 1] - (j - 1) * (me.vel[0] + 8), me.pos[1] + surround[i].history[1][j - 1] - (j - 1) * me.vel[1],
						GetColorHSV(190 + 6 * i, 255, 255), 2);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
				}
			}
			for (int j = 1; j <= 4; j++) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, (50 * j) / death);
				DrawCircle(me.pos[0] + surround[i].pos[0], me.pos[1] + surround[i].pos[1], 5 - j, GetColorHSV(190 + 6 * i, 255, 255), 1);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			}
		}
	}

	//自機操作（↑,↓,→,←）
	if (phase == phase_game || phase == phase_oneplayer) {
		control_me();
	}
}
