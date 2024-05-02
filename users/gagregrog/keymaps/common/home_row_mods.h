#pragma once
#include QMK_KEYBOARD_H

// clang-format off

/**
 * Take 4 keys and wrap them in the CAGS HRM Left
*/
#define HOME_ROW_MOD_CAGS_LEFT(HRM_L0, HRM_L1, HRM_L2, HRM_L3) LCTL_T(HRM_L0), LALT_T(HRM_L1), LGUI_T(HRM_L2), LSFT_T(HRM_L3)

/**
 * Take 4 keys and wrap them in the CAGS HRM Right
*/
#define HOME_ROW_MOD_CAGS_RIGHT(HRM_R0, HRM_R1, HRM_R2, HRM_R3) RSFT_T(HRM_R0), RGUI_T(HRM_R1), LALT_T(HRM_R2), RCTL_T(HRM_R3)

// just shift on the top
#define HOME_ROW_MOD_CAGS_LEFT_TOP(HRM_L0, HRM_L1, HRM_L2, HRM_L3) HRM_L0, HRM_L1, HRM_L2, LSFT_T(HRM_L3)
// full hrm on the bottom
#define HOME_ROW_MOD_CAGS_LEFT_BOT(HRM_L0, HRM_L1, HRM_L2, HRM_L3) LCTL_T(HRM_L0), LALT_T(HRM_L1), LGUI_T(HRM_L2), LSFT_T(HRM_L3)

// just shift on the top
#define HOME_ROW_MOD_CAGS_RIGHT_TOP(HRM_R0, HRM_R1, HRM_R2, HRM_R3) RSFT_T(HRM_R0), HRM_R1, HRM_R2, HRM_R3
// full hrm on the bottom
#define HOME_ROW_MOD_CAGS_RIGHT_BOT(HRM_R0, HRM_R1, HRM_R2, HRM_R3) RSFT_T(HRM_R0), RGUI_T(HRM_R1), LALT_T(HRM_R2), RCTL_T(HRM_R3)

/**
 * Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for CAGS (Ctl, Alt, Gui, Shift)
 * home row mods.  The layout passed in parameter must contain at least 20 keycodes.
 * Applies HRMs to the second row of the 10-key rows provided
 */
//   HOME_ROW_MOD_CAGS_LEFT(L10, L11, L12, L13), L14,      R15, HOME_ROW_MOD_CAGS_RIGHT(R16, R17, R18, R19),
#define _HOME_ROW_MOD_CAGS_5(                                                                                 \
  L00, L01, L02, L03, L04,                              R05, R06, R07, R08, R09,                              \
  L10, L11, L12, L13, L14,                              R15, R16, R17, R18, R19,                              \
  L20, L21, L22, L23, L24,                              R25, R26, R27, R28, R29,                              \
...)                                                                                                          \
  L00, L01, L02, L03, L04,                              R05, R06, R07, R08, R09,                              \
  HOME_ROW_MOD_CAGS_LEFT_TOP(L10, L11, L12, L13), L14,  R15, HOME_ROW_MOD_CAGS_RIGHT_TOP(R16, R17, R18, R19), \
  HOME_ROW_MOD_CAGS_LEFT_BOT(L20, L21, L22, L23), L24,  R25, HOME_ROW_MOD_CAGS_RIGHT_BOT(R26, R27, R28, R29), \
__VA_ARGS__

#define HOME_ROW_MOD_CAGS_5(...) _HOME_ROW_MOD_CAGS_5(__VA_ARGS__)

/**
 * Add Home Row mod to a layout.
 *
 * Expects a 12-key per row layout.  Adds support for CAGS (Ctl, Alt, Gui, Shift)
 * home row mods.  The layout passed in parameter must contain at least 24 keycodes.
 * Applies HRMs to the second row of the 12-key rows provided
 */
#define _HOME_ROW_MOD_CAGS_6(                                                                                       \
  L00, L01, L02, L03, L04, L05,                             R06, R07, R08, R09, R10, R11,                           \
  L12, L13, L14, L15, L16, L17,                             R18, R19, R20, R21, R22, R23,                           \
...)                                                                                                                \
  L00, L01, L02, L03, L04, L05,                             R06, R07, R08, R09, R10, R11,                           \
  L12, HOME_ROW_MOD_CAGS_LEFT(L13, L14, L15, L16), L17,     R18, HOME_ROW_MOD_CAGS_RIGHT(R19, R20, R21, R22), R23,  \
__VA_ARGS__

#define HOME_ROW_MOD_CAGS_6(...) _HOME_ROW_MOD_CAGS_6(__VA_ARGS__)
