#pragma once
#include QMK_KEYBOARD_H

/**
 * Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for CAGS (Ctl, Alt, Gui, Shift)
 * home row mods.  The layout passed in parameter must contain at least 20 keycodes.
 * Applies HRMs to the second row of the 10-key rows provided
 */

// clang-format off

#define _HOME_ROW_MOD_CAGS_5(                                                                                                                          \
  L00,          L01,          L02,          L03,          L04,               R05,          R06,          R07,          R08,          R09,            \
  L10,          L11,          L12,          L13,          L14,               R15,          R16,          R17,          R18,          R19,            \
...)                                                                                                                                                 \
  L00,          L01,          L02,          L03,          L04,               R05,          R06,          R07,          R08,          R09,            \
  LCTL_T(L10),  LALT_T(L11),  LGUI_T(L12),  LSFT_T(L13),  L14,               R15,          RSFT_T(R16),  RGUI_T(R17),  LALT_T(R18),  RCTL_T(R19),    \
__VA_ARGS__

#define HOME_ROW_MOD_CAGS_5(...) _HOME_ROW_MOD_CAGS_5(__VA_ARGS__)
