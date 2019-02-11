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
  int distance;
  int speed;
  switch (automode)  {
    case 1: {
      distance=300;
      speed=100;
      leftfront.move_relative(distance, speed); // Moves xxx units forward
      leftback.move_relative(distance, speed); //
      rightfront.move_relative(distance, speed); //
      rightback.move_relative(distance, speed); //
      break;
    }
    case 2: {
      distance=-300;
      speed=100;
      leftfront.move_relative(distance, speed); // Moves xxx units forward
      leftback.move_relative(distance, speed); //
      rightfront.move_relative(distance, speed); //
      rightback.move_relative(distance, speed); //
      break;
    }

    case 3:  {
      distance=790;
      speed=100;
      leftfront.move_relative(-distance, speed); // left turn
      leftback.move_relative(-distance, speed); //
      rightfront.move_relative(distance, speed); //
      rightback.move_relative(distance, speed); //
      break;
    }
    case 4: {
      distance=-790;
      speed=100;
      leftfront.move_relative(-distance, speed); // Right turn
      leftback.move_relative(-distance, speed); //
      rightfront.move_relative(distance, speed); //
      rightback.move_relative(distance, speed); //
      break;
    }
    default : {

    }

  }

}
