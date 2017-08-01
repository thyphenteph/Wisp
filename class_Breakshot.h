#pragma once

class Breakshot {
public:
	int count = 0;
	const int size = 600;

	Hitbox hitbox_around;
	Hitbox hitbox_laser_p;
	Hitbox hitbox_laser_s;

	//�ŏ��ɂ�邱��
	void start() {
		count = 0;

		me.motion = breakshotid;
		me.frame = 0;
		PlaySoundMem(se_breakshot_0, DX_PLAYTYPE_BACK);

		//�G�t�F�N�g�Z�b�g
		breakshot_around.end();
		breakshot_around.sethandle(gra_breakshot_around, breakshot_aroundlen);
		breakshot_around.setpos(me.pos[0], me.pos[1]);
		breakshot_around.setsize(size);
		breakshot_around.setangle(RandRange(-180, 180));

		for (int i = 0; i < 3; i++) {
			if (i + 2 == me.shotlevel) {
				breakshot_charge[i].end();
				breakshot_charge[i].sethandle(gra_breakshot_charge[i], breakshot_chargelen);
				breakshot_charge[i].setpos(me.pos[0], me.pos[1]);
				breakshot_charge[i].setsize(600);
				breakshot_charge[i].setangle(RandRange(-180,180));
			}
		}

		breakshot_laser_p.end();
		breakshot_laser_p.sethandle(gra_breakshot_laser_p, breakshot_laser_plen);
		breakshot_laser_p.setpos(me.pos[0] + 750, me.pos[1]);
		breakshot_laser_p.setsize(1500);
		breakshot_laser_p.setangle(0);

		for (int i = 0; i < 3; i++) {
			if (i + 2 == me.shotlevel) {
				breakshot_laser_s[i].end();
				breakshot_laser_s[i].sethandle(gra_breakshot_laser_s[i], breakshot_laser_slen);
				breakshot_laser_s[i].setpos(me.pos[0] + 650, me.pos[1]);
				breakshot_laser_s[i].setsize(1200, 400);
				breakshot_laser_s[i].setangle(0);

				breakshot_back[i].end();
				breakshot_back[i].sethandle(gra_breakshot_back[i], breakshot_backlen);
				breakshot_back[i].setpos(me.pos[0], me.pos[1]);
				breakshot_back[i].setsize(400);
				breakshot_back[i].setangle(0);
			}
		}


		//�U������Z�b�g
		hitbox_around.setdirect(FALSE);
		hitbox_around.setintercept(TRUE);
		hitbox_around.setshield(FALSE);
		hitbox_around.setproperty(size * 0.10 / 2, 60, 25);
		hitbox_around.setpos(me.pos[0], me.pos[1]);
		hitbox_around.setlaser(FALSE, 0, 0);
		hitbox_around.sethitse(0);

		hitbox_laser_p.setdirect(FALSE);
		hitbox_laser_p.setintercept(FALSE);
		hitbox_laser_p.setshield(FALSE);
		hitbox_laser_p.setproperty(20, 5, 60);
		hitbox_laser_p.setpos(me.pos[0], me.pos[1]);
		hitbox_laser_p.setlaser(TRUE, 100000, me.pos[1]);
		hitbox_laser_p.sethitse(se_breakshot_hit_p);

		hitbox_laser_s.setdirect(FALSE);
		hitbox_laser_s.setintercept(TRUE);
		hitbox_laser_s.setshield(FALSE);
		hitbox_laser_s.setproperty(20, 9.5 + me.exp / 75.0, 20);
		hitbox_laser_s.setpos(me.pos[0], me.pos[1]);
		hitbox_laser_s.setlaser(TRUE, 100000, me.pos[1]);
		hitbox_laser_s.sethitse(se_breakshot_hit_s);

		me.exp = 3;
	}

	//���͕��d
	void process_around() {
		switch (me.frame) {
		case 6:
			//�G�t�F�N�g
			breakshot_around.start();
			//����
			hitbox_around.reset(); //�J�n
			hitbox_around.size = size * 0.10 / 2;
			break;
		case 7:
			hitbox_around.size = size * 0.28 / 2;
			break;
		case 8:
			hitbox_around.size = size * 0.46 / 2;
			break;
		case 9:
			hitbox_around.size = size * 0.62 / 2;
			break;
		case 10:
			hitbox_around.size = size * 0.75 / 2;
			break;
		case 11:
			hitbox_around.size = size * 0.80 / 2;
			break;
		case 13:
			hitbox_around.del();
			break;
		case 149:
			//�G�t�F�N�g����
			breakshot_around.end();
			break;
		default:
			break;
		}
		if (me.frame >= 6) {
			//�G�t�F�N�g�`��
			breakshot_around.draw();
			//���菈��
			hitbox_around.judge(enemies, shotenemy1);
			hitbox_around.killenemy(100);
		}

	}

	//�`���[�W�܂��
	void process_charge() {
		switch (me.frame) {
		case 4:
			//�G�t�F�N�g�J�n
			for (int i = 0; i < 3; i++) {
				if (i + 2 == me.shotlevel) {
					breakshot_charge[i].start();
				}
			}
			break;
		case 10:
			//SE
			PlaySoundMem(se_breakshot_charge, DX_PLAYTYPE_BACK);
			break;
		case 149:
			//�G�t�F�N�g����
			for (int i = 0; i < 3; i++) {
				breakshot_charge[i].end();
			}
			break;
		}
		//�G�t�F�N�g�`��
		for (int i = 0; i < 3; i++) {
			breakshot_charge[i].draw();
		}
		//�G�t�F�N�g�̒���
		for (int i = 0; i < 3; i++) {
			breakshot_charge[i].setpos(me.pos[0], me.pos[1]);
		}

	}

	//�������[�U�[
	void process_laser_p() {
		switch (me.frame) {
		case 8:
			//�G�t�F�N�g
			breakshot_laser_p.start();
			//����
			hitbox_laser_p.reset();
			break;
		case 11:
			hitbox_laser_p.del();
		case 149:
			//�G�t�F�N�g����
			breakshot_laser_p.end();
			break;
		}
		if (me.frame >= 6) {
			//�G�t�F�N�g�`��
			breakshot_laser_p.draw();
			//���菈��
			hitbox_laser_p.judge(enemies, shotenemy1);
			hitbox_laser_p.killenemy(100);
		}
	}

	//��2���[�U�[
	void process_laser_s() {
		switch (me.frame) {
		case 55:
			//SE
			PlaySoundMem(se_breakshot_1, DX_PLAYTYPE_BACK);
			break;
		case 60:
			//�t���b�V��
			autoflash.set(0, 0, 255, 30, 180);
			autoflash.start();
			//����
			hitbox_laser_s.reset();
			//����
			me.vel[0] -= 8;
			break;
		case 120:
			hitbox_laser_s.del();
		case 149:
			//�G�t�F�N�g����
			for (int i = 0; i < 3; i++) {
				breakshot_laser_s[i].end();
				breakshot_back[i].end();
			}
			break;
		default:
			break;
		}

		if (me.frame > 60) {
			//����̒���
			hitbox_laser_s.size = hitbox_laser_s.size + 13.5 / pow((me.frame - 60), 0.75);
			hitbox_laser_s.changepos(me.pos[0], me.pos[1]);
#if DEBUG
			DrawFormatString(100, 50, GetColorHSV(0, 255, 255), "%3.1f, %3.1f", hitbox_laser_s.size, hitbox_laser_s.damage);
#endif
			//���[�U�[�G�t�F�N�g���[�v
			if (me.frame % 30 == 1) {
				for (int i = 0; i < 3; i++) {
					if (i + 2 == me.shotlevel) {
						breakshot_laser_s[i].start();
					}
				}
			}
			//�����G�t�F�N�g���[�v
			if (me.frame % 20 == 1) {
				//�G�t�F�N�g���[�v
				for (int i = 0; i < 3; i++) {
					if (i + 2 == me.shotlevel) {
						breakshot_laser_s[i].start();
						breakshot_back[i].start();
					}
				}
			}

			//�A���q�b�g����
			if (me.frame % 10 == 0 && me.frame < 120) {
				hitbox_laser_s.del();
				hitbox_laser_s.reset();
			}

			//�G�t�F�N�g�̒���
			for (int i = 0; i < 3; i++) {
				breakshot_laser_s[i].setsize(1500, 400 * hitbox_laser_s.size / 100);
				breakshot_laser_s[i].setpos(me.pos[0] + 650, me.pos[1]);
				breakshot_back[i].setpos(me.pos[0], me.pos[1]);
			}
		}

		//�G�t�F�N�g�����x������
		if (me.frame > 100) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (120 - me.frame) / (120 - 100));
		}
		//�G�t�F�N�g�`��
		if (me.frame >= 60) {
			for (int i = 0; i < 3; i++) {
				breakshot_laser_s[i].draw();
				breakshot_back[i].draw();
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

			//���菈��
			hitbox_laser_s.judge(enemies, shotenemy1);
			hitbox_laser_s.killenemy(100);
		}

		//�t���b�V��
		if (me.frame < 120) {
			autoflash.set(shot1hue + me.level * hueperlevel, 50, 255, 30, 2.5 * getmax(0, me.frame - 60));
			autoflash.start();
		}
	}

	void update() {
		process_around();
		process_charge();
		process_laser_p();
		process_laser_s();

		if (me.frame < 145) {
			me.exp = 3;
		}

		if (me.frame < 60) {
			me.vel[0] *= 0.90;
		}
		else {
			if(me.vel[0]>0){
				me.vel[0] *= 0.8;
			}
			else {
				me.vel[0] *= 0.95;
			}
		}
		me.vel[1] *= 0.90;

		count++;
		me.hitstop = 0;
	}
};

Breakshot breakshot;