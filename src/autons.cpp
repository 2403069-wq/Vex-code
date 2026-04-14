#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 127;
const int TURN_SPEED = 90;
const int SWING_SPEED = 110;
const int SUCC_SPEED = 65;

///
// Constants
///
void default_constants() {
  // PID más rápido (menos frenado)
  chassis.pid_drive_constants_set(12.0, 0.0, 80.0);

  chassis.pid_heading_constants_set(6.0, 0.0, 10.0);
  chassis.pid_turn_constants_set(3.0, 0.0, 14.0, 0.0);
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);

  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);

  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // 🔥 QUITAR LIMITACIÓN DE ACELERACIÓN
  chassis.slew_turn_constants_set(3_deg, 127);
  chassis.slew_drive_constants_set(0_in, 127);
  chassis.slew_swing_constants_set(3_in, 127);

  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(7_in);
  chassis.odom_boomerang_distance_set(16_in);
  chassis.odom_boomerang_dlead_set(0.625);

  chassis.pid_angle_behavior_set(ez::shortest);
}

///
// Drive Example
///

void prueba() {
  chassis.pid_targets_reset();

  // Avanza 24 pulgadas
  chassis.pid_drive_set(32.6_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  // Gira 45 grados
  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  //corrige su posicion
  chassis.pid_drive_set(8_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  // Activa succión
  intake_motors.move(SUCC_SPEED);

  pros::delay(1500);  // mantener prendida 1.5 segundos

  intake_motors.move(0);

  //despues de anotar se regresa
  chassis.pid_drive_set(-50_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(177_deg, TURN_SPEED);
  chassis.pid_wait();

// hacia atras (rápido)
  chassis.pid_drive_set(-25_in, 127, false);
  chassis.pid_wait();

// succion del cartucho en sentido contrario
  intake_motors.move(-127);

//activar piston 
  piston.set_value(true); 
  pros::delay(500);

// hacia adelante (rápido)
  chassis.pid_drive_set(35_in, 127, false);
  chassis.pid_wait();

  pros::delay(1000);
  intake_motors.move(0);

// hacia atras (rápido)
  chassis.pid_drive_set(-37_in, 127, false);
  chassis.pid_wait();

// anotar

  selector.move(-127);
  intake_expul.move(-127);
  almacen.move(127);

  pros::delay(9000);

// apagar todo
  intake_expul.move(0);
  selector.move(0);
  almacen.move(0);
}