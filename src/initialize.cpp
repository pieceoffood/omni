#include "main.h"
#include "motor.hpp"

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
    automode= id;
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

lv_obj_t* btn1;
lv_obj_t* btn2;
lv_obj_t* btn3;
lv_obj_t* btn4;
lv_obj_t* sw1;
lv_obj_t* sw2;

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
	lv_theme_t * th = lv_theme_alien_init(210, &lv_font_dejavu_20);     //Set a HUE value and a Font for the Night Theme
  lv_theme_set_current(th);
	lv_obj_t * label = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(label, "auto selection");
	lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 5);


//Create styles for the switch
static lv_style_t bg_style;
static lv_style_t indic_style;
static lv_style_t knob_on_style;
static lv_style_t knob_off_style;
lv_style_copy(&bg_style, &lv_style_pretty);
bg_style.body.radius = LV_RADIUS_CIRCLE;

lv_style_copy(&indic_style, &lv_style_pretty_color);
indic_style.body.radius = LV_RADIUS_CIRCLE;
indic_style.body.main_color = LV_COLOR_HEX(0x9fc8ef);
indic_style.body.grad_color = LV_COLOR_HEX(0x9fc8ef);
indic_style.body.padding.hor = 0;
indic_style.body.padding.ver = 0;

lv_style_copy(&knob_off_style, &lv_style_pretty);
knob_off_style.body.radius = LV_RADIUS_CIRCLE;
knob_off_style.body.shadow.width = 4;
knob_off_style.body.shadow.type = LV_SHADOW_BOTTOM;

lv_style_copy(&knob_on_style, &lv_style_pretty_color);
knob_on_style.body.radius = LV_RADIUS_CIRCLE;
knob_on_style.body.shadow.width = 4;
knob_on_style.body.shadow.type = LV_SHADOW_BOTTOM;



static lv_style_t style_txt;
lv_style_copy(&style_txt, &lv_style_plain);
//style_txt.text.font = &lv_font_dejavu_40;
style_txt.text.letter_space = 2;
style_txt.text.line_space = 1;
style_txt.text.color = LV_COLOR_HEX(0x606060);


//Create a switch and apply the styles
lv_obj_t *sw1 = lv_sw_create(lv_scr_act(), NULL);
lv_sw_set_style(sw1, LV_SW_STYLE_BG, &bg_style);
lv_sw_set_style(sw1, LV_SW_STYLE_INDIC, &indic_style);
lv_sw_set_style(sw1, LV_SW_STYLE_KNOB_ON, &knob_on_style);
lv_sw_set_style(sw1, LV_SW_STYLE_KNOB_OFF, &knob_off_style);
lv_obj_set_free_num(sw1, 1);
lv_obj_align(sw1, NULL, LV_ALIGN_CENTER, 0, -50);
label = lv_label_create(sw1, NULL);
lv_sw_off(sw1);
lv_label_set_text(label, "Red|blue");
lv_sw_set_action(sw1, switchonoff);
//switchonoff(sw1);


//Copy the first switch and turn it ON
lv_obj_t *sw2 = lv_sw_create(lv_scr_act(), sw1);
lv_sw_on(sw2);
lv_obj_align(sw2, NULL, LV_ALIGN_IN_LEFT_MID, 0, 50);
label = lv_label_create(sw2, NULL);
lv_sw_off(sw2);
lv_obj_set_free_num(sw2, 10);
lv_label_set_text(label, "front|back");
lv_sw_set_action(sw2, switchonoff);
master.print(0, 0, "automodesw: %d", automode);

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
