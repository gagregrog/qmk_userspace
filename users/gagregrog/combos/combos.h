#pragma once

#include QMK_KEYBOARD_H
#include "process_combo.h"

enum combos {
    COMBO_HRM_CTL,
    COMBO_HRM_ALT,
    COMBO_HRM_GUI,
    COMBO_HRM_SFT,
    COMBO_COUNT,
};

extern combo_t key_combos[COMBO_COUNT];
