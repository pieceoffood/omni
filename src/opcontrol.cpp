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
  int left ;
  int right ;
	master.print(0, 0, "automode %d", automode);

	while (true) {


		// Print to the 0 -2 line of controller screen [0-14]

    master.print(1, 0, "potentiameter: %d", potentiameter.get_value());
		master.print(2, 0, "flipper: %8.2f", claw.get_position());


// ballintake
    // one press start spinning; press again stop spinning
    intakecount += (master.get_digital(DIGITAL_R1)); // count how many time of button is pressed
    if (intakecount % 2 ==1)  {
      ballintake.move_velocity(200);
    } else {
      ballintake.move_velocity(0);
    };

		pros::delay(200);
	}
}
