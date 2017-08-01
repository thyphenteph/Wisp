#pragma once

class Core :public Enemy {
public:
	double summonmax = 1000;
	double summondef = summonmax / 3;
	double summon = summondef;

	void setdef() {
		hpmax = ene_hpmax[ene_core];
		hp = hpmax;
		size = 20;
	}
	void update() {
		if (summon < summonmax) {
			summon += 0.3 + 0.5 * (summonmax - summon) / summonmax;
		}
		else {
			summon = summonmax;
		}
	}
	
};

Core core;