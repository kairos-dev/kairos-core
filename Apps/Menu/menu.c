#include "launcher.h"
#include "lv_conf.h"
#include "lvgl.h"

void test_menu(void)
{
    /*Crate the list*/
    static lv_style_t style_btn_rel, style_btn_pr;
    lv_obj_t *label, *list;

    lv_obj_t *scr = lv_obj_create(NULL, NULL);
    lv_scr_load(scr);
    label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, "Menu");

    list = lv_list_create(lv_scr_act(), NULL);
    lv_obj_set_size(list, 128, LV_VER_RES);
    lv_obj_align(list, scr, LV_ALIGN_CENTER, 0, 20);

    /*Add list elements*/
    char voltage[10], bat_voltage[10];

    // sprintf(voltage, "%dmV", get_battery_raw_voltage());
    // sprintf(bat_voltage, "%dmV", get_battery_mv());
    // lv_list_add(list, SYMBOL_FILE, "New", NULL);
    // lv_list_add(list, SYMBOL_DIRECTORY, "Open", NULL);
    lv_list_add(list, NULL, voltage, NULL);
    lv_list_add(list, NULL, bat_voltage, NULL);
    lv_list_add(list, SYMBOL_CLOSE, "Delete", NULL);
    lv_list_add(list, SYMBOL_EDIT, "Edit", NULL);
    lv_list_add(list, SYMBOL_SAVE, "Save", NULL);

    lv_obj_align(label, scr, LV_ALIGN_OUT_TOP_MID, 0, 20);

    /*********************
     * Create new styles
     ********************/
    /*Create styles for the buttons*/
    lv_style_copy(&style_btn_rel, &lv_style_btn_rel);
    style_btn_rel.body.padding.ver = 2;
    style_btn_rel.body.padding.inner = 1;
    style_btn_rel.body.main_color = LV_COLOR_MAKE(0x30, 0x30, 0x30);
    style_btn_rel.body.grad_color = LV_COLOR_BLACK;
    style_btn_rel.body.border.color = LV_COLOR_SILVER;
    // style_btn_rel.body.border.width = 1;
    style_btn_rel.body.border.opa = LV_OPA_50;
    style_btn_rel.body.radius = 0;
    style_btn_rel.text.font = &lv_font_dejavu_20;

    lv_style_copy(&style_btn_pr, &style_btn_rel);
    style_btn_pr.body.padding.ver = 2;
    style_btn_pr.body.padding.inner = 1;
    style_btn_pr.body.main_color = LV_COLOR_MAKE(0x55, 0x96, 0xd8);
    style_btn_pr.body.grad_color = LV_COLOR_MAKE(0x37, 0x62, 0x90);
    style_btn_pr.text.color = LV_COLOR_MAKE(0xbb, 0xd5, 0xf1);
    style_btn_pr.text.font = &lv_font_dejavu_20;
    
    lv_list_set_sb_mode(list, LV_SB_MODE_DRAG);
    lv_list_set_style(list, LV_LIST_STYLE_BG, &lv_style_transp_tight);
    lv_list_set_style(list, LV_LIST_STYLE_SCRL, &lv_style_transp_tight);
    lv_list_set_style(list, LV_LIST_STYLE_BTN_REL, &style_btn_rel); /*Set the new button styles*/
    lv_list_set_style(list, LV_LIST_STYLE_BTN_PR, &style_btn_pr);

    // return scr;
}