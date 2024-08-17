#include QMK_KEYBOARD_H
#include "gagregrog.h"
#include "keymap.h"
#include "tap_dances/tap_dances.h"

const uint32_t PROGMEM unicode_map[] = {
    [BANG]  = 0x203D,  // ‽
    [IRONY] = 0x2E2E,  // ⸮
    [SNEK]  = 0x1F40D, // 🐍
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L1] = LAYOUT_1x2(TD_L1_K1, TD_L1_K2),
    [L2] = LAYOUT_1x2(KC_NO, TD_L2_K2),
};
