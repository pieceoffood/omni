#include "main.h"
#include "motor.hpp"
#include <string>

pros::Controller master  (pros::E_CONTROLLER_MASTER);
pros::Controller partner (pros::E_CONTROLLER_PARTNER);
pros::Motor leftfront  (7,  pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor leftback   (8,  pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightfront (9,  pros::E_MOTOR_GEARSET_18, true,  pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightback  (10, pros::E_MOTOR_GEARSET_18, true,  pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor lift       (20, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor claw       (12, pros::E_MOTOR_GEARSET_18, true,  pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor ballintake (19, pros::E_MOTOR_GEARSET_18, false);
pros::Motor catapult   (13, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::ADIDigitalIn limitswitch  (1);
pros::ADIAnalogIn potentiameter (2);
pros::ADIAnalogIn ballshooterp  (3);
pros::ADIDigitalIn limitswitchball(4);
pros::ADIDigitalIn blue (7); // use jumper to select side blue=1 and red=0
pros::ADIDigitalIn back (8); // use jumper to select front=0 and back=1


int automode;

static lv_res_t btn_click_action(lv_obj_t * btn)
	{
    uint8_t id = lv_obj_get_free_num(btn);
		//lv_btn_set_style(btn, LV_BTN_STYLE_REL, &lv_style_btn_tgl_rel);
    printf("Button %d is released\n", id);
		lv_btn_set_state(btn, LV_BTN_STATE_TGL_REL);
		lv_btn_get_state(btn);
    automode= id;
    /* The button is released.
     * Make something here */
    return LV_RES_OK; /*Return OK if the button is not deleted*/
}
static lv_res_t btn_long_press_action(lv_obj_t * btn)
	{
    uint8_t id = lv_obj_get_free_num(btn);
		//lv_btn_set_style(btn, LV_BTN_STYLE_REL, &lv_style_btn_tgl_rel);
    printf("Button %d is released\n", id);
		lv_btn_set_state(btn, LV_BTN_STATE_REL);
    automode= 0;
    /* The button is released.
     * Make something here */
    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t switchonoff(lv_obj_t * sw) {
	uint8_t id = lv_obj_get_free_num(sw);
	if (lv_sw_get_state(sw)) {
		automode =id*1 + automode;
	} else {
		automode =id*0  + automode;
	}
	return LV_RES_OK; /*Return OK if the button is not deleted*/
}


	static lv_res_t btnm_action(lv_obj_t * btnm, const char *txt)
	{
	    printf("Button: %s released\n", txt);
			if (strcmp(txt,"redfront")) {
				automode=1;
			} else if (strcmp(txt,"bluefront")) {
				automode=2;
			}

	    return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
	}




/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

	lift.set_brake_mode          (pros::E_MOTOR_BRAKE_HOLD);
  claw.set_brake_mode          (pros::E_MOTOR_BRAKE_HOLD);
  catapult.set_brake_mode      (pros::E_MOTOR_BRAKE_HOLD);


	/*Create a title label*/
	lv_obj_t * label = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(label, "auto selection");
	lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 5);

	/*Create a normal button*/
	lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
	lv_cont_set_fit(btn1, true, true); /*Enable resizing horizontally and vertically*/
	lv_obj_align(btn1, label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
	lv_btn_set_state(btn1, LV_BTN_STATE_REL);  /*Set toggled state*/
	lv_obj_set_free_num(btn1, 1);   /*Set a unique number for the button*/
	lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_click_action);
	lv_btn_set_action(btn1, LV_BTN_ACTION_LONG_PR, btn_long_press_action);
	/*Add a label to the button*/
	label = lv_label_create(btn1, NULL);
	lv_label_set_text(label, "Red Front");

	/*Copy the button and set release (The release action is copied too)*/
	lv_obj_t * btn2 = lv_btn_create(lv_scr_act(), btn1);
	lv_obj_align(btn2, btn1, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
	lv_btn_set_state(btn2, LV_BTN_STATE_REL);  /*Set toggled state*/
	lv_obj_set_free_num(btn2, 2);               /*Set a unique number for the button*/
	//lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, btn_click_action);
	label = lv_label_create(btn2, NULL);
	lv_label_set_text(label, "Red Back");

	/*Copy the button */
	lv_obj_t * btn3 = lv_btn_create(lv_scr_act(), btn1);
	lv_obj_align(btn3, btn1, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
	lv_btn_set_state(btn3, LV_BTN_STATE_REL);   /*Set inactive state*/
	lv_obj_set_free_num(btn3, 3);               /*Set a unique number for the button*/
	//lv_btn_set_action(btn3, LV_BTN_ACTION_CLICK, btn_click_action);
	label = lv_label_create(btn3, NULL);
	lv_label_set_text(label, "Blue Front");

	/*Copy the button */
	lv_obj_t * btn4 = lv_btn_create(lv_scr_act(), btn1);
	lv_obj_align(btn4, btn2, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
	lv_btn_set_state(btn4, LV_BTN_STATE_REL);   /*Set inactive state*/
	lv_obj_set_free_num(btn4, 4);               /*Set a unique number for the button*/
	//lv_btn_set_action(btn4, LV_BTN_ACTION_CLICK, btn_click_action);
	label = lv_label_create(btn4, NULL);
	lv_label_set_text(label, "Blue Back");

	/*Copy the button */
	lv_obj_t * btn5 = lv_btn_create(lv_scr_act(), btn1);
	lv_obj_align(btn5, btn3, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
	lv_btn_set_state(btn5, LV_BTN_STATE_REL);   /*Set inactive state*/
	lv_obj_set_free_num(btn5, 5);               /*Set a unique number for the button*/
	//lv_btn_set_action(btn4, LV_BTN_ACTION_CLICK, btn_click_action);
	label = lv_label_create(btn5, NULL);
	lv_label_set_text(label, "Skill 1");

	/*Copy the button */
	lv_obj_t * btn6 = lv_btn_create(lv_scr_act(), btn1);
	lv_obj_align(btn6, btn4, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
	lv_btn_set_state(btn6, LV_BTN_STATE_REL);   /*Set inactive state*/
	lv_obj_set_free_num(btn6, 6);               /*Set a unique number for the button*/
	//lv_btn_set_action(btn4, LV_BTN_ACTION_CLICK, btn_click_action);
	label = lv_label_create(btn6, NULL);
	lv_label_set_text(label, "Skill 2");



  master.print(0, 0, "automode: %d", automode);

//automode = lv_sw_get_state(sw1) + lv_sw_get_state(sw2)*2;
//master.print(0, 0, "autoIn0: %d, %d", lv_sw_get_state(sw1),lv_sw_get_state(sw2));

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
/*
	while(1){
		//lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_click_action);
		//lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, btn_click_action);
		//lv_btn_set_action(btn3, LV_BTN_ACTION_CLICK, btn_click_action);
		//lv_btn_set_action(btn4, LV_BTN_ACTION_CLICK, btn_click_action);
		automode = lv_sw_get_state(sw1) + lv_sw_get_state(sw2)*2;
		master.print(0, 0, "autoSW: %d, %d", lv_sw_get_state(sw1),lv_sw_get_state(sw2));
	  pros::delay(500);
	}
	master.print(0, 0, "autoSW2: %d, %d", lv_sw_get_state(sw1),lv_sw_get_state(sw2));
*/
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	//master.print(0, 0, "automode: %d", automode);
}
