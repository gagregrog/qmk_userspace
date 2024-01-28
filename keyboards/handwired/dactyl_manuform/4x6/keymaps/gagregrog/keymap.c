#include QMK_KEYBOARD_H
#include "gagregrog.h"

enum layers {
  _BASE,
  _NUMPAD,
  _MEDIA,
  _WINDOW,
  _MOUSE,
  _GAME,
  _RESET,
};

// layer switches
#define NUMPAD    TT(_NUMPAD)
#define MEDIA     TT(_MEDIA)
#define BASE      TT(_BASE)
#define TO_BASE   TO(_BASE)
#define WINDOW    TT(_WINDOW)
#define GAME      TO(_GAME)
#define MS_GRV    LT(_MOUSE, KC_GRV)
#define MO_RST    MO(_RESET)

#define CMD_ESC   LGUI_T(KC_ESC)
#define VOICE     LGUI(KC_F5)

#define DUP       LGUI(LSFT(KC_D))
#define ROW       LGUI(LSFT(KC_ENTER))

#define COPY      LGUI(KC_C)
#define PASTE     LGUI(KC_V)
#define CUT       LGUI(KC_X)
#define UNDO      LGUI(KC_Z)
#define NEXT      LGUI(KC_D)
#define SAVE      LGUI(KC_S)

// Left-hand home row mods - _BASE layer
#define CTRL_A    LCTL_T(KC_A)
#define ALT_R     LALT_T(KC_R)
#define GUI_S     LGUI_T(KC_S)
#define SHFT_T    LSFT_T(KC_T)

// Right-hand home row mods - _BASE layer
#define SHFT_N    RSFT_T(KC_N)
#define GUI_E     RGUI_T(KC_E)
#define ALT_I     LALT_T(KC_I)
#define CTRL_O    RCTL_T(KC_O)

// Left-hand home row mods - _NUMPAD layer
// #define CTRL_A    LCTL_T(KC_A)
#define ALT_LEFT  LALT_T(KC_LEFT)
#define GUI_DOWN  LGUI_T(KC_DOWN)
#define SHFT_RGT  LSFT_T(KC_RIGHT)

// Right-hand home row mods - _NUMPAD layer
#define SHFT_4    RSFT_T(KC_4)
#define GUI_5     RGUI_T(KC_5)
#define ALT_6     LALT_T(KC_6)
#define CTRL_PLS  RCTL_T(KC_PMNS)

uint32_t last_light_mode;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base (colmak dh mod)
     * +-----------------------------------------+                             +-----------------------------------------+
     * | TAB  |   q  |   w  |   f  |   p  |   b  |                             |   j  |   l  |   u  |   y  |   p  |  ;   |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * |CMDESC|   a  |   r  |   s  |   t  |   g  |                             |   m  |   n  |   e  |   i  |   o  |CMD/' |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * | SHFT |   z  |   x  |   c  |   d  |   v  |                             |   k  |   h  |   ,  |   .  |   /  | SHFT |
     * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
     *               |  [   |   ]  |                                                         |   {  |  }   |
     *               +-------------+-------------+                             +-------------+-------------+
     *                             | SPACE|BCKSPC|                             |  =/+ |  ENT |
     *                             +-------------+                             +-------------+
     *                                           +-------------+ +-------------+
     *                                           |   `~ |NUMPAD | |MEDIA |   -  |
     *                                           |------+------| |------+------|
     *                                           | LEFT |RIGHT | |  UP  |DOWN  |
     *                                           +-------------+ +-------------+
     */
    /**
 * Copyright 2023 Gary Gregory Rogers <gagregrog@gmail.com> (@gagregrog)
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
// include all common keycodes / macros
#include "gagregrog.h"

USE_GAGREGROG_KEYMAP

uint32_t last_light_mode;

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

void matrix_init_user(void) {
  rgblight_enable();
};


layer_state_t layer_state_set_user(layer_state_t state) {
  uint32_t current_light_mode = rgblight_get_mode();

  // if we're switching away from a color mode, store it
  if (current_light_mode != RGBLIGHT_MODE_STATIC_LIGHT) {
    last_light_mode = current_light_mode;
  }

  switch (biton32(state)) {
    case _BASE:
      rgblight_mode_noeeprom(last_light_mode);
      break;
    case _MEDIA:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_PURPLE);
      break;
    case _NUMPAD:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_GREEN);
      break;
    case _WINDOW:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_MAGENTA);
      break;
    case _MOUSE:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_TEAL);
      break;
    case _GAME:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_CHARTREUSE);
      break;
    case _RESET:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_RED);
      break;
    default: //  for any other layers, or the default layer
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_ORANGE);
      break;
  }
  return state;
}

void keyboard_post_init_keymap(void) {
  rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
  rgblight_sethsv(HSV_ORANGE);
  last_light_mode = RGBLIGHT_MODE_RAINBOW_SWIRL;
}
