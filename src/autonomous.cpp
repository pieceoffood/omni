#include "main.h"
#include "config.hpp"
#include "cmath"
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
 void basemovement(double distance, int speed)
 {
   double ticks=(distance*900)/(4*M_PI);
   leftfront.move_relative  (ticks, speed);
   leftback.move_relative   (ticks, speed);
   rightfront.move_relative (ticks, speed);
   rightback.move_relative  (ticks, speed);
 }
 void baseturn(int left, int speed)
 {
   double ticks=735*left;
   leftfront.move_relative  (-ticks, speed);
   leftback.move_relative   (-ticks, speed);
   rightfront.move_relative (ticks, speed);
   rightback.move_relative  (ticks, speed);
 }

void autonomous() {
  double distance;
  int speed;
  redblue side=red;
  switch (automode)  {
    case 1: {
      side=red;
      basemovement(12,100);
      break;
    }
    case 2: {
      side=blue;
      basemovement(-12,100);
      break;
    }

    case 3:  {
      side=red;
      baseturn(1*side, 50);//
      break;
    }
    case 4: {
      side=blue;
      baseturn(-1*side, 50); //
      break;
    }
    default : {

    }

  }

}
