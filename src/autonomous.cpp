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
