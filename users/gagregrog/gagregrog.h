#pragma once
#include QMK_KEYBOARD_H
#include "keymaps/keymap.h"
#include "utils/keycode_utils.h"

#if defined(OLED_ENABLE)
#    include "oled/oled_util.h"
#endif // OLED_ENABLE

#if defined(DEBUG_RGB_MATRIX)
#    include "led/led_util.h"
#endif // DEBUG_RGB_MATRIX

#if defined(MOUSE_TURBO_CLICK)
#    include "mouse_turbo_click/mouse_turbo_click.h"
#endif // MOUSE_TURBO_CLICK

#if defined(DEFAULT_TAP_DANCES_ENABLE)
#    include "tap_dance/default/default_tap_dances.h"
#endif // DEFAULT_TAP_DANCES_ENABLE

#if defined(TAP_DANCE_ENABLE)
#    include "tap_dance/tap_dance_utils.h"
#endif // TAP_DANCE_ENABLE

#if defined(COMBO_ENABLE)
#    include "combos/combos.h"
#endif // COMBO_ENABLE

#ifdef KEY_OVERRIDE_ENABLE
#    include "overrides/overrides.h"
#endif // KEY_OVERRIDE_ENABLE

#if defined(POINTING_DEVICE_ENABLE)
report_mouse_t pointing_device_task_keymap(report_mouse_t mouse_report);
#endif // POINTING_DEVICE_ENABLE

#if defined(INCLUDE_SECRETS) && !defined(NO_SECRETS)
// define this so it can be used in tapdances
void send_secret(uint16_t keycode);
#endif // INCLUDE_SECRETS && !NO_SECRETS

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif // CONSOLE_ENABLE
