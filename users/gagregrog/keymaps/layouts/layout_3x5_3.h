#pragma once
#include QMK_KEYBOARD_H

// clang-format off

#define LAYOUT_wrapper(...) LAYOUT_split_3x5_3_h(__VA_ARGS__)
#define LAYOUT_HRM_wrapper(...) LAYOUT_wrapper(HOME_ROW_MOD_CAGS_5(__VA_ARGS__))

#define THUMB_TRNS          KC_TRANS,  KC_TRANS,  KC_TRANS
#define BASE_THUMB_L        XXXXXXX, KC_SPC,  NUM_GRV
#define BASE_THUMB_R        UTIL_MN, KC_BSPC, KC_ENT

/**
 * Wrap a 3x5 core layout with the base _3 thumb keys
*/
#define _ADD_THREE_THUMB_BASE( \
    L00,     L01,     L02,     L03,     L04,               R05,     R06,     R07,     R08,     R09, \
    L10,     L11,     L12,     L13,     L14,               R15,     R16,     R17,     R18,     R19, \
    L20,     L21,     L22,     L23,     L24,               R25,     R26,     R27,     R28,     R29  \
) \
    L00,     L01,     L02,     L03,     L04,               R05,     R06,     R07,     R08,     R09, \
    L10,     L11,     L12,     L13,     L14,               R15,     R16,     R17,     R18,     R19, \
    L20,     L21,     L22,     L23,     L24,               R25,     R26,     R27,     R28,     R29, \
                               BASE_THUMB_L,               BASE_THUMB_R

#define ADD_THREE_THUMB_BASE(...) _ADD_THREE_THUMB_BASE(__VA_ARGS__)

#define LAYOUT_COLEMAK_DH ADD_THREE_THUMB_BASE(LAYOUT_CORE_COLEMAK_DH)
#define LAYOUT_QWERTY ADD_THREE_THUMB_BASE(LAYOUT_CORE_QWERTY)

#define NUMERIC_THUMB_L     KC_NO, KC_NO, _______
#define NUMERIC_THUMB_R     KC_EQL, KC_0, KC_PDOT
#define LAYOUT_NUMERIC                                                                              \
                        LAYOUT_CORE_NUMERIC,                                                        \
                NUMERIC_THUMB_L,    NUMERIC_THUMB_R

#define UTILITY_THUMB_L     XXXXXXX, XXXXXXX, MO_SETS
#define UTILITY_THUMB_R     _______, XXXXXXX, XXXXXXX
#define LAYOUT_UTILITY                                                                              \
                        LAYOUT_CORE_UTILITY,                                                        \
                UTILITY_THUMB_L,     UTILITY_THUMB_R

#define SETTINGS_THUMB_L    XXXXXXX, XXXXXXX, _______
#define SETTINGS_THUMB_R    _______, XXXXXXX, XXXXXXX
#define LAYOUT_SETTINGS                                                                             \
                        LAYOUT_CORE_SETTINGS,                                                       \
                SETTINGS_THUMB_L,    SETTINGS_THUMB_R

#ifdef POINTING_DEVICE_ENABLE
#   define MOUSE_THUMB_L       AM_KILL,   KC_BTN1,   KC_BTN2
#   define MOUSE_THUMB_R       KC_BTN2,   KC_BTN1,   AM_KILL
#else
#   define MOUSE_THUMB_L       THUMB_TRNS
#   define MOUSE_THUMB_R       THUMB_TRNS
#endif // POINTING_DEVICE_ENABLE
#define LAYOUT_AUTOMOUSE                                                                            \
                        LAYOUT_CORE_TRNS,                                                           \
                MOUSE_THUMB_L,       MOUSE_THUMB_R
