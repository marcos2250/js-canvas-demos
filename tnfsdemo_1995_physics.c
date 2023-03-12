#include <stdio.h>

// fixed point math macros
#define abs(x) (((x) < 0) ? (-x) : (x))
#define sign(x) ((x) + 0x8000) >> 16)
#define mul(x,y) (((x) * (y) + 0x8000) >> 16)
#define round(x) ((x)) // >> 8)

#define fix16(a) ((a<0 ? a + 0xfffff : a) >> 16)
#define fix15(a) ((a<0 ? a + 0x7ffff : a) >> 15)
#define fix8(a) ((a<0 ? a + 0xff : a) >> 8)
#define fix7(a) ((a<0 ? a + 0x7f : a) >> 7)
#define fix4(a) ((a<0 ? a + 0xf : a) >> 4)
#define fix3(a) ((a<0 ? a + 0x7 : a) >> 3)
#define fix2(a) ((a<0 ? a + 3 : a) >> 2)

#define fixmul(x,y) ((x*y)/10000);

struct tnfs_car_specs {
	//  ...
	int front_drive_percentage; //00000018
	int front_brake_percentage; //0000001C
	//  ...
	int max_brake_force_1; //00000028
	int max_brake_force_2; //0000002C
	//  ...
	int max_speed; //00000038
	//  ...
	int diff_ratio; //00000054
	//  ...
	int gear_ratio_table; //00000070
	//  ...
	int max_slip_angle; //000000a4
	int rpm_redline; //000000ac
	int rpm_idle; //000000b0
	int torque_table_r01; //000000b4
	int torque_table_t01; //000000b8
	//  ...
	int torque_table_r10; //000000fc
	int torque_table_t10; //00000100
	//  ...
	int gear_ratio_table_2; //000002b8
	//  ...
	int body_roll_factor; //000002D4
	int body_pitch_factor; //000002D8
	//  ...
	int max_tire_lateral_force; //0000031C
	//  ...
	int thrust_to_acc_factor; //0000032C
	//  ...
	int diff_ratio_2; //00000368
};

struct tnfs_car_data {
	int pos_x; //00000000
	int pos_y; //00000004
	int pos_z; //00000008
	int angle_x; //0000000C
	int angle_y; //00000010
	int angle_z; //00000014
	int steer_angle; //00000018
	// ...
	int road_segment_a; //00000048
	int road_segment_b; //0000004C
	int game_status; //00000050
	int speed_x; //00000054
	int speed_y; //00000058
	int speed_z; //0000005C
	int speed_local_lat; //00000060
	int speed_local_vert; //00000064
	int speed_local_lon; //00000068
	int speed_drivetrain; //0000006C
	int speed; //00000070
	int angular_speed; //00000074
	// ...
	int body_roll; //00000365
	int body_pitch; //00000369
	// ...
	int throttle; //000003B1
	int gap3B5; //000003B5
	int brake; //000003B9
	int dword3BD; //000003BD
	short rpm_redline; //000003C1
	short rpm_idle; //000003C2
	int road_grip_increment; //000003C9
	int tire_grip_rear; //000003CD
	int tire_grip_front; //000003D1
	int dword3D5; //000003D5
	int dword3D9; //000003D9
	int gap3DD; //000003DD
	int dword3E1; //000003E1
	int thrust; //000003E5
	int gear_RND; //000003E9
	int gear_speed; //000003ED
	int gap3F1; //000003F1
	int handbrake; //000003F5
	short gap3F9[12]; //0000039F
	int slide_front; //00000405
	int slide_rear; //00000409
	int slide; //0000040D
	int susp_incl_lat; //00000411
	int susp_incl_lon; //00000415
	int gear_speed_selected; //00000419
	int gear_speed_previous; //0000041D
	int gear_shift_interval; //00000421
	short tire_skid_front; //00000425
	short tire_skid_rear; //00000426
	// ...
	int weight_distribution; //00000435
	// ...
	int weight_transfer_factor; //00000445
	int rear_friction_factor; //00000449
	int front_friction_factor; //0000044D
	int wheel_base; //00000451
	int wheel_track; //00000455
	int front_yaw_factor; //00000459
	int rear_yaw_factor; //0000045D
	// ...
	struct tnfs_car_specs *car_specs_ptr; //00000471
	int dword475; //00000475
	// ...
	int ctrl_throttle; //00000491
	int ctrl_brake; //00000495
	int gap499; //00000499
	int surface_type; //0000049D
	// ...
	int is_throttle_pressed; //000004AD
	int is_brake_pressed; //000004B1
	// ...
	int scale_a; //000004D5
	int scale_b; //000004D9
};

int dword_144728, dword_146493, dword_1465DD, dword_122C20, dword_D8AE4, dword_146475, //
		dword_146460, dword_123CC0, dword_12DECC, dword_1328E4, dword_1328DC, dword_132F74, dword_DC52C, //
		dword_132EFC, dword_122CAC, dword_146483, dword_D8AFC, dword_122CAC, dword_D8B00, //
		dword_D8AF0, dword_D8AF4, dword_D8AF8, dword_D8AE8, dword_D8AEC, dword_D8AEC, //
		dword_DC82C, dword_14649B, unk_F423F;

int road_surface_type_array[10];
int dword_132F84[10];
int unknown_collision_array[128];

//math stub functions
int math_abs(int a) {
	return a < 0 ? -a : a;
}
int math_mul(int a, int b) {
	return a * b / 10000;
}
int math_sin(int input) {
	int a = (input < 0 ? -input : input) % 262143; //360
	int v = a % 0x10000; //fake sin "curve"
	if (a > 196607) v =  v - 0x10000; //>270
	else if (a > 131071) v =  -v; //>180
	else if (a >  65535) v =  0x10000 - v; //>90
	if (input < 0) return -v;
	return v;
}
int math_cos(int a) {
	return math_sin(a + 65535);
}
int math_atan2(int x, int y) { //really low precision atan2
	if (x > 0) {
		if (y > 0) return 0x1FFFFE; //45
		if (y < 0) return -0x1FFFFE; //-45
	}
	if (x < 0) {
		if (y > 0) return 0x5FFFFA; //135
		if (y < 0) return -0x5FFFFA; //-135
	}
	return 0;
}
void math_rotate_2d(int x1, int y1, int angle, int *x2, int *y2) {
	int sin = math_sin(angle >> 6);
	int cos = math_cos(angle >> 6);
	*x2 = fix16( x1 * cos + y1 * sin );
	*y2 = fix16( x1 * sin + y1 * cos );
}
void math_matrix_mul3(int *a, int b, int c, int d) {
	//stub
}
void sub_34309(int a, int b, int x, int y) {
	//stub math_matrix_mul3
}
void sub_343C2(int a, int b) {
	//stub
}

// stub TNFS functions
void tnfs_engine_rev_limiter(struct tnfs_car_data *car_data) {
	//TODO
}
int tnfs_engine_thrust(struct tnfs_car_data *car_data) {
	return 10000; //TODO
}
void tnfs_engine_auto_shift(struct tnfs_car_data *car_data) {
	//TODO
}
void tnfs_physics_018(int a, int b, int c, int d, int e, int f) {
	//TODO
}
int tnfs_physics_024(struct tnfs_car_data *car_data, int speed) {
	return 0; //TODO
}
void tnfs_physics_collision_001(struct tnfs_car_data *car_data) {
	//TODO
}
void tnfs_physics_collision_003(int a) {
	//TODO
}

void tnfs_tire_handbrake_1() {
	int i;
	if (dword_DC82C == 4 && dword_122CAC > 300) {
		for (i = 0; i < dword_14649B; ++i) {
			math_matrix_mul3(&dword_132F84[i], 0xa0000, 0xa0000, 0xa0000);
		}
	}
}

/* locked wheels */
void tnfs_physics_handbrake_2(int *force_lat, int *force_lon, signed int max_grip, int *slide) {
	signed int v5;
	int v6;
	int v7;
	int v8;
	signed int v10;

	// total force
	v7 = abs(*force_lat);
	v8 = abs(*force_lon);
	if (v7 <= v8)
		v10 = (v7 >> 2) + v8;
	else
		v10 = (v8 >> 2) + v7;

	// calculates resulting forces
	if (v10 > max_grip) {
		v5 = max_grip - fix3(3 * max_grip);
		v6 = fix8(v10);

		*force_lat = fix8(v5 / v6 * *force_lat);
		*force_lon = fix8(v5 / v6 * *force_lon);
		*slide = v10 - v5;
	}
}

void tnfs_road_surface_modifier(struct tnfs_car_data *car_data) {
	int v4;
	int v5;
	signed int v7;
	signed int v8;
	signed int v9;
	signed int v10;
	int iVar3;

	//v10 = *(dword_12DECC + 36 * (dword_1328E4 & car_data->road_segment_a) + 18) >> 16 << 10;
	v10 = 0;
	if (v10 > 0x800000)
		v10 -= 0x1000000;

	//if (dword_1328DC) {
	//	v9 = *(dword_12DECC + 36 * (dword_1328E4 & dword_1328E4 & (car_data->road_segment_a + 1)) + 18) >> 16 << 10;
	//} else {
	//	v9 = *(dword_12DECC + 36 * (dword_1328E4 & (car_data->road_segment_a + 1)) + 18) >> 16 << 10;
	//}
	v9 = 0;
	if (v9 > 0x800000)
		v9 -= 0x1000000;

	iVar3 = math_cos((v9 - v10) >> 14);
	iVar3 = math_mul(iVar3, car_data->speed_local_lon);
	v8 = iVar3 * 4;

	if (v8 > 0)
		v8 += v8 >> 1;
	v7 = car_data->angle_z;
	if (v7 > 0x800000)
		v7 -= 0x1000000;

	v4 = abs(v7);
	v5 = abs(car_data->speed_local_lon);
	car_data->road_grip_increment = 2 * (mul(v5, v4) >> 7) + v8;

	car_data->tire_grip_front += car_data->road_grip_increment;
	if (car_data->tire_grip_front < 0)
		car_data->tire_grip_front = 0;

	car_data->tire_grip_rear += car_data->road_grip_increment;
	if (car_data->tire_grip_rear < 0)
		car_data->tire_grip_rear = 0;
}

/*
 read grip table for a given slip angle
 offset 884, table size 2 x 512 bytes

 front engine RWD cars
 off	fr	rr
 000	2	174
 010	14	174
 020	26	174
 030	37	174
 040	51	175
 050	65	176
 060	101	177
 070	111	177
 080	120	200
 090	126	200
 0a0	140	200
 0b0	150	200
 0c0	160	177
 0d0	165	177
 0e0	174	177
 0f0	176	177
 100	176	177
 110	176	177
 120	176	177
 130	176	177
 140	176	177
 150	176	177
 160	177	177
 170	177	177
 180	177	177
 190	200	200
 1a0	200	176
 1b0	200	173
 1c0	174	170
 1d0	167	165
 1e0	161	162
 1f0	152	156
 200	142	153
 */
int tnfs_tire_slide_table(struct tnfs_car_data *a1, signed int slip_angle, int is_rear_wheels) {
	signed int v4;

	v4 = slip_angle;
	if (slip_angle > 2097150)
		v4 = 2097150;

	//original
	//return *(a1->car_specs_ptr + (is_rear_wheels << 9) + (v4 >> 12) + 884) << 9;

	if (slip_angle == 0) return 0;
	//stub value
	return 127;
}

void tnfs_tire_limit_max_grip(struct tnfs_car_data *car_data, //
		int *force_lat, signed int *force_lon, signed int max_grip, int *slide) {

	int f_lat_abs;
	signed int f_lon_abs;
	signed int v9;
	int v10;
	int v11;
	signed int v12;
	int f_lon_abs2;
	int f_total;

	v9 = max_grip;

	// total force
	f_lat_abs = abs(*force_lat);
	f_lon_abs = abs(*force_lon);
	f_lon_abs2 = f_lon_abs;
	if (f_lat_abs <= f_lon_abs)
		f_total = (f_lat_abs >> 2) + f_lon_abs;
	else
		f_total = (f_lon_abs >> 2) + f_lat_abs;

	if (car_data->is_throttle_pressed) {
		if (f_total > max_grip) {
			if (f_lon_abs <= f_total - max_grip) {
				*force_lon = 0;
				f_lon_abs2 = 0;
			} else {
				f_lon_abs2 = f_lon_abs - (f_total - max_grip);
				if (*force_lon <= 0)
					*force_lon = -f_lon_abs2;
				else
					*force_lon = f_lon_abs2;
			}
		}
		if (f_lat_abs <= f_lon_abs2)
			f_total = (f_lat_abs >> 2) + f_lon_abs2;
		else
			f_total = (f_lon_abs2 >> 2) + f_lat_abs;
	}

	if (f_total > max_grip) {
		// decrease slide
		*slide = f_total - max_grip;

		v10 = f_total;
		if (f_total > fix4(18 * max_grip))
			v10 = fix4(18 * max_grip);

		v12 = (v10 - max_grip);

		if (v10 - max_grip > 0)
			v9 = max_grip - v12;

		v11 = v9 / fix8(f_total);

		if ((car_data->brake <= 150 || *&car_data->ctrl_brake) && car_data->handbrake == 0) {
			// not locked wheels
			if (*force_lat > max_grip)
				*force_lat = max_grip;
			else if (*force_lat < -max_grip)
				*force_lat = -max_grip;

			if (car_data->throttle >= 50) {
				*force_lon = fix8(v11 * *force_lon);

			} else {
				if (*force_lon > max_grip)
					*force_lon = max_grip;
				else if (*force_lon < -max_grip)
					*force_lon = -max_grip;
			}
		} else {
			// locked wheels
			*force_lat = fix8(v11 * *force_lat);
			*force_lon = fix8(v11 * *force_lon);
			// ANGLE WARNING!!
			printf("ANGLE WARNING!! %s=%d", (char*) 'a', f_lat_abs);
		}
	}

	if (&car_data->slide_rear == slide) {
		if ((*force_lon > 0 && car_data->speed_local_lon > 0) || (*force_lon < 0 && car_data->speed_local_lon < 0)) {
			car_data->slide = v12;
		}
	}
}

void tnfs_tire_forces(struct tnfs_car_data *_car_data, //
		int *_result_Lat, int *_result_Lon, //
		int force_Lat, int force_Lon, //
		signed int steering, int thrust_force, int braking_force, //
		int is_front_wheels) {

	signed int slip_angle;
	int v11;
	int v14;
	int v15;
	int f_lat_loc_abs2;
	int f_lon_loc_abs2;
	int f_lat_loc_abs;
	int force_lat_local_abs2;
	int v23;
	int v24;
	int force_lat_local_abs;
	struct tnfs_car_data *car_data;
	int *slide;
	short *skid;
	signed int max_grip;
	int v34;
	int force_lon_local;
	int force_lat_local;
	int result_brake_thrust;
	int v38;
	struct tnfs_car_specs *car_specs;

	car_data = _car_data;
	car_specs = car_data->car_specs_ptr;

	v34 = 0;
	if (*&_car_data->gap3F9[4] == 0) {
		*_result_Lon = 0;
		*_result_Lat = 0;
		return;
	}

	if (is_front_wheels == 1) {
		math_rotate_2d(force_Lat, force_Lon, -steering, &force_lat_local, &force_lon_local);
		max_grip = car_data->tire_grip_front;
		skid = &car_data->tire_skid_front;
		slide = &car_data->slide_front;
	} else {
		force_lat_local = force_Lat;
		force_lon_local = force_Lon;
		max_grip = _car_data->tire_grip_rear;
		skid = &_car_data->tire_skid_rear;
		slide = &_car_data->slide_rear;
	}
	*skid = 0;
	dword_132F74 = *_result_Lon + *_result_Lat;

	force_lat_local_abs = abs(force_lat_local);
	if (force_lon_local <= 0)
		slip_angle = math_atan2(-force_lon_local, force_lat_local_abs);
	else
		slip_angle = math_atan2(force_lon_local, force_lat_local_abs);

	if (slip_angle > car_specs->max_slip_angle) {
		slip_angle = car_specs->max_slip_angle;
		*skid |= 1u;
	}

	if ( fix2(5 * max_grip) >= abs(braking_force) || (*&car_data->ctrl_brake != 0 && car_data->handbrake == 0)) {
		// not locked wheels

		// lateral tire grip factor
		v11 = tnfs_tire_slide_table(car_data, slip_angle, is_front_wheels - 1);

		v38 = mul(max_grip, v11);
		v24 = abs(force_lat_local);

		if (v24 > v38) {
			//lateral force exceeding max grip
			v23 = 8 * v38;
			if (force_lat_local <= 0)
				force_lat_local_abs2 = -force_lat_local;
			else
				force_lat_local_abs2 = force_lat_local;

			// visual effects
			if (force_lat_local_abs2 > v23 && slip_angle > 0xf0000) {
				if (slip_angle <= 1966080) {
					f_lat_loc_abs = abs(force_lat_local);
					v34 = fix2(f_lat_loc_abs - v23);
					*skid |= 4u;
				} else {
					*skid |= 1u;
					v34 = abs( force_lat_local ) - v23;
				}
			}

			if (force_lat_local <= 0)
				force_lat_local = -v38;
			else
				force_lat_local = v38;
		}

		if (force_lon_local <= 0)
			braking_force = -braking_force;

		result_brake_thrust = braking_force + thrust_force;

		if (abs(thrust_force) > abs(braking_force)) {
			//acceleration
			force_lon_local = result_brake_thrust;
			f_lon_loc_abs2 = abs(force_lon_local);
			f_lat_loc_abs2 = abs(force_lat_local);
			if (f_lat_loc_abs2 + f_lon_loc_abs2 > max_grip) {
				*skid = 2;
				if (f_lon_loc_abs2 > max_grip && dword_D8AE4 && !*&car_data->ctrl_throttle) {
					force_lat_local = fix2(force_lat_local);
				}
			}
			tnfs_tire_limit_max_grip(car_data, &force_lat_local, &force_lon_local, max_grip, slide);
			if (*slide != 0) {
				*slide *= 8;
			}
			if (*slide < v34) {
				*slide = v34;
			}

		} else {
			//deceleration
			v15 = abs(result_brake_thrust);
			v14 = abs(force_lon_local);
			if (v15 < v14) {
				if (force_lon_local <= 0) {
					force_lon_local = -v15;
				} else {
					force_lon_local = v15;
				}
			}
			tnfs_tire_limit_max_grip(car_data, &force_lat_local, &force_lon_local, max_grip, slide);
			*slide |= v34;
			if (car_data->is_brake_pressed)
				*slide = 0;

		}

	} else {
		// locked wheels: hard braking or handbrake
		if (abs(force_lon_local) > max_grip)
			*skid |= 1u;

		tnfs_physics_handbrake_2(&force_lat_local, &force_lon_local, max_grip, slide);
	}

	// function return, rotate back to car frame
	if (*slide > 9830400)
		*slide = 9830400;

	if (steering != 0) {
		math_rotate_2d(force_lat_local, force_lon_local, steering, _result_Lat, _result_Lon);
	} else {
		*_result_Lat = force_lat_local;
		*_result_Lon = force_lon_local;
	}
}

/* 
 * Offset 0003F0FA
 * Main physics routine
 */
void tnfs_physics_main(struct tnfs_car_data *a1) {
	signed int v2;
	int v3;
	signed int v4;
	int v5;
	signed int v6;
	signed int v7;
	signed int v8;
	signed int v9;
	int v14;
	signed int v17;
	signed int v18;
	int v19;
	signed int v20;
	int v24;
	int v25;
	signed int v26;
	signed int v27;
	int v33;
	int force_lon_total;
	int limit_tire_force;
	int v43;
	signed int v44;
	signed int v45;
	struct tnfs_car_data *car_data;
	int rLon;
	int rLat;
	int fLon;
	int fLat;
	int *v51;
	int braking_rear;
	int braking_front;
	int traction_rear;
	int traction_front;
	int drag_lon;
	int drag_lat;
	signed int thrust_force;
	signed int v59;
	int steering;
	int v61;
	int force_Lon;
	int force_lon_adj;
	int force_Lat;
	int f_R_Lon;
	int f_R_Lat;
	int f_F_Lon;
	int f_F_Lat;
	int sLon;
	int sLat;
	int v71;
	int v72;
	struct tnfs_car_specs *car_specs;
	int cos_angle_z;
	int iVar2;

	// gather basic car data
	car_data = a1;

	//v51 = &dword_144728[116 * a1->dword475];
	v51 = &unknown_collision_array;

	dword_D8AE4 = 0;
	car_specs = a1->car_specs_ptr;

	// fast vec2 length
	v44 = abs(a1->speed_x);
	v45 = abs(a1->speed_z);
	if (v44 <= v45)
		a1->speed = (v44 >> 2) + v45;
	else
		a1->speed = (v45 >> 2) + v44;

	// fixed values
	a1->scale_a = 2184;
	a1->scale_b = 30;

	// custom scales, not used
	if (dword_146493 > 1 && dword_1465DD != 0) {
		//v43 = (*(dword_132F84[1 - a1->dword475] + 76) - a1->road_segment_b) / 2;
		v43 = 0;
		if (v43 > 0) {
			if (v43 > dword_1465DD)
				v43 = dword_1465DD;
			a1->scale_b = 30 - v43;
			a1->scale_a = 0x10000 / a1->scale_b;
		}
	}

	// throttle and brake controller inputs
	if ((dword_122C20 & 0x10) != 0 && a1->handbrake == 0) {
		a1->is_brake_pressed = *&a1->ctrl_brake;
		a1->is_throttle_pressed = *&a1->ctrl_throttle;
	} else {
		a1->is_brake_pressed = 0;
		a1->is_throttle_pressed = 0;
	}

	// car engine control
	if ((dword_122C20 & 4) || a1->gear_speed == -1) {
		tnfs_engine_rev_limiter(a1);
		if (car_data->gear_RND > 0) {
			switch (car_data->gear_RND) {
			case 3:
				tnfs_engine_auto_shift(car_data);
				break;
			case 2:
				car_data->gear_speed = -1;
				break;
			case 1:
				car_data->gear_speed = -2;
				break;
			}
		}
	}
	car_data->thrust = tnfs_engine_thrust(car_data);
	thrust_force = car_data->thrust;

	if (car_data->is_throttle_pressed != 0 && car_data->gear_speed == 0)
		thrust_force -= fix2(thrust_force);

	car_data->slide = 0;

	// traction forces
	traction_front = (car_specs->front_drive_percentage >> 8) * (thrust_force >> 8);
	traction_rear = thrust_force - traction_front;

	// braking forces
	if (car_data->brake <= 240) {
		v2 = (330 * car_data->brake >> 8) * ((car_data->tire_grip_rear + car_data->tire_grip_front) >> 8);
		braking_front = ((car_specs->front_brake_percentage >> 8) * (v2 >> 8));
		braking_rear = (v2 - braking_front);
	} else {
		// hard braking
		braking_front = 0x140000;
		braking_rear = 0x140000;
	}
	// handbrake
	if (car_data->handbrake == 1) {
		traction_rear = 0;
		braking_rear = 0x280000;
		tnfs_tire_handbrake_1();
	}

	// gear wheel lock
	if (abs(car_data->speed_local_lat) < 0x1999 //
	&& ((car_data->speed_local_lon > 0x10000 && car_data->gear_speed == -2) //
	|| (car_data->speed_local_lon < -0x10000 && car_data->gear_speed >= 0))) {
		if (traction_front != 0 && traction_front < car_data->tire_grip_front) {
			traction_front = 0;
			braking_front = car_specs->max_brake_force_1;
		}
		if (traction_rear != 0 && traction_rear < car_data->tire_grip_rear) {
			traction_rear = 0;
			braking_rear = car_specs->max_brake_force_1;
		}
	}

	// shift controls/throttle ramp
	if (car_data->throttle >= 40) {
		if (car_data->is_throttle_pressed != 0) {
			if ( abs(thrust_force) > 0x70000 && car_data->throttle > 83)
				car_data->throttle -= 12;
		}
	} else {
		car_data->is_throttle_pressed = 0;
	}
	if (car_data->brake < 40)
		car_data->is_brake_pressed = 0;
	if (car_data->gear_speed != car_data->gear_speed_selected) {
		car_data->gear_shift_interval = 16;
		car_data->gear_speed_previous = car_data->gear_speed_selected;
		car_data->gear_speed_selected = car_data->gear_speed;
	}
	if (car_data->gear_shift_interval > 0) {
		if (car_data->gear_shift_interval > 12 || car_data->dword3BD < 1)
			--car_data->gear_shift_interval;

		if (car_data->dword475 == dword_146460 //
		&& car_data->gear_shift_interval == 11 //
		&& !dword_123CC0 //
				&& car_data->dword3BD < 1) {
			tnfs_physics_018(-1, 13, 0, 0, 1, 15728640);
		}
	}

	// aero/drag forces (?)
	drag_lat = tnfs_physics_024(car_data, car_data->speed_local_lat);
	drag_lon = tnfs_physics_024(car_data, car_data->speed_local_lon);
	if (car_data->speed_local_lon > car_specs->max_speed && dword_146475 != 6) {
		if (drag_lon > 0 && drag_lon < thrust_force) {
			drag_lon = abs(thrust_force);
		} else if (drag_lon < 0) {
			if ( abs(drag_lon) < abs(thrust_force)) {
				drag_lon = -abs(thrust_force);
			}
		}
	}

	// BEGIN of car traction/slip trajectory
	v72 = math_abs(car_data->steer_angle + car_data->angle_y);

	// convert to local frame of reference
	math_rotate_2d(car_data->speed_x, car_data->speed_z, -car_data->angle_y, &car_data->speed_local_lat, &car_data->speed_local_lon);

	// scale speeds
	sLat = car_data->scale_b * car_data->speed_local_lat;
	sLon = car_data->scale_b * car_data->speed_local_lon;

	// sideslip
	v3 = mul(car_data->wheel_base, car_data->scale_b * car_data->angular_speed);

	// front and rear forces
	fLat = -mul(car_data->weight_distribution, sLat) - drag_lat / 2 + v3;
	rLat = -(sLat - mul(car_data->weight_distribution, sLat)) - drag_lat / 2 - v3;
	rLon = -(sLon - mul(car_data->weight_distribution, sLon)) - drag_lon / 2;
	fLon = -mul(car_data->weight_distribution, sLon) - drag_lon / 2;

	// adjust steer sensitivity
	v59 = car_data->steer_angle;
	if (car_data->brake <= 200) {
		v4 = fix8(car_data->speed_local_lon) * v59;
		steering = v59 - fix15(v4);
	} else {
		steering = v59 / 2;
	}

	// tire forces (bicycle model)
	car_data->slide_front = 0;
	car_data->slide_rear = 0;
	tnfs_tire_forces(car_data, &f_F_Lat, &f_F_Lon, fLat, fLon, steering, traction_front, braking_front, 1);
	tnfs_tire_forces(car_data, &f_R_Lat, &f_R_Lon, rLat, rLon, 0, traction_rear, braking_rear, 2);
	force_Lat = f_R_Lat + f_F_Lat;
	force_Lon = f_R_Lon + f_F_Lon;

	// limit braking forces
	if (car_data->brake > 100 || car_data->handbrake) {
		if (car_data->speed >= 1755054) {
			if (car_data->speed >= 2621440) {
				if (car_specs->max_brake_force_2 <= car_specs->max_brake_force_1) {
					limit_tire_force = car_specs->max_brake_force_1;
				} else {
					limit_tire_force = car_specs->max_brake_force_2;
				}
			} else {
				limit_tire_force = car_specs->max_brake_force_2;
			}
		} else {
			limit_tire_force = car_specs->max_brake_force_1;
		}
		if (force_Lon <= 0) {
			force_lon_total = -force_Lon;
		} else {
			force_lon_total = f_R_Lon + f_F_Lon;
		}
		if (force_lon_total > limit_tire_force) {
			if (force_Lon < 0) {
				force_Lon = -limit_tire_force;
			} else {
				force_Lon = limit_tire_force;
			}
		}
		if (dword_146475 == 3 && (car_data->road_segment_a <= 97 || car_data->road_segment_a >= 465)) {
			v33 = force_Lat <= 0 ? -force_Lat : f_R_Lat + f_F_Lat;
			if (v33 > limit_tire_force) {
				if (force_Lat < 0) {
					force_Lat = -limit_tire_force;
				} else {
					force_Lat = limit_tire_force;
				}
			}
		}
	}

	// tire lateral force limit
	v61 = car_data->road_grip_increment + car_specs->max_tire_lateral_force;
	if (v61 < 0)
		v61 = 0;
	if ( abs( force_Lat ) > v61) {
		if (force_Lat < 0)
			force_Lat = -v61;
		else
			force_Lat = v61;
	}

	// calculate grip forces
	v5 = (force_Lon >> 8) * (car_data->weight_transfer_factor >> 8);

	v6 = (car_data->front_friction_factor - v5) * road_surface_type_array[4 * car_data->surface_type];
	car_data->tire_grip_front = fix8(v6);

	v7 = (v5 + car_data->rear_friction_factor) * road_surface_type_array[4 * car_data->surface_type];
	car_data->tire_grip_rear = fix8(v7);

	tnfs_road_surface_modifier(car_data);

	// thrust force to acc (force/mass=acc?)
	v8 = car_specs->thrust_to_acc_factor * force_Lon;
	force_lon_adj = fix8(v8);

	// suspension inclination
	car_data->susp_incl_lat = force_Lat;
	car_data->susp_incl_lon = force_lon_adj;

	// convert speeds to world scale
	if ( abs(car_data->speed_local_lon) + abs(car_data->speed_local_lat) >= 19660) {
		// car moving
		car_data->speed_local_lat += mul(car_data->scale_a, (drag_lat + force_Lat + car_data->dword3D9));
		car_data->speed_local_lon += mul(car_data->scale_a, (drag_lon + force_lon_adj + car_data->dword3E1));
		//3d9 and 3e1: slope/gravity/resistive forces?
	} else {
		// car stopped
		car_data->speed_local_lat += mul(car_data->scale_a, force_Lat);
		car_data->speed_local_lon += mul(car_data->scale_a, force_lon_adj);

		if (car_data->gear_speed == -1 || car_data->throttle == 0) {
			car_data->speed_local_lon = 0;
			car_data->speed_local_lat = 0;
		}
	}

	// rotate back to global frame of reference
	math_rotate_2d(car_data->speed_local_lat, car_data->speed_local_lon, car_data->angle_y, &car_data->speed_x, &car_data->speed_z);

	// move the car
	car_data->pos_z += fixmul(car_data->scale_a, car_data->speed_z);
	car_data->pos_x -= fixmul(car_data->scale_a, car_data->speed_x);

	// suspension body roll
	if (car_data->speed_local_lat + car_data->speed_local_lon <= 6553) {
		car_data->body_roll += -car_data->body_roll / 2;
		car_data->body_pitch += -car_data->body_pitch / 2;
	} else {
		car_data->body_roll += (-((car_data->susp_incl_lat >> 8) * (car_specs->body_roll_factor >> 8)) - car_data->body_roll) / 2;
		car_data->body_pitch += (-((car_data->susp_incl_lon >> 8) * (car_specs->body_pitch_factor >> 8)) - car_data->body_pitch) / 2;
	}

	// calc angular speed
	v71 = (mul(car_data->rear_yaw_factor, f_R_Lat)) - (mul(car_data->front_yaw_factor, f_F_Lat));
	car_data->angular_speed += mul(car_data->scale_a, v71);

	if ( abs(car_data->angular_speed) > 9830400) {
		if (car_data->angular_speed >= 0)
			car_data->angular_speed = 9830400;
		else
			car_data->angular_speed = -9830400;
	}

	// rotate car body
	v9 = mul(car_data->scale_a, car_data->angular_speed);
	car_data->angle_y += fix2(v9) + v9;

	// further angle move
	if (abs( car_data->angle_z ) > 0x30000) {

		v27 = 0; //TODO *(dword_12DECC + 36 * (dword_1328E4 & car_data->road_segment_a) + 22) >> 16 << 10;
		if (v27 > 0x800000)
			v27 -= 0x1000000;

		if (dword_1328DC) {
			v26 = 0; //TODO *(dword_12DECC + 36 * (dword_1328E4 & dword_1328E4 & (car_data->road_segment_a + 1)) + 22) >> 16 << 10;
		} else {
			v26 = 0; //TODO *(dword_12DECC + 36 * (dword_1328E4 & (car_data->road_segment_a + 1)) + 22) >> 16 << 10;
		}

		if (v26 > 0x800000)
			v26 -= 0x1000000;

		cos_angle_z = math_cos(car_data->angle_z >> 14);
		iVar2 = fix8(car_data->speed_local_lon) * (v26 - v27);
		iVar2 = math_mul(cos_angle_z, fix8(iVar2));
		car_data->angle_y -= fix7(iVar2);
	}

	// unsign angle
	car_data->angle_y = math_abs(car_data->angle_y);

	// collision calculations
	dword_132F74 = car_data->speed_local_lon + car_data->speed_local_vert + car_data->speed_local_lat;
	tnfs_physics_collision_001(car_data);
	if ((dword_122C20 & 4) && dword_DC52C == 1) {
		if (car_data->speed_local_lon / 2 <= 0)
			v24 = car_data->speed_local_lon / -2;
		else
			v24 = car_data->speed_local_lon / 2;
		if (car_data->speed_local_lat <= 0)
			v25 = -car_data->speed_local_lat;
		else
			v25 = car_data->speed_local_lat;
		if (v25 > v24 && car_data->speed_local_lat > 0x8000)
			tnfs_physics_collision_003(87);
		if ((car_data->slide_front || car_data->slide_rear) //
		&& car_data->speed > 0x140000 //
		&& ((car_data->tire_skid_rear & 1) || (car_data->tire_skid_front & 1))) {
			tnfs_physics_collision_003(40);
		}
		if (!dword_132EFC) {
			if ( abs(car_data->speed_local_lon) > 3276) {
				tnfs_physics_collision_003(120);
				dword_132EFC = dword_122CAC + 1;
			}
		}
	}

	if (v51[113] < abs(car_data->speed_local_lon)) {
		v51[113] = abs(car_data->speed_local_lon);
	}

	// used for debug
	if (!dword_146483 && dword_146475 == 3) {
		if (car_data->road_segment_a <= 97 || car_data->road_segment_a >= 465) {
			if (car_data->speed_local_lon < 13107) {
				dword_D8AFC = dword_122CAC;
				dword_D8B00 = car_data->road_segment_b;
				dword_D8AF0 = 99999;
				dword_D8AF4 = 99999;
				dword_D8AF8 = 99999;
			}
			v19 = dword_122CAC - dword_D8AFC;
			if (car_data->throttle > 50 && v19 < 1500 && v19 > 100) {
				if (car_data->speed_local_lon > 1755447 && dword_D8AF0 > v19) {
					dword_D8AF0 = dword_122CAC - dword_D8AFC;
					sub_34309(v19, 0, 0, 0);
					if (v51[102] > v19)
						v51[102] = v19;
				}
				if (car_data->speed_local_lon > 2926182 && dword_D8AF4 > v19) {
					dword_D8AF4 = v19;
					sub_34309(0, v19, 0, 0);
					if (v51[103] > v19)
						v51[103] = v19;
				}
			}
			if (car_data->road_segment_b - dword_D8B00 > 83) {
				//TODO dword_D8B00 = &unk_F423F;
				v20 = dword_122CAC - dword_D8AFC;
				if (dword_D8AF8 > dword_122CAC - dword_D8AFC && v20 < 1000) {
					if (v20 < v51[107]) {
						v51[107] = v20;
						v51[106] = car_data->speed_local_lon;
					}
					sub_34309(0, 0, v20, car_data->speed_local_lon);
					dword_D8AF8 = v20;
				}
			}
			if (car_data->brake > 50) {
				if (car_data->speed_local_lon > 2340290)
					dword_D8AE8 = dword_122CAC;
				if (car_data->speed_local_lon > 1755447)
					dword_D8AEC = dword_122CAC;
				if (car_data->speed_local_lon < 6553 && dword_D8AEC > 0) {
					v17 = dword_122CAC - dword_D8AEC;

					printf("TUNING STATS : 60-0 in seconds %d = feet %d", 100 * (dword_122CAC - dword_D8AEC) / 60, v17);
					sub_343C2(v17, 0);
					dword_D8AEC = 0;
					if (v51[105] > v17)
						v51[105] = v17;
				}
				if (car_data->speed_local_lon < 6553 && dword_D8AE8 > 0) {
					v18 = dword_122CAC - dword_D8AE8;

					printf("TUNING STATS : 80-0 in %d seconds = %d feet", 100 * (dword_122CAC - dword_D8AE8) / 60, v18);
					sub_343C2(0, v18);
					dword_D8AE8 = 0;
					if (v51[104] > v18)
						v51[104] = v18;
				}
			}
		}
		if (car_data->tire_skid_rear) {
			v14 = car_data->tire_skid_rear;

			if ( abs(car_data->angular_speed) > 3276800)
				tnfs_physics_collision_003(87);
		}
	}

	dword_132F74 = car_data->pos_z + car_data->pos_y + car_data->pos_x;
}

void printData(struct tnfs_car_data *c1) {
	printf("x:%i, y:%i, z:%i, a:%i, s:%i\r\n", c1->pos_x, c1->pos_y, c1->pos_z, c1->angle_y, c1->speed);
}

int main(int argc, char **argv) {
	struct tnfs_car_data car_data;
	struct tnfs_car_specs car_specs;

	for (int i = 0; i < 10; ++i) {
		road_surface_type_array[i] = 100;
	}

	dword_122C20 = 0x10;

	car_specs.front_brake_percentage = 0xc000; //70%
	car_specs.front_drive_percentage = 0; //RWD
	car_specs.max_brake_force_1 = 0x133fff;
	car_specs.max_brake_force_2 = 0x133fff;
	car_specs.body_roll_factor = 0x2666; //0.15
	car_specs.body_pitch_factor = 0x2666; //0.15
	car_specs.max_slip_angle = 0x1fe667; //~45deg
	car_specs.max_speed = 0x47c000; //71m/s
	car_specs.max_tire_lateral_force = 0x150000;
	car_specs.thrust_to_acc_factor = 0x66; //1577kg TNFS scale

	car_data.car_specs_ptr = &car_specs;
	car_data.weight_distribution = 0x7e49; //49% front
	car_data.weight_transfer_factor = 0x3028;
	car_data.front_friction_factor = 0xe469a;
	car_data.rear_friction_factor = 0xd10de;
	car_data.wheel_base = 0x7a9; //2.44m TNFS scale
	car_data.wheel_track = 0x3d5; //1.50m TNFS scale
	car_data.front_yaw_factor = 0x107a77;
	car_data.rear_yaw_factor = 0x107a77;
	car_data.gear_speed = 1;
	car_data.gear_speed_selected = 1;
	car_data.throttle = 60;
	car_data.is_throttle_pressed = 1;
	car_data.ctrl_throttle = 1;
	car_data.brake = 0;
	car_data.is_brake_pressed = 0;
	car_data.ctrl_brake = 0;
	car_data.gap3F9[4] = 1; //???
	car_data.surface_type = 0;
	car_data.tire_grip_front = 0xe469a;
	car_data.tire_grip_rear = 0xd10de;
	car_data.dword3D9 = 0;
	car_data.dword3E1 = 0;

	car_data.pos_x = 10;
	car_data.pos_y = 0;
	car_data.pos_z = 15;
	car_data.angle_x = 0;
	car_data.angle_y = 0; //uint32 0 to 16777215(0xFFFFFF)
	car_data.angle_z = 0;
	car_data.angular_speed = 0;
	car_data.speed_x = 0;
	car_data.speed_y = 0;
	car_data.speed_z = 10000;
	car_data.speed = 10000;
	car_data.speed_drivetrain = 10000;
	car_data.speed_local_lon = 10000;
	car_data.speed_local_lat = 0;
	car_data.steer_angle = -1769472; //int32 -1769472 to +1769472
	car_data.road_segment_a = 0;
	car_data.road_segment_b = 0;
	car_data.game_status = 1;

	printData(&car_data);
	for (int i = 0; i < 10; ++i) {
		tnfs_physics_main(&car_data);
		printData(&car_data);
	}

	return 0;
}


