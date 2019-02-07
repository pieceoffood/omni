#include "main.h"
#include "motor.hpp"

// prosv5 upload --slot 5
//prosv5 v5 rm-file slot_4.bin --erase-all
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	int intakecount = 0; // count how many time of button is pressed
	int flippernow;
  int left ;
  int right ;

	while (true) {


		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

		// Print to the 0th line of the emulated LCD screen
    pros::lcd::print(1, "Joystick right: %d", right);
		pros::lcd::print(3, "flipper: %d", flipper.get_position());
		master.print(0, 0, "Counter: %d", flipper.get_position());



    // use cubic function of the Joystick input to improve operatable.
    // add dead zone of 10. Joystick move between -10 to 10 (in -127 to 127 range) will not move motor
    left  = (abs(master.get_analog  (ANALOG_LEFT_Y))<10  )? 0 : pow(master.get_analog (ANALOG_LEFT_Y), 3);
    //right = (abs(master.get_analog  (ANALOG_RIGHT_Y))<10 )? 0 : pow((master.get_analog (ANALOG_RIGHT_Y),3);
    if (abs(master.get_analog  (ANALOG_RIGHT_Y))<10 ) {
      right=0;
    } else {
      right = pow(master.get_analog (ANALOG_RIGHT_Y),3);
    }
		leftfront.move  (left);
		leftback.move   (left);
		rightfront.move (right);
		rightback.move  (right);

// arm lift
		if (master.get_digital   (DIGITAL_L1)) {
			liftleft.move_velocity (200);
			liftright.move_velocity(200);
		}
		else if (master.get_digital(DIGITAL_L2) and bumper.get_value() == 0 ) {
      // low dowm arm until hit the bumper
			liftleft.move_velocity(-100);
			liftright.move_velocity(-100);
		}
		else {
			liftleft.move_velocity(0);
			liftright.move_velocity(0);
		}

// intake
    // one press start spinning; press again stop spinning
    intakecount += (master.get_digital(DIGITAL_R1)); // count how many time of button is pressed
    if (intakecount % 2 ==1)  {
      intake.move_velocity(200);
    } else {
      intake.move_velocity(0);
    };
// catapult
    if (master.get_digital(DIGITAL_R2)) {
      while ( potentiometer.get_value() < 4095 ) {
        catapult.move_velocity(200);
        // use potentiometer to control how long/far the catapult motor move
      }

    }

		pros::delay(20);
	}
}
