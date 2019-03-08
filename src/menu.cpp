#include "main.h"
#include "config.hpp"
#include <string>

static lv_res_t btnm_action(lv_obj_t * btnm, const char *txt)
{
    printf("Button: %s released\n", txt);
    if (strcmp(txt, "redfront")==0)  {
      automode=1;
      //side=red;
      //isfront=front;
    }
    else if (strcmp(txt, "bluefront")==0) {
      automode=2;
      //side=blue;
      //isfront=front;
    }
    else if (strcmp(txt, "redback")==0) {
      automode=3;
      //side=red;
      //isfront=back;
    }
    else if (strcmp(txt, "blueback")==0) {
      automode=4;
      //side=blue;
      //isfront=back;
    }
    else if (strcmp(txt, "skill 1")==0)   automode=5;
    else if (strcmp(txt, "skill 2")==0)   automode=6;
    else if (strcmp(txt, "no auto")==0)   automode=7;
    else automode=8;
    printf("%s automode %d\n", txt,automode);
    return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}

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
	if (id == 1) {
		if (lv_sw_get_state(sw)) {
			side = red;
		} else {
			side = blue;
		}
	} else
	if (id == 2) {
		if (lv_sw_get_state(sw)) {
			isfront = front;
		} else {
			isfront = back;
		}
	}

		return LV_RES_OK; /*Return OK if the button is not deleted*/
}


void menuButton() {
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
}


void menuSwitch() {
	lv_obj_t * label = lv_label_create(lv_scr_act(), NULL);
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
	lv_obj_set_free_num(sw1, 1);
	lv_label_set_text(label, "Red|blue");
	lv_sw_set_action(sw1, switchonoff);
	//switchonoff(sw1);


	//Copy the first switch and turn it ON
	lv_obj_t *sw2 = lv_sw_create(lv_scr_act(), sw1);
	lv_sw_on(sw2);
	lv_obj_align(sw2, NULL, LV_ALIGN_IN_LEFT_MID, 0, 50);
	label = lv_label_create(sw2, NULL);
	lv_sw_off(sw2);
	lv_obj_set_free_num(sw2, 2);
	lv_label_set_text(label, "front|back");
	lv_sw_set_action(sw2, switchonoff);
}
