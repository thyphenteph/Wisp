#pragma once

void move_shotenemy1() {
	for (int i = 0; i < shotenemy1_maxmem; i++) {
		switch (shotenemy1[i].type) {
		case ene_common:
			break;
		case ene_rush:
			if (shotenemy1[i].count <= 120) {
				shotenemy1[i].speed -= 0.025 * shotenemy1[i].speed;
			}
			else {
				shotenemy1[i].delflag = 1;
			}
			break;
		case ene_boss:
			if (shotenemy1[i].type_2 == 1 && shotenemy1[i].count < 30) {
				shotenemy1[i].dir += 3;
			}
			break;
		default:
			break;
		}
	}
}
