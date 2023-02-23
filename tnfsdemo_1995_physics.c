#include <stdio.h>

// fixed point math macros
#define abs(x) (((x) < 0) ? (-x) : (x))
#define sign(x) ((x) + 0x8000) >> 16)
#define mul(x,y) (((x) * (y) + 0x8000) >> 16)
#define round(x) ((x)) // >> 8)

#define fix15(a) ((a<0 ? a + 0x7ffff : a) >> 15)
#define fix8(a) ((a<0 ? a + 0xff : a) >> 8)
#define fix7(a) ((a<0 ? a + 0x7f : a) >> 7)
#define fix4(a) ((a<0 ? a + 0xf : a) >> 4)
#define fix3(a) ((a<0 ? a + 0x7 : a) >> 3)
#define fix2(a) ((a<0 ? a + 3 : a) >> 2)

#define fixmul(x,y) ((x*y)/10000);

struct tnfs_car_data {
	int pos_x; //00000000
	int pos_y; //00000004
	int pos_z; //00000008
	int angle_x; //0000000C
	int angle_y; //00000010
	int angle_z; //00000014
	int steer_angle; //00000018
	short gap1C[44]; //0000001C
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
	short gap78[749]; //00000078
	int body_roll_lat; //00000365
	int body_roll_lon; //00000369
	short gap36D[68]; //0000036D
	int throttle; //000003B1
	int gap3B5; //000003B5
	int brake; //000003B9
	int dword3BD; //000003BD
	short rpm[2]; //000003C1
	int dword3C9; //000003C9
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
	short gap3F9[12]; //000003F9
	int slide_front; //00000405
	int slide_rear; //00000409
	int slide_unused; //0000040D
	int susp_incl_lat; //00000411
	int susp_incl_lon; //00000415
	int gear_speed_selected; //00000419
	int gear_speed_previous; //0000041D
	int gear_shift_interval; //00000421
	short tire_skid_front; //00000425
	short tire_skid_rear; //00000426
	short gap427[14]; //00000427
	int weight_distr; //00000435
	short gap439[12]; //00000439
	int grip_2_const; //00000445
	int tire_max_grip_rear; //00000449
	int tire_max_grip_front; //0000044D
	int wheelbase; //00000451
	int gap455; //00000455
	int wheelbase_half_front; //00000459
	int wheelbase_half_rear; //0000045D
	short gap461[16]; //00000461
	int *car_specs_ptr; //00000471
	int dword475; //00000475
	short gap479[24]; //00000479
	int brake_c1; //00000491
	int brake_c2; //00000495
	int gap499; //00000499
	int surface_type; //0000049D
	short gap4A1[12]; //000004A1
	int dword4AD; //000004AD
	int abs_brake; //000004B1
	short gap4B5[32]; //000004B5
	int scale_a; //000004D5
	int scale_b; //000004D9
};

struct tnfs_car_specs {
	short gap0[24];  //00000000
	int traction_side; //00000018
	int brake_bias; //0000001C
	short gap20[8]; //00000020
	int friction_const_2; //00000028
	int friction_const_1; //0000002C
	short gap30[676]; //00000030
	int body_roll_lat_max; //000002D4
	int body_roll_lon_max; //000002D8
	short gap2DC[64]; //000002DC
	int dword31C; //0000031C
	int dword_56;
	int dword_164;
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
int math_cos(int a) {
	return 2; //stub
}
int math_atan2(int x, int y) {
	return 0; //stub
}
void math_rotate_2d(int x1, int y1, int angle, int *x2, int *y2) {
	int sin = 1;
	int cos = 0;
	*x2 = x1 * cos + y1 * sin;
	*y2 = y1 * sin + x1 * cos;
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
int tnfs_engine_calculate_thrust(struct tnfs_car_data *car_data) {
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

void tnfs_physics_handbrake() {
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

void tnfs_physics_005(struct tnfs_car_data *car_data) {
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
	car_data->dword3C9 = 2 * (mul(v5, v4) >> 7) + v8;

	car_data->tire_grip_front += car_data->dword3C9;
	if (car_data->tire_grip_front < 0)
		car_data->tire_grip_front = 0;

	car_data->tire_grip_rear += car_data->dword3C9;
	if (car_data->tire_grip_rear < 0)
		car_data->tire_grip_rear = 0;
}

/*
 read grip table for a given slip angle
 offset 884, table size 2 x 512 bytes

 Toyota Supra values
 off	fr	rr
 000	2	124
 116	80	128
 188	111
 237	126
 396		127
 397	128
 406		127
 437	128
 442		121
 463	119
 476		115
 491		111
 503		108
 510	98	59
 512
 */
int tnfs_physics_slidetable(struct tnfs_car_data *a1, signed int slip_angle, int is_rear_wheels) {
	signed int v4;

	v4 = slip_angle;
	if (slip_angle > 2097150)
		v4 = 2097150;

	//original
	//return *(a1->car_specs_ptr + (is_rear_wheels << 9) + (v4 >> 12) + 884) << 9;

	//stub value
	return 127;
}

void tnfs_physics_limit_max_grip(struct tnfs_car_data *car_data, //
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

	// never called
	if (car_data->dword4AD) {
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

		if ((car_data->brake <= 150 || *&car_data->brake_c2) && car_data->handbrake == 0) {
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
			*force_lat = fix8(v11 * *force_lat);
			*force_lon = fix8(v11 * *force_lon);
			// ANGLE WARNING!!
			printf("ANGLE WARNING!! %s=%d", (char*) 'a', f_lat_abs);
		}
	}

	// unused
	if (&car_data->slide_rear == slide) {
		if ((*force_lon > 0 && car_data->speed_local_lon > 0) || (*force_lon < 0 && car_data->speed_local_lon < 0)) {
			car_data->slide_unused = v12;
		}
	}
}

void tnfs_physics_tire_forces(struct tnfs_car_data *_car_data, //
		int *_result_Lat, int *_result_Lon, //
		int force_Lat, int force_Lon, //
		signed int steering, int thrust_force, int braking, //
		int is_front_wheels) {

	signed int total_force2;
	int v11;
	int v12;
	int v13;
	int v14;
	int v15;
	int f_lat_loc_abs2;
	int f_lon_loc_abs2;
	int braking_abs;
	int thrust_abs;
	int f_lat_loc_abs;
	int force_lat_local_abs2;
	int v23;
	int v24;
	int v25;
	int force_lat_local_abs;
	struct tnfs_car_data *car_data;
	int *slide;
	short *skid;
	signed int max_grip;
	signed int total_force;
	int v34;
	int force_lon_local;
	int force_lat_local;
	int result_brake_thrust;
	int v38;
	int v39;
	struct tnfs_car_specs *car_specs;

	car_data = _car_data;
	car_specs = &car_data->car_specs_ptr;

	v34 = 0;
	if (*&_car_data->gap3F9[4] == 0) {
		*_result_Lon = 0;
		*_result_Lat = *_result_Lon;
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
		total_force2 = math_atan2(-force_lon_local, force_lat_local_abs);
	else
		total_force2 = math_atan2(force_lon_local, force_lat_local_abs);

	total_force = total_force2;
	if (total_force2 > car_specs->dword_164) {
		total_force = car_specs->dword_164;
		*skid |= 1u;
	}

	if ( fix2(5 * max_grip) >= abs(braking) || (*&car_data->brake_c2 != 0 && car_data->handbrake == 0)) {
		// not locked wheels

		// calculate lateral grip force
		v11 = tnfs_physics_slidetable(car_data, total_force, is_front_wheels - 1);
		v39 = v11;

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
			if (force_lat_local_abs2 > v23 && total_force > 0xf0000) {
				if (total_force <= 1966080) {
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
			braking = -braking;

		result_brake_thrust = braking + thrust_force;
		thrust_abs = abs(thrust_force);
		braking_abs = abs(braking);

		if (thrust_abs <= braking_abs) {
			//deceleration
			v15 = abs(result_brake_thrust);
			v14 = abs(force_lon_local);
			if (v15 < v14) {
				if (force_lon_local <= 0) {
					v12 = abs(result_brake_thrust);
					force_lon_local = -v12;
				} else {
					v13 = abs(result_brake_thrust);
					force_lon_local = v13;
				}
			}
			tnfs_physics_limit_max_grip(car_data, &force_lat_local, &force_lon_local, max_grip, slide);
			*slide |= v34;
			if (car_data->abs_brake)
				*slide = 0;

		} else {
			//acceleration
			force_lon_local = result_brake_thrust;
			f_lon_loc_abs2 = abs(force_lon_local);
			f_lat_loc_abs2 = abs(force_lat_local);
			if (f_lat_loc_abs2 + f_lon_loc_abs2 <= max_grip) {
				tnfs_physics_limit_max_grip(car_data, &force_lat_local, &force_lon_local, max_grip, slide);
			} else {
				*skid = 2;
				if (f_lon_loc_abs2 > max_grip && dword_D8AE4 && !*&car_data->brake_c1)
					force_lat_local = fix2(force_lat_local);

				tnfs_physics_limit_max_grip(car_data, &force_lat_local, &force_lon_local, max_grip, slide);
			}
			if (*slide != 0) {
				*slide *= 8;
			}
			if (*slide < v34) {
				*slide = v34;
			}

			force_lat_local = -v38;
		}

	} else {
		// locked wheels: hard braking or handbrake
		v25 = abs(force_lon_local);
		if (v25 > max_grip)
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
void tnfs_physics_001b(struct tnfs_car_data *a1) {
	signed int v2;
	int v3;
	signed int v4;
	int v5;
	signed int v6;
	signed int v7;
	signed int v8;
	int v14;
	signed int v9;
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
	int friction_const_2;
	int friction_const;
	int speed_lat;
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
	car_specs = (struct tnfs_car_specs*) a1->car_specs_ptr;

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

	// brake stuff
	if ((dword_122C20 & 0x10) != 0 && a1->handbrake == 0) {
		a1->abs_brake = *&a1->brake_c2;
		a1->dword4AD = *&a1->brake_c1;
	} else {
		a1->abs_brake = 0;
		a1->dword4AD = 0;
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
	car_data->thrust = tnfs_engine_calculate_thrust(car_data);
	thrust_force = car_data->thrust;

	// unused
	if (car_data->dword4AD != 0 && car_data->gear_speed == 0)
		thrust_force -= fix2(thrust_force);

	car_data->slide_unused = 0;

	// traction forces
	traction_front = (car_specs->traction_side >> 8) * (thrust_force >> 8);
	traction_rear = thrust_force - traction_front;

	// braking forces
	if (car_data->brake <= 240) {
		v2 = (330 * car_data->brake >> 8) * ((car_data->tire_grip_rear + car_data->tire_grip_front) >> 8);
		braking_front = ((car_specs->brake_bias >> 8) * (v2 >> 8));
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
		tnfs_physics_handbrake();
	}

	// correct forces
	speed_lat = abs(car_data->speed_local_lat);
	if (speed_lat < 0x1999 //
	&& ((car_data->speed_local_lon > 0x10000 && car_data->gear_speed == -2) //
	|| (car_data->speed_local_lon < -0x10000 && car_data->gear_speed >= 0))) {
		if (traction_front != 0 && traction_front < car_data->tire_grip_front) {
			traction_front = 0;
			braking_front = car_specs->friction_const_2;
		}
		if (traction_rear != 0 && traction_rear < car_data->tire_grip_rear) {
			traction_rear = 0;
			braking_rear = car_specs->friction_const_2;
		}
	}

	// shift/abs/tcs controls
	if (car_data->throttle >= 40) {
		if (car_data->dword4AD != 0) {
			if ( abs(thrust_force) > 0x70000 && car_data->throttle > 83)
				car_data->throttle -= 12;
		}
	} else {
		car_data->dword4AD = 0;
	}
	if (car_data->brake < 40)
		car_data->abs_brake = 0;
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
	if (car_data->speed_local_lon > car_specs->dword_56 && dword_146475 != 6) {
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
	v3 = mul(car_data->wheelbase, car_data->scale_b * car_data->angular_speed);

	// front and rear forces
	fLat = v3 + -mul(car_data->weight_distr, sLat) - drag_lat / 2;
	rLat = -(sLat - mul(car_data->weight_distr, sLat)) - drag_lat / 2 - v3;
	rLon = -(sLon - mul(car_data->weight_distr, sLon)) - drag_lon / 2;
	fLon = -mul(car_data->weight_distr, sLon) - drag_lon / 2;

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
	tnfs_physics_tire_forces(car_data, &f_F_Lat, &f_F_Lon, fLat, fLon, steering, traction_front, braking_front, 1);
	tnfs_physics_tire_forces(car_data, &f_R_Lat, &f_R_Lon, rLat, rLon, 0, traction_rear, braking_rear, 2);
	force_Lat = f_R_Lat + f_F_Lat;
	force_Lon = f_R_Lon + f_F_Lon;

	// friction constants
	if (car_data->brake > 100 || car_data->handbrake) {
		if (car_data->speed >= 1755054) {
			if (car_data->speed >= 2621440) {
				if (car_specs->friction_const_1 <= car_specs->friction_const_2) {
					friction_const_2 = car_specs->friction_const_2;
				} else {
					friction_const_2 = car_specs->friction_const_1;
				}
				friction_const = friction_const_2;
			} else {
				friction_const = car_specs->friction_const_1;
			}
		} else {
			friction_const = car_specs->friction_const_2;
		}
		if (force_Lon <= 0) {
			force_lon_total = -force_Lon;
		} else {
			force_lon_total = f_R_Lon + f_F_Lon;
		}
		if (force_lon_total > friction_const) {
			if (force_Lon < 0) {
				force_Lon = -friction_const;
			} else {
				force_Lon = friction_const;
			}
		}
		if (dword_146475 == 3 && (car_data->road_segment_a <= 97 || car_data->road_segment_a >= 465)) {
			v33 = force_Lat <= 0 ? -force_Lat : f_R_Lat + f_F_Lat;
			if (v33 > friction_const) {
				if (force_Lat < 0) {
					force_Lat = -friction_const;
				} else {
					force_Lat = friction_const;
				}
			}
		}
	}

	v61 = car_data->dword3C9 + car_specs->dword31C;
	if (v61 < 0)
		v61 = 0;

	if ( abs( force_Lat ) > v61) {
		if (force_Lat < 0)
			force_Lat = -v61;
		else
			force_Lat = v61;
	}

	// calculate grip forces
	v5 = (force_Lon >> 8) * (car_data->grip_2_const >> 8);

	v6 = (car_data->tire_max_grip_front - v5) * road_surface_type_array[4 * car_data->surface_type];
	car_data->tire_grip_front = fix8(v6);

	v7 = (v5 + car_data->tire_max_grip_rear) * road_surface_type_array[4 * car_data->surface_type];
	car_data->tire_grip_rear = fix8(v7);

	tnfs_physics_005(car_data);

	// suspension bounce 1
	v8 = *(car_data->car_specs_ptr + 812) * force_Lon;
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

	// suspension bounce 2
	if (car_data->speed_local_lat + car_data->speed_local_lon <= 6553) {
		car_data->body_roll_lat += -car_data->body_roll_lat / 2;
		car_data->body_roll_lon += -car_data->body_roll_lon / 2;
	} else {
		car_data->body_roll_lat += (-((car_data->susp_incl_lat >> 8) * (car_specs->body_roll_lat_max >> 8)) - car_data->body_roll_lat) / 2;
		car_data->body_roll_lon += (-((car_data->susp_incl_lon >> 8) * (car_specs->body_roll_lon_max >> 8)) - car_data->body_roll_lon) / 2;
	}

	// calc angular speed
	v71 = (mul(car_data->wheelbase_half_rear, f_R_Lat)) - (mul(car_data->wheelbase_half_front, f_F_Lat));
	car_data->angular_speed += mul(car_data->scale_a, v71);

	if ( abs(car_data->angular_speed) > 9830400) {
		if (car_data->angular_speed >= 0)
			car_data->angular_speed = 9830400;
		else
			car_data->angular_speed = -9830400;
	}

	// move car rotation
	v9 = mul(car_data->scale_a, car_data->angular_speed);
	car_data->angle_y += fix2(v9) + v9;

	// move angle longitudinal
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

	// unsigned angle
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

void printPosition(struct tnfs_car_data *c1) {
	printf("x:%i, y:%i, a:%i, s:%i\r\n", c1->pos_x, c1->pos_z, c1->angle_y, c1->speed);
}

int main(int argc, char **argv) {
	struct tnfs_car_data car_data;
	struct tnfs_car_specs car_specs;

	for (int i = 0; i < 10; ++i) {
		road_surface_type_array[i] = 1000;
	}

	car_specs.brake_bias = 1;
	car_specs.traction_side = 1;
	car_specs.friction_const_1 = 1;
	car_specs.friction_const_2 = 1;

	car_data.car_specs_ptr = &car_specs;
	car_data.weight_distr = 0x7f11;
	car_data.tire_grip_front = 0xc2c4d;
	car_data.tire_grip_rear = 0xf3760;
	car_data.tire_max_grip_front = 797773;
	car_data.tire_max_grip_rear = 997216;
	car_data.grip_2_const = 0x2e14;
	car_data.wheelbase_half_front = 0xfddc5;
	car_data.wheelbase_half_rear = 0xfddc5;
	car_data.wheelbase = 0x802;
	car_data.gear_speed = 1;
	car_data.gear_speed_selected = 1;
	car_data.brake = 0;
	car_data.abs_brake = 0;
	car_data.gap3F9[4] = 1; //???

	car_data.pos_x = 10;
	car_data.pos_y = 0;
	car_data.pos_z = 15;
	car_data.angle_x = 0;
	car_data.angle_y = 0;
	car_data.angle_z = 0;
	car_data.angular_speed = 0;
	car_data.speed_x = 0;
	car_data.speed_y = 0;
	car_data.speed_z = 100;
	car_data.speed = 0;
	car_data.speed_drivetrain = 0;
	car_data.steer_angle = 100;
	car_data.road_segment_a = 0;
	car_data.road_segment_b = 0;
	car_data.game_status = 1;

	printPosition(&car_data);

	for (int i = 0; i < 10; ++i) {
		tnfs_physics_001b(&car_data);
		printPosition(&car_data);
	}

	return 0;
}


