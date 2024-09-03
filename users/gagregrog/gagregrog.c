#include QMK_KEYBOARD_H
#include "gagregrog.h"

#ifdef POINTING_DEVICE_ENABLE
__attribute__((weak)) report_mouse_t pointing_device_task_keymap(report_mouse_t mouse_report) {
    return mouse_report;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (mouse_report.x | mouse_report.y | mouse_report.h | mouse_report.v) {
#    ifdef POINTING_DEVICE_INVERT_SCROLL
        mouse_report.h *= -1;
        mouse_report.v *= -1;
#    endif

#    if defined(KB_DILEMMA) || defined(KB_CHARYBDIS)
#        if defined(KB_DILEMMA)
        uint8_t mods                     = get_mods();
        bool    is_snipe_modifier_active = mods & MOD_MASK_CTRL;
        // activate drag scroll on dilemma if any of these mods are active
        bool is_drag_modifier_active = mods & (MOD_MASK_GUI | MOD_MASK_SHIFT | MOD_MASK_ALT);
        bool drag_scroll_enabled     = dilemma_get_pointer_dragscroll_enabled();

        if (!drag_scroll_enabled && is_drag_modifier_active) {
            dilemma_set_pointer_dragscroll_enabled(true);
        } else if (drag_scroll_enabled && !is_drag_modifier_active) {
            dilemma_set_pointer_dragscroll_enabled(false);
        }

        bool is_sniping_enabled = dilemma_get_pointer_sniping_enabled();
        if (!is_sniping_enabled && is_snipe_modifier_active) {
            dilemma_set_pointer_sniping_enabled(true);
        } else if (is_sniping_enabled && !is_snipe_modifier_active) {
            dilemma_set_pointer_sniping_enabled(false);
        }
#        elif defined(KB_CHARYBDIS)
        // TODO: enable base charybdis functionality
        // bool is_sniping_enabled = charybdis_get_pointer_sniping_enabled();
        // if (!is_sniping_enabled && is_snipe_modifier_active) {
        //   charybdis_set_pointer_sniping_enabled(true);
        // } else if (is_sniping_enabled && !is_snipe_modifier_active) {
        //   charybdis_set_pointer_sniping_enabled(false);
        // }
#        endif
#    endif // defined(KB_DILEMMA) || defined(KB_CHARYBDIS)
    }

    return pointing_device_task_keymap(mouse_report);
}
#endif // POINTING_DEVICE_ENABLE

#ifdef TRACKPOINT_ENABLE
bool    msScrollPress         = false;
bool    msScrollLock          = false;
bool    msEnabled             = true;
uint8_t mouseReportCount      = 0;
uint8_t mouseDebounce         = 3;
bool    hasIgnoredFirstReport = false;

void rotate_mouse_report(report_mouse_t *mouse_report) {
    // https://doubleroot.in/lessons/coordinate-geometry-basics/rotation-of-axes/
    // theta = -pi/4
    const double cos_theta = 0.7071067811865475;
    const double sin_theta = -0.7071067811865475;
    double       x_cos     = cos_theta * mouse_report->x;
    double       y_cos     = cos_theta * mouse_report->y;
    double       x_sin     = sin_theta * mouse_report->x;
    double       y_sin     = sin_theta * mouse_report->y;
    double       x         = x_cos - y_sin;
    double       y         = x_sin + y_cos;
    mouse_report->x        = (mouse_xy_report_t)x;
    mouse_report->y        = (mouse_xy_report_t)y;
}

void ignoreMouseReport(report_mouse_t *mouse_report) {
    mouse_report->x       = 0;
    mouse_report->y       = 0;
    mouse_report->h       = 0;
    mouse_report->v       = 0;
    mouse_report->buttons = 0;
}

void ps2_mouse_moved_user(report_mouse_t *mouse_report) {
    if (!hasIgnoredFirstReport) {
        // first report always does a right click and jumps the cursor,
        // so let's ignore it
        hasIgnoredFirstReport = true;
        ignoreMouseReport(mouse_report);
        return;
    }

    if (!msEnabled) {
        ignoreMouseReport(mouse_report);
        return;
    }

    // process special mouse mode whether pressed or locked
    bool lockActive        = msScrollLock && !msScrollPress;
    bool pressActive       = !msScrollLock && msScrollPress;
    bool mouseScrollActive = (lockActive || pressActive);

    // only handle special mouse modes when enabled by press or lock
    if (!mouseScrollActive) {
        return;
    }

    // debounce mouse mode actions so it is more controllable
    if (mouseReportCount > mouseDebounce) {
        mouseReportCount = 0;
    }

    // only register mouse mode behavior once every mouseDebounce times
    if (!mouseReportCount) {
        // reassign normal mouse movement to scroll movement
        mouse_report->h = mouse_report->x / -3;
        mouse_report->v = mouse_report->y / -3;
    }

    // disable normal mouse movement
    // must happen after reassigning the movement above
    mouse_report->x = 0;
    mouse_report->y = 0;

    // increment counter to limit scroll processing
    mouseReportCount++;
}
#endif // TRACKPOINT_ENABLE

#if defined(INCLUDE_SECRETS) && !defined(NO_SECRETS)

__attribute__((weak)) bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
    return true;
}

#endif // INCLUDE_SECRETS

__attribute__((weak)) void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void) {
#if defined(POINTING_DEVICE_AUTO_MOUSE_ENABLE)
    // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_layer(_LAYER_AUTOMOUSE);
    // always required before the auto mouse feature will work
    set_auto_mouse_enable(true);
#    if defined(POINTING_DEVICE_COMBINED)
    // flash each side so cpi is set for each
    pmw33xx_set_cpi(0, is_keyboard_left() ? SCROLL_CPI : MOUSE_CPI);
#    endif // POINTING_DEVICE_COMBINED
#endif     // POINTING_DEVICE_AUTO_MOUSE_ENABLE

    keyboard_post_init_keymap();
}

// CIRQUE defines its own auto_mouse_activation, so skip if in use
#if defined(POINTING_DEVICE_AUTO_MOUSE_ENABLE) && !CIRQUE_PINNACLE_POSITION_MODE
// require 8 mouse movements in a row to trigger an auto mouse layer
#    define AUTO_MOUSE_BUFFER_TARGET 0b11111111

uint8_t auto_mouse_buffer = 0;
bool    auto_mouse_activation(report_mouse_t mouse_report) {
    bool has_movement = mouse_report.x != 0 || mouse_report.y != 0;
    // shift the LSB to make space for the latest
    auto_mouse_buffer <<= 1;
    // fill the LSB with 1 or 0 if there was any mouse movement
    auto_mouse_buffer |= (uint8_t)has_movement;
    // only keep the 8 LSBS
    auto_mouse_buffer &= AUTO_MOUSE_BUFFER_TARGET;
    // only count it as a move if the buffer is filled
    bool is_mouse_move = auto_mouse_buffer == AUTO_MOUSE_BUFFER_TARGET;

    return is_mouse_move;
}
#endif // POINTING_DEVICE_AUTO_MOUSE_ENABLE

#if defined(POINTING_DEVICE_COMBINED)
report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    static int8_t scroll_debounce_x = 0;
    static int8_t scroll_debounce_y = 0;

    scroll_debounce_x += left_report.x;
    scroll_debounce_y += left_report.y;

    left_report.x = 0;
    left_report.y = 0;

    if (abs(scroll_debounce_x) > 100) {
        left_report.h     = scroll_debounce_x > 0 ? -1 : 1;
        scroll_debounce_x = 0;
    }
    if (abs(scroll_debounce_y) > 100) {
        left_report.v     = scroll_debounce_y > 0 ? -1 : 1;
        scroll_debounce_y = 0;
    }

    // disable horizontal scrolling (require shift)
    left_report.h = 0;
    return pointing_device_combine_reports(left_report, right_report);
}
#endif // POINTING_DEVICE_COMBINED

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true; // Process all other keycodes normally
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_smtd(keycode, record)) {
        return false;
    }
#ifdef MOUSE_TURBO_CLICK
    if (!process_mouse_turbo_click(keycode, record, MS_TURBO)) {
        return false;
    }
#endif // MOUSE_TURBO_CLICK

    switch (keycode) {
#if defined(DEBUG_RGB_MATRIX)
        case RGB_MOD:
        case RGB_TOG:
            debug_rgb_matrix(keycode, record->event.pressed);
            return true;
#endif
// replace with better ifdef
#if defined(LAYOUT_split_3x5_3_h) || defined(LAYOUT_split_4x6_6)
        case BASE_TOGGLE:
            if (record->event.pressed) {
                if (IS_LAYER_ON(_LAYER_QWERTY_HRM)) {
                    layer_off(_LAYER_QWERTY_HRM);
                } else if (IS_LAYER_ON(_LAYER_QWERTY)) {
                    layer_on(_LAYER_COLEMAK_DH);
                    layer_off(_LAYER_QWERTY);
                } else if (IS_LAYER_ON(_LAYER_COLEMAK_DH)) {
                    layer_on(_LAYER_QWERTY);
                    layer_off(_LAYER_COLEMAK_DH);
                } else {
                    layer_on(_LAYER_QWERTY_HRM);
                }
            }
            return false;
        case HRM_TOGGLE:
            if (record->event.pressed) {
                if (IS_LAYER_ON(_LAYER_QWERTY_HRM)) {
                    layer_on(_LAYER_QWERTY);
                    layer_off(_LAYER_QWERTY_HRM);
                } else if (IS_LAYER_ON(_LAYER_QWERTY)) {
                    layer_on(_LAYER_QWERTY_HRM);
                    layer_off(_LAYER_QWERTY);
                } else if (IS_LAYER_ON(_LAYER_COLEMAK_DH)) {
                    layer_off(_LAYER_COLEMAK_DH);
                } else {
                    layer_on(_LAYER_COLEMAK_DH);
                }
            }
            return false;
#endif // LAYOUT_split_3x5_3_h || LAYOUT_split_4x6_6
#ifdef TRACKPOINT_ENABLE
        case MOUSE_SCROLL_PRESS:
            msScrollPress = record->event.pressed;
            return false; // Skip all further processing of this key
        case MOUSE_SCROLL_LOCK:
            if (record->event.pressed) {
                msScrollLock = !msScrollLock;
            }
            return false;
        case MOUSE_TOGGLE:
            if (record->event.pressed) {
                msEnabled = !msEnabled;
            }
            return false;
#endif // TRACKPOINT_ENABLE
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
        case AM_TOGGLE:
            if (record->event.pressed) {
                auto_mouse_layer_off(); // disable target layer if needed
                set_auto_mouse_enable((AUTO_MOUSE_ENABLED) ^ 1);
#    ifdef CONSOLE_ENABLE
                xprintf("Toggling Auto Mouse: %d\n", AUTO_MOUSE_ENABLED);
#    endif
            }
            return false;
        case AM_KILL:
            if (record->event.pressed) {
                auto_mouse_layer_off();
            }
            return false;
        case KC_BTN1:
        case KC_BTN2:
            if (get_mods() & MOD_MASK_SHIFT) {
                // runs on both press and release since otherwise this is treated
                // as a mouse key and reactivates the mouse layer
                auto_mouse_layer_off();
                return false;
            }
            return true;
#endif // POINTING_DEVICE_AUTO_MOUSE_ENABLE
        default:
#if defined(INCLUDE_SECRETS) && !defined(NO_SECRETS)
            return process_record_keymap(keycode, record) && process_record_secrets(keycode, record);
#else
            return process_record_keymap(keycode, record);
#endif
    }
}

#if defined(KEY_OVERRIDE_ENABLE) && defined(USE_BRACKET_OVERRIDE)
const key_override_t lcbr_key_override           = ko_make_basic(MOD_MASK_SHIFT, KC_LCBR, KC_RCBR);
const key_override_t lbrc_key_override           = ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, KC_RBRC);
const key_override_t lprn_key_override           = ko_make_basic(MOD_MASK_SHIFT, KC_LPRN, KC_RPRN);
const key_override_t spc_gui_key_override        = ko_make_basic(MOD_BIT_RGUI, KC_SPC, LGUI(KC_BSPC));
const key_override_t spc_alt_key_override        = ko_make_basic(MOD_MASK_ALT, KC_SPC, LALT(KC_BSPC));
const key_override_t spc_shift_key_override      = ko_make_basic(MOD_MASK_SHIFT, KC_SPC, KC_BSPC);
const key_override_t vol_up_shift_key_override   = ko_make_basic(MOD_MASK_SHIFT, KC_VOLU, KC_MPLY);
const key_override_t vol_down_shift_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_VOLD, KC_MUTE);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &lcbr_key_override,
    &lbrc_key_override,
    &lprn_key_override,
    &spc_gui_key_override,
    &spc_alt_key_override,
    &spc_shift_key_override,
    &vol_up_shift_key_override,
    &vol_down_shift_key_override,
    NULL // Null terminate the array of overrides!
};
#endif

void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    // since we have multiple base layers that we can toggle between
    // and the base layers share some common keys w/ different modifiers
    // we switch on the active base layer to prevent duplicate actions
    if (IS_LAYER_ON(_LAYER_COLEMAK_DH_HRM)) {
        switch (keycode) {
            // Colemak Mod DH
            SM_MT(KC_A, KC_LEFT_CTRL, 1)
            SM_MT(KC_R, KC_LEFT_ALT, 1)
            SM_MT(KC_S, KC_LEFT_GUI, 1)
            SM_MT(KC_T, KC_LSFT, 1)
            SM_MT(KC_N, KC_RSFT, 1)
            SM_MT(KC_E, KC_RIGHT_GUI, 1)
            SM_MT(KC_I, KC_RIGHT_ALT, 1)
            SM_MT(KC_O, KC_RIGHT_CTRL, 1)
        }
    } else if (IS_LAYER_ON(_LAYER_QWERTY_HRM)) {
        switch (keycode) {
            // QWERTY
            SM_MT(KC_A, KC_LEFT_CTRL, 1)
            SM_MT(KC_S, KC_LEFT_ALT, 1)
            SM_MT(KC_D, KC_LEFT_GUI, 1)
            SM_MT(KC_F, KC_LSFT, 1)
            SM_MT(KC_J, KC_RSFT, 1)
            SM_MT(KC_K, KC_RIGHT_GUI, 1)
            SM_MT(KC_L, KC_RIGHT_ALT, 1)
            SM_MT(KC_QUOT, KC_RIGHT_CTRL, 1)
        }
    }
    if (!IS_LAYER_ON(_LAYER_QWERTY_HRM)) {
        // vim maps on settings layer conflict with QWERTY, so only use if QWERTY not active
        switch (keycode) {
            SM_MT(KC_J, KC_RSFT, 1)
            SM_MT(KC_K, KC_RIGHT_GUI, 1)
            SM_MT(KC_L, KC_RIGHT_ALT, 1)
        }
    }
    switch (keycode) {
        // Numeric
        SM_MT(KC_ESC, KC_LEFT_CTRL, 1)
        SM_MT(KC_LEFT, KC_LEFT_ALT, 1)
        SM_MT(KC_DOWN, KC_LEFT_GUI, 1)
        SM_MT(KC_RIGHT, KC_LSFT, 1)
        SM_MT(KC_4, KC_RSFT, 1)
        SM_MT(KC_5, KC_RIGHT_GUI, 1)
        SM_MT(KC_6, KC_RIGHT_ALT, 1)
        SM_MT(KC_SCLN, KC_RIGHT_CTRL, 1)

        // Utility
        SM_MT(KC_MPRV, KC_LEFT_ALT, 1)
        SM_MT(KC_VOLD, KC_LEFT_GUI, 1)
        SM_MT(KC_MNXT, KC_LSFT, 1)
        SMTD_MT(SM_HR_MV_L, KC_MV_L, KC_RSFT)
        SMTD_MT(SM_HR_MV_C, KC_MV_C, KC_RIGHT_GUI)
        SMTD_MT(SM_HR_MV_R, KC_MV_R, KC_RIGHT_ALT)

        // Settings
        SMTD_MT(SM_HR_MACL, KC_MACL, KC_LSFT)

        // dummy modifiers
        SMTD_MT(SM_HR_LCTL, XXXXXXX, KC_LEFT_CTRL)
        SMTD_MT(SM_HR_LALT, XXXXXXX, KC_LEFT_ALT)
        SMTD_MT(SM_HR_LGUI, XXXXXXX, KC_LEFT_GUI)
        SMTD_MT(SM_HR_LSFT, XXXXXXX, KC_LSFT)
        SMTD_MT(SM_HR_RCTL, XXXXXXX, KC_RIGHT_CTRL)
        SMTD_MT(SM_HR_RALT, XXXXXXX, KC_RIGHT_ALT)
        SMTD_MT(SM_HR_RGUI, XXXXXXX, KC_RIGHT_GUI)
        SMTD_MT(SM_HR_RSFT, XXXXXXX, KC_RSFT)
    }
}

uint32_t get_smtd_timeout(uint16_t keycode, smtd_timeout timeout) {
    switch (keycode) {
        case SM_KC_LEFT:
        case SM_KC_DOWN:
        case SM_KC_RIGHT:
            // make tap & press faster for arrow key movements
            if (timeout == SMTD_TIMEOUT_SEQUENCE) {
                return 300;
            }
    }

    return get_smtd_timeout_default(timeout);
}
