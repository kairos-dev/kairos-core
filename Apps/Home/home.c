#include "home.h"
#include "lv_conf.h"
#include "lvgl.h"

void test_home(void)
{
    lv_obj_t *label_date, *label_icons, *label_hour;
    static lv_style_t style_icons, style_hour, style_date;
    
    lv_obj_t * scr = lv_obj_create(NULL, NULL);
    lv_scr_load(scr);
    // Create the icons style
    lv_style_copy(&style_icons, &lv_style_plain);
    style_icons.text.font = &lv_font_dejavu_20;
    style_icons.text.letter_space = 2*10;
    style_icons.text.line_space = 1*10;

    // Create the hour style
    lv_style_copy(&style_hour, &lv_style_plain);
    style_hour.text.font = &lv_font_dejavu_40;
    style_hour.text.letter_space = 2*3;
    style_hour.text.line_space = 1*3;

    // Create the date style
    lv_style_copy(&style_date, &lv_style_plain);
    style_date.text.font = &lv_font_dejavu_10;
    style_date.text.letter_space = 2;
    style_date.text.line_space = 1;

    // Create the icons label
    label_icons = lv_label_create(lv_scr_act(), NULL);
    lv_obj_set_style(label_icons, &style_icons);
    lv_label_set_text(label_icons, " "SYMBOL_BELL SYMBOL_BLUETOOTH SYMBOL_BATTERY_3);
    lv_obj_align(label_icons, scr, LV_ALIGN_IN_TOP_MID, 0, 0);

    // Create the date label
    label_date = lv_label_create(lv_scr_act(), NULL);
    lv_obj_set_style(label_date, &style_date);
    lv_label_set_text(label_date, "Fri 17 Aug");
    lv_obj_align(label_date, scr, LV_ALIGN_CENTER, 0, 0);

    // Create the hour label
    label_hour = lv_label_create(lv_scr_act(), NULL);
    lv_obj_set_style(label_hour, &style_hour);
    lv_label_set_text(label_hour, "19:09");
    lv_obj_align(label_hour, scr, LV_ALIGN_CENTER, 0, 19);

    // return scr;
}
