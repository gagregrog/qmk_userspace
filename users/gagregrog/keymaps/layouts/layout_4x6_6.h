#pragma once
#include QMK_KEYBOARD_H
#include "./layout_core.h"

// clang-format off

#define LAYOUT_wrapper(...) LAYOUT_split_4x6_6(__VA_ARGS__)
#define LAYOUT_HRM_wrapper(...) LAYOUT_wrapper(HOME_ROW_MOD_CAGS_6(__VA_ARGS__))

/**
 * Wrap a 3x5 core layout to add an outside column to the left and right, making it 3x6
*/
#define _WRAP_3x5_CORE_ADD_COLUMN_OUTSIDE(                                                                             \
    L00,                                                                                                               \
    L12,                                                                                                               \
    L24,                                                                                                               \
             CL00,    CL01,    CL02,    CL03,    CL04,          CR05,    CR06,    CR07,    CR08,    CR09,              \
             CL10,    CL11,    CL12,    CL13,    CL14,          CR15,    CR16,    CR17,    CR18,    CR19,              \
             CL20,    CL21,    CL22,    CL23,    CL24,          CR25,    CR26,    CR27,    CR28,    CR29,              \
                                                                                                                 R11,  \
                                                                                                                 R23,  \
                                                                                                                 R35   \
)                                                                                                                      \
    L00,     CL00,    CL01,    CL02,    CL03,    CL04,          CR05,    CR06,    CR07,    CR08,    CR09,        R11,  \
    L12,     CL10,    CL11,    CL12,    CL13,    CL14,          CR15,    CR16,    CR17,    CR18,    CR19,        R23,  \
    L24,     CL20,    CL21,    CL22,    CL23,    CL24,          CR25,    CR26,    CR27,    CR28,    CR29,        R35

#define WRAP_3x5_CORE_ADD_COLUMN_OUTSIDE(...) _WRAP_3x5_CORE_ADD_COLUMN_OUTSIDE(__VA_ARGS__)

/**
 * Wrap a 3x6 layout with the base + 2+6 thumb keys
*/
#define _ADD_BASE_THUMBS_3x6(                                                                                            \
    L00,     L01,     L02,     L03,     L04,     L05,               R06,     R07,     R08,     R09,     R10,     R11,    \
    L12,     L13,     L14,     L15,     L16,     L17,               R18,     R19,     R20,     R21,     R22,     R23,    \
    L24,     L25,     L26,     L27,     L28,     L29,               R30,     R31,     R32,     R33,     R34,     R35     \
)                                                                                                                        \
    L00,     L01,     L02,     L03,     L04,     L05,               R06,     R07,     R08,     R09,     R10,     R11,    \
    L12,     L13,     L14,     L15,     L16,     L17,               R18,     R19,     R20,     R21,     R22,     R23,    \
    L24,     L25,     L26,     L27,     L28,     L29,               R30,     R31,     R32,     R33,     R34,     R35,    \
                      KC_LBRC, KC_RBRC,                                               KC_LCBR, KC_RCBR,                  \
                                        KC_BTN1, KC_SPC,            TRACKPT, KC_ENT,                                     \
                                        KC_GRV,  NUM_GRV,           UTIL_MN, KC_MINS,                                    \
                                        MS_SCL_P,MS_SCL_L,          KC_TRNS, KC_TRNS

#define ADD_BASE_THUMBS_3x6(...) _ADD_BASE_THUMBS_3x6(__VA_ARGS__)

#define LEFT_COLUMN_BASE       KC_TAB, CMD_ESC, SC_LSPO
#define RIGHT_COLUMN_BASE      SCRN_C, KC_SCLN, SC_RSPC

#define LAYOUT_COLEMAK_DH                                                                                                \
    ADD_BASE_THUMBS_3x6(                                                                                                 \
        WRAP_3x5_CORE_ADD_COLUMN_OUTSIDE(                                                                                \
            LEFT_COLUMN_BASE, LAYOUT_CORE_COLEMAK_DH, RIGHT_COLUMN_BASE                                                  \
        )                                                                                                                \
    )

#define LAYOUT_QWERTY                                                                                                    \
    ADD_BASE_THUMBS_3x6(                                                                                                 \
        WRAP_3x5_CORE_ADD_COLUMN_OUTSIDE(                                                                                \
            LEFT_COLUMN_BASE, LAYOUT_CORE_QWERTY, RIGHT_COLUMN_BASE                                                      \
        )                                                                                                                \
    )

#define LEFT_COLUMN_NUMERIC  RGB_VAD, RGB_VAI, RGB_MOD
#define RIGHT_COLUMN_NUMERIC KC_PAST, KC_PPLS, KC_PIPE

#define LAYOUT_NUMERIC                                                                                                   \
    WRAP_3x5_CORE_ADD_COLUMN_OUTSIDE(                                                                                    \
        LEFT_COLUMN_NUMERIC, LAYOUT_CORE_NUMERIC, RIGHT_COLUMN_NUMERIC                                                   \
    ),                                                                                                                   \
    KC_TRNS,KC_TRNS,                                            KC_0, KC_PDOT,                                           \
                    KC_TRNS, KC_TRNS,           TRACKPT, KC_EQL,                                                         \
                    KC_TRNS, KC_TRNS,           SETS_PLS,KC_MINS,                                                        \
                    KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS                                                         \


#define LEFT_COLUMN_UTILITY  KC_TRNS, KC_TRNS, KC_TRNS
#define RIGHT_COLUMN_UTILITY KC_TRNS, KC_TRNS, KC_TRNS
#define LAYOUT_UTILITY                                                                                                   \
    WRAP_3x5_CORE_ADD_COLUMN_OUTSIDE(                                                                                    \
        LEFT_COLUMN_UTILITY, LAYOUT_CORE_UTILITY, RIGHT_COLUMN_UTILITY                                                   \
    ),                                                                                                                   \
    KC_TRNS,KC_TRNS,                                            KC_TRNS,KC_TRNS,                                         \
                    KC_TRNS, KC_TRNS,           TRACKPT, KC_TRNS,                                                        \
                    KC_TRNS, MO_SETS,           KC_TRNS, KC_TRNS,                                                        \
                    KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS                                                         \


#define LEFT_COLUMN_SETTINGS  KC_TRNS, KC_TRNS, KC_TRNS
#define RIGHT_COLUMN_SETTINGS KC_TRNS, KC_TRNS, KC_TRNS
#define LAYOUT_SETTINGS                                                                                                  \
    WRAP_3x5_CORE_ADD_COLUMN_OUTSIDE(                                                                                    \
        LEFT_COLUMN_SETTINGS, LAYOUT_CORE_SETTINGS, RIGHT_COLUMN_SETTINGS                                                \
    ),                                                                                                                   \
    KC_TRNS,KC_TRNS,                                            KC_TRNS,KC_TRNS,                                         \
                    KC_TRNS, KC_TRNS,           TRACKPT, KC_TRNS,                                                        \
                    KC_TRNS, KC_TRNS,           KC_TRNS, MO_SETS,                                                        \
                    KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS                                                         \


#define LEFT_COLUMN_AUTOMOUSE  KC_TRNS, KC_TRNS, KC_TRNS
#define RIGHT_COLUMN_AUTOMOUSE KC_TRNS, KC_TRNS, KC_TRNS
#define LAYOUT_AUTOMOUSE                                                                                                 \
    WRAP_3x5_CORE_ADD_COLUMN_OUTSIDE(                                                                                    \
        LEFT_COLUMN_AUTOMOUSE, LAYOUT_CORE_TRNS, RIGHT_COLUMN_AUTOMOUSE                                                  \
    ),                                                                                                                   \
    KC_TRNS,KC_TRNS,                                            KC_TRNS,KC_TRNS,                                         \
                    KC_BTN1, KC_BTN2,           TRACKPT, KC_TRNS,                                                        \
                    KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS,                                                        \
                    KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS
