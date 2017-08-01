#pragma once

void attackbreakshot() {
	//モーション切り替え
	if (phase != phase_title) {
		//VSモード
		if (game.countdown == 0 && game.remain > 0) {
			if (keystate[KEY_INPUT_C] == 1 && me.motion != breakshotid && me.shotlevel > 1 && me.hp > 0) {
				breakshot.start();
			}

			if (me.motion == breakshotid) {
				breakshot.update();
			}
		}
		//1Pモード
		else if (oneplayer.countdown == 0 && oneplayer.remain > 0) {
			if (keystate[KEY_INPUT_C] == 1 && me.motion != breakshotid && me.shotlevel > 1 && me.hp > 0) {
				breakshot.start();
			}

			if (me.motion == breakshotid) {
				breakshot.update();
			}
		}
	}
	returnmotion(breakshotid);
}