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
     error=fabs(ticks) - fabs(leftfront.get_position()-startpoint);
     printf("move error %8.2f\n", error);
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
     error=fabs(ticks) - fabs(leftfront.get_position()-startpoint);
     printf("tturn error %8.2f\n", error);
   }
   pros::delay(10);
 }


void autonomous() {
  std::ofstream LogFile;
  LogFile.open("/usd/logfile.txt");

  redblue side ; // red or blude, make turn in opposite when on blue side
  frontback isfront ; // front or back

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
      break;
    }
    case 6: // skill programe 2
    {
      // add code here
      break;
    }
    default:
    {
      break;
    }
  }
  printf("automode:%d,side: %d,front: %d\n",automode, side, isfront);

  master.print(0, 0, "autois %d", automode);
  if (automode>=1 && automode <=4 ) {
    master.clear();
    switch (isfront) {
      case front : { //front
        if (side==blue) {
          master.print   (0, 0, "bluefront: %d%d%d", automode, blue, isfront);
        } else {
           master.print  (0, 0, "redfront:  %d%d%d", automode, blue, isfront);
        }

        moving (-45,100); // move back to hit the low flag
        pros::delay (10);

        moving (70, 100); //move forwards

        turning   (1*side, 100); //turn left
        pros::delay (10);

        moving (-62, 150); //park on the platform

        break;

      }

      case back : { //back
        if (side==red) {

          master.print(0, 0, "blueback:  %d%d%d", automode, blue, isfront);
        } else {
          master.print(0, 0, "redback:   %d%d%d", automode, blue, isfront);
        }

        moving (-35, 100); //move forwards

        ballintake.move (200); //get ball under cap
        ballintake.move (0);

        moving (5, 50); //forwards

        turning     (-1*side, 50); //turn right
        pros::delay  (1500);

        moving     (-42, 150); //park on the platoform

        break;
      }
      default : {
        master.clear();
        break;
      }
     }
    }
  else  if (automode == 5)
    {
      //skill 1 program
      master.clear();
      master.print(0, 0, "automode:  %d%d%d", automode, blue, isfront);
      moving (36, 100);
      claw.move_absolute(750,200); // close claw
      pros::delay(500);
      lift.move_absolute(150, 200);// lift up a little
      moving (-36, 100);
      lift.move_absolute(0, 100);// lift down
      pros::delay(500);
      claw.move_absolute(0,200); // claw open
      pros::delay(500);
      lift.move_absolute(450, 200);
      pros::delay(500);
      lift.move_absolute(0, 200);
      pros::delay(500);

    }
  else if (automode ==6 )
    {
      //skill 2 program
      master.clear();
      master.print(0, 0, "automode:  %d%d%d", automode, blue, isfront);
    }

  master.clear();
  LogFile<< " automode,"  << automode << ","<< leftfront.get_position() << "\n" ;
  LogFile.close();



  //littlvgl screen
  lv_obj_t * txt = lv_label_create(lv_scr_act(), NULL);
	//lv_obj_set_style(txt, &style_txt);                    /*Set the created style*/
	lv_label_set_long_mode(txt, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
	lv_label_set_recolor(txt, true);                      /*Enable re-coloring by commands in the text*/
	lv_label_set_align(txt, LV_LABEL_ALIGN_CENTER);       /*Center aligned lines*/
	lv_label_set_text(txt, NULL);
	lv_obj_set_width(txt, 300);                           /*Set a width*/
	lv_obj_align(txt, NULL, LV_ALIGN_CENTER, 0, 20);      /*Align to center*/
  char autotext[64];
	sprintf(autotext, "automode: %d\n"
		                "side: %d\n"
										"front/back %d\n"
										,
		       automode, side, isfront
         );
	lv_label_set_text(txt, autotext);

}
