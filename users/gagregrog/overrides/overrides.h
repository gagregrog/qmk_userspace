#pragma once

#include QMK_KEYBOARD_H
#include "process_key_override.h"

// must maintain this enum and extern the overrides for introspection to work
// https://github.com/qmk/qmk_firmware/issues/24457
// https://github.com/Diaoul/keyboards/commit/38cec299d8e53b10ffe2ff2091f924b2032e23bc
enum {
    LCBR_OVERRIDE,
    LBRC_OVERRIDE,
    LPRN_OVERRIDE,
    SPC_GUI_OVERRIDE,
    SPC_ALT_OVERRIDE,
    SPC_SHIFT_OVERRIDE,
    VOL_UP_SHIFT_OVERRIDE,
    VOL_DOWN_SHIFT_OVERRIDE,
    KEY_OVERRIDE_COUNT, // must keep this final member for key override introspection to work
};

extern const key_override_t *key_overrides[KEY_OVERRIDE_COUNT];
