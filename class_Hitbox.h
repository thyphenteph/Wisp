#pragma once
#include "class_Hitdamagenum.h"
#include "class_Shot.h"
#include "class_Shotenemy1.h"

#define VISUALIZE 0

class Hitbox {
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
	bool kill[enemiesmax] = { FALSE };//とどめを刺したか

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
			kill[i] = FALSE;
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
			//canhit[i] = FALSE;
			hit[i] = FALSE;
		}
	}

	virtual void judge(Enemy enemy[enemiesmax], std::vector<Shotenemy1> &shot) {
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
		for (int i = 0; i < enemiesmax; i++) {
			if (!laser) {
				if (enemy[i].type == ene_shield && shield) {
					if (getdist(pos, enemy[i].pos) <= size + enemy[i].size + enemy[i].shieldsize && shield && enemy[i].hp > 0) {
						hit[i] = TRUE;
					}
					else {
						hit[i] = FALSE;
					}
				}
				else {
					if (getdist(pos, enemy[i].pos) <= size + enemy[i].size &&  enemy[i].hp > 0) {
						hit[i] = TRUE;
					}
					else {
						hit[i] = FALSE;
					}
				}
			}
			else {
				if (enemy[i].type == ene_shield && shield) {
					if (distpointtoline(enemy[i].pos, laserpos, (laserpos[1] - pos[1]) / (laserpos[0] - pos[0])) <= size + enemy[i].size + enemy[i].shieldsize && shield //距離
						&& ((enemy[i].pos[0] > laserpos[0] && enemy[i].pos[0] < pos[0]) || (enemy[i].pos[0] < laserpos[0] && enemy[i].pos[0] > pos[0])) //位置取り
						/*&& (laserpos[0] > leftlimit && laserpos[0] < rightlimit && laserpos[1] > uplimit && laserpos[1] < downlimit)*/) { //ターゲット位置画面内

						hit[i] = TRUE;
					}
					else {
						hit[i] = FALSE;
					}
				}
				else {
					if (distpointtoline(enemy[i].pos, laserpos, (laserpos[1] - pos[1]) / (laserpos[0] - pos[0])) <= size + enemy[i].size
						&& ((enemy[i].pos[0] > laserpos[0] && enemy[i].pos[0] < pos[0]) || (enemy[i].pos[0] < laserpos[0] && enemy[i].pos[0] > pos[0]))
						/*&& (laserpos[0] > leftlimit && laserpos[0] < rightlimit && laserpos[1] > uplimit && laserpos[1] < downlimit)*/) {

						hit[i] = TRUE;
					}
					else {
						hit[i] = FALSE;
					}
				}
			}


			if (canhit[i]) {//まだ当たってない
				if (hit[i] && !enemy[i].invincible && exist) {
					hitonce = TRUE;
					//シールド敵かつシールド有効弾
					if (enemy[i].type == ene_shield && shield) {
						shielded = TRUE;
						PlaySoundMem(se_shield, DX_PLAYTYPE_BACK);

						//反射
						shotenemy1[shotenemy1_del].reset();
						if (shotenemy1[shotenemy1_del].count == 0) {
							shotenemy1[shotenemy1_del].type = ene_shield;
							shotenemy1[shotenemy1_del].setdef(me, enemy[i]);
							shotenemy1[shotenemy1_del].damage = 2;
							shotenemy1[shotenemy1_del].hitstop = 6;
							shotenemy1[shotenemy1_del].dir = shotenemy1[shotenemy1_del].targetdir + RandRange(-20, 20);
							shotenemy1[shotenemy1_del].speed = 10;
							shotenemy1[shotenemy1_del].hue = ene_hue[ene_shield];
							shotenemy1[shotenemy1_del].saturation = ene_saturation[ene_shield];
							shotenemy1[shotenemy1_del].value = ene_value[ene_shield];
						}
						shotenemy1_del++;
						shotenemy1_del %= shotenemy1_maxmem;
					}
					else {
						//ダメージ付加
						if (enemy[i].hp > damage) {
							enemy[i].hp -= damage;
						}
						else {
							enemy[i].hp = 0;
							kill[i] = TRUE;
						}
						//ヒットストップ付加
						enemy[i].hitstop = hitstop;
						if (direct) {
							me.hitstop = hitstop;
						}
						//ダメージ表示
						hitdamagenum[hitdamageid][i].reset();
						hitdamagenum[hitdamageid][i].exist = 1;
						hitdamagenum[hitdamageid][i].setdamage(damage);
						hitdamageid++;
						hitdamageid %= 50;
						//効果音 SE
						if (hitse != 0) {
							PlaySoundMem(hitse, DX_PLAYTYPE_BACK);
						}
						//ヒット判定終了
						canhit[i] = FALSE;
					}
				}
			}
			else {
				hittime[i]++;
			}
		}
		/*
		//ヒット後時間計測
		if (hitonce && exist) {
			hittimeonce++;
		}*/

#if DEBUG
		/*
		for (int i = 0; i < enemiesmax; i++) {
			DrawFormatString(pos[0], pos[1] - 200 + i * 20, GetColorHSV(0, 255, 255), "%d", kill[i]);
		}*/
#endif

		//相殺
		if (exist && intercept) {
			for (int i = 0; i < shot.size(); i++) {
				if (!laser) {
					if (getdist(pos, shot[i].pos) <= size + shot[i].size && !shot[i].delflag) {
						//敵弾消去p
						shot[i].delflag = 1;
						//相殺フラグ
						interceptonce = TRUE;
						shot[i].intercepted = TRUE;
						//SE
						if (shot[i].vanishcount == 0) {
							//PlaySoundMem(se_shot1hit, DX_PLAYTYPE_BACK);
						}
						//ヒットストップ・吸収
						if (direct && me.hp > 0) {
							me.hitstop = 5;
							me.hp += 0.5;
						}
					}
				}
				else {
					if (distpointtoline(shot[i].pos, laserpos, (laserpos[1] - pos[1]) / (laserpos[0] - pos[0])) <= size + shot[i].size//距離
						&& ((shot[i].pos[0] > laserpos[0] && shot[i].pos[0] < pos[0]) || (shot[i].pos[0] < laserpos[0] && shot[i].pos[0] > pos[0]))//位置取り
						&& !shot[i].delflag) {
						//敵弾消去p
						shot[i].delflag = 1;
						//相殺フラグ
						interceptonce = TRUE;
						shot[i].intercepted = TRUE;
						//SE
						if (shot[i].vanishcount == 0) {
							//PlaySoundMem(se_shot1hit, DX_PLAYTYPE_BACK);
						}
						//ヒットストップ・吸収
						if (direct) {
							me.hitstop = 5;
							me.hp += 0.5;
						}
					}
				}
			}
		}

	}

	void killenemy(double power) {
		for (int i = 0; i < enemiesmax; i++) {
			if (enemies[i].hp <= 0 && enemies[i].hitstop == 0 && kill[i] && hittime[i] < enemies[i].vanishend + 40) {//ヒット→死亡
				if (direct) {
					enemies[i].pos[0] += power * (enemies[i].pos[0] - me.pos[0]) / getdist(me.pos, enemies[i].pos) / (enemies[i].vanishcount + 1) * (20.0 / enemies[i].size);
					enemies[i].pos[1] += power * (enemies[i].pos[1] - me.pos[1]) / getdist(me.pos, enemies[i].pos) / (enemies[i].vanishcount + 1) * (20.0 / enemies[i].size);
				}
				else {
					enemies[i].pos[0] += power * (enemies[i].pos[0] - pos[0]) / getdist(pos, enemies[i].pos) / (enemies[i].vanishcount + 1) * (20.0 / enemies[i].size);
					enemies[i].pos[1] += power * (enemies[i].pos[1] - pos[1]) / getdist(pos, enemies[i].pos) / (enemies[i].vanishcount + 1) * (20.0 / enemies[i].size);
				}
				//DrawCircle(0, 0, 100, GetColor(255, 255, 255), 1);
			}
		}
	}

};


/*
class EnemyHitbox : public Hitbox {
public:
	virtual void judge(Me me) {
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
};*/