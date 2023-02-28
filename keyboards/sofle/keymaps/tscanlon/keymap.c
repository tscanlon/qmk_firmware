 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#include QMK_KEYBOARD_H

#include "oled.c"
#include "encoder.c"

// Base layer is the number of layers CYCLE selects from.
#define BASE_LAYERS 3

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE,  // can always be here (4 bytes)
    CYCLE                      // cycle through first BASE_LAYERS (62 bytes)
};

enum custom_layers {
    _QWERTY,
    _WORK,
    _COLEMAK,
    _LOWER
};

// Extra keys are added for rotary encoder support in VIA
#define LAYOUT_via( \
    LA1, LA2, LA3, LA4, LA5, LA6,           RA6, RA5, RA4, RA3, RA2, RA1, \
    LB1, LB2, LB3, LB4, LB5, LB6, LB7, RB7, RB6, RB5, RB4, RB3, RB2, RB1, \
    LC1, LC2, LC3, LC4, LC5, LC6, LE1, RE6, RC6, RC5, RC4, RC3, RC2, RC1, \
    LD1, LD2, LD3, LD4, LD5, LD6, LD7, RD7, RD6, RD5, RD4, RD3, RD2, RD1, \
              LE2, LE3, LE4, LE5, LE6, RE5, RE4, RE3, RE2, RE1 \
    ) \
    { \
        { LA1, LA2, LA3, LA4, LA5, LA6, KC_NO }, \
        { LB1, LB2, LB3, LB4, LB5, LB6, LB7   }, \
        { LC1, LC2, LC3, LC4, LC5, LC6, KC_NO }, \
        { LD1, LD2, LD3, LD4, LD5, LD6, LD7   }, \
        { LE1, LE2, LE3, LE4, LE5, LE6, KC_NO }, \
        { RA1, RA2, RA3, RA4, RA5, RA6, KC_NO }, \
        { RB1, RB2, RB3, RB4, RB5, RB6, RB7   }, \
        { RC1, RC2, RC3, RC4, RC5, RC6, KC_NO }, \
        { RD1, RD2, RD3, RD4, RD5, RD6, RD7   }, \
        { RE1, RE2, RE3, RE4, RE5, RE6, KC_NO } \
    }

//Default keymap. This can be changed in Via. Use oled.c to change beavior that Via cannot change.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_via(
   KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                         KC_6    , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV ,
   KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_VOLU,       KC_PGUP, KC_Y    , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
   KC_LSFT, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_MUTE,       KC_NO  , KC_H    , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
   KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_VOLD,       KC_PGDN, KC_N    , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                  KC_LGUI,KC_LALT , MO(_LOWER), KC_SPC, KC_ENT,           KC_TAB  , KC_BSPC, MO(_LOWER),KC_RCTL, KC_RGUI
),

[_WORK] = LAYOUT_via(
   KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                         KC_6    , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV ,
   KC_DEL , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_VOLU,       KC_PGUP, KC_Y    , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
   KC_NO, KC_A   , LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), LGUI_T(KC_G), KC_MUTE,       KC_NO  , RGUI_T(KC_H)    , RSFT_T(KC_J)   , RCTL_T(KC_K)  , RALT_T(KC_L)   , KC_SCLN, KC_QUOT,
   KC_NO, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_VOLD,       KC_PGDN, KC_N    , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                  KC_LGUI,KC_LALT , MO(_LOWER), KC_SPC, KC_ENT,           KC_TAB  , KC_BSPC, MO(_LOWER),KC_RCTL, KC_RGUI
),

[_COLEMAK] = LAYOUT_via(
   KC_ESC, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                          KC_6    , KC_7   , KC_8   , KC_9   , KC_0   , KC_NO,
   KC_DEL, KC_Q   , KC_W   , KC_F   , KC_P   , KC_G   , KC_VOLU,       KC_PGUP,  KC_J    , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_NO,
   KC_NO, KC_A   , LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), LGUI_T(KC_D), KC_MUTE,       KC_NO  , RGUI_T(KC_H)    , RSFT_T(KC_N)   , RCTL_T(KC_E)  , RALT_T(KC_I)   , KC_O, KC_NO,
   KC_NO , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_VOLD,       KC_PGDN,  KC_N    , KC_M   , KC_COMM,  KC_DOT, KC_SLSH, KC_NO,
                  KC_LGUI,KC_LALT , MO(_LOWER), KC_SPC, KC_ENT,           KC_TAB  , KC_BSPC, MO(_LOWER),KC_RCTL, KC_RGUI
),

[_LOWER] = LAYOUT_via(
  CYCLE, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                         KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
  KC_CAPS, KC_NO, KC_NO  , KC_BSLS, KC_LBRC , KC_GRV,   RGB_MOD,    RGB_VAI, KC_NO, KC_RBRC, KC_QUOT, KC_NO, KC_NO, KC_F12,
  KC_NO, KC_1   , LALT_T(KC_2), LCTL_T(KC_3), LSFT_T(KC_4), LGUI_T(KC_5), KC_MUTE,       KC_NO  , RGUI_T(KC_6)    , RSFT_T(KC_7)   , RCTL_T(KC_8)  , RALT_T(KC_9)   , KC_O, KC_NO,
  KC_NO  , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , _______,    RGB_TOG, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_NO ,
  _______, KC_NO , KC_NO, KC_NO, KC_MINUS, KC_EQL,      RGB_RMOD,   RGB_VAD, KC_LEFT, KC_UP, KC_DOWN, KC_LEFT, KC_NO, _______,
                  _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______
),

};

// Custom keycode handling.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // handling this once instead of in each keycode uses less program memory.
    if ((keycode >= SAFE_RANGE) && !(record->event.pressed)) {
        return false;
    }

    switch (keycode) {
        case CYCLE:
            set_single_persistent_default_layer((1+get_highest_layer(default_layer_state)) % BASE_LAYERS);
            break;
    }

    // this uses less memory than returning in each case.
    return keycode < SAFE_RANGE;
};
