#pragma once
#include QMK_KEYBOARD_H

#include "../common/keycodes.h"

// clang-format off
#define _________________TRNS_X5___________________       KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS
#define _________________NOPE_X5___________________       XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX

#define ______________COLEMAK_MOD_DH_L1____________       KC_Q,      KC_W,      KC_F,      KC_P,      KC_B
#define ______________COLEMAK_MOD_DH_L2____________       KC_A,      KC_R,      KC_S,      KC_T,      KC_G
#define ______________COLEMAK_MOD_DH_L3____________       KC_Z,      KC_X,      KC_C,      KC_D,      KC_V

#define ______________COLEMAK_MOD_DH_R1____________       KC_J,      KC_L,      KC_U,      KC_Y,      KC_QUOT
#define ______________COLEMAK_MOD_DH_R2____________       KC_M,      KC_N,      KC_E,      KC_I,      KC_O
#define ______________COLEMAK_MOD_DH_R3____________       KC_K,      KC_H,      KC_COMM,   KC_DOT,    KC_SLASH

#define _________________QWERTY_L1_________________       KC_Q,      KC_W,      KC_E,      KC_R,      KC_T
#define _________________QWERTY_L2_________________       KC_A,      KC_S,      KC_D,      KC_F,      KC_G
#define _________________QWERTY_L3_________________       KC_Z,      KC_X,      KC_C,      KC_V,      KC_B

#define _________________QWERTY_R1_________________       KC_Y,      KC_U,      KC_I,      KC_O,      KC_P
#define _________________QWERTY_R2_________________       KC_H,      KC_J,      KC_K,      KC_L,      KC_QUOT
#define _________________QWERTY_R3_________________       KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH

#define _________________NUMERIC_L1________________       KC_TAB,    KC_F1,     KC_UP,     KC_F2,     PR_LPRN
#define _________________NUMERIC_L2________________       KC_ESC,    KC_LEFT,   KC_DOWN,   KC_RIGHT,  PR_LCBR
#define _________________NUMERIC_L3________________       KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_LBRC

#define _________________NUMERIC_R1________________       PR_RPRN,   KC_7,      KC_8,      KC_9,      KC_PIPE
#define _________________NUMERIC_R2________________       PR_RCBR,   KC_4,      KC_5,      KC_6,      KC_SCLN
#define _________________NUMERIC_R3________________       KC_RBRC,   KC_1,      KC_2,      KC_3,      KC_BSLS

#define _________________UTILITY_L1________________       XXXXXXX,   XXXXXXX,   KC_VOLU,   XXXXXXX,   PR_LPRN
#define _________________UTILITY_L2________________       XXXXXXX,   KC_MPRV,   KC_VOLD,   KC_MNXT,   PR_LCBR
#define _________________UTILITY_L3________________       XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_LBRC

#define _________________UTILITY_R1________________       PR_RPRN,   KC_MV_UL,  KC_MV_U,   KC_MV_UR,  XXXXXXX
#define _________________UTILITY_R2________________       PR_RCBR,   HR_MV_L,   HR_MV_C,   HR_MV_R,   XXXXXXX
#define _________________UTILITY_R3________________       KC_RBRC,   KC_MV_DL,  KC_MV_D,   KC_MV_DR,  XXXXXXX

#define _________________SETTINGS_L1_______________       QK_BOOT,   XXXXXXX,   XXXXXXX,   XXXXXXX,   QK_MAKE
#define _________________SETTINGS_L2_______________       XXXXXXX,   XXXXXXX,   XXXXXXX,   HR_MACL,   XXXXXXX
#define _________________SETTINGS_L3_______________       _________________NOPE_X5___________________

#define _________________SETTINGS_R1_______________       TG_HRM,    XXXXXXX,   XXXXXXX,   XXXXXXX,   TG_BASE
#define _________________SETTINGS_R2_______________       KC_H,      KC_J,      KC_K,      KC_L,      XXXXXXX
#if defined(RGB_MATRIX_ENABLE)
#define _________________SETTINGS_R3_______________       RM_TOGG,   RM_NEXT,   XXXXXXX,   XXXXXXX,   AM_TG_SF
#elif defined(RGBLIGHT_ENABLE)
#define _________________SETTINGS_R3_______________       UG_TOGG,   UG_NEXT,   XXXXXXX,   XXXXXXX,   AM_TG_SF
#else
#define _________________SETTINGS_R3_______________       XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   AM_TG_SF
#endif


#define LAYOUT_CORE_COLEMAK_DH                                                                                \
        ______________COLEMAK_MOD_DH_L1____________,         ______________COLEMAK_MOD_DH_R1____________,     \
        ______________COLEMAK_MOD_DH_L2____________,         ______________COLEMAK_MOD_DH_R2____________,     \
        ______________COLEMAK_MOD_DH_L3____________,         ______________COLEMAK_MOD_DH_R3____________

#define LAYOUT_CORE_QWERTY                                                                                    \
        _________________QWERTY_L1_________________,         _________________QWERTY_R1_________________,     \
        _________________QWERTY_L2_________________,         _________________QWERTY_R2_________________,     \
        _________________QWERTY_L3_________________,         _________________QWERTY_R3_________________

#define LAYOUT_CORE_NUMERIC                                                                                   \
        _________________NUMERIC_L1________________,          _________________NUMERIC_R1________________,    \
        _________________NUMERIC_L2________________,          _________________NUMERIC_R2________________,    \
        _________________NUMERIC_L3________________,          _________________NUMERIC_R3________________

#define LAYOUT_CORE_UTILITY                                                                                   \
        _________________UTILITY_L1________________,          _________________UTILITY_R1________________,    \
        _________________UTILITY_L2________________,          _________________UTILITY_R2________________,    \
        _________________UTILITY_L3________________,          _________________UTILITY_R3________________

#define LAYOUT_CORE_SETTINGS                                                                                  \
        _________________SETTINGS_L1_______________,          _________________SETTINGS_R1_______________,    \
        _________________SETTINGS_L2_______________,          _________________SETTINGS_R2_______________,    \
        _________________SETTINGS_L3_______________,          _________________SETTINGS_R3_______________

#define LAYOUT_CORE_TRNS                                                                                      \
        _________________TRNS_X5___________________,          _________________TRNS_X5___________________,    \
        _________________TRNS_X5___________________,          _________________TRNS_X5___________________,    \
        _________________TRNS_X5___________________,          _________________TRNS_X5___________________

