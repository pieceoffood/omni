#include "main.h"
#include "motor.hpp"
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */


void autonomous() {
/*
  pros::Controller master(pros::E_CONTROLLER_MASTER);
  //pros::Motor motor (8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor leftfront(1, true);
  pros::Motor leftback(2, true);
  pros::Motor rightfront(3);
  pros::Motor rightback(4);
  pros::Motor liftleft(5);
  pros::Motor liftright(6, true);
*/
  leftfront.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  rightfront.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  leftback.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  rightback.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  liftleft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  liftright.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);


  leftfront.move_absolute(100, 100); // Moves 100 units forward
  leftback.move_absolute(100, 100); //
  rightfront.move_absolute(100, 100); //
  rightback.move_absolute(100, 100); //

  leftfront.set_zero_position(80);//Sets the zero position for the motor in its encoder units.
  leftback.set_zero_position(80);//Sets the zero position for the motor in its encoder units.
  rightfront.set_zero_position(80);//Sets the zero position for the motor in its encoder units.
  rightback.set_zero_position(80);//Sets the zero position for the motor in its encoder units.

  leftfront.move_absolute(100, 100); // Moves 120 units forward
  leftback.move_absolute(100, 100); // Moves 120 units forward
  rightfront.move_absolute(100, 100); // Moves 120 units forward
  rightback.move_absolute(100, 100); // Moves 120 units forward
  pros::delay(2);

  leftfront.move_absolute(100, 100); // Moves 100 units forward
  leftback.move_absolute(100, 100); //
  rightfront.move_absolute(100, 100); //
  rightback.move_absolute(100, 100); //
  while (!(
            (leftfront.get_position() < 105) && (leftfront.get_position() > 95) &&
            (rightfront.get_position() < 105) && (rightfront.get_position() > 95)
          )) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
    pros::delay(2);
  }


  leftfront.tare_position(); //Sets the “absolute” zero position of the motor to its current position.
  rightfront.tare_position();//Sets the “absolute” zero position of the motor to its current position.
  leftfront.move_absolute(100, 100); // Moves 100 units forward
  leftback.move_absolute(100, 100); //
  rightfront.move_absolute(100, 100); //
  rightback.move_absolute(100, 100); //
  while (!(
            (leftfront.get_position() < 105) && (leftfront.get_position() > 95) &&
            (rightfront.get_position() < 105) && (rightfront.get_position() > 95)
          )) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
    pros::delay(2);
  }

}
