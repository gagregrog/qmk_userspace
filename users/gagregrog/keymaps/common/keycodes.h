#pragma once
#include QMK_KEYBOARD_H

#ifdef UNICODE_COMMON
#    include "unicode.h"
#endif

enum gagregrog_keycodes {
#if defined(DILEMMA_SAFE_RANGE)
    BASE_TOGGLE = DILEMMA_SAFE_RANGE,
#elif defined(CHARYBDIS_SAFE_RANGE)
    BASE_TOGGLE = CHARYBDIS_SAFE_RANGE
#else
    BASE_TOGGLE = SAFE_RANGE,
#endif // SAFE_RANGE
    HRM_TOGGLE,
#if defined(MOUSE_TURBO_CLICK)
    MS_TURBO,
#endif // MOUSE_TURBO_CLICK
#if defined(TRACKPOINT_ENABLE)
    MOUSE_SCROLL_PRESS,
    MOUSE_SCROLL_LOCK,
    MOUSE_TOGGLE,
#endif // TRACKPOINT_ENABLE
#if defined(INCLUDE_SECRETS) && !defined(NO_SECRETS)
    KC_SECRET_1,
    KC_SECRET_2,
    KC_SECRET_3,
    KC_SECRET_4,
    KC_SECRET_5,
#endif // INCLUDE_SECRETS && !defined(NO_SECRETS)
#if defined(POINTING_DEVICE_ENABLE)
    AM_TOGGLE,
    AM_KILL,
#endif // POINTING_DEVICE_ENABLE
    // START keys that require special processing in process_record_user()
    KC_HRM_MAC_LOCK,
    KC_HRM_MV_R,
    KC_HRM_MV_C,
    KC_HRM_MV_L,
    KC_HRM_MV_DL,
    KC_HRM_MV_D,
    KC_HRM_MV_DR,
    PR_LPRN,
    PR_RPRN,
    PR_LCBR,
    PR_RCBR,
    // END keys that require special processing in process_record_user()
    NEW_SAFE_RANGE,
};

#if defined(POINTING_DEVICE_ENABLE)
#    define AM_TG_SF AM_TOGGLE
#else
#    define AM_TG_SF KC_NO
#endif

// useful special keys
#define CMD_ESC LGUI_T(KC_ESC)
#define SCRN_C LCTL(SGUI(KC_4))
#define SCRN_S SGUI(KC_4)
#define KC_OS_LOCK LCTL(LGUI(KC_Q))

// windowing shortcuts
#define KC_MV_UL LCAG(KC_F17)
#define KC_MV_U LCAG(KC_UP)
#define KC_MV_UR LCAG(KC_F15)
#define KC_MV_R LCAG(KC_RIGHT)
#define KC_MV_C LCAG(KC_ENT)
#define KC_MV_L LCAG(KC_LEFT)
#define KC_MV_DL LCAG(KC_F18)
#define KC_MV_D LCAG(KC_DOWN)
#define KC_MV_DR LCAG(KC_F16)

// lock mac screen
#define KC_MAC_LOCK LGUI(LCTL(KC_Q))
#define HR_MACL KC_HRM_MAC_LOCK

// hrm windowing shortcuts
// these are needed when a HRM key overlaps with a window shortcut
#define HR_MV_R KC_HRM_MV_R
#define HR_MV_C KC_HRM_MV_C
#define HR_MV_L KC_HRM_MV_L
#define HR_MV_DL KC_HRM_MV_DL
#define HR_MV_D KC_HRM_MV_D
#define HR_MV_DR KC_HRM_MV_DR

#if defined(TRACKPOINT_ENABLE)
#    define TRACKPT KC_NO
#    define MS_SCL_P MOUSE_SCROLL_PRESS
#    define MS_SCL_L MOUSE_SCROLL_LOCK
#    define MS_TGGL MOUSE_TOGGLE
#endif // TRACKPOINT_ENABLE

#define TG_BASE BASE_TOGGLE
#define TG_HRM HRM_TOGGLE

// layer switches
#define NUM_GRV LT(_LAYER_NUM, KC_GRV)
#define UTIL_MN LT(_LAYER_UTIL, KC_MINS)
#define MO_SETS MO(_LAYER_SETTINGS)
#define SETS_PLS LT(_LAYER_SETTINGS, KC_PLUS)
#define SETS_EQL LT(_LAYER_SETTINGS, KC_EQL)

// TODO: implement useful tap dances
#if defined(DEFAULT_TAP_DANCES_ENABLE)
#    define MO_SPC TD_MO_SPC
#    define MO_BSPC TD_MO_BSPC
#else
#    define MO_SPC KC_SPC
#    define MO_BSPC KC_BSPC
#endif
