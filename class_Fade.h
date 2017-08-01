#pragma once

class Fade {
public:
	int inout;

	int count = 600;
	int length;

	int nextphase;

	bool fadeflag = FALSE;
	
	void set(int inout0, int length0, int nextphase0) {
		inout = inout0;
		nextphase = nextphase0;
		length = length0;
		count = 600;
	}
	void start() {
		count = 0;
	}

	void draw() {//íÀs
		if (count <= length) {
			fadeflag = TRUE;

			if (inout == FADEOUT) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255.0 * count / length);
			}
			else if (inout == FADEIN) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255.0 * (length - count) / length);
			}
			DrawBox(0, 0, SCREEN_X, SCREEN_Y, GetColorHSV(0, 0, 0), 1);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

			if (count == length) {
				phase = nextphase;
				flagpause = 0;

				fadeflag = FALSE;
			}

			count++;
		}
		else {
			count = 600;
			fadeflag = FALSE;
		}
	}
};

Fade fade;