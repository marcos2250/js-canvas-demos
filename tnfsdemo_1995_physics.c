#include <stdio.h>

// fixed point math macros
#define FixHalfRound(x, bits)   (((x) + (1 << (bits-1))) >> bits)
#define FixFloorSigned(x, bits) ((x) / (1 << bits))
#define M_INT_2(a,b) (((a) << 16) | (b))
#define abs(x) (((x) < 0) ? (-x) : (x))
#define sign(x) ((x) + 0x8000) >> 16)
#define mul(x,y) (((x) * (y) + 0x8000) >> 16)

#define fix15(a) ((a<0 ? a + 0x7ffff : a) >> 15)
#define fix8(a) ((a<0 ? a + 0xff : a) >> 8)
#define fix7(a) ((a<0 ? a + 0x7f : a) >> 7)
#define fix4(a) ((a<0 ? a + 0xf : a) >> 4)
#define fix2(a) ((a<0 ? a + 3 : a) >> 2)

#define fixmul(x,y) (((x)*((((y)-(__CFSHL__((y)>>32,2)+4*(y)>>32)))>>2)+(y))+0x8000)>>16);


struct tnfs_car_data {
   int pos_x; //00000000
   int pos_y; //00000004
   int pos_z; //00000008
   int angle_x; //0000000C
   int angle_y; //00000010
   int angle_z; //00000014
   int steer_angle; //00000018
   byte gap1C[44]; //0000001C
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
   byte gap78[749]; //00000078
   int body_roll_lat; //00000365
   int body_roll_lon; //00000369
   byte gap36D[68]; //0000036D
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
   byte gap3F9[12]; //000003F9
   int slide_front; //00000405
   int slide_rear; //00000409
   int slide_unused; //0000040D
   int susp_incl_lat; //00000411
   int susp_incl_lon; //00000415
   int gear_speed_selected; //00000419
   int gear_speed_previous; //0000041D
   int gear_shift_interval; //00000421
   byte tire_skid_front; //00000425
   byte tire_skid_rear; //00000426
   byte gap427[14]; //00000427
   int dword435; //00000435
   byte gap439[12]; //00000439
   int dword445; //00000445
   int tire_max_grip_rear; //00000449
   int tire_max_grip_front; //0000044D
   int wheelbase; //00000451
   int gap455; //00000455
   int wheelbase_half_front; //00000459
   int wheelbase_half_rear; //0000045D
   byte gap461[16]; //00000461
   int* car_specs_ptr; //00000471
   int dword475; //00000475
   byte gap479[24]; //00000479
   int brake_c1; //00000491
   int brake_c2; //00000495
   int gap499; //00000499
   int surface_type; //0000049D
   byte gap4A1[12]; //000004A1
   int dword4AD; //000004AD
   int abs_brake; //000004B1
   byte gap4B5[32]; //000004B5
   int scale_a; //000004D5
   int scale_b; //000004D9
}



/* 
* Offset 0003F0FA
* Main physics routine
*/
void tnfs_physics_001b(tnfs_car_data *a1)
{
  signed __int64 v1; // rtt@16
  signed int v2; // STD0_4@36
  int v3; // STC8_4@104
  signed int v4; // edx@106
  int v5; // STC4_4@145
  signed int v6; // edx@145
  signed int v7; // edx@145
  signed int v8; // edx@145
  signed int v9; // STD0_4@167
  signed int v10; // edx@178
  int v11; // eax@178
  int v12; // ecx@178
  signed int v13; // ST34_4@178
  char v14; // t0@255
  int result; // eax@260
  int v16; // [sp+0h] [bp-F4h]@256
  signed int v17; // [sp+4h] [bp-F0h]@247
  signed int v18; // [sp+4h] [bp-F0h]@252
  int v19; // [sp+8h] [bp-ECh]@219
  signed int v20; // [sp+8h] [bp-ECh]@233
  int v21; // [sp+Ch] [bp-E8h]@209
  int v22; // [sp+10h] [bp-E4h]@205
  int v23; // [sp+14h] [bp-E0h]@200
  int v24; // [sp+18h] [bp-DCh]@183
  int v25; // [sp+1Ch] [bp-D8h]@186
  signed int v26; // [sp+28h] [bp-CCh]@174
  signed int v27; // [sp+2Ch] [bp-C8h]@171
  int angle_abs; // [sp+30h] [bp-C4h]@168
  int v29; // [sp+34h] [bp-C0h]@161
  int v30; // [sp+38h] [bp-BCh]@146
  int v31; // [sp+3Ch] [bp-B8h]@149
  int force_lat_abs; // [sp+40h] [bp-B4h]@139
  int v33; // [sp+44h] [bp-B0h]@130
  int force_lon_total; // [sp+48h] [bp-ACh]@118
  void *friction_const_2; // [sp+4Ch] [bp-A8h]@114
  void *friction_const; // [sp+50h] [bp-A4h]@110
  int v37; // [sp+54h] [bp-A0h]@101
  int v38; // [sp+58h] [bp-9Ch]@93
  int v39; // [sp+5Ch] [bp-98h]@96
  int v40; // [sp+60h] [bp-94h]@88
  int thrust_abs; // [sp+64h] [bp-90h]@60
  int speed_lat; // [sp+68h] [bp-8Ch]@40
  int v43; // [sp+6Ch] [bp-88h]@13
  signed int v44; // [sp+70h] [bp-84h]@2
  signed int v45; // [sp+74h] [bp-80h]@5
  tnfs_car_data *car_data; // [sp+78h] [bp-7Ch]@1
  int rLon; // [sp+7Ch] [bp-78h]@104
  int rLat; // [sp+80h] [bp-74h]@104
  int fLon; // [sp+84h] [bp-70h]@104
  int fLat; // [sp+88h] [bp-6Ch]@104
  int *v51; // [sp+8Ch] [bp-68h]@1
  void *braking_rear; // [sp+94h] [bp-60h]@35
  void *braking_front; // [sp+98h] [bp-5Ch]@35
  int traction_rear; // [sp+9Ch] [bp-58h]@34
  int traction_front; // [sp+A0h] [bp-54h]@34
  int drag_lon; // [sp+A4h] [bp-50h]@81
  int drag_lat; // [sp+A8h] [bp-4Ch]@81
  signed int thrust_force; // [sp+ACh] [bp-48h]@30
  signed int v59; // [sp+BCh] [bp-38h]@104
  int steering; // [sp+BCh] [bp-38h]@105
  int v61; // [sp+BCh] [bp-38h]@136
  signed int force_Lon; // [sp+C8h] [bp-2Ch]@107
  int force_lon_adj; // [sp+C8h] [bp-2Ch]@145
  int force_Lat; // [sp+CCh] [bp-28h]@107
  int f_R_Lon; // [sp+D0h] [bp-24h]@107
  int f_R_Lat; // [sp+D4h] [bp-20h]@107
  int f_F_Lon; // [sp+D8h] [bp-1Ch]@107
  int f_F_Lat; // [sp+DCh] [bp-18h]@107
  int sLon; // [sp+E0h] [bp-14h]@104
  int sLat; // [sp+E4h] [bp-10h]@104
  int v71; // [sp+E8h] [bp-Ch]@160
  int v72; // [sp+ECh] [bp-8h]@104
  struct_v73 *car_specs; // [sp+F0h] [bp-4h]@1

  // gather basic car data
  car_data = a1;
  v51 = &dword_144728[116 * a1->dword475];
  dword_D8AE4 = 0;
  car_specs = a1->car_specs_ptr;


  // fast vec2 length
  v44 = abs( a1->speed_x );
  v45 = abs( a1->speed_z );
  if ( v44 <= v45 )
    a1->speed = (v44 >> 2) + v45;
  else
    a1->speed = (v45 >> 2) + v44;


  // fixed values
  a1->scale_a = 2184;
  a1->scale_b = 30;


  // custom scales, not used
  if ( dword_146493 > 1 && dword_1465DD != 0 )
    {
      v43 = (*(dword_132F84[1 - a1->dword475] + 76) - a1->road_segment_b) / 2;
      if ( v43 > 0 )
      {
        if ( v43 > dword_1465DD )
          v43 = dword_1465DD;
        a1->scale_b = 30 - v43;
        LODWORD(v1) = sub_10000;
        HIDWORD(v1) = sub_10000 >> 31;
        a1->scale_a = v1 / a1->scale_b;
      }
  }


  // brake stuff
  if ( (dword_122C20 & 0x10) != 0 && a1->handbrake == 0)
  {
    a1->abs_brake = *&a1->brake_c2;
    a1->dword4AD = *&a1->brake_c1;
  }
  else
  {
    a1->abs_brake = 0;
    a1->dword4AD = 0;
  }


  // car engine control
  if ( dword_122C20 & 4 || a1->gear_speed == -1 )
  {
    tnfs_engine_rev_limiter(a1);
    if ( car_data->gear_RND > 0 )
    {
      switch ( car_data->gear_RND )
      {
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
  if ( car_data->dword4AD != 0 &&  car_data->gear_speed == 0 )
    thrust_force -= fix2(thrust_force);

  car_data->slide_unused = 0;

  // traction forces
  traction_front = (car_specs->traction_side >> 8) * (thrust_force >> 8);
  traction_rear = thrust_force - traction_front;


  // braking forces
  if ( car_data->brake <= 240 )
  {
    v2 = (330 * car_data->brake >> 8) * ((car_data->tire_grip_rear + car_data->tire_grip_front) >> 8);
    braking_front = ((car_specs->brake_bias >> 8) * (v2 >> 8));
    braking_rear = (v2 - braking_front);
  }
  else
  {
    // hard braking
    braking_front = 0x140000;
    braking_rear = 0x140000;
  }
  // handbrake
  if ( car_data->handbrake == 1 )
  {
    traction_rear = 0;
    braking_rear = 0x280000;
    tnfs_physics_handbrake();
  }


  // correct forces
  speed_lat = abs( car_data->speed_local_lat );
  if ( speed_lat < 0x1999
    && (car_data->speed_local_lon > 0x10000 && car_data->gear_speed == -2
     || car_data->speed_local_lon < -0x10000 && car_data->gear_speed >= 0) )
  {
    if ( traction_front != 0 && traction_front < car_data->tire_grip_front )
    {
      traction_front = 0;
      braking_front = car_specs->friction_const_2;
    }
    if ( traction_rear != 0 && traction_rear < car_data->tire_grip_rear )
    {
      traction_rear = 0;
      braking_rear = car_specs->friction_const_2;
    }
  }


  // shift/abs/tcs controls
  if ( car_data->throttle >= 40 )
  {
    if ( car_data->dword4AD != 0 )
    {
      if ( abs(thrust_force) > 0x70000 && car_data->throttle > 83 )
        car_data->throttle -= 12;
    }
  }
  else
  {
    car_data->dword4AD = 0;
  }
  if ( car_data->brake < 40 )
    car_data->abs_brake = 0;
  if ( car_data->gear_speed != car_data->gear_speed_selected )
  {
    car_data->gear_shift_interval = 16;
    car_data->gear_speed_previous = car_data->gear_speed_selected;
    car_data->gear_speed_selected = car_data->gear_speed;
  }
  if ( car_data->gear_shift_interval > 0 )
  {
    if ( car_data->gear_shift_interval > 12 || car_data->dword3BD < 1 )
      --car_data->gear_shift_interval;
    if ( car_data->dword475 == dword_146460
      && car_data->gear_shift_interval == 11
      && !dword_123CC0
      && car_data->dword3BD < 1 )
    {
      tnfs_physics_018(-1, 13, 0, 0, 1, 15728640);
    }
  }


  // aero/drag forces (?)
  drag_lat = tnfs_physics_024(car_data, car_data->speed_local_lat);
  drag_lon = tnfs_physics_024(car_data, car_data->speed_local_lon);
  if ( car_data->speed_local_lon > *(car_data->car_specs_ptr + 56) && dword_146475 != 6 )
  {
    if ( drag_lon > 0 && drag_lon < thrust_force ) {
      drag_lon = abs( thrust_force );
    }
    else if ( drag_lon < 0 ) {
      if ( abs(drag_lon) < abs(thrust_force) ) {
        drag_lon = -abs( thrust_force );
      }
    }
  }



  // BEGIN of car traction/slip trajectory
  v72 = math_abs(car_data->steer_angle + car_data->angle_y);

  // convert to local frame of reference
  math_rotate_2d(
    car_data->speed_x,
    car_data->speed_z,
    -car_data->angle_y,
    &car_data->speed_local_lat,
    &car_data->speed_local_lon);

  // scale speeds
  sLat = car_data->scale_b * car_data->speed_local_lat;
  sLon = car_data->scale_b * car_data->speed_local_lon;

  // sideslip
  v3 = mul(car_data->wheelbase, car_data->scale_b * car_data->angular_speed);

  // front and rear forces
  fLat = v3 + -mul(car_data->dword435, sLat) - drag_lat / 2;
  rLat = -(sLat - mul(car_data->dword435, sLat) - drag_lat / 2 - v3;
  rLon = -(sLon - mul(car_data->dword435, sLon) - drag_lon / 2;
  fLon = -mul(car_data->dword435, sLon) - drag_lon / 2;




  // adjust steer sensitivity
  v59 = car_data->steer_angle;
  if ( car_data->brake <= 200 )
  {
    v4 = fix8(car_data->speed_local_lon) * v59;
    steering = v59 - fix15(v4);
  }
  else
  {
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
  if ( car_data->brake > 100 || car_data->handbrake )
  {
    if ( car_data->speed >= 1755054 )
    {
      if ( car_data->speed >= 2621440 )
      {
        if ( car_specs->friction_const_1 <= car_specs->friction_const_2 )
          friction_const_2 = car_specs->friction_const_2;
        else
          friction_const_2 = car_specs->friction_const_1;
        friction_const = friction_const_2;
      }
      else
      {
        friction_const = car_specs->friction_const_1;
      }
    }
    else
    {
      friction_const = car_specs->friction_const_2;
    }
    if ( force_Lon <= 0 )
      force_lon_total = -force_Lon;
    else
      force_lon_total = f_R_Lon + f_F_Lon;
    if ( force_lon_total > friction_const )
    {
      if ( force_Lon < 0 )
        force_Lon = -friction_const;
      else
        force_Lon = friction_const;
    }
    if ( dword_146475 == 3 && (car_data->road_segment_a <= 97 || car_data->road_segment_a >= 465) )
    {
      v33 = force_Lat <= 0 ? -force_Lat : f_R_Lat + f_F_Lat;
      if ( v33 > friction_const )
      {
        if ( force_Lat < 0 )
          force_Lat = -friction_const;
        else
          force_Lat = friction_const;
      }
    }
  }

  v61 = car_data->dword3C9 + car_specs->dword31C;
  if ( v61 < 0 )
    v61 = 0;
  
  if ( abs( force_Lat ) > v61 ))
  {
    if ( force_Lat < 0 )
      force_Lat = -v61;
    else
      force_Lat = v61;
  }


  // calculate grip forces
  v5 = (force_Lon >> 8) * (car_data->dword445 >> 8);

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
  if ( abs( car_data->speed_local_lon ) + abs( car_data->speed_local_lat ) >= 19660 )
  {
    // car moving
    car_data->speed_local_lat += mul(car_data->scale_a , (drag_lat + force_Lat + car_data->dword3D9) );
    car_data->speed_local_lon += mul(car_data->scale_a, (drag_lon + force_lon_adj + car_data->dword3E1) );
    //3d9 and 3e1: slope/gravity/resistive forces?
  }
  else
  {
    // car stopped
    car_data->speed_local_lat += mul(car_data->scale_a, force_Lat);
    car_data->speed_local_lon += mul(car_data->scale_a, force_lon_adj);

    if ( car_data->gear_speed == -1
      || car_data->throttle == 0 )
    {
      car_data->speed_local_lon = 0;
      car_data->speed_local_lat = 0;
    }
  }


  // rotate back to global frame of reference
  math_rotate_2d(
    car_data->speed_local_lat,
    car_data->speed_local_lon,
    car_data->angle_y,
    &car_data->speed_x,
    &car_data->speed_z);


  // move the car
  car_data->pos_z += fixmul(car_data->scale_a,
                    car_data->speed_z);

  car_data->pos_x -= fixmul(car_data->scale_a,
                    car_data->speed_x);


  // suspension bounce 2
  if ( car_data->speed_local_lat + car_data->speed_local_lon <= 6553 )
  {
    car_data->body_roll_lat += -car_data->body_roll_lat / 2;
    car_data->body_roll_lon += -car_data->body_roll_lon / 2;
  }
  else
  {
    car_data->body_roll_lat += (-((car_data->susp_incl_lat >> 8) * (car_specs->body_roll_lat_max >> 8))
                              - car_data->body_roll_lat)
                             / 2;
    car_data->body_roll_lon += (-((car_data->susp_incl_lon >> 8) * (car_specs->body_roll_lon_max >> 8))
                              - car_data->body_roll_lon)
                             / 2;
  }


  // calc angular speed
  v71 = (mul(car_data->wheelbase_half_rear, f_R_Lat))
      - (mul(car_data->wheelbase_half_front, f_F_Lat));
  car_data->angular_speed += mul(car_data->scale_a, v71);

  if ( abs(car_data->angular_speed) > 9830400 )
  {
    if ( car_data->angular_speed >= 0 )
      car_data->angular_speed = 9830400;
    else
      car_data->angular_speed = -9830400;
  }


  // move car rotation
  v9 = mul(car_data->scale_a, car_data->angular_speed);
  car_data->angle_y += fix2(v9) + v9;


  // move angle longitudinal
  if ( abs( car_data->angle_z ) > 0x30000 )
  {

    v27 = *(dword_12DECC + 36 * (dword_1328E4 & car_data->road_segment_a) + 22) >> 16 << 10;
    if ( v27 > 0x800000 )
      v27 -= 0x1000000;

    if ( dword_1328DC )
      v26 = *(dword_12DECC + 36 * (dword_1328E4 & dword_1328E4 & (car_data->road_segment_a + 1)) + 22) >> 16 << 10;

    else
      v26 = *(dword_12DECC + 36 * (dword_1328E4 & (car_data->road_segment_a + 1)) + 22) >> 16 << 10;

    if ( v26 > 0x800000 )
      v26 -= 0x1000000;


    cos_angle_z = math_cos(car_data->angle_z >> 14);
    iVar2 = fix8(car_data->speed_local_long) * (v26 - v27);
    iVar2 = math_mul(cos_angle_z, fix8(iVar2));
    car_data->angle_y -= fix7(iVar2);
  }



// unsigned angle
  car_data->angle_y = math_abs(car_data->angle_y);


  // collision calculations
  dword_132F74 = car_data->speed_local_lon + car_data->speed_local_vert + car_data->speed_local_lat;
  tnfs_physics_collision_001(car_data);
  if ( dword_122C20 & 4 && dword_DC52C == 1 )
  {
    if ( car_data->speed_local_lon / 2 <= 0 )
      v24 = car_data->speed_local_lon / -2;
    else
      v24 = car_data->speed_local_lon / 2;
    if ( car_data->speed_local_lat <= 0 )
      v25 = -car_data->speed_local_lat;
    else
      v25 = car_data->speed_local_lat;
    if ( v25 > v24 && car_data->speed_local_lat > 0x8000 )
      tnfs_physics_collision_003(87);
    if ( (car_data->slide_front || car_data->slide_rear)
      && car_data->speed > &dword_140000
      && (car_data->tire_skid_rear & 1 || car_data->tire_skid_front & 1) )
    {
      tnfs_physics_collision_003(40);
    }
    if ( !dword_132EFC )
    {
      if ( abs(car_data->speed_local_lon) > 3276 )
      {
        tnfs_physics_collision_003(120);
        dword_132EFC = dword_122CAC + 1;
      }
    }
  }

  if ( v51[113] < abs( car_data->speed_local_lon ) )
  {
    v51[113] = abs( car_data->speed_local_lon );
  }


  // used for debug
  if ( !dword_146483 && dword_146475 == 3 )
  {
    if ( car_data->road_segment_a <= 97 || car_data->road_segment_a >= 465 )
    {
      if ( car_data->speed_local_lon < 13107 )
      {
        dword_D8AFC = dword_122CAC;
        dword_D8B00 = car_data->road_segment_b;
        dword_D8AF0 = 99999;
        dword_D8AF4 = 99999;
        dword_D8AF8 = 99999;
      }
      v19 = dword_122CAC - dword_D8AFC;
      if ( car_data->throttle > 50 && v19 < 1500 && v19 > 100 )
      {
        if ( car_data->speed_local_lon > 1755447 && dword_D8AF0 > v19 )
        {
          dword_D8AF0 = dword_122CAC - dword_D8AFC;
          sub_34309(v19, 0, 0, 0);
          if ( v51[102] > v19 )
            v51[102] = v19;
        }
        if ( car_data->speed_local_lon > 2926182 && dword_D8AF4 > v19 )
        {
          dword_D8AF4 = v19;
          sub_34309(0, v19, 0, 0);
          if ( v51[103] > v19 )
            v51[103] = v19;
        }
      }
      if ( car_data->road_segment_b - dword_D8B00 > 83 )
      {
        dword_D8B00 = &unk_F423F;
        v20 = dword_122CAC - dword_D8AFC;
        if ( dword_D8AF8 > dword_122CAC - dword_D8AFC && v20 < 1000 )
        {
          if ( v20 < v51[107] )
          {
            v51[107] = v20;
            v51[106] = car_data->speed_local_lon;
          }
          sub_34309(0, 0, v20, car_data->speed_local_lon);
          dword_D8AF8 = v20;
        }
      }
      if ( car_data->brake > 50 )
      {
        if ( car_data->speed_local_lon > 2340290 )
          dword_D8AE8 = dword_122CAC;
        if ( car_data->speed_local_lon > 1755447 )
          dword_D8AEC = dword_122CAC;
        if ( car_data->speed_local_lon < 6553 && dword_D8AEC > 0 )
        {
          v17 = dword_122CAC - dword_D8AEC;
          printf('TUNING STATS : 60-0 in seconds %d = feet %d', 100 * (dword_122CAC - dword_D8AEC) / 60, v17);
          sub_343C2(v17, 0);
          dword_D8AEC = 0;
          if ( v51[105] > v17 )
            v51[105] = v17;
        }
        if ( car_data->speed_local_lon < 6553 && dword_D8AE8 > 0 )
        {
          v18 = dword_122CAC - dword_D8AE8;
          printf('TUNING STATS : 80-0 in %d seconds = %d feet', 100 * (dword_122CAC - dword_D8AE8) / 60, v18);
          sub_343C2(0, v18);
          dword_D8AE8 = 0;
          if ( v51[104] > v18 )
            v51[104] = v18;
        }
      }
    }
    if ( car_data->tire_skid_rear )
    {
      v14 = car_data->tire_skid_rear;
   
      if ( abs(car_data->angular_speed) > 3276800 )
        tnfs_physics_collision_003(87);
    }
  }


  dword_132F74 = car_data->pos_z + car_data->pos_y + car_data->pos_x;
}







void tnfs_physics_tire_forces(tnfs_car_data *_car_data, int *_result_Lat, int *_result_Lon, int force_Lat, int force_Lon, signed int steering, int thrust_force, int braking, int is_front_wheels)
{
  _DWORD *result; // eax@2
  signed int total_force2; // eax@10
  int v11; // eax@21
  int v12; // [sp+0h] [bp-8Ch]@90
  int v13; // [sp+4h] [bp-88h]@86
  int v14; // [sp+8h] [bp-84h]@81
  int v15; // [sp+Ch] [bp-80h]@78
  int f_lat_loc_abs2; // [sp+10h] [bp-7Ch]@62
  int f_lon_loc_abs2; // [sp+14h] [bp-78h]@59
  int braking_abs; // [sp+18h] [bp-74h]@55
  int thrust_abs; // [sp+1Ch] [bp-70h]@52
  int f_lat_loc_abs; // [sp+20h] [bp-6Ch]@43
  int v21; // [sp+24h] [bp-68h]@39
  int force_lat_local_abs2; // [sp+28h] [bp-64h]@33
  int v23; // [sp+2Ch] [bp-60h]@32
  int v24; // [sp+30h] [bp-5Ch]@29
  int v25; // [sp+34h] [bp-58h]@23
  int force_lat_local_abs; // [sp+40h] [bp-4Ch]@7
  tnfs_car_data *car_data; // [sp+48h] [bp-44h]@1
  _DWORD *result_Lat; // [sp+4Ch] [bp-40h]@1
  char *slide; // [sp+5Ch] [bp-30h]@4
  char *skid; // [sp+60h] [bp-2Ch]@4
  signed int max_grip; // [sp+64h] [bp-28h]@4
  signed int total_force; // [sp+68h] [bp-24h]@12
  int v34; // [sp+6Ch] [bp-20h]@1
  int force_lon_local; // [sp+78h] [bp-14h]@4
  int force_lat_local; // [sp+7Ch] [bp-10h]@4
  int result_brake_thrust; // [sp+80h] [bp-Ch]@51
  int v38; // [sp+84h] [bp-8h]@28
  int v39; // [sp+88h] [bp-4h]@28

  car_data = _car_data;
  result_Lat = _result_Lat;
  v34 = 0;
  if ( *&_car_data->gap3F9[4] == 0) {
    result = _result_Lat;
    *_result_Lon = 0;
    *_result_Lat = *_result_Lon;
    return;
  }



    if ( is_front_wheels == 1 ) {
      math_rotate_2d(force_Lat, force_Lon, -steering, &force_lat_local, &force_lon_local);
      max_grip = car_data->tire_grip_front;
      skid = &car_data->tire_skid_front;
      slide = &car_data->slide_front;
    } else {
      force_lat_local = force_Lat;
      force_lon_local = force_Lon;
      max_grip = _car_data->tire_grip_rear;
      skid = &_car_data->tire_skid_rear;
      slide = &_car_data->slide_rear;
    }
    *skid = 0;
    dword_132F74 = *_result_Lon + *result_Lat;
   

    force_lat_local_abs = abs( force_lat_local );

    if ( force_lon_local <= 0 )
      total_force2 = math_atan2(-force_lon_local, force_lat_local_abs);
    else
      total_force2 = math_atan2(force_lon_local, force_lat_local_abs);


    total_force = total_force2;
    if ( total_force2 > *(car_data->car_specs_ptr + 164) )
    {
      total_force = *(car_data->car_specs_ptr + 164);
      *skid |= 1u;
    }
    

    if ( fix2(5 * max_grip) >= abs(braking)
      || *&car_data->brake_c2 != 0
      && car_data->handbrake == 0)
    {
      // not locked wheels

      // calculate lateral grip force
      v11 = tnfs_physics_004(car_data, total_force, is_front_wheels - 1);
      v39 = v11;

      v38 = mul(max_grip, v11);
      v24 = abs( force_lat_local );
      if ( v24 > v38 ) {
        v23 = 8 * v38;
        if ( force_lat_local <= 0 )
          force_lat_local_abs2 = -force_lat_local;
        else
          force_lat_local_abs2 = force_lat_local;

        if ( force_lat_local_abs2 > v23 && total_force > 0xf0000 ) {
          if ( total_force <= 1966080 ) {
            f_lat_loc_abs = abs( force_lat_local );
            v34 = fix2(f_lat_loc_abs - v23);
            *skid |= 4u;
          }
          else
          {
            *skid |= 1u;
            v34 = abs( force_lat_local ) - v23;
          }
        }
        if ( force_lat_local <= 0 )
          force_lat_local = -v38;
        else
          force_lat_local = v38;
      }



      if ( force_lon_local <= 0 )
        braking = -braking;

      result_brake_thrust = braking + thrust_force;
 
      thrust_abs = abs( thrust_force );
      braking_abs = abs( braking );

      if ( thrust_abs <= braking_abs ) {
        v15 = abs( result_brake_thrust );
        v14 = abs( force_lon_local );
        if ( v15 < v14 ) {
          if ( force_lon_local <= 0 ) {
            v12 = abs( result_brake_thrust );
            force_lon_local = -v12;
          }
          else
          {
            v13 = abs( result_brake_thrust );
            force_lon_local = v13;
          }
        }
        tnfs_physics_006(car_data, &force_lat_local, &force_lon_local, max_grip, slide);
        *slide |= v34;
        if ( car_data->abs_brake ) *slide = 0;

      }
      else
      {
        force_lon_local = result_brake_thrust;
        f_lon_loc_abs2 = abs( force_lon_local );
        f_lat_loc_abs2 = abs( force_lat_local );
        if ( f_lat_loc_abs2 + f_lon_loc_abs2 <= max_grip ) {
          tnfs_physics_006(car_data, &force_lat_local, &force_lon_local, max_grip, slide);
        }
        else
        {
          *skid = 2;
          if ( f_lon_loc_abs2 > max_grip && dword_D8AE4 && !*&car_data->brake_c1 )
            force_lat_local = fix2(force_lat_local);

          tnfs_physics_006(car_data, &force_lat_local, &force_lon_local, max_grip, slide);
        }
        if ( *slide ) *slide *= 8;
        if ( *slide < v34 ) *slide = v34;
      }


    }
    else
    {
      // locked wheels
      v25 = abs( force_lon_local );
      if ( v25 > max_grip ) *skid |= 1u;
      tnfs_physics_handbrake_2(&force_lat_local, &force_lon_local, max_grip, slide);
    }


    // function return, rotate back to car frame
    if ( *slide > 9830400 )
      *slide = 9830400;

    if ( steering != 0 ) {
      math_rotate_2d(force_lat_local, force_lon_local, steering, &result_Lat, &_result_Lon);
    } else {
      *result_Lat = force_lat_local;
      *_result_Lon = force_lon_local;
    }
  }
 
}







void tnfs_physics_005(tnfs_car_data *car_data)
{
  int v1; // eax@8
  int v2; // ecx@8
  tnfs_car_data *result; // eax@20
  int v4; // [sp+0h] [bp-24h]@13
  int v5; // [sp+4h] [bp-20h]@16
  tnfs_car_data *v6; // [sp+8h] [bp-1Ch]@1
  signed int v7; // [sp+10h] [bp-14h]@10
  signed int v8; // [sp+14h] [bp-10h]@8
  signed int v9; // [sp+1Ch] [bp-8h]@4
  signed int v10; // [sp+20h] [bp-4h]@1

  v6 = car_data;


  v10 = *(dword_12DECC + 36 * (dword_1328E4 & car_data->road_segment_a) + 18) >> 16 << 10;

  if ( v10 > 0x800000 )
    v10 -= 0x1000000;

  if ( dword_1328DC )
    v9 = *(dword_12DECC + 36 * (dword_1328E4 & dword_1328E4 & (car_data->road_segment_a + 1)) + 18) >> 16 << 10;
  else
    v9 = *(dword_12DECC + 36 * (dword_1328E4 & (car_data->road_segment_a + 1)) + 18) >> 16 << 10;
  if ( v9 > 0x800000 )
    v9 -= 0x1000000;

  iVar3 = math_cos(iVar1 - iVar3 >> 14);
  iVar3 = math_mul(iVar3,car_data->speed_local_lon);
  v8 = iVar3 * 4;

  if ( v8 > 0 )
    v8 += v8 >> 1;
  v7 = v6->angle_z;
  if ( v7 > 0x800000 )
    v7 -= 0x1000000;
 
  v4 = abs(v7);
  v5 = abs( v6->speed_local_lon );
  v6->dword3C9 = 2 * ((mul(v5, v4) >> 7) + v8;

  v6->tire_grip_front += v6->dword3C9;
  if ( v6->tire_grip_front < 0 )
    v6->tire_grip_front = 0;

  v6->tire_grip_rear += v6->dword3C9;
  if ( v6->tire_grip_rear < 0 )
    v6->tire_grip_rear = 0;
}











/* convert steering angle */
int tnfs_physics_004(tnfs_car_data *a1, signed int a2, int a3)
{
  signed int v4;

  v4 = a2;
  if ( a2 > 2097150 )
    v4 = 2097150;
  return *(a1->car_specs_ptr + (a3 << 9) + (v4 >> 12) + 884) << 9;
}

// psx version
int tnfs_physics_004(tnfs_car_data *car_data,int turn_rate,int 
is_rear_wheels)
{
  if (0x1ffffe < turn_rate) {
    turn_rate = 0x1ffffe;
  }
  return (uint)*(byte *)(is_rear_wheels * 512 + car_data->car_specs_ptr + 
(turn_rate >> 12) + 884) << 9;
}





/* improve drifting/sliding */
void tnfs_physics_006(tnfs_car_data *car_data, int *force_lat, signed int *force_lon, signed int max_grip, int *slide)
{
  signed int *result; // eax@41
  int f_lat_abs; // [sp+0h] [bp-38h]@2
  signed int f_lon_abs; // [sp+4h] [bp-34h]@5
  tnfs_car_data *v8; // [sp+8h] [bp-30h]@1
  signed int v9; // [sp+14h] [bp-24h]@1
  int v10; // [sp+20h] [bp-18h]@22
  int v11; // [sp+20h] [bp-18h]@26
  signed int *v12; // [sp+24h] [bp-14h]@1
  int f_lon_abs2; // [sp+2Ch] [bp-Ch]@7
  int f_total; // [sp+34h] [bp-4h]@8

  v8 = car_data;
  v9 = max_grip;
  v12 = 0;
 
  // total force
  f_lat_abs = abs( *force_lat );
  f_lon_abs = abs( *force_lon );
  f_lon_abs2 = f_lon_abs;
  if ( f_lat_abs <= f_lon_abs )
    f_total = (f_lat_abs >> 2) + f_lon_abs;
  else
    f_total = (f_lon_abs >> 2) + f_lat_abs;


  // never called
  if ( car_data->dword4AD )
  {
    if ( f_total > max_grip )
    {
      if ( f_lon_abs <= f_total - max_grip )
      {
        *force_lon = 0;
        f_lon_abs2 = 0;
      }
      else
      {
        f_lon_abs2 = f_lon_abs - (f_total - max_grip);
        if ( *force_lon <= 0 )
          *force_lon = -f_lon_abs2;
        else
          *force_lon = f_lon_abs2;
      }
    }
    if ( f_lat_abs <= f_lon_abs2 )
      f_total = (f_lat_abs >> 2) + f_lon_abs2;
    else
      f_total = (f_lon_abs2 >> 2) + f_lat_abs;
  }



  if ( f_total > max_grip )
  {
    // decrease slide
    *slide = f_total - max_grip;

    v10 = f_total;
    if ( f_total > fix4(18 * max_grip) )
      v10 = fix4(18 * max_grip);

    v12 = (v10 - max_grip);

    if ( v10 - max_grip > 0 )
      v9 = max_grip - v12;

    v11 = v9 / fix8(f_total);


    if ( (car_data->brake <= 150 ||  
          *&car_data->brake_c2) 
       && car_data->handbrake == 0)
    {
      if ( *force_lat > max_grip )
          *force_lat = max_grip;
      else if ( *force_lat < -max_grip )
          *force_lat = -max_grip;

      if ( car_data->throttle >= 50 ) {
        *force_lon = fix8(v11 * *force_lon);

      } else { 
        if ( *force_lon > max_grip ) 
             *force_lon = max_grip;
        else if ( *force_lon < -max_grip )
             *force_lon = -max_grip;
      }


    }
    else
    {

      *force_lat = fix8(v11 * *force_lat);
      *force_lon = fix8(v11 * *force_lon);

      // ANGLE WARNING!!
      printf('ANGLE WARNING!! %s=%d', f_lat_abs, v11);
    }
  }


  // unecessary
  if ( &v8->slide_rear == slide )
  {
    if (*force_lon > 0 && v8->speed_local_lon > 0)
      || (*force_lon < 0 && v8->speed_local_lon < 0)
    {
      result = v12;
      v8->slide_unused = v12;
    }
  }

}



/* locked wheels */
void tnfs_physics_handbrake_2(int *force_lat, int *force_lon, signed int max_grip, int *slide)
{
  int result;
  signed int v5;
  int v6;
  int v7;
  int v8;
  signed int v10;
  
  // total force
  v7 = abs( *force_lat );
  v8 = abs( *force_lon );
  if ( v7 <= v8 )
    v10 = (v7 >> 2) + v8;
  else
    v10 = (v8 >> 2) + v7;

  // calculates resulting forces
  if ( v10 > max_grip ) {
    v5 = max_grip - ((3 * max_grip - (__CFSHL__(3 * max_grip >> 31, 3) + 8 * (3 * max_grip >> 31))) >> 3);

    v6 = fix8(v10);

    *force_lat = fix8(v5 / v6 * *force_lat);
    *force_lon = fix8(v5 / v6 * *force_lon);

    *slide = v10 - v5;
  }
}




