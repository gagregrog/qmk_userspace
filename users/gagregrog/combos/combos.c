#include "combos.h"

// combos for each hrm key for a colemak mod dh layout
// activated when like mods are pressed concurrently
const uint16_t PROGMEM hr_ctrl_combo[] = {LCTL_T(KC_A), RCTL_T(KC_O), COMBO_END};
// Note: HRM on right hand sends LALT instead of RALT
const uint16_t PROGMEM hr_alt_combo[] = {LALT_T(KC_R), LALT_T(KC_I), COMBO_END};
const uint16_t PROGMEM hr_gui_combo[] = {LGUI_T(KC_S), RGUI_T(KC_E), COMBO_END};
const uint16_t PROGMEM hr_shift_combo[] = {LSFT_T(KC_T), RSFT_T(KC_N), COMBO_END};

combo_t key_combos[] = {
    [COMBO_HRM_CTL] = COMBO_ACTION(hr_ctrl_combo),
    [COMBO_HRM_ALT] = COMBO_ACTION(hr_alt_combo),
    [COMBO_HRM_GUI] = COMBO_ACTION(hr_gui_combo),
    [COMBO_HRM_SFT] = COMBO_ACTION(hr_shift_combo),
};

