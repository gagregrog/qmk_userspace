/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// note: the first time you flash a board you must set the side in the EEPROM
// see 4x6/keymaps/gagregrog/README.md for more info
#define EE_HANDS

/* Use I2C or Serial, not both */
#define USE_SERIAL
#undef USE_I2C

#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS \
    { B5, B4, E6, D7, C6, D4 }

#undef RGBLIGHT_LED_COUNT
#define RGBLIGHT_LED_COUNT 14

// Synchronization of the RGB light modes between the two controllers
#define RGBLIGHT_SPLIT
#define RGBLED_SPLIT \
    { 7, 7 }

#define RGBLIGHT_LIMIT_VAL 200 /* The maximum brightness level */
#define RGBLIGHT_SLEEP         /* RGB lighting will be switched off when the host goes to sleep */
#define RGBLIGHT_DEFAULT_VAL 175

#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST

#define NO_ACTION_ONESHOT

#define TAPPING_TOGGLE 2
// Home Row Mod settings
#define TAPPING_TERM 175

// permissive hold - pressing a mod-tap key and pressing/releasing a second key before the mod-tap key is released registers the mod-tap immediately, even if before the tapping term has been reached
#define PERMISSIVE_HOLD

// disable features to try and shrink the firmware size
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_ACTION_ONESHOT
#define LAYER_STATE_8BIT
#undef POINTING_DEVICE_AUTO_MOUSE_ENABLE
