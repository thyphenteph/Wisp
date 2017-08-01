#pragma once

void attack_shotenemy1() {
	for (int i = 0; i < shotenemy1.size(); i++) {
		int glowlen = 10;
		double glowsize = 10;
		double bodysize = 2.5 * shotenemy1[i].sizedef / 10;;
		double sur = 1.8;
		int alpha = 170;
		if (shotenemy1[i].vanishcount <= glowlen) {
			//slashとの判定
			/*
			if (slash.hitshot(shotenemy1[i]) == 1) {
				int hit = 0;
				for (int j = 0; j < enemiesmax; j++) {
					if (slash.canhit[j] == 1) {
						hit = 1;
					}
				}
				if (hit == 1) {
					//PlaySoundMem(se_slashhit, DX_PLAYTYPE_BACK);
					shotenemy1[i].delflag = 1;
					int hitstop = 5;
					if (shotenemy1[i].vanishcount < 2) {
						me.hitstop = hitstop;
					}
				}
			}*/

			//処理
			if (shotenemy1[i].delflag == 0) {
				shotenemy1[i].setvel();
				shotenemy1[i].setpos();
			}
			//shotenemy1[i].sethistory();
			shotenemy1[i].update();
			/*
			//残像
			for (int j = glowlen; j > 0; j--) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0.6*(alpha - j * alpha / glowlen));
				DrawLine(shotenemy1[i].history[0][j], shotenemy1[i].history[1][j],
					shotenemy1[i].history[0][j - 1], shotenemy1[i].history[1][j - 1],
					GetColorHSV(shotenemy1[i].hue, 255, 255), glowsize - j * glowsize / glowlen);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			}
			*/
			//本体
			int p[4][2];
			p[0][0] = bodysize * 10 * cos(deg2rad(shotenemy1[i].dir));//右
			p[0][1] = bodysize * 10 * sin(deg2rad(shotenemy1[i].dir));
			p[1][0] = bodysize * 3 * cos(deg2rad(shotenemy1[i].dir + 120));//下
			p[1][1] = bodysize * 3 * sin(deg2rad(shotenemy1[i].dir + 120));
			p[2][0] = bodysize * 8 * cos(deg2rad(shotenemy1[i].dir + 180));//左
			p[2][1] = bodysize * 8 * sin(deg2rad(shotenemy1[i].dir + 180));
			p[3][0] = bodysize * 3 * cos(deg2rad(shotenemy1[i].dir - 120));//上
			p[3][1] = bodysize * 3 * sin(deg2rad(shotenemy1[i].dir - 120));
			int mex = shotenemy1[i].pos[0];
			int mey = shotenemy1[i].pos[1];
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha * 0.5 * (10 - 0.5*shotenemy1[i].vanishcount) / 10);
			DrawQuadrangle(mex + p[0][0] * sur, mey + p[0][1] * sur, mex + p[1][0] * sur, mey + p[1][1] * sur,
				mex + p[2][0] * sur, mey + p[2][1] * sur, mex + p[3][0] * sur, mey + p[3][1] * sur,
				GetColorHSV(shotenemy1[i].hue, shotenemy1[i].saturation, shotenemy1[i].value), 1);//周囲
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (10 - shotenemy1[i].vanishcount) / 10);
			DrawTriangle(mex, mey, mex + p[0][0], mey + p[0][1], //右下
				mex + p[1][0], mey + p[1][1], GetColorHSV(shotenemy1[i].hue, shotenemy1[i].saturation, shotenemy1[i].value - 55), 1);
			DrawTriangle(mex, mey, mex + p[1][0], mey + p[1][1], //左下
				mex + p[2][0], mey + p[2][1], GetColorHSV(shotenemy1[i].hue, shotenemy1[i].saturation, shotenemy1[i].value - 85), 1);
			DrawTriangle(mex, mey, mex + p[2][0], mey + p[2][1], //左上
				mex + p[3][0], mey + p[3][1], GetColorHSV(shotenemy1[i].hue, shotenemy1[i].saturation, shotenemy1[i].value - 35), 1);
			DrawTriangle(mex, mey, mex + p[3][0], mey + p[3][1], //右上
				mex + p[0][0], mey + p[0][1], GetColorHSV(shotenemy1[i].hue, shotenemy1[i].saturation, shotenemy1[i].value), 1);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}

		/*
		//攻撃判定
		DrawFormatString(200, 200 + i * 20, GetColorHSV(0, 255, 255), "%.1f", shotenemy1[i].damage);
		if (shotenemy1[i].count == 1) {
			shotenemy1[i].enemyhitbox.reset();
			shotenemy1[i].enemyhitbox.setdirect(FALSE);
			shotenemy1[i].enemyhitbox.setintercept(TRUE);
			shotenemy1[i].enemyhitbox.setshield(TRUE);
			shotenemy1[i].enemyhitbox.setproperty(shotenemy1[i].size, shotenemy1[i].damage, shotenemy1[i].hitstop);
			shotenemy1[i].enemyhitbox.setlaser(FALSE, 0, 0);
			shotenemy1[i].enemyhitbox.sethitse(se_shot1hit);
		}
		if (shotenemy1[i].count > 0) {
			shotenemy1[i].enemyhitbox.setpos(shotenemy1[i].pos[0], shotenemy1[i].pos[1]);
			shotenemy1[i].enemyhitbox.setsize(shotenemy1[i].size);
			shotenemy1[i].enemyhitbox.judge(me);
		}*/

		//相殺エフェクト
		if (shotenemy1[i].intercepttime == 1) {
			shotenemy1break[i].sethandle(gra_shotenemy1break, glassbreaklen);
			shotenemy1break[i].setpos(shotenemy1[i].pos[0], shotenemy1[i].pos[1]);
			shotenemy1break[i].setsize(300);
			shotenemy1break[i].setangle(RandRange(-180, 180));
			shotenemy1break[i].start();
			shotenemy1breakcore[i].sethandle(gra_shotenemy1breakcore, glassbreaklen);
			shotenemy1breakcore[i].setpos(shotenemy1[i].pos[0], shotenemy1[i].pos[1]);
			shotenemy1breakcore[i].setsize(300);
			shotenemy1breakcore[i].setangle(shotenemy1[i].dir);
			shotenemy1breakcore[i].start();
			//SE
			PlaySoundMem(se_intercept, DX_PLAYTYPE_BACK);
		}
		shotenemy1break[i].draw();
		shotenemy1breakcore[i].draw();
	}
}