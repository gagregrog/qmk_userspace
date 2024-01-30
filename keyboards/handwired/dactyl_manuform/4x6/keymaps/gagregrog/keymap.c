#include QMK_KEYBOARD_H
// include all common keycodes / macros
#include "gagregrog.h"

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
 */

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
    case _LAYER_COLEMAK_DH_HRM:
    case _LAYER_COLEMAK_DH:
      rgblight_mode_noeeprom(last_light_mode);
      break;
    case _LAYER_QWERTY_HRM:
    case _LAYER_QWERTY:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_GREEN);
      break;
    case _LAYER_NUM:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_MAGENTA);
      break;
    case _LAYER_UTIL:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_CHARTREUSE);
      break;
    case _LAYER_SETTINGS:
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
