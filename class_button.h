#pragma once

class button {
public:
	int id = 0;
	int selected = 0;
	double size[2] = { FRAME_RIGHT * 0.8 , size[0] / 5 };
	double pos[2];
	unsigned int color = GetColorHSV(0, 0, 0);
	char* name;

	int count = 0;

	void setname() {
		switch(id){
		case ene_common:
			name = "Common";
			break;
		case ene_escape:
			name = "Escape";
			break;
		case ene_rush:
			name = "Rush";
			break;
		case ene_ninja:
			name = "Ninja";
			break;
		case ene_shield:
			name = "Shield";
			break;
		case ene_boss:
			name = "Boss";
			break;
		case ene_bossg:
			name = "Boss_G";
			break;
		}
	}
	void setpos(button a) {
		pos[0] = rightlimit + 25;
		pos[1] = a.pos[1] + (a.size[1] + 10);
	}
	void update() {
		count++;
	}
};

button dummybutton;
button summonbutton[10];
