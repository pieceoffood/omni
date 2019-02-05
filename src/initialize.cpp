#include "main.h"
#include "motor.hpp"


	pros::Controller master(pros::E_CONTROLLER_MASTER);
  //pros::Motor motor (8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor leftfront  (1, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
  pros::Motor leftback   (2, pros::E_MOTOR_GEARSET_18, true);
  pros::Motor rightfront (3, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
  pros::Motor rightback  (4, pros::E_MOTOR_GEARSET_18);
  pros::Motor liftleft   (11);
  pros::Motor liftright  (12, true);
	pros::Motor intake     (5, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
  pros::Motor catapult   (6, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
	pros::Motor flipper    (7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
	pros::ADIAnalogIn bumper (10);
	pros::ADIAnalogIn potent (9); //potentiameter



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

	liftleft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	liftright.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
