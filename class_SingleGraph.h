#pragma once

class SingleGraph {
public:
	int handle;
	double pos[2];
	double vel[2];
	double history[2][60];
	double size;
	double angle;//deg
	bool usehistory;
	int historylength;

	int count = 0;
	
	void set(int handle0, double posx0, double posy0, double size0, double angle0, bool usehistory0, int historylength0) {
		handle = handle0;
		pos[0] = posx0;
		pos[1] = posy0;
		vel[0] = 0;
		vel[1] = 0;
		size = size0;
		angle = angle0;
		usehistory = usehistory0;
		historylength = historylength0;
	}

	void setvel(double velx, double vely) {
		vel[0] = velx;
		vel[1] = vely;
	}

	void setpos() {
		pos[0] += vel[0];
		pos[1] += vel[1];
	}

	void sethistory() {
		if (count == 0) {
			for (int i = 0; i < 2; i++) {
				for (int j = historylength - 1; j >= 0; j--) {
					history[i][j] = pos[i];
				}
			}
		}
		else {
			for (int i = 0; i < 2; i++) {
				for (int j = historylength - 1; j > 0; j--) {
					history[i][j] = history[i][j - 1];
				}
				history[i][0] = pos[i];
			}
		}
	}
	//DrawRotaGraph(450, 370 + 50 * select, 0.5, deg2rad(90), gra_titleselect, 1, 0);

	void draw(double alpha) {
		DrawRotaGraph(pos[0], pos[1], size, deg2rad(angle), gra_titleselect, 1, 0);
		if (usehistory) {
			for (int j = historylength - 1; j > 0; j--) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha * (historylength - j) / historylength);
				DrawRotaGraph(history[0][j], history[1][j], size * (historylength - j) / historylength, deg2rad(angle), gra_titleselect, 1, 0);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			}
		}
	}

	void update() {
		if (usehistory) {
			sethistory();
		}
		count++;
	}

	void reset() {
		count = 0;
	}
};