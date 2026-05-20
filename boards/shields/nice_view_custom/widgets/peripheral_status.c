/*
 * Copyright (c) 2023 The ZMK Contributors
 * SPDX-License-Identifier: MIT
 * Cat RAWR!!! animation
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/battery.h>
#include <zmk/display.h>
#include <zmk/events/usb_conn_state_changed.h>
#include <zmk/event_manager.h>
#include <zmk/events/battery_state_changed.h>
#include <zmk/split/bluetooth/peripheral.h>
#include <zmk/events/split_peripheral_status_changed.h>
#include <zmk/usb.h>
#include <zmk/ble.h>

#include "peripheral_status.h"

LV_IMG_DECLARE(cat_frame01); LV_IMG_DECLARE(cat_frame02); LV_IMG_DECLARE(cat_frame03);
LV_IMG_DECLARE(cat_frame04); LV_IMG_DECLARE(cat_frame05); LV_IMG_DECLARE(cat_frame06);
LV_IMG_DECLARE(cat_frame07); LV_IMG_DECLARE(cat_frame08); LV_IMG_DECLARE(cat_frame09);
LV_IMG_DECLARE(cat_frame10); LV_IMG_DECLARE(cat_frame11); LV_IMG_DECLARE(cat_frame12);
LV_IMG_DECLARE(cat_frame13); LV_IMG_DECLARE(cat_frame14); LV_IMG_DECLARE(cat_frame15);
LV_IMG_DECLARE(cat_frame16); LV_IMG_DECLARE(cat_frame17); LV_IMG_DECLARE(cat_frame18);
LV_IMG_DECLARE(cat_frame19); LV_IMG_DECLARE(cat_frame20); LV_IMG_DECLARE(cat_frame21);
LV_IMG_DECLARE(cat_frame22); LV_IMG_DECLARE(cat_frame23); LV_IMG_DECLARE(cat_frame24);
LV_IMG_DECLARE(cat_frame25); LV_IMG_DECLARE(cat_frame26); LV_IMG_DECLARE(cat_frame27);
LV_IMG_DECLARE(cat_frame28); LV_IMG_DECLARE(cat_frame29); LV_IMG_DECLARE(cat_frame30);
LV_IMG_DECLARE(cat_frame31); LV_IMG_DECLARE(cat_frame32); LV_IMG_DECLARE(cat_frame33);
LV_IMG_DECLARE(cat_frame34); LV_IMG_DECLARE(cat_frame35); LV_IMG_DECLARE(cat_frame36);
LV_IMG_DECLARE(cat_frame37); LV_IMG_DECLARE(cat_frame38); LV_IMG_DECLARE(cat_frame39);
LV_IMG_DECLARE(cat_frame40); LV_IMG_DECLARE(cat_frame41); LV_IMG_DECLARE(cat_frame42);
LV_IMG_DECLARE(cat_frame43); LV_IMG_DECLARE(cat_frame44); LV_IMG_DECLARE(cat_frame45);
LV_IMG_DECLARE(cat_frame46); LV_IMG_DECLARE(cat_frame47); LV_IMG_DECLARE(cat_frame48);
LV_IMG_DECLARE(cat_frame49); LV_IMG_DECLARE(cat_frame50); LV_IMG_DECLARE(cat_frame51);
LV_IMG_DECLARE(cat_frame52); LV_IMG_DECLARE(cat_frame53); LV_IMG_DECLARE(cat_frame54);
LV_IMG_DECLARE(cat_frame55); LV_IMG_DECLARE(cat_frame56); LV_IMG_DECLARE(cat_frame57);
LV_IMG_DECLARE(cat_frame58); LV_IMG_DECLARE(cat_frame59); LV_IMG_DECLARE(cat_frame60);
LV_IMG_DECLARE(cat_frame61); LV_IMG_DECLARE(cat_frame62); LV_IMG_DECLARE(cat_frame63);
LV_IMG_DECLARE(cat_frame64); LV_IMG_DECLARE(cat_frame65); LV_IMG_DECLARE(cat_frame66);
LV_IMG_DECLARE(cat_frame67); LV_IMG_DECLARE(cat_frame68); LV_IMG_DECLARE(cat_frame69);
LV_IMG_DECLARE(cat_frame70); LV_IMG_DECLARE(cat_frame71); LV_IMG_DECLARE(cat_frame72);
LV_IMG_DECLARE(cat_frame73); LV_IMG_DECLARE(cat_frame74); LV_IMG_DECLARE(cat_frame75);
LV_IMG_DECLARE(cat_frame76); LV_IMG_DECLARE(cat_frame77); LV_IMG_DECLARE(cat_frame78);

const lv_img_dsc_t *anim_imgs[] = {
    &cat_frame01, &cat_frame02, &cat_frame03, &cat_frame04, &cat_frame05,
    &cat_frame06, &cat_frame07, &cat_frame08, &cat_frame09, &cat_frame10,
    &cat_frame11, &cat_frame12, &cat_frame13, &cat_frame14, &cat_frame15,
    &cat_frame16, &cat_frame17, &cat_frame18, &cat_frame19, &cat_frame20,
    &cat_frame21, &cat_frame22, &cat_frame23, &cat_frame24, &cat_frame25,
    &cat_frame26, &cat_frame27, &cat_frame28, &cat_frame29, &cat_frame30,
    &cat_frame31, &cat_frame32, &cat_frame33, &cat_frame34, &cat_frame35,
    &cat_frame36, &cat_frame37, &cat_frame38, &cat_frame39, &cat_frame40,
    &cat_frame41, &cat_frame42, &cat_frame43, &cat_frame44, &cat_frame45,
    &cat_frame46, &cat_frame47, &cat_frame48, &cat_frame49, &cat_frame50,
    &cat_frame51, &cat_frame52, &cat_frame53, &cat_frame54, &cat_frame55,
    &cat_frame56, &cat_frame57, &cat_frame58, &cat_frame59, &cat_frame60,
    &cat_frame61, &cat_frame62, &cat_frame63, &cat_frame64, &cat_frame65,
    &cat_frame66, &cat_frame67, &cat_frame68, &cat_frame69, &cat_frame70,
    &cat_frame71, &cat_frame72, &cat_frame73, &cat_frame74, &cat_frame75,
    &cat_frame76, &cat_frame77, &cat_frame78,
};

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

struct peripheral_status_state { bool connected; };

static void draw_top(lv_obj_t *widget, lv_color_t cbuf[], const struct status_state *state) {
    lv_obj_t *canvas = lv_obj_get_child(widget, 0);
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &lv_font_montserrat_16, LV_TEXT_ALIGN_RIGHT);
    lv_draw_rect_dsc_t rect_black_dsc;
    init_rect_dsc(&rect_black_dsc, LVGL_BACKGROUND);
    lv_canvas_draw_rect(canvas, 0, 0, CANVAS_SIZE, CANVAS_SIZE, &rect_black_dsc);
    draw_battery(canvas, state);
    lv_canvas_draw_text(canvas, 0, 0, CANVAS_SIZE, &label_dsc,
                        state->connected ? LV_SYMBOL_WIFI : LV_SYMBOL_CLOSE);
    rotate_canvas(canvas, cbuf);
}

static void set_battery_status(struct zmk_widget_status *widget,
                               struct battery_status_state state) {
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
    widget->state.charging = state.usb_present;
#endif
    widget->state.battery = state.level;
    draw_top(widget->obj, widget->cbuf, &widget->state);
}

static void battery_status_update_cb(struct battery_status_state state) {
    struct zmk_widget_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) { set_battery_status(widget, state); }
}

static struct battery_status_state battery_status_get_state(const zmk_event_t *eh) {
    return (struct battery_status_state){
        .level = zmk_battery_state_of_charge(),
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
        .usb_present = zmk_usb_is_powered(),
#endif
    };
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_battery_status, struct battery_status_state,
                            battery_status_update_cb, battery_status_get_state)
ZMK_SUBSCRIPTION(widget_battery_status, zmk_battery_state_changed);
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
ZMK_SUBSCRIPTION(widget_battery_status, zmk_usb_conn_state_changed);
#endif

static struct peripheral_status_state get_state(const zmk_event_t *_eh) {
    return (struct peripheral_status_state){.connected = zmk_split_bt_peripheral_is_connected()};
}

static void set_connection_status(struct zmk_widget_status *widget,
                                  struct peripheral_status_state state) {
    widget->state.connected = state.connected;
    draw_top(widget->obj, widget->cbuf, &widget->state);
}

static void output_status_update_cb(struct peripheral_status_state state) {
    struct zmk_widget_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) { set_connection_status(widget, state); }
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_peripheral_status, struct peripheral_status_state,
                            output_status_update_cb, get_state)
ZMK_SUBSCRIPTION(widget_peripheral_status, zmk_split_peripheral_status_changed);

int zmk_widget_status_init(struct zmk_widget_status *widget, lv_obj_t *parent) {
    widget->obj = lv_obj_create(parent);
    lv_obj_set_size(widget->obj, 160, 68);

    lv_obj_t *top = lv_canvas_create(widget->obj);
    lv_obj_align(top, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_canvas_set_buffer(top, widget->cbuf, CANVAS_SIZE, CANVAS_SIZE, LV_IMG_CF_TRUE_COLOR);

    lv_obj_t *art = lv_animimg_create(widget->obj);
    lv_obj_center(art);
    lv_animimg_set_src(art, (const void **)anim_imgs, 78);
    lv_animimg_set_duration(art, 7800);
    lv_animimg_set_repeat_count(art, LV_ANIM_REPEAT_INFINITE);
    lv_animimg_start(art);
    lv_obj_align(art, LV_ALIGN_TOP_LEFT, 0, 0);

    sys_slist_append(&widgets, &widget->node);
    widget_battery_status_init();
    widget_peripheral_status_init();

    return 0;
}

lv_obj_t *zmk_widget_status_obj(struct zmk_widget_status *widget) { return widget->obj; }
