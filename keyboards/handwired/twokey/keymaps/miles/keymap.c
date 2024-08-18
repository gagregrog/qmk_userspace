#include QMK_KEYBOARD_H
#include "gagregrog.h"
#include "keymap.h"
#include "tap_dances/tap_dances.h"

const uint32_t PROGMEM unicode_map[] = {
    [CAT] =           0x1F63C, // 😼
    [FIRE] =          0x1F525, // 🔥
    [MIDDLE_FINGER] = 0x1F595, // 🖕
    [PREGNANT_MAN] =  0x1FAC3, // 🫃
    [SHOUT] =         0x1F5E3, // 🗣️
    [SKULL] =         0x1F480, // 💀
    [SUNGLASSES] =    0x1F60E, // 😎
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L1] = LAYOUT_1x2(TD_L1_K1, TD_L1_K2),
    [L2] = LAYOUT_1x2(TD_L2_K1, TD_L2_K2),
};

