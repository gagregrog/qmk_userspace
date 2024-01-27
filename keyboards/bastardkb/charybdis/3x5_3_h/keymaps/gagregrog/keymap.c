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

#ifdef RGBLIGHT_ENABLE
  const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {25, 12, 5};
#endif

void keyboard_post_init_keymap(void) {
  #ifdef RGB_MATRIX_ENABLE
    rgblight_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
    rgblight_sethsv(HSV_ORANGE);
  #endif
}
