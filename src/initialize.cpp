#include "main.h"
#include "motor.hpp"

  static int automode;

	pros::Controller master(pros::E_CONTROLLER_MASTER);
  //pros::Motor motor (8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor leftfront  (1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
  pros::Motor leftback   (2, pros::E_MOTOR_GEARSET_18, false);
  pros::Motor rightfront (3, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
  pros::Motor rightback  (4, pros::E_MOTOR_GEARSET_18, true);
  pros::Motor liftleft   (11);
  pros::Motor liftright  (12, true);
	pros::Motor intake     (5, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
  pros::Motor catapult   (6, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
	pros::Motor flipper    (7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
	pros::ADIAnalogIn bumper (10);
	pros::ADIAnalogIn potentiameter (9); //potentiameter
  int automode;

	static lv_res_t btn_click_action(lv_obj_t * btn)
{
    uint8_t id = lv_obj_get_free_num(btn);

    printf("Button %d is released\n", id);

    /* The button is released.
     * Make something here */

    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

	leftfront.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
	rightfront.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
	leftback.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
	rightback.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
	liftleft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	liftright.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);


/*Create a title label*/
lv_obj_t * label = lv_label_create(lv_scr_act(), NULL);
lv_label_set_text(label, "auto selection");
lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 5);

/*Create a normal button*/
lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
lv_cont_set_fit(btn1, true, true); /*Enable resizing horizontally and vertically*/
lv_obj_align(btn1, label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
lv_obj_set_free_num(btn1, 1);   /*Set a unique number for the button*/
lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_click_action);

/*Add a label to the button*/
label = lv_label_create(btn1, NULL);
lv_label_set_text(label, "Blue Front");

/*Copy the button and set toggled state. (The release action is copied too)*/
lv_obj_t * btn2 = lv_btn_create(lv_scr_act(), btn1);
lv_obj_align(btn2, btn1, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
lv_btn_set_state(btn2, LV_BTN_STATE_TGL_REL);  /*Set toggled state*/
lv_obj_set_free_num(btn2, 2);               /*Set a unique number for the button*/

/*Add a label to the toggled button*/
label = lv_label_create(btn2, NULL);
lv_label_set_text(label, "Blue Back");

/*Copy the button and set inactive state.*/
lv_obj_t * btn3 = lv_btn_create(lv_scr_act(), btn1);
lv_obj_align(btn3, btn1, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
lv_btn_set_state(btn3, LV_BTN_STATE_REL);   /*Set inactive state*/
lv_obj_set_free_num(btn3, 3);               /*Set a unique number for the button*/

/*Add a label to the inactive button*/
label = lv_label_create(btn3, NULL);
lv_label_set_text(label, "Red Front");

/*Copy the button and set inactive state.*/
lv_obj_t * btn4 = lv_btn_create(lv_scr_act(), btn1);
lv_obj_align(btn4, btn2, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
lv_btn_set_state(btn4, LV_BTN_STATE_REL);   /*Set inactive state*/
lv_obj_set_free_num(btn4, 4);               /*Set a unique number for the button*/

/*Add a label to the inactive button*/
label = lv_label_create(btn4, NULL);
lv_label_set_text(label, "Red Back");

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
