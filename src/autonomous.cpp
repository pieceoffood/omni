#include "main.h"
#include "config.hpp"
#include "cmath"
#include <fstream>
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


 void moving (double distance, int speed)
 {
   double ticks = (distance*900)/(4*M_PI);
   double startpoint = leftfront.get_position();
   double error=fabs(ticks) - fabs(leftfront.get_position()-startpoint);
   leftfront.move_relative  (ticks, speed);
   leftback.move_relative   (ticks, speed);
   rightfront.move_relative (ticks, speed);
   rightback.move_relative  (ticks, speed);

   while ( error>0 ) {
     pros::delay(3);
   }
   pros::delay(10);
 }
 void turning (int left, int speed)
 {
   double ticks = 735*left;
   double startpoint = leftfront.get_position();
   double error=fabs(ticks) - fabs(leftfront.get_position()-startpoint);
   leftfront.move_relative  (-ticks, speed);
   leftback.move_relative   (-ticks, speed);
   rightfront.move_relative (ticks, speed);
   rightback.move_relative  (ticks, speed);

   while ( error>0 ) {
     pros::delay(3);
   }
   pros::delay(10);
 }


void autonomous() {
  std::ofstream LogFile;
  LogFile.open("/usd/logfile.txt");

  redblue side = red; // red or blude, make turn in opposite when on blue side
  frontback isfront = front; // front or back
  switch (automode)  {
    case 1: {
      side=red;
      basemovement(12,100);
      basemovement(-12,100);
      break;
    }
    case 2: {
      side=blue;
      basemovement(-12,100);
      break;
    }

    case 3:  {
      side=red;
      turning(1*side, 150);//
      break;
    }
    case 4: {
      side=blue;
      turning(1*side, 150); //
      break;
    }
    default : {

    }
  }


  // automode value
  // 1 red front
  // 2 blue front
  // 3 red back
  // 4 blue back
  // 5 skill program 1
  // 6 skill program 2
  switch(automode)
  {
    case 1:
    {
      side=red;
      isfront=front;
      break;
    }
    case 2:
    {
      side=blue;
      isfront=front;
      break;
    }
    case 3:
    {
      side=red;
      isfront=back;
      break;
    }
    case 4:
    {
      side=blue;
      isfront=back;
      break;
    }
    case 5: // skill programe 1
    {
      // add code here
    }
    case 6: // skill programe 2
    {
      // add code here
    }
    default:
    {
      side=red;
      isfront=front;
      break;
    }
  }

  // four automode program
  switch (isfront) {
    case front : { //front
      if (side==blue) {
        master.print   (0, 0, "bluefront: %d", automode);
      } else {
         master.print  (0, 0, "redfront:  %d", automode);
      }
      moving (-45, 100); // move back to hit the low flag

      moving (70, 100); //move forwards
      turning   (1*side, 100); //turn left
      pros::delay (1000);

      moving (-62, 100); //park on the platform
      break;
      }

    case back : { //back
      if (side==blue) {
        master.print(0, 0, "blueback:  %d", automode);
      } else {
        master.print(0, 0, "redback:   %d", automode);
      }

      moving (-35, 100); //move forwards

      ballintake.move (200); //get ball under cap
      pros::delay  (1500);
      ballintake.move (0);

      moving (5, 100); //forwards

      turning     (-1*side, 100); //turn right


      moving     (-42, 100);
      break;
    }
    default : {
      break;
    }
  }

  master.clear();
  LogFile<< " automode,"  << automode << ","<< leftfront.get_position() << "\n" ;
  LogFile.close();

}
