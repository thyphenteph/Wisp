#pragma once

#define PI asin(1) * 2
#define SCREEN_X 1200
#define SCREEN_Y 640
#define FRAME_LEFT 60
#define FRAME_RIGHT 240
#define FRAME_UP 20
#define FRAME_DOWN 80
#define IN_SCREEN pos[0] <= SCREEN_X && pos[0] >= 0 && pos[1] <= SCREEN_Y && pos[1] >= 0
#define FADEOUT 1
#define FADEIN 2

const double uplimit = FRAME_UP;
const double downlimit = SCREEN_Y - FRAME_DOWN;
const double rightlimit = SCREEN_X - FRAME_RIGHT;
const double leftlimit = FRAME_LEFT;
const double center_x = leftlimit + (rightlimit - leftlimit) / 2;
const double center_y = uplimit + (downlimit - uplimit) / 2;

const int phase_title = 0;
const int phase_handi = 1;
const int phase_game = 2;
const int phase_oneplayer = 4;
const int phase_result = 3;