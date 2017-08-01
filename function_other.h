#pragma once

void DrawQuad(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, unsigned int color, int fill) {
	DrawTriangle(x1, y1, x2, y2, x3, y3, color, fill);
	DrawTriangle(x1, y1, x4, y4, x3, y3, color, fill);
}

void returnmotion(int motion) {
	if (me.motion == motion) {
		if (me.hitstop == 0) {
			me.frame++;
		}
		if (me.frame >= motionframe[motion]) {
			me.motion = waitid;
			me.frame = 0;
			if (motion == slashid) {
				slash.reset();
			}
		}
	}
}

int in_screen(double pos[]) {
	if (pos[0] <= SCREEN_X && pos[0] >= 0 && pos[1] <= SCREEN_Y && pos[1] >= 0) {
		return 1;
	}
	else {
		return 0;
	}
}

void DrawCircleBlur(double x, double y, double r, int handle) {
	DrawRotaGraph(x, y, r / 50 * 1.5, 0, handle, 1, 0);
}

void mousewindow(int margin) {//margin: í[Ç©ÇÁÇÃãóó£
	if (mouse[0] < margin) {
		SetMousePoint(margin, mouse[1]);
	}
	if (mouse[0] > SCREEN_X - margin) {
		SetMousePoint(SCREEN_X - margin, mouse[1]);
	}
	if (mouse[1] < margin) {
		SetMousePoint(mouse[0], margin);
	}
	if (mouse[1] > SCREEN_Y - margin) {
		SetMousePoint(mouse[0], SCREEN_Y - margin);
	}
}

void initialize() {
	//Wisp
	me.reset();
	//ìGè¡ãé
	for (int i = 0; i < enemiesmax; i++) {
		enemies[i].reset();
		enemies[i].exist = 0;
	}
	//ìGíeè¡ãé
	for (int i = 0; i < shotenemy1.size(); i++) {
		shotenemy1[i].delflag = 1;
	}
	//Summon
	core.summon = core.summondef;
	summontype = ene_common;
}

class Effectdeath {
public:
	int count = 0;
	int offset[2] = { 0, 0 };
	int size = 15;
	int posmem[2];

	void draw(Me me) {
		if (count == 0) {
			switch (me.shotlevel) {
			case 1:
				GraphFilter(gra_medeath, DX_GRAPH_FILTER_HSB, 1, 160, 0, 0);
				break;
			case 2:
				GraphFilter(gra_medeath, DX_GRAPH_FILTER_HSB, 1, 210, 0, 0);
				break;
			case 3:
				GraphFilter(gra_medeath, DX_GRAPH_FILTER_HSB, 1, 260, 0, 0);
				break;
			case 4:
				GraphFilter(gra_medeath, DX_GRAPH_FILTER_HSB, 1, 310, 0, 0);
				break;
			default:
				break;
			}
		}

		if (count < 50) {
			if (count == 1) {
				PlaySoundMem(se_medeath1, DX_PLAYTYPE_BACK);
			}
			if (count % 8 == 0) {
				offset[0] = RandRange(-30, 30);
				offset[1] = RandRange(-30, 30);
				size = count / 5 + RandRange(3, 10);
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (count % 8) * 20);
			DrawCircleBlur(me.pos[0] + offset[0], me.pos[1] + offset[1], (count % 8) * size, gra_medeath);
		}
		else {
			if (count == 50) {
				PlaySoundMem(se_medeath2, DX_PLAYTYPE_BACK);
			}
			DrawCircleBlur(me.pos[0], me.pos[1], (count - 50) * 5, gra_medeath);
		}
	}

	void drawcore(Enemy ene) {
		if (count == 0) {
			switch (summontype) {
			case ene_common:
				GraphFilter(gra_medeath, DX_GRAPH_FILTER_HSB, 1, ene_hue[ene_common], 0, 0);
				break;
			case ene_escape:
				GraphFilter(gra_medeath, DX_GRAPH_FILTER_HSB, 1, ene_hue[ene_escape], 0, 0);
				break;
			case ene_rush:
				GraphFilter(gra_medeath, DX_GRAPH_FILTER_HSB, 1, ene_hue[ene_rush], 0, 0);
				break;
			case ene_ninja:
				GraphFilter(gra_medeath, DX_GRAPH_FILTER_HSB, 1, ene_hue[ene_ninja], -255, ene_value[ene_ninja]);
				break;
			case ene_shield:
				GraphFilter(gra_medeath, DX_GRAPH_FILTER_HSB, 1, ene_hue[ene_shield], -255, ene_value[ene_shield]);
				break;
			case ene_boss:
				GraphFilter(gra_medeath, DX_GRAPH_FILTER_HSB, 1, ene_hue[ene_boss], 0, 0);
				break;
			case ene_bossg:
				GraphFilter(gra_medeath, DX_GRAPH_FILTER_HSB, 1, ene_hue[ene_bossg], 0, 0);
				break;
			default:
				break;
			}
		}

		if (count < 50) {
			if (count == 1) {
				PlaySoundMem(se_medeath1, DX_PLAYTYPE_BACK);
				posmem[0] = ene.pos[0];
				posmem[1] = ene.pos[1];
			}
			if (count % 8 == 0) {
				offset[0] = RandRange(-30, 30);
				offset[1] = RandRange(-30, 30);
				size = count / 5 + RandRange(3, 10);
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (count % 8) * 20);
			DrawCircleBlur(posmem[0] + offset[0], posmem[1] + offset[1], (count % 8) * size, gra_medeath);
		}
		else {
			if (count == 50) {
				PlaySoundMem(se_medeath2, DX_PLAYTYPE_BACK);
			}
			DrawCircleBlur(posmem[0], posmem[1], (count - 50) * 5, gra_medeath);
		}

	}

	void update() {
		count++;
	}
	void reset() {
		count = 0;
	}
};
Effectdeath effectmedeath;
Effectdeath effectcoredeath;