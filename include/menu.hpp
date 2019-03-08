#include "main.h"

#ifndef MENU_H
#define MENU_H

static lv_res_t btn_long_press_action(lv_obj_t * btn);
static lv_res_t btn_click_action(lv_obj_t * btn);
static lv_res_t switchonoff(lv_obj_t * sw);
static lv_res_t btnm_action(lv_obj_t * btnm, const char *txt);
void menuButton();
void menuSwitch();

#endif
