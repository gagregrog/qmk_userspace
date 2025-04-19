#include QMK_KEYBOARD_H
#include "gagregrog.h"
#include "overrides.h"

/* no longer using overrides for brackets, but keeping this here as an example */
/**/
/* bool flush_modifiers(bool key_down, void* context) */
/* { */
/*     send_keyboard_report(); */
/*     return true; */
/* } */
/* const key_override_t lbrc_key_override = { */
/*     .trigger_mods    = MOD_MASK_SHIFT, */
/*     .trigger         = KC_LBRC, */
/*     .replacement     = KC_RBRC, */
/*     .layers          = ~0, */
/*     // We need to suppress shift from the output to ensure we get ] and not } */
/*     .suppressed_mods = MOD_MASK_SHIFT, */
/*     // For some reason the shift is not cleared if Karabiner is running, */
/*     // so we must manually flush the modifiers first to ensure that they */
/*     // are cleared by the time that our replacement is sent */
/*     .custom_action   = flush_modifiers, */
/*     .options         = ko_options_default, */
/*     .enabled         = NULL */
/* }; */

const key_override_t spc_gui_key_override = ko_make_basic(MOD_BIT_RGUI, KC_SPC, LGUI(KC_BSPC));
const key_override_t spc_alt_key_override = ko_make_basic(MOD_MASK_ALT, KC_SPC, LALT(KC_BSPC));
const key_override_t vol_up_shift_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_VOLU, KC_MPLY);
const key_override_t vol_down_shift_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_VOLD, KC_MUTE);

// we must define an extern'd version of this in overrides.h
// https://github.com/qmk/qmk_firmware/issues/24457
// https://github.com/Diaoul/keyboards/commit/38cec299d8e53b10ffe2ff2091f924b2032e23bc

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
    [SPC_GUI_OVERRIDE]        = &spc_gui_key_override,
    [SPC_ALT_OVERRIDE]        = &spc_alt_key_override,
    [VOL_UP_SHIFT_OVERRIDE]   = &vol_up_shift_key_override,
    [VOL_DOWN_SHIFT_OVERRIDE] = &vol_down_shift_key_override
};
