#include "gagregrog.h"
#include "tap_dances.h"
#include "keymap.h"

// - All Tap Dances

tap_dance_action_t tap_dance_actions[] = {
  [T_L1_K1]  = ACTION_TAP_DANCE_GAGREGROG(td_handle_L1_K1),
  [T_L1_K2]  = ACTION_TAP_DANCE_GAGREGROG(td_handle_L1_K2),
};

static void commandShiftE(void) {
    register_mods(MOD_LGUI | MOD_LSFT);
    register_code(KC_E);
    unregister_code(KC_E);
    unregister_mods(MOD_LGUI | MOD_LSFT);
};


static void commandSW(void) {
    register_mods(MOD_LGUI);
    tap_code(KC_S);
    wait_ms(500);
    tap_code(KC_W);
    unregister_mods(MOD_LGUI);
};

static void justU(void) {
    tap_code(KC_U);
};

static void justQ(void) {
    tap_code(KC_Q);
};

// L1_K1 (near usb port)
static td_actions_gagregrog_t actions_L1_K1[] = {
  KEY__TD_ACTION_GAGREGROG(KC_BACKSLASH),
  FN__TD_ACTION_GAGREGROG(commandSW),
  NULL__TD_ACTION_GAGREGROG,
  FN__TD_ACTION_GAGREGROG(commandShiftE),
};
void td_handle_L1_K1(TD_ARGS_GAGREGROG) {
  HANDLE_TAP_DANCE_GAGREGROG(actions_L1_K1);
}

// L1_K2
static td_actions_gagregrog_t actions_L1_K2[] = {
  KEY__TD_ACTION_GAGREGROG(KC_P),
  FN__TD_ACTION_GAGREGROG(justU),
  NULL__TD_ACTION_GAGREGROG,
  FN__TD_ACTION_GAGREGROG(justQ),
};
void td_handle_L1_K2(TD_ARGS_GAGREGROG) {
  HANDLE_TAP_DANCE_GAGREGROG(actions_L1_K2);
}
