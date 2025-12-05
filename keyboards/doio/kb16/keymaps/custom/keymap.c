/* Copyright 2022 DOIO
 * Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
 * Modified 2024 - Added Raw HID layer broadcasting
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "via.h"

// OLED animation
#include "lib/layer_status/layer_status.h"

// Custom HID message types for macro browser communication
#define MSG_LAYER_BROADCAST 0xAA
#define MSG_LAYER_SWITCH    0xBB

// Each layer gets a name for readability
enum layer_names {
    _BASE,
    _FN,
    _FN1,
    _FN2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
                KC_1,     KC_2,    KC_3,    KC_4,     KC_MPLY,
                KC_5,     KC_6,    KC_7,    KC_8,     TO(_FN),
                KC_9,     KC_0,    KC_UP,   KC_ENT,   KC_MUTE,
                MO(_FN2), KC_LEFT, KC_DOWN, KC_RIGHT
            ),

    [_FN] = LAYOUT(
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______, TO(_FN1),
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______
            ),

    [_FN1] = LAYOUT(
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______, TO(_FN2),
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______
            ),

    [_FN2] = LAYOUT(
                RM_SPDU, RM_SPDD, EE_CLR,  QK_BOOT, _______,
                RM_SATU, RM_SATD, _______, _______, TO(_BASE),
                RM_TOGG, RM_NEXT, RM_HUEU, _______, _______,
                _______, RM_VALU, RM_HUED, RM_VALD
            ),
};

// Broadcast layer change to host application via Raw HID
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);
    uint8_t data[32] = {0};
    data[0] = MSG_LAYER_BROADCAST;
    data[1] = layer;
    raw_hid_send(data, 32);
    return state;
}

// Handle unhandled VIA commands - this is called for command IDs VIA doesn't recognize
bool via_command_kb(uint8_t *data, uint8_t length) {
    // Handle our custom layer switch command
    if (data[0] == MSG_LAYER_SWITCH) {
        layer_move(data[1]);
        return true;  // We handled this command
    }
    return false;  // Let VIA handle other commands
}

#ifdef OLED_ENABLE
    bool oled_task_user(void) {
        render_layer_status();
        return true;
    }
#endif

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN]   = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_FN1]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_FN2]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif
