#pragma once


class EnemyHitbox {
public:
	bool exist = FALSE;
	bool canhit[enemiesmax] = { FALSE };
	bool hit[enemiesmax] = { FALSE };
	bool hitonce = FALSE;
	int hittime[enemiesmax] = { 0 };//各敵に対してのカウント
	int hittimeonce = 0;//1回でも当たればカウント
	bool intercept = FALSE;//有効・無効
	bool interceptonce = FALSE;//一度でも相殺したか
	bool intercepted[shotenemy1_maxmem] = { FALSE };//各敵弾への相殺状況
	int intercepttime[shotenemy1_maxmem] = { 0 };//相殺後の時間
	bool shield = FALSE;
	bool shielded = FALSE;

	bool direct;
	double pos[2];
	double size;
	double damage;
	int hitstop;
	int hiteff;
	int hitse;
	bool laser;
	double laserpos[2];


	void set(bool direct0, bool intercept0, double posx0, double posy0, double size0, double damage0, int hitstop0,
		int hiteff0, int hitse0, bool laser0) {

		exist = TRUE;
		for (int i = 0; i < enemiesmax; i++) {
			hit[i] = FALSE;
			canhit[i] = TRUE;
			hittime[i] = 0;
		}
		direct = direct0;
		intercept = intercept0;
		pos[0] = posx0;
		pos[1] = posy0;
		size = size0;
		damage = damage0;
		hitstop = hitstop0;
		hiteff = hiteff0;
		hitse = hitse0;
		laser = laser0;

		interceptonce = FALSE;
		shielded = FALSE;
	}

	void reset() {
		exist = TRUE;
		hitonce = FALSE;
		for (int i = 0; i < enemiesmax; i++) {
			hit[i] = FALSE;
			canhit[i] = TRUE;
			hittime[i] = 0;
		}
		hittimeonce = 0;
		interceptonce = FALSE;
		for (int i = 0; i < shotenemy1_maxmem; i++) {
			intercepted[i] = FALSE;
			intercepttime[i] = 0;
		}
		shielded = FALSE;
	}

	void setdirect(bool direct0) {
		direct = direct0;
	}

	void setintercept(bool intercept0) {
		intercept = intercept0;
	}

	void setshield(bool shield0) {
		shield = shield0;
	}

	void setpos(double posx0, double posy0) {
		pos[0] = posx0;
		pos[1] = posy0;
	}

	void setproperty(double size0, double damage0, int hitstop0) {
		size = size0;
		damage = damage0;
		hitstop = hitstop0;
	}

	void setsize(double size0) {
		size = size0;
	}

	void sethitse(int hitse0) {
		hitse = hitse0;
	}

	void setlaser(bool laser0, double laserposx0, double laserposy0) {
		laser = laser0;
		laserpos[0] = laserposx0;
		laserpos[1] = laserposy0;
	}

	void changeintercept(bool newintercept) {
		intercept = newintercept;
	}

	void changeshield(bool newshield) {
		shield = newshield;
	}

	void changepos(double newx, double newy) {
		pos[0] = newx;
		pos[1] = newy;
	}

	void changesize(double newsize) {
		size = newsize;
	}

	void changedamage(double newdamage) {
		damage = newdamage;
	}

	void changehitstop(int newhitstop) {
		hitstop = newhitstop;
	}

	void changelaser(bool newlaser, double newlaserposx, double newlaserposy) {
		laser = newlaser;
		laserpos[0] = newlaserposx;
		laserpos[1] = newlaserposy;
	}

	void changehitse(int newhitse) {
		hitse = newhitse;
	}

	void del() {
		exist = FALSE;
		for (int i = 0; i < 50; i++) {
			canhit[i] = FALSE;
			hit[i] = FALSE;
		}
	}

	void judge(Me me) {
		//判定可視化
#if VISUALIZE
		if (exist) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
			if (!laser) {
				DrawCircle(pos[0], pos[1], size, GetColorHSV(50, 255, 255), 1);
			}
			else {
				DrawLine(pos[0], pos[1], laserpos[0], laserpos[1], GetColorHSV(50, 255, 255), size * 2);
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
#endif

		//敵に対する処理
		if (!laser) {
			if (getdist(pos, me.pos) <= size + me.size &&  me.hp > 0) {
				hit[0] = TRUE;
			}
			else {
				hit[0] = FALSE;
			}
		}
		else {
			if (distpointtoline(me.pos, laserpos, (laserpos[1] - pos[1]) / (laserpos[0] - pos[0])) <= size + me.size
				&& ((me.pos[0] > laserpos[0] && me.pos[0] < pos[0]) || (me.pos[0] < laserpos[0] && me.pos[0] > pos[0]))) {

				hit[0] = TRUE;
			}
			else {
				hit[0] = FALSE;
			}
		}

		if (canhit[0]) {//まだ当たってない
			if (hit[0]) {
				hitonce = TRUE;
				//ダメージ付加
				if (me.hp > damage) {
					me.hp -= damage;
				}
				else {
					me.hp = 0;
				}
				//ヒットストップ付加
				me.hitstop = hitstop;
				if (direct) {
					me.hitstop = hitstop;
				}
				//効果音
				if (hitse != 0) {
					PlaySoundMem(hitse, DX_PLAYTYPE_BACK);
				}
				//ヒット判定終了
				canhit[0] = FALSE;
			}

		}
		else {
			hittime[0]++;
		}
	}
};