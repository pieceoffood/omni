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
/*
	pros::Controller master(pros::E_CONTROLLER_MASTER);
  //pros::Motor motor (8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor leftfront  (1, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
  pros::Motor leftback   (2, pros::E_MOTOR_GEARSET_18, true);
  pros::Motor rightfront (3, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
  pros::Motor rightback  (4, pros::E_MOTOR_GEARSET_18);
  pros::Motor liftleft   (5);
  pros::Motor liftright  (6, true);
	pros::Motor flipper    (7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
*/
  leftfront.set_encoder_units  (pros::E_MOTOR_ENCODER_COUNTS);
  rightfront.set_encoder_units (pros::E_MOTOR_ENCODER_COUNTS);
  leftback.set_encoder_units   (pros::E_MOTOR_ENCODER_COUNTS);
  rightback.set_encoder_units  (pros::E_MOTOR_ENCODER_COUNTS);
  flipper.set_encoder_units    (pros::E_MOTOR_ENCODER_COUNTS);
  liftleft.set_brake_mode      (pros::E_MOTOR_BRAKE_HOLD);
  liftright.set_brake_mode     (pros::E_MOTOR_BRAKE_HOLD);

	int intakecount = 0; // count how many time of button is pressed
	int flippernow;

	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

		// Print to the 0th line of the emulated LCD screen
		pros::lcd::print(0, "Joystick val: %d", master.get_analog(ANALOG_RIGHT_Y));
		pros::lcd::print(3, "flipper: %d", flipper.get_position());
		master.print(0, 0, "Counter: %d", flipper.get_position());

		int left ;
		int right ;

    // use cubic root of the Joystick input to improve operatable.
    // add dead zone of 10. Joystick move between -10 to 10 (in -127 to 127 range) will not move motor
    left  = (abs(master.get_analog  (ANALOG_LEFT_Y))<10) ? 0 : cbrt(master.get_analog  (ANALOG_LEFT_Y));
    right = (abs(master.get_analog  (ANALOG_LEFT_Y))<10) ? 0 : cbrt(master.get_analog (ANALOG_RIGHT_Y));

		leftfront.move  (left);
		leftback.move   (left);
		rightfront.move (right);
		rightback.move  (right);

// arm lift
		if (master.get_digital   (DIGITAL_L1)) {
			liftleft.move_velocity (-100);
			liftright.move_velocity(-100);
		}
		else if (master.get_digital(DIGITAL_L2)) {
			liftleft.move_velocity(40);
			liftright.move_velocity(40);
		}
		else {
			liftleft.move_velocity(0);
			liftright.move_velocity(0);
		}

// intake
    // one press start spinning; press again stop spinning
    intakecount += (master.get_digital(DIGITAL_R1)); // count how many time of button is pressed
    if (intakecount % 2 ==1)  {
      intake.move(200);
    } else {
      intake.move(0);
    };
// catapult
    if (master.get_digital(DIGITAL_R2)) {
      while ( potentiometer.get_value() < 4095 ) {
        catapult.move(200);
        // use potentiometer to control how long/far the catapult motor move
      }

    }


		pros::delay(20);
	}
}
