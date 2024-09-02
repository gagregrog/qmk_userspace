#pragma once
#include QMK_KEYBOARD_H
#include "common/keycodes.h"
#include "common/home_row_mods.h"
#include "common/layers.h"

#if defined(LAYOUT_split_3x5_3_h)
#    include "layouts/layout_3x5_3.h"
#elif defined(LAYOUT_split_4x6_6)
#    include "layouts/layout_4x6_6.h"
#endif

// clang-format off
#define USE_GAGREGROG_KEYMAP                                     \
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {   \
  [_LAYER_COLEMAK_DH_HRM] = LAYOUT_HRM_wrapper(                  \
    LAYOUT_COLEMAK_DH                                            \
  ),                                                             \
  [_LAYER_COLEMAK_DH] = LAYOUT_wrapper(                          \
    LAYOUT_COLEMAK_DH                                            \
  ),                                                             \
  [_LAYER_QWERTY_HRM] = LAYOUT_HRM_wrapper(                      \
    LAYOUT_QWERTY                                                \
  ),                                                             \
  [_LAYER_QWERTY] = LAYOUT_wrapper(                              \
    LAYOUT_QWERTY                                                \
  ),                                                             \
  [_LAYER_NUM] = LAYOUT_HRM_wrapper(                             \
    LAYOUT_NUMERIC                                               \
  ),                                                             \
  [_LAYER_UTIL] = LAYOUT_HRM_wrapper(                            \
    LAYOUT_UTILITY                                               \
  ),                                                             \
  [_LAYER_SETTINGS] = LAYOUT_wrapper(                        \
    LAYOUT_SETTINGS                                              \
  ),                                                             \
  [_LAYER_AUTOMOUSE] = LAYOUT_wrapper(                           \
    LAYOUT_AUTOMOUSE                                             \
  ),                                                             \
};
